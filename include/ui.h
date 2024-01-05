#ifndef __UI_H__
#define __UI_H__

#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

#include "argparser.h"
#include "config.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"



namespace PAFL
{
class UI
{
public:
    enum class Method{ TARANTULA, OCHIAI, DSTAR, BARINEL, CNN, RNN, MLP };
    using method_set = std::set<Method>;
    using docs = std::list<std::pair<rapidjson::Document, bool>>;

public:
    UI(int argc, char *argv[]);

    const std::string& getProject() const                   { return _project; }
    PrgLang getLanguage() const                             { return _pl; }
    size_t numVersion() const                               { return _version.size(); }
    const method_set& getMethodSet() const                  { return _method; }
    
    const fs::path& getDirectoryPath() const                { return _parser.getDirectoryPath(); }
    const fs::path& getProjectPath(size_t iter) const       { return _src_path[iter]; }
    const fault_loc& getFaultLocation(size_t iter) const    { return _faults[iter]; }
    size_t getVersion(size_t iter) const                    { return _version[iter]; }
    const std::vector<std::string>& getExtensions() const   { return _extensions; }

    bool hasLogger() const                                  { return _logger; }
    bool hasTimeLogger() const                              { return _time_logger; }
    bool hasCache() const                                   { return __cache; }

    fs::path getFilePath(size_t iter, const std::string& file) const;
    docs getCoverageList(size_t iter) const;


private:
    void _throwInvalidInput() const                         { throw std::invalid_argument("Invalid argument"); }
    void _readIn();
    void _setContainer();

private:
    const ArgParser _parser;
    std::string _project;
    PrgLang _pl;
    std::vector<size_t> _version;
    std::set<Method> _method;
    std::list<fs::path> _sub_dir;
    std::vector<std::string> _extensions;

    fs::path _project_path;
    fs::path _testsuite_path;
    fs::path _oracle_path;
    bool _logger;
    bool _time_logger;
    bool __cache;

    Config _config;
    std::vector<fs::path> _src_path;
    std::vector<fault_loc> _faults;
};

rapidjson::Document parseDoc(const fs::path& path);
std::list<fs::path> _collectDir(const fs::path& path, std::string key);
}






namespace PAFL
{
UI::UI(int argc, char *argv[]) :
    _parser(argc, argv), _project_path(fs::current_path()), _testsuite_path(fs::current_path()), _oracle_path(fs::current_path()),
    _logger(false), _time_logger(false), __cache(false)
{
    _readIn();
    _config.configure(_pl, _parser.getDirectoryPath());
    _setContainer();
}



fs::path UI::getFilePath(size_t iter, const std::string& file) const
{
    fs::path ret(_src_path[iter] / file);
    if (fs::exists(ret))
        return ret;
    else for (auto& dir: _sub_dir) {
        
        fs::path src(_src_path[iter] / dir.parent_path());
        auto key(dir.filename().string());

        for (auto& dir : _collectDir(src, key)) {

            ret = dir / file;
            if (fs::exists(ret))
                return ret;
        }
    }

    throw std::domain_error(file);
}



UI::docs UI::getCoverageList(size_t iter) const
{
    docs ret;
    std::string VER(std::to_string(_version[iter]));

    // Set docs
    for (size_t tc = 1;; tc++) {

        std::string CASE(std::to_string(tc));
        fs::path tc_path = _testsuite_path / _config.TESTCASE_LOC(_project, VER, CASE);
        if (!fs::exists(tc_path))
            break;
        
        std::cout << _project << "-" << VER << "> case " << CASE << '\n';

        // Parse document
        bool pf = false;
        {// Check pass/fail
            std::ifstream ifs(tc_path / _config.TEST_NAME(_project, VER, CASE));
            std::string buf;
            std::getline(ifs, buf);

            if (buf == _config.TEST_PASS(_project, VER, CASE))
                pf = true;
        }
        ret.emplace_back(parseDoc(tc_path / _config.COVERAGE_NAME(_project, VER, CASE)), pf);
    }
    std::cout << '\n';

    return ret;
}



void UI::_readIn()
{
    {// --project | -p [PROJECT]
        _project = _parser[{"-p", "--project"}];
        if (_project.empty())
            _throwInvalidInput();
    }

    {// --language | -l [PL]
        auto arg = _parser[{"-l", "--language"}];
        if (arg.empty())
            _throwInvalidInput();

        if (arg == "cpp" || arg == "c++" || arg == "c") {

            _pl = PrgLang::CPP;
            _extensions = { ".h", ".c", ".hpp", ".cpp", ".cc" };
        }
        else if (arg == "python" || arg == "py") {

            _pl = PrgLang::PYTHON;
            _extensions = { ".py", "pyi", "pyc" };
        }
        else if (arg == "java")
            _pl = PrgLang::JAVA;
        else
            _throwInvalidInput();
    }

    {// --method | -m [METHOD 1],[METHOD 2]
        auto arg = _parser[{"-m", "--method"}];
        if (arg.empty())
            _throwInvalidInput();

        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);

            std::string method(arg.substr(pos, split - pos));
            if (method == "tarantula")
                _method.insert(Method::TARANTULA);
            else if (method == "ochiai")
                _method.insert(Method::OCHIAI);
            else if (method == "dstar")
                _method.insert(Method::DSTAR);
            else if (method == "barinel")
                _method.insert(Method::BARINEL);
            else
                _throwInvalidInput();

            pos = split == std::string::npos ? std::string::npos : split + 1;
        }
    }

    {// --version | -v [V1],[V2],[V3]-[V4]
        auto arg = _parser[{"-v", "--version"}];
        if (arg.empty())
            _throwInvalidInput();

        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);

            std::string interval(arg.substr(pos, split - pos));
            auto connector = interval.find('-');
            // Interval
            if (connector != std::string::npos) {
                
                auto left = std::stoi(interval.substr(0, connector));
                auto right = std::stoi(interval.substr(connector + 1));
                if (left > right)
                    _throwInvalidInput();

                for (auto i = left; i <= right; i++)
                    _version.push_back(i);
            }
            // Single value
            else
                _version.push_back(std::stoi(interval));

            pos = split == std::string::npos ? std::string::npos : split + 1;
        }
    }

    if (_parser.contains("--sub-dir")) {// --sub-dir <DIR1>,<DIR2>
        
        auto arg = _parser["--sub-dir"];
        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);
            _sub_dir.emplace_back(arg.substr(pos, split - pos));
            pos = split == std::string::npos ? std::string::npos : split + 1;
        }
    }

    if (_parser.contains({"-d", "--project-dir"}))// --project-dir | -d [PATH]
        _project_path = _parser[{"-d", "--project-dir"}];

    if (_parser.contains({"-s", "--testsuite"}))// --testsuite | -s [PATH]
        _testsuite_path = _parser[{"-t", "--testsuite"}];
    
    if (_parser.contains({"-i", "--fault-info"}))// --fault-info | -i [PATH]
        _oracle_path = _parser[{"-d", "--project-dir"}];
    
    if (_parser.contains({"-g", "--debug"}))
        _logger = true;
    
    if (_parser.contains({"-t", "--time-log"}))
        _logger = true;
    
    if (_parser.contains({"-c", "--cache"}))
        __cache = true;
}



