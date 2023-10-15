#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <fstream>
#include <vector>
#include <algorithm>
#include <charconv>
#include <map>

#include "type.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"



namespace PAFL
{
class TestSuite
{
public:
    typedef struct { index_t index; line_t line; float sbfl_sus, sus; line_t ranking; } ranking_info;
    typedef struct { size_t Ncs, Ncf; ranking_info* ptr_ranking; } param;

    typedef struct { std::list<std::pair<index_t, line_t>> lines; bool is_passed; } test_case;
    using test_suite = std::list<test_case>;


    TestSuite() : _is_initialized(false), _fail(0), _highest_sbfl(0.0f) {}
    void addTestCase(const rapidjson::Document& d, bool is_successed);

    template<class Func>
    void setSbflSus(Func func);
    void assignSbfl()
        { for (auto& info : _ranking) info.sus = info.sbfl_sus; }
    const std::list<ranking_info>& rank();


    index_t getIndexFromFile(const std::string& file) const;
    index_t MaxIndex() const
        { return _index2file.size(); }
    const std::string& getFileFromIndex(index_t idx) const
        { return _index2file[idx]; }
    ranking_info* getRankingInfo(index_t idx, line_t line)
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking : nullptr; }
    line_t getRankingSum(const fault_loc& faults) const;

    float getSbflSus(index_t idx, line_t line) const
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->sbfl_sus : 0.0f; }
    float getSus(index_t idx, line_t line) const
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->sus : 0.0f; }
    float getHighestSbflSus() const
        { return _highest_sbfl; }
    const test_suite& getTestSuite() const
        { return _test_suite; }


    void save(const fs::path& path) const;
    void _write(const fs::path& path) const;
    bool _read(const fs::path& path);


    decltype(auto) begin()
        { return _line_param.begin(); }
    decltype(auto) end()
        { return _line_param.end(); }
    decltype(auto) cbegin() const
        { return _line_param.cbegin(); }
    decltype(auto) cend() const
        { return _line_param.cend(); }


private:
    bool _is_initialized;
    size_t _fail;
    size_t _succ;

    std::vector<std::string> _index2file;
    std::unordered_map<std::string, index_t> _file2index;

    std::vector<std::map<line_t, param>> _line_param;
    std::list<ranking_info> _ranking;
    float _highest_sbfl;

    test_suite _test_suite;
};
}






namespace PAFL
{
void TestSuite::addTestCase(const rapidjson::Document& d, bool is_successed)
{
    const auto& json_files = d["files"].GetArray();
    const auto sizeof_files = json_files.Size();
    
    // Reserve containers' capacity
    if (!_is_initialized) {
        
        _file2index.reserve(sizeof_files + 32);
        _index2file.reserve(sizeof_files + 32);
        _line_param.reserve(sizeof_files + 32);
        _is_initialized = true;
    }
    is_successed ? _succ++ : _fail++;


    // Add test case
    auto& tc_lines = _test_suite.emplace_back(test_case{std::list<std::pair<index_t, line_t>>(), is_successed}).lines;
    

    for (rapidjson::SizeType i = 0; i != sizeof_files; ++i) {
        
        const auto& json_file = json_files[i].GetObject();
        const auto& json_lines = json_file["lines"].GetArray();
        std::string key(json_file["file"].GetString());
        
        // "file" is not in filelist --> initialize
        if (!_file2index.contains(key)) {
            
            auto index_now = static_cast<index_t>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _line_param.emplace_back();
            
            for (rapidjson::SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (json_line["count"].GetUint64()) {
                    
                    line_t line_now = json_line["line_number"].GetUint();
                    tc_lines.emplace_back(index_now, line_now);
                    _ranking.push_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });

                    auto val = is_successed ? param{ 1, 0, &*_ranking.rbegin() } : param{ 0, 1, &*_ranking.rbegin() };
                    _line_param[index_now].emplace(line_now, val);
                }
            }
        }
        
        
        // "file" is in filelist
        else
            for (rapidjson::SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (json_line["count"].GetUint64()) {
                    
                    index_t index_now(_file2index[key]);
                    line_t line_now = json_line["line_number"].GetUint();
                    tc_lines.emplace_back(index_now, line_now);

                    // line is not in _line_param
                    if (!_line_param[index_now].contains(line_now)) {
                        
                        auto& ptr = _ranking.emplace_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });
                        auto val = is_successed ? param{ 1, 0, &*_ranking.rbegin() } : param{ 0, 1, &*_ranking.rbegin() };
                        _line_param[index_now].emplace(line_now, val);
                    }

                    // line is in _line_param
                    else {

                        auto& line = _line_param[index_now][line_now];
                        is_successed ? line.Ncs++ : line.Ncf++;
                    }
                }
            }
    }
}

template<class Func>
void TestSuite::setSbflSus(Func func)
{
    for (auto& map : _line_param)
        for (auto& item : map) {

            item.second.ptr_ranking->sus = item.second.ptr_ranking->sbfl_sus
            = func(_succ, _fail, item.second.Ncs, item.second.Ncf);
            if (_highest_sbfl < item.second.ptr_ranking->sbfl_sus)
                _highest_sbfl = item.second.ptr_ranking->sbfl_sus;
        }
}

