#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <charconv>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "type.h"

using namespace rapidjson;



namespace PAFL
{
class TestSuite
{
public:
    struct ranking_info { index_t index; line_t line; float ochiai_sus, sus; line_t ranking; };
    struct param { size_t Ncf, Ncs; ranking_info* ptr_ranking; };
    using dict = std::unordered_map<line_t, param>;
    using file2index_t = std::unordered_map<std::string, index_t>;

    struct test_case { std::list<std::pair<index_t, line_t>> lines; bool is_passed; };
    using test_suite = std::list<test_case>;


    TestSuite() : _is_initialized(false), _fail(0), _highest_ochiai(0.0f) {}
    TestSuite(const TestSuite& rhs);
    void AddTestCase(const Document& d, bool is_successed);
    void CalculateSus();
    void SusToOchiai()
        { for (auto& info : _ranking) info.sus = info.ochiai_sus; }
    const std::list<ranking_info>& Rank();
    void Save(std::ofstream& ofs) const;

    index_t GetIndexFromFile(const std::string& file) const
        { return _file2index.contains(file) ? _file2index.at(file) : throw std::out_of_range(file + " is out of range"); }
    index_t MaxIndex() const
        { return _index2file.size(); }
    std::string GetFileFromIndex(index_t idx) const
        { return _index2file[idx]; }
    ranking_info* GetRankingInfo(index_t idx, line_t line)
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking : nullptr; }
    line_t GetRankingSum(index_t idx, const std::list<line_t>& target_lines) const;

    float GetOchiaiSus(index_t idx, line_t line) const
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->ochiai_sus : 0.0f; }
    float GetSus(index_t idx, line_t line) const
        { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->sus : 0.0f; }
    float GetHighestOchiaiSus() const
        { return _highest_ochiai; }
    const test_suite& GetTestSuite() const
        { return _test_suite; }

    void _write(std::ofstream& ofs);
    void _read(std::ifstream& ifs);


    decltype(auto) begin()
        { return _line_param.begin(); }
    decltype(auto) end()
        { return _line_param.end(); }
    decltype(auto) cbegin() const
        { return _line_param.cbegin(); }
    decltype(auto) cend()  const
        { return _line_param.cend(); }


private:
    bool _is_initialized;
    size_t _fail;
    size_t _success;

    std::vector<std::string> _index2file;
    file2index_t _file2index;

    std::vector<dict> _line_param;
    std::list<ranking_info> _ranking;
    test_suite _test_suite;

    float _highest_ochiai;
};
}






