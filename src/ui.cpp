#include "ui.h"

namespace PAFL
{
UI::UI(int argc, char *argv[]) :
    _parser(argc, argv), _project_path(fs::current_path()), _testsuite_path(fs::current_path()), _oracle_path(fs::current_path()),
    _debug(false), _cache(false), _is_project_aware(false),
    _normalizer(std::make_unique<SqrtNormalizer>())
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
        
        std::cout << _project << "-" << VER << "-" << CASE << '\n';

        // Parse document
        bool pf = false;
        {// Check pass/fail
            std::ifstream ifs(tc_path / _config.TEST_NAME(_project, VER, CASE));
            std::string buf;
            std::getline(ifs, buf);

            if (buf == _config.TEST_PASS(_project, VER, CASE))
                pf = true;
        }
        ret.emplace_back(rapidjson::parseDoc(tc_path / _config.COVERAGE_NAME(_project, VER, CASE)), pf);
    }

    return ret;
}



void UI::_readIn()
{
    {// --project | -p [PROJECT]
        _project = _parser[{"-p", "--project"}];
        _assert(!_project.empty(), "Project name is missing");
    }

    {// --language | -l [PL]
        auto arg = _parser[{"-l", "--language"}];
        _assert(!arg.empty(), "Language is missing");

        if (arg == "cpp" || arg == "c++" || arg == "c") {

            _pl = PrgLang::CPP;
            _extensions = { ".h", ".c", ".hpp", ".cpp", ".cc" };
        }
        else if (arg == "python" || arg == "py") {

            _pl = PrgLang::PYTHON;
            _extensions = { ".py" };
        }
        else if (arg == "java")
            _pl = PrgLang::JAVA;
        else
            _throwInvalidInput("Invalid language");
    }

    {// --method | -m [METHOD 1],[METHOD 2]
        auto arg = _parser[{"-m", "--method"}];
        _assert(!arg.empty(), "Method is missing");

        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);

            std::string method(arg.substr(pos, split - pos));
            // SBFL
            if (method == "tarantula")
                _method.emplace_back(std::make_unique<Tarantula>(method));
            else if (method == "ochiai")
                _method.emplace_back(std::make_unique<Ochiai>(method));
            else if (method == "dstar")
                _method.emplace_back(std::make_unique<Dstar>(method));
            else if (method == "barinel")
                _method.emplace_back(std::make_unique<Barinel>(method));
            else if (method == "ones")
                _method.emplace_back(std::make_unique<Ones>(method));
            // DLFL
            else
                _method.emplace_back(std::make_unique<CusmtomMethod>(method, getDirectoryPath()));

            pos = split == std::string::npos ? std::string::npos : split + 1;
        }
    }

    {// --version | -v [V1],[V2]-[V3]
        auto arg = _parser[{"-v", "--version"}];
        _assert(!arg.empty(), "Version is missing");

        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);

            std::string interval(arg.substr(pos, split - pos));
            auto connector = interval.find('-');
            // Interval
            if (connector != std::string::npos) {
                
                auto left = std::stoi(interval.substr(0, connector));
                auto right = std::stoi(interval.substr(connector + 1));

                if (left <= right)
                    for (auto i = left; i <= right; i++)
                        _version.push_back(i);
                else
                    for (auto i = left; i >= right; i--)
                        _version.push_back(i);
            }
            // Single value
            else
                _version.push_back(std::stoi(interval));

            pos = split == std::string::npos ? std::string::npos : split + 1;
        }
    }

    // --pafl
    if (_parser.contains("--pafl"))
        _is_project_aware = true;

    /*
        Normalized sus is in [0.6, 1.0]
        normalizer = linear | sqrt | cbrt | qdrt
        Default normalizer=qdrt
    */
    // --normalizer=linear
    if (_parser.contains({"--normalizer=linear"}))
        _normalizer = std::make_unique<LinearNormalizer>();

    // --normalizer=sqrt
    if (_parser.contains({"--normalizer=sqrt"}))
        _normalizer = std::make_unique<SqrtNormalizer>();

    // --normalizer=cbrt
    if (_parser.contains({"--normalizer=cbrt"}))
        _normalizer = std::make_unique<CbrtNormalizer>();

    // --normalizer=bqrt
    if (_parser.contains({"--normalizer=qdrt"}))
        _normalizer = std::make_unique<QdrtNormalizer>();

    /*
        Path options
    */ 
    // --project-dir | -d [PATH]
    if (_parser.contains({"-d", "--project-dir"}))
        _project_path = _parser[{"-d", "--project-dir"}];

    // --testsuite | -s [PATH]
    if (_parser.contains({"-t", "--testsuite"}))
        _testsuite_path = _parser[{"-t", "--testsuite"}];
    
    // --fault-info | -i [PATH]
    if (_parser.contains({"-i", "--fault-info"}))
        _oracle_path = _parser[{"-i", "--fault-info"}];

    // --debug | -g 
    if (_parser.contains({"-g", "--debug"}))
        _debug = true;
    
    // --cache | -c
    if (_parser.contains({"-c", "--cache"}))
        _cache = true;

    // --sub-dir <DIR1>,<DIR2>
    if (_parser.contains("--sub-dir")) {
        
        auto arg = _parser["--sub-dir"];
        for (size_t pos = 0; pos < arg.size(); ) {

            auto split = arg.find(',', pos);
            _sub_dir.emplace_back(arg.substr(pos, split - pos));
            pos = split == std::string::npos ? std::string::npos : split + 1;
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
    rapidjson::Document info(rapidjson::parseDoc(_oracle_path / (_project + ".json")));
    const auto& ver = info["version"].GetArray();

    for (size_t i = 0; i != _version.size(); i++) 
        for (const auto& fault : ver[_version[i] - 1].GetArray()) {

            const auto& fileline = fault.GetObject();
            auto& line_set = _faults[i].emplace(fileline["file"].GetString(), std::unordered_set<line_t>()).first->second;

            for (auto& line : fileline["lines"].GetArray())
                line_set.insert(line.GetUint());
        }
}



std::list<fs::path> UI::_collectDir(const fs::path& path, std::string key)
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