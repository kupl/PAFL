#include "testsuite/testsuite.h"

namespace PAFL
{
TestSuite::TestSuite() : _fail(0)
{
    _initBoundary();
    constexpr int size = 256;
    _file2index.reserve(size);
    _index2file.reserve(size);
    _param_container.reserve(size);
}



void TestSuite::oversample(size_t iter)
{
    _fail *= 1 + iter;

    for (auto& tc : _total_test_case)
        if (!tc.is_passed)
            for (auto& item : tc.lines)
                _param_container.at(item.first).at(item.second).Ncf += iter;
}



const std::list<TestSuite::Ranking>& TestSuite::rank()
{
    // Sort
    _ranking.sort([](const Ranking& lhs, const Ranking& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_t virtual_ranking = 0;
    float sus = _ranking.begin()->sus;

    std::list<Ranking*> tie;
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



TestSuite::FaultSet TestSuite::toFaultSet(const fault_loc& faults) const
{
    FaultSet ret;
    for (auto& pair : faults) {
        
        auto& map = _param_container[_file2index.at(pair.first)];
        for (auto line : pair.second)
            if (map.contains(line))
                ret.insert(&map.at(line));
    }
    return ret;
}



line_t TestSuite::getFirstRanking(const fault_loc& faults) const
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



void TestSuite::caching(const fs::path& path) const
{
    std::ofstream ofs(path, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    archive(*this);
}



int TestSuite::readCache(const fs::path& path)
{
    if (!fs::exists(path))
        return 1;
    std::ifstream ifs(path, std::ios::binary);
    cereal::BinaryInputArchive archive(ifs);
    archive(*this);
    return 0;
}



void TestSuite::toJson(const fs::path& path) const
{
    std::string buffer;
    buffer.reserve(StringEditor::MiB(16));

    // total
    StringEditor::append(buffer.append("{\n\"total\": "), _ranking.size()).append(",\n\"lines\": [\n");

    // lines
    for (auto item : _ranking) {
        
        buffer.append("\t{ ");
        // index
        buffer.append("\"file\": \"").append(_index2file[item.index]).append("\", ");
        // line
        StringEditor::append(buffer.append("\"line\": "), item.line).append(", ");
        // ranking
        StringEditor::append(buffer.append("\"ranking\": "), item.ranking).append(", ");
        // sus
        buffer.append("\"sus\": ");
        if (item.sus < std::numeric_limits<float>::infinity())
            StringEditor::append(buffer, item.sus);
        else
            buffer.append("\"inf\"");
        buffer.append(" },\n");
    }
    StringEditor::eraseEndIf(buffer, ",\n");
    buffer.append("]\n} ");

    std::ofstream(path).write(buffer.c_str(), buffer.size());
}



void TestSuite::toCovMatrix(const fs::path& dir, const fault_loc& faults) const
{
    // mapper
    std::vector<std::unordered_map<line_t, line_t>> mapper;
    line_t total_plus_one = 1;

    {// Init mapper
        mapper.reserve(_param_container.size());
        for (auto& file : _param_container) {

            auto& map = mapper.emplace_back();
            map.reserve(file.size());
            for (auto& item : file)
                map.emplace(item.first, total_plus_one++);
        }

        // componentinfo
        std::string buf;
        buf.reserve(StringEditor::MiB(16));
        StringEditor::append(buf, total_plus_one - 1).push_back('\n');
        for (line_t l = 1; l != total_plus_one; ++l)
            StringEditor::append(buf, l).push_back(' ');
        buf.pop_back();
        std::ofstream(dir / "componentinfo.txt").write(buf.c_str(), buf.size());
    }

    {// faultLine
        std::string buf;
        buf.reserve(1024);
        buf.append("fault=", 6);
        for (auto& item : faults) {

            auto index = _file2index.at(item.first);
            for (auto line : item.second)
                if (mapper[index].contains(line)) {

                    buf.push_back('"');
                    StringEditor::append(buf, mapper[index].at(line)).push_back('"');
                }
        }
        std::ofstream(dir / "faultLine.txt").write(buf.c_str(), buf.size());
    }
    
    {// covMatrix & error
        std::string buf;
        buf.reserve(StringEditor::MiB(64));
        std::ofstream error(dir / "error.txt");

        for (auto& tc : _total_test_case) {

            error << !tc.is_passed << '\n';
            // Line set
            std::unordered_set<line_t> line_set;
            for (auto item : tc.lines)
                line_set.insert(mapper[item.first].at(item.second));
            for (line_t l = 1; l != total_plus_one; ++l)
                buf.append(line_set.contains(l) ? "1 " : "0 ", 2);
            buf.pop_back();
            buf.push_back('\n');
        }

        buf.pop_back();
        std::ofstream(dir / "covMatrix.txt").write(buf.c_str(), buf.size());
    }
}



int TestSuite::loadBaseSus(const fs::path& path)
{
    if (!fs::exists(path))
        return 1;
    _initBoundary();

    // Init mapper
    std::vector<float*> mapper(_ranking.size() + 1, nullptr);
    {
        line_t l = 0;
        for (auto& file : _param_container)
            for (auto& iter : file) {

                iter.second.ranking_ptr->base_sus = 0.0f;
                mapper[l++] = &iter.second.ranking_ptr->base_sus;
            }
    }

    // Read suspicousness
    std::ifstream ifs(path);
    while (true) {

        line_t line;
        if (!(ifs >> line))
            break;
        std::string str_sus;
        ifs >> str_sus;
        float sus = std::stof(str_sus);
        *mapper[line - 1] = sus;

        if (_highest < sus)
            _highest = sus;
        if (_finite_highest < sus && sus < std::numeric_limits<float>::infinity())
            _finite_highest = sus;
        if (sus > 0.0f && sus < _lowest_nonzero)
            _lowest_nonzero = sus;
    }

    // Set uncovered line to 0
    for (auto& file : _param_container)
        for (auto& item : file)
            if (item.second.Ncf == 0)
                item.second.ranking_ptr->base_sus = 0.0f;
    return 0;
}
}
