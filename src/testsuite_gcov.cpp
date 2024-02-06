#include "testsuite/testsuite_gcov.h"
#include <iostream>
namespace PAFL
{
void TestSuiteGcov::addTestCase(const rapidjson::Document& d, bool is_successed, const string_set& extensions)
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
    
    for (auto& json_file_obj : json_files) {
        
        const auto& json_file = json_file_obj.GetObject();
        const auto& json_lines = json_file["lines"].GetArray();
        std::string key(json_file["file"].GetString());

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
            _line_param.emplace_back();
            
            for (auto& json_line_obj : json_lines) {

                const auto& json_line = json_line_obj.GetObject();
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
        else for (auto& json_line_obj : json_lines) {

            const auto& json_line = json_line_obj.GetObject();
            if (json_line["count"].GetUint64()) {
                
                index_t index_now = _file2index[key];
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
}
