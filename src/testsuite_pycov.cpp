#include "testsuite/testsuite_pycov.h"

namespace PAFL
{
void TestSuitePycov::addTestCase(const rapidjson::Document& doc, bool is_successed, const string_set& extensions)
{
    const auto& json_files = doc["files"].GetObject();
    size_t sizeof_files = json_files.MemberCount();
    is_successed ? _succ++ : _fail++;

    // Add test case
    auto& tc_lines = _total_test_case.emplace_back(TestCase{std::list<std::pair<index_t, line_t>>(), is_successed}).lines;
    

    for (auto& json_file : json_files) {
        
        const auto& json_lines = json_file.value.GetObject()["executed_lines"].GetArray();
        std::string key(json_file.name.GetString());

        // Check if it is a permitted extension
        if (!extensions.contains(fs::path(key).extension().string()))
            continue;

        // Check if it is a valid file
        if (json_lines.Empty())
            continue;
        
        // "file" is not in filelist --> initialize
        if (!_file2index.contains(key)) {
            
            auto index_now = static_cast<index_t>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _param_container.emplace_back();
            
            for (auto& json_line : json_lines) {
                
                line_t line_now = json_line.GetUint();
                tc_lines.emplace_back(index_now, line_now);
                _ranking.push_back(Ranking{ index_now, line_now, 0.0f, 0.0f, 0 });

                auto val = is_successed ? Param{ 1, 0, &*_ranking.rbegin() } : Param{ 0, 1, &*_ranking.rbegin() };
                _param_container[index_now].emplace(line_now, val);
            }
        }
        
        // "file" is in filelist
        else for (auto& json_line : json_lines) {
                
            line_t line_now = json_line.GetUint();
            index_t index_now = _file2index[key];
            tc_lines.emplace_back(index_now, line_now);

            // line is not in _param_container
            if (!_param_container[index_now].contains(line_now)) {
                
                auto& ptr = _ranking.emplace_back(Ranking{ index_now, line_now, 0.0f, 0.0f, 0 });
                auto val = is_successed ? Param{ 1, 0, &*_ranking.rbegin() } : Param{ 0, 1, &*_ranking.rbegin() };
                _param_container[index_now].emplace(line_now, val);
            }

            // line is in _param_container
            else {

                auto& line = _param_container[index_now][line_now];
                is_successed ? line.Ncs++ : line.Ncf++;
            }
        }
    }
}
}