void UI::_setContainer()
{
    // Set version path
    _src_path.reserve(_version.size());
    _faults.reserve(_version.size());
    
    for (auto v : _version) {

        std::string VER(std::to_string(v));
        _src_path.emplace_back(_project_path / _config.PROJECT_LOC(_project, VER, ""));
        _faults.emplace_back();
    }

    // Set fault location
    rapidjson::Document info(parseDoc(_oracle_path / (_project + ".json")));
    const auto& ver = info["version"].GetArray();

    for (size_t i = 0; i != _version.size(); i++) 
        for (const auto& fault : ver[_version[i] - 1].GetArray()) {

            const auto& fileline = fault.GetObject();
            auto& line_set = _faults[i].emplace(fileline["file"].GetString(), std::unordered_set<line_t>()).first->second;

            for (auto& line : fileline["lines"].GetArray())
                line_set.insert(line.GetUint());
        }
}



rapidjson::Document parseDoc(const fs::path& path)
{
    std::FILE* fp = std::fopen(path.c_str(), "rb");
    std::fseek(fp, 0, SEEK_END);
    auto size = std::ftell(fp);
    std::rewind(fp);

    char* buf = (char*)std::calloc(size + 1, sizeof(char));
    if (!buf)
        throw std::range_error("malloc failed");
    std::fread(buf, size, 1, fp);
    std::fclose(fp);

    rapidjson::Document doc;
    doc.Parse(buf);
    std::free(buf);

    return doc;
}



std::list<fs::path> _collectDir(const fs::path& path, std::string key)
{
    std::list<fs::path> ret;

    if (key[0] != '*') {

        if (*key.rbegin() != '*')
            return std::list<fs::path>{path / key};

        key.erase(key.end() - 1);
        for (const auto& entry : fs::directory_iterator(path))
            if (entry.path().filename().string().starts_with(key))
                ret.emplace_back(entry.path());
        return ret;
    }

    key.erase(key.front());
    {
        if (*key.rbegin() != '*') {

            for (const auto& entry : fs::directory_iterator(path))
                if (entry.path().filename().string().ends_with(key))
                    ret.emplace_back(entry.path());
            return ret;
        }

        key.erase(key.end() - 1);
        for (const auto& entry : fs::directory_iterator(path))
            if (entry.path().filename().string().find(key) != std::string::npos)
                ret.emplace_back(entry.path());
        return ret;
    }
}
}
#endif