const std::list<TestSuite::ranking_info>& TestSuite::rank()
{
    // Sort
    _ranking.sort([](const ranking_info& lhs, const ranking_info& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_t ranking;
    line_t virtual_ranking = 1;
    float sus = std::numeric_limits<float>::infinity();

    for (auto& iter : _ranking) {

        if (sus > iter.sus) {

            sus = iter.sus;
            ranking = virtual_ranking;
        }
        iter.ranking = ranking;
        virtual_ranking++;
    }

    return _ranking;
}



index_t TestSuite::getIndexFromFile(const std::string& file) const
{
    if (_file2index.contains(file))
        return _file2index.at(file);
    std::cerr << file + " is out of range";
    throw std::out_of_range(file);
}

line_t TestSuite::getRankingSum(const fault_loc& faults) const
{

    for (auto iter = _ranking.cbegin(); ; iter++)
        if (faults.contains(_index2file[iter->index])) {
            
            auto& line_set = faults.at(_index2file[iter->index]);
            if (line_set.contains(iter->line)) {

                auto ranking = iter->ranking;
                for (; iter != _ranking.cend(); iter++)
                    if (iter->ranking != ranking)
                        break;
                return ranking + ((iter == _ranking.cend()) ? _ranking.size() : iter->ranking - 1);
            }
        }
}






void TestSuite::save(const fs::path& path) const
{
    std::ofstream ofs(path);
    char buf[10];

    // files
    ofs.write("{\n\t\"files\": [\n", 14);
    for (size_t i = 0; i != _index2file.size(); ++i) {

        ofs.write("\t\t\"", 3);
        ofs.write(_index2file[i].c_str(), _index2file[i].size());
        i != _index2file.size() - 1 ? ofs.write("\",\n", 3) : ofs.write("\"\n", 2);
    }      
    ofs.write("\t],\n", 4);

    // total                                                                                                                                                                                                                                                 
    ofs.write("\t\"total\": ", 10);
    auto result_ptr = std::to_chars(buf, buf + 10, _ranking.size()).ptr;
    ofs.write(buf, result_ptr - buf);
    ofs.write(",\n\t\"lines\": [\n", 14);

    // lines
    auto end = _ranking.end();
    end--;
    for (auto iter = _ranking.cbegin(); iter != _ranking.cend(); iter++) {
        
        // index
        ofs.write("\t\t{ \"index\": ", 13);
        auto result_ptr = std::to_chars(buf, buf + 10, iter->index).ptr;
        ofs.write(buf, result_ptr - buf);
        // line
        ofs.write(", \"line\": ", 10);
        result_ptr = std::to_chars(buf, buf + 10, iter->line).ptr;
        ofs.write(buf, result_ptr - buf);
        // sus
        ofs.write(", \"sus\": ", 9);
        ofs << iter->sus;
        // ranking
        ofs.write(", \"ranking\": ", 13);
        result_ptr = std::to_chars(buf, buf + 10, iter->ranking).ptr;
        ofs.write(buf, result_ptr - buf);
        iter != end ? ofs.write(" },\n", 4) : ofs.write("}\n", 2);
    }
    ofs.write("\t]\n}", 4);
    ofs.put(' ');
}



void TestSuite::_write(const fs::path& path) const
{
    // TestSuite
    std::ofstream ofs(path);
    ofs << _is_initialized << '\n' << _fail << '\n' << _index2file.size() << '\n';
    
    for (auto& iter : _index2file) {

        ofs.write(iter.c_str(), iter.size());
        ofs.put('\n');
    }

    for (auto& file : _line_param) {

        ofs << file.size() << '\n';
        for (auto& iter : file)
            ofs << iter.first << '\n' << iter.second.Ncs << '\n' << iter.second.Ncf << '\n';
    }

    // Test suite
    ofs << _test_suite.size() << '\n';
    for (auto& tc : _test_suite) {
        
        ofs << tc.is_passed << '\n' << tc.lines.size() << '\n';
        for (auto& item : tc.lines)
            ofs << item.first << '\n' << item.second << '\n';
    }

}

bool TestSuite::_read(const fs::path& path)
{
    if (!fs::exists(path))
        return false;

    std::ifstream ifs(path);
    index_t index_size = 0;
    ifs >> _is_initialized >> _fail >> index_size;

    _index2file.clear();
    _index2file.reserve(index_size);
    _file2index.clear();
    _file2index.reserve(index_size);
    for (index_t i = 0; i != index_size; i++) {

        std::string buf;
        ifs >> buf;
        _index2file.emplace_back(buf);
        _file2index.emplace(buf, i);
    }

    _ranking.clear();
    _line_param.clear();
    _line_param.reserve(index_size);
    for (index_t idx = 0; idx != index_size; idx++) {
        
        line_t file_size;
        ifs >> file_size;
        _line_param.emplace_back();

        for (line_t j = 0; j != file_size; j++) {

            line_t line;
            size_t Ncs, Ncf;
            ifs >> line >> Ncs >> Ncf;

            auto& ptr = _ranking.emplace_back(ranking_info{ idx, line, 0.0f, 0.0f, 0 });
            _line_param[idx].emplace(line, param{ Ncs, Ncf, &ptr });
        }
    }

    // Test suite
    size_t suite_size = 0;
    ifs >> suite_size;
    _test_suite.clear();
    for (size_t i = 0; i != suite_size; i++) {
        
        bool is_passed;
        size_t tc_size = 0;
        ifs >> is_passed >> tc_size;
        auto& tc_lines = _test_suite.emplace_back(test_case{std::list<std::pair<index_t, line_t>>(), is_passed}).lines;

        for (size_t j = 0; j != tc_size; j++) {

            index_t index = 0;
            line_t line = 0;
            ifs >> index >> line;
            tc_lines.emplace_back(index, line);
        }
    }

    return true;
}
}
#endif
