#include "testsuite/testsuite_gcov.h"

namespace PAFL
{
void TestSuiteGcov::addTestCase(const rapidjson::Document& doc, bool is_passed)
{
    const auto& json_files = doc["files"].GetArray();
    const auto sizeof_files = json_files.Size();
    is_passed ? _succ++ : _fail++;

    // Add test case
    auto& tc_lines = _testcase_vec.emplace_back(TestCase{std::vector<std::pair<index_t, line_t>>(), is_passed}).lines;
    
    for (auto& json_file_obj : json_files) {
        
        const auto& json_file = json_file_obj.GetObject();
        const auto& json_lines = json_file["lines"].GetArray();
        std::string key(json_file["file"].GetString());
        std::filesystem::path file_path(key);

        // Check if it is a permitted extension
        if (!_extensions.contains(file_path.extension().string()))
            continue;

        // Check if it is a valid file
        if (json_lines.Empty())
            continue;

        {// Check if it is a test file
            auto top_dir = file_path;
            for (; !top_dir.parent_path().empty(); top_dir = top_dir.parent_path());
            auto top_dir_string(top_dir.string());
            std::transform(top_dir_string.begin(), top_dir_string.end(), top_dir_string.begin(), tolower);
            if (top_dir_string == "test" || top_dir_string == "tests")
                continue;
        }
        
        // If "file" is not in filelist, initialize
        if (!_file2index.contains(key)) {
            
            auto index_now = static_cast<index_t>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _content.emplace_back();
            
            for (auto& json_line_obj : json_lines) {

                const auto& json_line = json_line_obj.GetObject();
                if (json_line["count"].GetUint64()) {
                    
                    line_t line_now = json_line["line_number"].GetUint();
                    tc_lines.emplace_back(index_now, line_now);
                    auto& ranking = _ranking.emplace_back(Ranking{index_now, line_now, 0.0f, 0.0f, 0});
                    _content[index_now].emplace(line_now, is_passed ? Param{1, 0, &ranking} : Param{0, 1, &ranking});
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
}
