#ifndef __UI_H__
#define __UI_H__

#include <iostream>
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
        { return _num_version; }
    const method_set& getMethodSet() const
        { return _method; }
    
    const fs::path& getProjectPath(size_t version) const
        { return _src_path[version]; }
    const fault_loc& getFaultLocation(size_t version) const
        { return _faults[version]; }
    bool hasLogger() const
        { return _logger; }
    bool hasTimeLogger() const
        { return _time_logger; }

    docs getCoverageList(size_t version) const;


private:
    void _throwInvalidInput()
        { throw "Invalid arguments"; }

    void _readIn(int argc, char *argv[]);
    void _setContainer();

    std::string _project;
    PrgLang _pl;
    size_t _num_version;
    std::set<Method> _method;

    fs::path _project_path;
    fs::path _testsuite_path;
    fs::path _bug_info_path;
    bool _logger;
    bool _time_logger;

    Config _config;
    std::vector<fs::path> _src_path;
    std::vector<fault_loc> _faults;
};

rapidjson::Document parseDoc(const fs::path& path);
}






namespace PAFL
{
UI::UI(int argc, char *argv[]) :
    _project_path(fs::current_path()), _testsuite_path(fs::current_path()), _bug_info_path(fs::current_path()),
    _logger(false), _time_logger(false), _num_version(0)
{
    _readIn(argc, argv);
    _config.configure(_pl);
    _setContainer();
}



UI::docs UI::getCoverageList(size_t version) const
{
    docs ret;
    std::string VER(std::to_string(version));

    // Set docs
    for (size_t tc = 0;; tc++) {

        std::string CASE(std::to_string(tc+1));
        fs::path tc_path = _testsuite_path / _config.getStringFromLine(_config.TESTCASE_LOC, _project, VER, CASE);
        if (!fs::exists(tc_path))
            break;
        
        std::cout << _project << "-" << VER << "> case " << CASE << '\n';

        // Parse document
        bool pf = false;
        {// Check pass/fail
            std::ifstream ifs(tc_path / _config.getStringFromLine(_config.TEST_NAME, _project, VER, CASE));
            std::string buf;
            std::getline(ifs, buf);

            if (buf == _config.getStringFromLine(_config.TEST_PASS, _project, VER, CASE))
                pf = true;
        }
        ret.emplace_back(parseDoc(tc_path / _config.getStringFromLine(_config.COVERAGE_NAME, _project, VER, CASE)), pf);
    }
    std::cout << '\n';

    return ret;
}



void UI::_readIn(int argc, char *argv[])
{
    if (argc <= 3)
        _throwInvalidInput();

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

    {// <SIZE>
        _num_version = std::atoi(argv[2]);
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

        if (arg.starts_with("-P"))
            _project_path = arg.substr(2);

        else if (arg.starts_with("-T"))
            _testsuite_path = arg.substr(2);

        else if (arg.starts_with("-B"))
            _bug_info_path = arg.substr(2);

        else if (arg == "-tl" || arg == "--timelog")
            _logger = true;

        else if (arg == "-l" || arg == "--log")
            _time_logger = true;
        
        else 
            _throwInvalidInput();
    }
}



void UI::_setContainer()
{
    // Set version path
    _src_path.reserve(_num_version);
    _faults.reserve(_num_version);
    
    for (size_t v = 0; v != _num_version; v++) {

        std::string VER(std::to_string(v+1));
        _src_path.emplace_back(_project_path / _config.getStringFromLine(_config.PROJECT_LOC, _project, VER, ""));
        _faults.emplace_back();
    }

    // Set fault location
    rapidjson::Document info(parseDoc(_bug_info_path / (_project + ".json")));
    const auto& ver = info["version"].GetArray();

    for (size_t v = 0; v != _num_version; v++)
        for (const auto& fault : ver[v].GetArray()) {

            const auto& fileline = fault.GetObject();
            auto& line_set = _faults[v].emplace(fileline["file"].GetString(), std::unordered_set<line_t>()).first->second;

            for (auto& line : fileline["lines"].GetArray())
                line_set.insert(line.GetUint());
        }
}



rapidjson::Document parseDoc(const fs::path& path)
{
    rapidjson::Document doc;
    std::ifstream ifs(path);
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();

    char* buf = (char*)std::calloc(size, sizeof(char));
    if (!buf)
        throw std::range_error("malloc failed");

    ifs.seekg(0);
    ifs.read(buf, size);
    ifs.close();

    doc.Parse(buf);
    std::free(buf);

    return doc;
}
}
#endif
