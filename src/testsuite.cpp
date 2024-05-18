#include "testsuite/testsuite.h"

namespace PAFL
{
TestSuite::TestSuite() : _fail(0)
{
    _initBoundary();
    constexpr int size = 256;
    _file2index.reserve(size);
    _index2file.reserve(size);
    _content.reserve(size);
}



void TestSuite::rank()
{
    // Sort
    if (_ranking.size() == 0)
        return;
    _ranking.sort([](const Ranking& lhs, const Ranking& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_t virtual_ranking = 0;
    float sus = _ranking.begin()->sus;

    std::vector<Ranking*> tie;
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
}



TestSuite::fault_set_t TestSuite::makeFalutSet(const rapidjson::Document& doc) const
{
    fault_set_t ret;
    
    // Read JSON document
    const auto& files = doc["locations"].GetArray();
    for (const auto& file_obj : files) {

        // Read file path
        const auto& file = file_obj.GetObject();
        auto index = _file2index.at(file["file"].GetString());
        auto& map = _content.at(index);

        // Read lines
        for (const auto& line_uint : file["lines"].GetArray()) {

            auto line = line_uint.GetUint();
            if (map.contains(line))
                ret.emplace(index, line);
        }
    }

    return ret;
}



TestSuite::line_t TestSuite::getFirstRanking(const fault_set_t& faults) const
{
    for (auto item : _ranking)
        if (faults.contains(std::make_pair(item.index, item.line)))
            return item.ranking;
    return _ranking.size();
}



float TestSuite::getAverageRanking(const fault_set_t& faults) const
{
    float avg = 0.0f;
    size_t size = 0;
    for (auto item : faults)
        if (_content.at(item.first).contains(item.second)) {

            avg += _content.at(item.first).at(item.second).ranking_ptr->ranking;
            ++size;
        }
    return size ? avg / size : 0.0f;
}



void TestSuite::readSus(const rapidjson::Document& doc)
{
    _initBoundary();
    for (const auto& info_obj : doc["lines"].GetArray()) {

        const auto& info = info_obj.GetObject();
        auto file(info["file"].GetString());
        line_t line(info["lineno"].GetUint());
        auto sus(info["sus"].GetFloat());

        // Update the suspiciousness values
        if (_file2index.contains(file)) {

            auto index = _file2index.at(file);
            if (_content.at(index).contains(line)) {

                auto& param = _content.at(index).at(line);
                // Update lines which is covered by failed test cases
                if (param.Ncf) {
                    
                    param.ranking_ptr->sus = param.ranking_ptr->base_sus = sus;
                    if (_highest < sus)
                        _highest = sus;
                    if (_finite_highest < sus && sus < std::numeric_limits<float>::infinity())
                        _finite_highest = sus;
                    if (0.0f < sus && sus < _lowest_nonzero)
                        _lowest_nonzero = sus;
                }
                // Set uncovered line to 0
                else
                    param.ranking_ptr->sus = param.ranking_ptr->base_sus = 0.0f;
            }
        }
    }
}



std::string TestSuite::toJson() const
{
    std::string bufferfer;
    bufferfer.reserve(StringEditor::MiB(16));

    // total
    StringEditor::append(bufferfer.append("{\n\"total\": "), _ranking.size()).append(",\n\"lines\": [\n");

    // lines
    for (auto item : _ranking) {
        
        bufferfer.append("\t{ ");
        // index
        bufferfer.append("\"file\": \"").append(_index2file[item.index]).append("\", ");
        // line
        StringEditor::append(bufferfer.append("\"line\": "), item.line).append(", ");
        // ranking
        StringEditor::append(bufferfer.append("\"ranking\": "), item.ranking).append(", ");
        // sus
        bufferfer.append("\"sus\": ");
        if (item.sus < std::numeric_limits<float>::infinity())
            StringEditor::append(bufferfer, item.sus);
        else
            bufferfer.append("\"inf\"");
        bufferfer.append(" },\n");
    }
    StringEditor::eraseEndIf(bufferfer, ",\n");
    bufferfer.append("]\n} ");
    return bufferfer;
}



void TestSuite::saveAsCovMatrix(const std::filesystem::path& dir, const fault_set_t& faults) const
{
    /*
        <mapper>
        JSON format
        {
            "lines": [
                { "file": "FILE_NAME", "lineno": INT },
                ...
            ]
        }
    */
    std::vector<std::unordered_map<line_t, line_t>> mapper;
    line_t total_plus_one = 1;

    {   // Init mapper
        mapper.reserve(_content.size());

        // Init buffer
        std::string buffer;
        buffer.reserve(StringEditor::MiB(16));
        buffer.append("{\"lines\":[");

        // For all (file, line) in _content
        for (auto& file : _content) {

            auto& map = mapper.emplace_back();
            map.reserve(file.size());
            for (auto& item : file) {
                
                // Push new line to mapper
                map.emplace(item.first, total_plus_one++);
                // Save information of new line
                StringEditor::append(buffer.append("{\"file\":\"").append(_index2file.at(item.second.ranking_ptr->index)).append("\",\"lineno\":"), item.first).append("},");
            }
        }

        // Save mapper
        StringEditor::eraseEndIf(buffer, ',');
        buffer.append("]}");
        std::ofstream(dir / "map.json").write(buffer.c_str(), buffer.size());
    }


    {// componentinfo
        std::string buffer;
        buffer.reserve(StringEditor::MiB(16));
        StringEditor::append(buffer, total_plus_one - 1).push_back('\n');
        for (line_t l = 1; l != total_plus_one; ++l)
            StringEditor::append(buffer, l).push_back(' ');
        buffer.pop_back();
        std::ofstream(dir / "componentinfo.txt").write(buffer.c_str(), buffer.size());
    }

    {// faultLine
        std::string buffer;
        buffer.reserve(1024);
        buffer.append("fault=", 6);
        for (auto item : faults) {

            buffer.push_back('"');
            StringEditor::append(buffer, mapper[item.first].at(item.second)).push_back('"');
        }
        std::ofstream(dir / "faultLine.txt").write(buffer.c_str(), buffer.size());
    }
    
    {// covMatrix & error
        std::string buffer;
        buffer.reserve(StringEditor::MiB(64));
        std::ofstream error(dir / "error.txt");

        for (auto& tc : _testcase_vec) {

            error << !tc.is_passed << '\n';
            // Line set
            std::unordered_set<line_t> line_set;
            for (auto item : tc.lines)
                line_set.insert(mapper[item.first].at(item.second));
            for (line_t l = 1; l != total_plus_one; ++l)
                buffer.append(line_set.contains(l) ? "1 " : "0 ", 2);
            buffer.pop_back();
            buffer.push_back('\n');
        }

        buffer.pop_back();
        std::ofstream(dir / "covMatrix.txt").write(buffer.c_str(), buffer.size());
    }
}
}



namespace PAFL
{
TestSuite::Copy::Copy(const TestSuite& suite) :
    content(suite._content.size())
{
    for (index_t index = 0; index != content.size(); ++index)
        for (auto item : suite._content.at(index)) {

            auto& ref = ranking.emplace_back(*item.second.ranking_ptr);
            content[index].emplace(item.first, &ref);
        }
}



void TestSuite::Copy::rank()
{
    // Sort
    if (ranking.size() == 0)
        return;
    ranking.sort([](const Ranking& lhs, const Ranking& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_t virtual_ranking = 0;
    float sus = ranking.begin()->sus;

    std::vector<Ranking*> tie;
    for (auto& iter : ranking) {

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
        ptr_info->ranking = ranking.size();
}



TestSuite::line_t TestSuite::Copy::getFirstRanking(const TestSuite::fault_set_t& faults) const
{
    for (auto item : ranking)
        if (faults.contains(std::make_pair(item.index, item.line)))
            return item.ranking;
    return ranking.size();
}
}
