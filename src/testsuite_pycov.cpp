#include "testsuite/testsuite_pycov.h"

namespace PAFL
{
void TestSuitePycov::addTestCase(const rapidjson::Document& doc, bool is_passed)
{
    const auto& json_files = doc["files"].GetObject();
    size_t sizeof_files = json_files.MemberCount();
    is_passed ? _succ++ : _fail++;

    // Add test case
    auto& tc_lines = _testcase_vec.emplace_back(TestCase{std::vector<std::pair<index_t, line_t>>(), is_passed}).lines;
    

    for (auto& json_file : json_files) {
        
        const auto& json_lines = json_file.value.GetObject()["executed_lines"].GetArray();
        std::string key(json_file.name.GetString());

        // Check if it is a permitted extension
        if (!_extensions.contains(std::filesystem::path(key).extension().string()))
            continue;

        // Check if it is a valid file
        if (json_lines.Empty())
            continue;
        
        // If "file" is not in filelist, initialize
        if (!_file2index.contains(key)) {
            
            auto index_now = static_cast<index_t>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _content.emplace_back();
            
            for (auto& json_line : json_lines) {
                
                line_t line_now = json_line.GetUint();
                tc_lines.emplace_back(index_now, line_now);
                auto& ranking = _ranking.emplace_back(Ranking{index_now, line_now, 0.0f, 0.0f, 0});
                _content[index_now].emplace(line_now, is_passed ? Param{1, 0, &ranking} : Param{0, 1, &ranking});
            }
        }
        
        // "file" is in filelist
        else for (auto& json_line : json_lines) {
                
            line_t line_now = json_line.GetUint();
            index_t index_now = _file2index[key];
            tc_lines.emplace_back(index_now, line_now);

            // line is in _content
            if (_content.at(index_now).contains(line_now))
                if (is_passed)
                    _content[index_now].at(line_now).Ncs++;
                else
                    _content[index_now].at(line_now).Ncf++;

            // line is not in _content
            else {

                auto& ranking = _ranking.emplace_back(Ranking{index_now, line_now, 0.0f, 0.0f, 0});
                _content[index_now].emplace(line_now, is_passed ? Param{1, 0, &ranking} : Param{0, 1, &ranking});
            }
        }
    }
}
}
