#ifndef __UI_H__
#define __UI_H__

#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

#include "config.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"



namespace PAFL
{
class UI
{
public:
    enum class Method{ PAFL, TARANTULA, OCHIAI, DSTAR, BARINEL };
    using method_set = std::set<Method>;
    using docs = std::list<std::pair<rapidjson::Document, bool>>;


    UI(int argc, char *argv[]);

    const std::string& getProject() const
        { return _project; }
    PrgLang getLanguage() const
        { return _pl; }
    size_t numVersion() const
        { return _version.size(); }
    const method_set& getMethodSet() const
        { return _method; }
    
    const fs::path& getExePath() const
        { return _exe_path; }
    const fs::path& getProjectPath(size_t iter) const
        { return _src_path[iter]; }
    const fault_loc& getFaultLocation(size_t iter) const
        { return _faults[iter]; }
    size_t getVersion(size_t iter) const
        { return _version[iter]; }

    bool hasLogger() const
        { return _logger; }
    bool hasTimeLogger() const
        { return _time_logger; }
    bool hasCache() const
        { return __cache; }

    fs::path getFilePath(size_t iter, const std::string& file) const;
    docs getCoverageList(size_t iter) const;


private:
    void _throwInvalidInput()
        { std::cout << "Invalid arguments\n"; throw "Invalid arguments"; }

    void _readIn(int argc, char *argv[]);
    void _setContainer();

    std::string _project;
    PrgLang _pl;
    std::vector<size_t> _version;
    std::set<Method> _method;
    std::list<std::string> _sub_dir;

    fs::path _exe_path;
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
}






namespace PAFL
{
UI::UI(int argc, char *argv[]) :
    _project_path(fs::current_path()), _testsuite_path(fs::current_path()), _oracle_path(fs::current_path()),
    _logger(false), _time_logger(false), __cache(false)
{
    _readIn(argc, argv);
    _config.configure(_pl, _exe_path);
    _setContainer();
}



fs::path UI::getFilePath(size_t iter, const std::string& file) const
{
    fs::path ret(_src_path[iter] / file);
    if (fs::exists(ret))
        return ret;
    else for (auto& dir : _sub_dir) {

        ret = _src_path[iter] / dir / file;
        if (fs::exists(ret))
            return ret;
    }
    std::cout << "Invalid file path\n"; throw "Invalid file path";
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



void UI::_readIn(int argc, char *argv[])
{
    if (argc <= 3)
        _throwInvalidInput();

    {// Execution location
        _exe_path = fs::path(argv[0]).parent_path();
    }

    {// <PROJECT>:<METHOD>
        std::string arg(argv[1]);
        auto split = arg.find(':');
        if (split == std::string::npos)
            _throwInvalidInput();

        // <PROJECT>
        _project = arg.substr(0, split);

        // <METHOD>
        std::string pl(arg.substr(split + 1));
        std::transform(pl.begin(), pl.end(), pl.begin(),
                        [](std::string::value_type c){ return std::tolower(c); });

        if (pl == "cpp" || pl == "c++" || pl == "c")
            _pl = PrgLang::CPP;
        else if (pl == "python" || pl == "py")
            _pl = PrgLang::PYTHON;
        else if (pl == "java")
            _pl = PrgLang::JAVA;
        else
            _throwInvalidInput();
    }

    {// <VERSION>
        std::string arg(argv[2]);
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

    {// <METHOD>
        std::string arg(argv[3]);
        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);

            std::string method(arg.substr(pos, split - pos));
            if (method == "pafl")
                _method.insert(Method::PAFL);
            else if (method == "tarantula")
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

    // <OPTION>
    for (int i = 4; i != argc; i++) {

        std::string arg(argv[i]);
        if (!arg.starts_with('-'))
            _throwInvalidInput();
        arg.erase(0, 1);

        if (arg.starts_with('P'))
            _project_path = arg.substr(1);

        else if (arg.starts_with('T'))
            _testsuite_path = arg.substr(1);

        else if (arg.starts_with('B'))
            _oracle_path = arg.substr(1);

        else if (arg.starts_with("-sub-dir=")) {// --sub-dir=<DIRECTORY>

            std::string dirs(arg.substr(9));
            for (size_t pos = 0; pos < dirs.size(); ) {

                auto split = dirs.find(',', pos);
                _sub_dir.emplace_back(dirs.substr(pos, split - pos));
                pos = split == std::string::npos ? std::string::npos : split + 1;
            }
        }

        else if (arg == "-log")
            _logger = true;

        else if (arg == "-timelog")
            _time_logger = true;

        else if (arg == "-dev-cache")
            __cache = true;
        
        // abbreviation
        else for(; !arg.empty(); arg.erase(0, 1)) {

            if (arg.starts_with('l'))
                _logger = true;
            else if (arg.starts_with('t'))
                _time_logger = true;
            else if (arg.starts_with('c'))
                __cache = true;
            else
                _throwInvalidInput();
        }
    }
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
}
#endif
