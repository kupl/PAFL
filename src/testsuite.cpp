#include "testsuite/testsuite.h"

namespace PAFL
{
void TestSuite::oversample(size_t iter)
{
    _fail *= 1 + iter;

    for (auto& tc : _test_suite)
        if (!tc.is_passed)
            for (auto& item : tc.lines)
                _line_param.at(item.first).at(item.second).Ncf += iter;
}



const std::list<TestSuite::ranking_info>& TestSuite::rank()
{
    // Sort
    _ranking.sort([](const ranking_info& lhs, const ranking_info& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_t virtual_ranking = 0;
    float sus = std::numeric_limits<float>::infinity();

    std::list<ranking_info*> tie;
    for (auto& iter : _ranking) {

        if (sus > iter.sus) {

            sus = iter.sus;
            for (auto ptr_info : tie)
                ptr_info->ranking = virtual_ranking;
            tie.clear();
        }
        tie.push_back(&iter);
        virtual_ranking++;
    }
    for (auto ptr_info : tie)
        ptr_info->ranking = _ranking.size();

    return _ranking;
}



index_t TestSuite::getIndexFromFile(const std::string& file) const
{
    if (_file2index.contains(file))
        return _file2index.at(file);
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



void TestSuite::toJson(const fs::path& path) const
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



void TestSuite::caching(const fs::path& path) const
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



int TestSuite::loadCache(const fs::path& path)
{
    if (!fs::exists(path))
        return 1;

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
    _succ = suite_size - _fail;
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
    return 0;
}



void TestSuite::toCovMatrix(const fs::path& dir, const fault_loc& faults) const
{
    // mapper
    std::vector<std::unordered_map<line_t, line_t>> mapper;
    line_t total_plus_one = 1;
    {// Init mapper
        mapper.reserve(_line_param.size());
        for (auto& file : _line_param) {

            auto& map = mapper.emplace_back();
            map.reserve(file.size());
            for (auto& iter : file)
                map.emplace(iter.first, total_plus_one++);
        }

        // componentinfo
        std::ofstream cmp_info(dir / "componentinfo.txt");
        cmp_info << total_plus_one - 1 << '\n';
        for (line_t l = 1; l != total_plus_one; ++l)
            cmp_info << l << ' ';
    }

    {// faultLine
        std::ofstream fault_line(dir / "covMatrix.txt");
        fault_line << "fault=\"";
        for (auto iter = faults.begin(); iter != faults.end(); ++iter) {

            auto index = _file2index.at(iter->first);
            for (auto jter = iter->second.begin(); jter != iter->second.end(); ++jter) {

                fault_line << mapper[index].at(*jter);
                auto temp = jter;
                if (iter != faults.end() || ++temp != iter->second.end())
                    fault_line << ',';
            }
        }
        fault_line << '"';
    }
    
    {// covMatrix & error
        std::ofstream cov_matrix(dir / "covMatrix.txt");
        std::ofstream error(dir / "error.txt");

        for (auto& tc : _test_suite) {

            error << tc.is_passed << '\n';
            // Line set
            std::unordered_set<line_t> line_set;
            for (auto item : tc.lines)
                line_set.insert(mapper[item.first].at(item.second));
            for (line_t l = 1; l != total_plus_one; ++l)
                cov_matrix.write(line_set.contains(l) ? "1 " : "0 ", 2);
            cov_matrix.put('\n');
        }
    }
}



int TestSuite::loadBaseSus(const fs::path& path)
{
    if (!fs::exists(path))
        return 1;

    // Init mapper
    std::vector<float*> mapper(_ranking.size() + 1, nullptr);
    {
        line_t l = 0;
        for (auto& file : _line_param) {
            for (auto& iter : file)
                mapper[l++] = &iter.second.ptr_ranking->base_sus;
        }
    }

    // Read suspicousness
    std::ifstream ifs(path);
    for (auto ptr : mapper) {

        ifs >> *ptr;
        if (_highest_sus < *ptr) {

                _highest_sus = *ptr;
                if (_highest_sus < std::numeric_limits<float>::infinity())
                    _finite_highest_sus = _highest_sus;
            }
    }
    return 0;
}
}