namespace PAFL
{
TestSuite::TestSuite(const TestSuite& rhs) :
    _line_param(rhs._line_param), _ranking(rhs._ranking), _is_initialized(rhs._is_initialized), _fail(rhs._fail),
    _index2file(rhs._index2file), _file2index(rhs._file2index), _highest_ochiai(0.0f)
{
    for (auto& iter : _ranking)
        _line_param[iter.index].at(iter.line).ptr_ranking = &iter;
}



void TestSuite::AddTestCase(const Document& d, bool is_successed)
{
    const auto& json_files = d["files"].GetArray();
    const auto sizeof_files = json_files.Size();
    
    // Reserve containers' capacity
    if (!_is_initialized) {
        
        _file2index.reserve(sizeof_files + 8);
        _index2file.reserve(sizeof_files + 8);
        _line_param.reserve(sizeof_files + 8);
        _is_initialized = true;
    }
    is_successed ? _success++ : _fail++;

    // Add test case
    auto& tc_lines = _test_suite.emplace_back(test_case{std::list<std::pair<index_t, line_t>>(), is_successed}).lines;
    

    for (SizeType i = 0; i != sizeof_files; ++i) {
        
        const auto& json_file = json_files[i].GetObject();
        const auto& json_lines = json_file["lines"].GetArray();
        std::string key(json_file["file"].GetString());
        
        // If the file is a test, ignore
        if (key.rfind("test/", 0) == 0 || key.rfind("tests/", 0) == 0 || json_lines.Size() == 0)
            continue;
        
        // "file" is not in filelist --> initialize
        if (std::find(_index2file.begin(), _index2file.end(), key) == _index2file.end()) {
            
            auto index_now = static_cast<index_t>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _line_param.emplace_back();
            
            for (SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (json_line["count"].GetUint64()) {
                    
                    line_t line_now = json_line["line_number"].GetUint();
                    tc_lines.emplace_back(index_now, line_now);
                    _ranking.push_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });

                    auto val = is_successed ? param{ 0, 1, &*_ranking.rbegin() } : param{ 1, 0, &*_ranking.rbegin() };
                    _line_param[index_now].emplace(line_now, val);
                }
            }
        }
        
        
        // "file" is in filelist
        else
            for (SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (json_line["count"].GetUint64()) {
                    
                    index_t index_now(_file2index[key]);
                    line_t line_now = json_line["line_number"].GetUint();
                    tc_lines.emplace_back(index_now, line_now);

                    // line is not in _line_param
                    if (!_line_param[index_now].contains(line_now)) {
                        
                        auto& ptr = _ranking.emplace_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });
                        auto val = is_successed ? param{ 0, 1, &*_ranking.rbegin() } : param{ 1, 0, &*_ranking.rbegin() };
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

void TestSuite::CalculateSus()
{
    for (auto& dict_iter : _line_param)
        for (auto& param_iter : dict_iter) {

            auto& p = param_iter.second;
            int denom = _fail * (p.Ncf + p.Ncs);
            p.ptr_ranking->sus = p.ptr_ranking->ochiai_sus = denom ? p.Ncf / std::sqrt(denom) : 0.0f;
            if (_highest_ochiai < p.ptr_ranking->ochiai_sus)
                _highest_ochiai = p.ptr_ranking->ochiai_sus;
        }
    
}

const std::list<TestSuite::ranking_info>& TestSuite::Rank()
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

void TestSuite::Save(std::ofstream& ofs) const
{
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

line_t TestSuite::GetRankingSum(index_t idx, const std::list<line_t>& target_lines) const
{
    for (auto iter = _ranking.cbegin(); ; iter++)
        if (iter->index == idx && std::find(target_lines.begin(), target_lines.end(), iter->line) != std::end(target_lines)) {

            auto ranking = iter->ranking;
            for (; iter != _ranking.cend(); iter++)
                if (iter->ranking != ranking)
                    break;
            return ranking + ((iter == _ranking.cend()) ? _ranking.size() : iter->ranking - 1);
        }
}






void TestSuite::_write(std::ofstream& ofs)
{
    // TestSuite
    ofs << _is_initialized << '\n' << _fail << '\n' << _index2file.size() << '\n';
    
    for (auto& iter : _index2file) {

        ofs.write(iter.c_str(), iter.size());
        ofs.put('\n');
    }

    for (auto& file : _line_param) {

        ofs << file.size() << '\n';
        for (auto& iter : file)
            ofs << iter.first << '\n' << iter.second.Ncf << '\n' << iter.second.Ncs << '\n';
    }

    // Test suite
    ofs << _test_suite.size() << '\n';
    for (auto& tc : _test_suite) {
        
        ofs << tc.is_passed << '\n' << tc.lines.size() << '\n';
        for (auto& item : tc.lines)
            ofs << item.first << '\n' << item.second << '\n';
    }

}

void TestSuite::_read(std::ifstream& ifs)
{
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
        _line_param[idx].reserve(file_size);

        for (line_t j = 0; j != file_size; j++) {

            line_t line;
            size_t Ncf, Ncs;
            ifs >> line >> Ncf >> Ncs;

            auto& ptr = _ranking.emplace_back(ranking_info{ idx, line, 0.0f, 0.0f, 0 });
            _line_param[idx].emplace(line, param{ Ncf, Ncs, &ptr });
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
}
}
#endif
