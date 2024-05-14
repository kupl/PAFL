#include "pipeline/pipeline.h"

namespace PAFL
{
void Pipeline::run()
{
    _assert(_args.size() > 1, "Command option is required.\nRun 'pafl help' for information on a command.");

    // Command run-base
    if (_args[1] == "run-base") {

        _assert(!_readProfileConfig(_args[{"-P", "--profile"}]), "Invalid profile");
        _source_dir = _args[{"-S", "--source-dir"}];
        _test_dir = _args[{"-T", "--test-dir"}];

        _cache_testsuite = _args.contains({"-c", "--cache-testsuite"});
        _thread_num = _args.contains("--thread") ? std::stoul(_args["--thread"]) : 1;
        _cmdRunBase();
    }

    // Command run-pafl
    else if (_args[1] == "run-pafl") {

        _assert(!_readProfileConfig(_args[{"-P", "--profile"}]), "Invalid profile");
        _source_dir = _args[{"-S", "--source-dir"}];
        _test_dir = _args[{"-T", "--test-dir"}];
        
        _cache_testsuite = _args.contains({"-c", "--cache-testsuite"});
        _thread_num = _args.contains("--thread") ? std::stoul(_args["--thread"]) : 1;
        _log = _args.contains({"-l", "-log"});
        _cmdRunPafl();
    }

    // Command train
    else if (_args[1] == "train") {

        _assert(!_readProfileConfig(_args[{"-P", "--profile"}]), "Invalid profile");
        _source_dir = _args[{"-S", "--source-dir"}];
        _test_dir = _args[{"-T", "--test-dir"}];
        _oracle_path = _args[{"-O", "--oracle-path"}];

        _cache_testsuite = _args.contains({"-c", "--cache-testsuite"});
        _thread_num = _args.contains("--thread") ? std::stoul(_args["--thread"]) : 1;
        _log = _args.contains({"-l", "-log"});
        _cmdTrain();
    }

    // Command profile
    else if (_args[1] == "profile") {

        _assert(_args.size() == 5 || _args.size() == 6, "Invalid arguments\nRun 'pafl help' for information on a command.");
        _cmdProfile(_args[2], _args[3], _args[4], _args.size() == 6 ? _args[5] : "11111", _directory);
    }

    // Command deletion of profile
    else if (_args[1] == "profile-rm") {

        _assert(_args.size() == 3, "Invalid arguments\nRun 'pafl help' for information on a command.");
        _cmdProfileRemove(_args[2], _directory);
    }

    // Command deletion of profile's FL model
    else if (_args[1] == "profile-reset") {

        _assert(_args.size() == 3, "Invalid arguments\nRun 'pafl help' for information on a command.");
        _cmdProfileReset(_args[2], _directory);
    }

    // Command caching
    else if (_args[1] == "caching") {

        _assert(_args.size() == 4, "Invalid arguments\nRun 'pafl help' for information on a command.");
        _cmdCaching(_args[2], _args[3]);
    }

    // Command to-covmatrix-from-cache
    else if (_args[1] == "to-covmatrix-from-cache") {

        _assert(_args.size() == 5, "Invalid arguments");
        _cmdToCovmatrix(_args[2], _args[3], _args[4]);
    }

    // Command help
    else if (_args[1] == "help")
        _cmdHelp();

    // Otherwise
    else
        _assert(false, "Command option is not avaliable.\nRun 'pafl help' for information on a command.");
}



int Pipeline::_cmdRunBase()
{
    _printProfile();
    
    // Load test suite
    if (_cache_testsuite) {

        if (_loadCache(_suite.get(), _test_dir))
            return 1;
    }
    else if (_load(_suite.get(), _test_dir))
        return 1;
    
    // Run
    std::cout << "Localizing ...\n";
    _method->setSus(_suite.get());
    _suite->rank();
    auto path(_createDirectory(_test_dir / _PAFL_ / (_profile + "-base")) / "ranking.json");
    StringEditor::write(path.c_str(), _suite->toJson());

    std::cout << "Done.\n";
    return 0;
}



int Pipeline::_cmdRunPafl()
{
    StopWatch<std::chrono::milliseconds> timer;
    timer.start();
    _printProfile();

    // Load FL model
    FLModel model;
    readCereal(model, _directory / PROFILE_DIRECTORY / _profile / MODEL_BIN);
    model.setUpdaterDepth(_depth);
    std::cout << " model version: " << model.getMaxID() << "\n>\n";

    // Load test suite
    if (_cache_testsuite) {

        if (_loadCache(_suite.get(), _test_dir))
            return 1;
    }
    else if (_load(_suite.get(), _test_dir))
        return 1;

    // Make statement graphs
    auto graphs(_makeGraphs());

    // Run localizing phase of Project-Aware FL
    std::cout << "Localizing ...\n";
    _method->setSus(_suite.get());
    if (model.getMaxID() > 1) {

        _normalizer->normalize(_suite.get());
        model.localize(_suite.get(), graphs);
        if (_log) {// Logging result
        
            auto path(_createDirectory(_directory / PROFILE_DIRECTORY / _profile / LOG_DIRECTORY));
            auto log_file = std::to_string(model.getMaxID()) + "_localize";
            StringEditor::write((path / log_file).c_str(), FLModel::convertResultToString(model.localize(_suite.get(), graphs)));
        }
        else
            model.localize(_suite.get(), graphs);
    }
    _suite->rank();
    auto path(_createDirectory(_test_dir / _PAFL_ / (_profile + "-pafl")) / "ranking.json");
    StringEditor::write(path.c_str(), _suite->toJson());
    
    std::cout << "Done.\n";
    if (_log) {// Logging time

        auto path(_createDirectory(_directory / PROFILE_DIRECTORY / _profile / TIME_LOG_DIRECTORY));
        auto log_file = std::to_string(model.getMaxID()) + "_localize";
        StringEditor::write((path / log_file).c_str(), std::to_string(timer.lap()));
    }
    return 0;
}



int Pipeline::_cmdTrain()
{
    StopWatch<std::chrono::milliseconds> timer;
    timer.start();
    _printProfile();

    // Load FL model
    FLModel model;
    readCereal(model, _directory / PROFILE_DIRECTORY / _profile / MODEL_BIN);
    model.setUpdaterDepth(_depth);
    std::cout << " model version: " << model.getMaxID() << "\n";
    std::cout << " updater depth: " << (int)_depth.target_depth << _depth.pred_depth << _depth.succ_depth << _depth.parent_depth << _depth.child_depth << "\n>\n";

    // Load test suite
    if (_cache_testsuite) {

        if (_loadCache(_suite.get(), _test_dir))
            return 1;
    }
    else if (_load(_suite.get(), _test_dir))
        return 1;

    // Load fault oracle
    rapidjson::Document doc;
    doc.Parse(StringEditor::read(_oracle_path.c_str()).c_str());
    auto fault(_suite->makeFalutSet(doc));

    // Make or Load statement graphs
    auto graphs(_loadGraphs());

    // Run training phase of Project-Aware FL
    std::cout << "Training ...\n";
    _method->setSus(_suite.get());
    _normalizer->normalize(_suite.get());
    if (_log) {// Logging result
        
        auto path(_createDirectory(_directory / PROFILE_DIRECTORY / _profile / LOG_DIRECTORY));
        auto log_file = std::to_string(model.getMaxID()) + "_train";
        StringEditor::write((path / log_file).c_str(), FLModel::convertResultToString(model.train(_suite.get(), graphs, fault, _thread_num)));
    }
    else
        model.train(_suite.get(), graphs, fault, _thread_num);

    // Save FL model
    writeCereal(model, _directory / PROFILE_DIRECTORY / _profile / MODEL_BIN);
    std::cout << "Done.\n";

    if (_log) {// Logging time

        auto path(_createDirectory(_directory / PROFILE_DIRECTORY / _profile / TIME_LOG_DIRECTORY));
        auto log_file = std::to_string(model.getMaxID()) + "_train";
        StringEditor::write((path / log_file).c_str(), std::to_string(timer.lap()));
    }
    return 0;
}



void Pipeline::_cmdProfile(const std::string& profile, const std::string& language, const std::string& method, const std::string& updater, const std::filesystem::path& directory)
{
    std::string buffer;
    buffer.append("{ \"language\": \"").append(language).append("\", ");
    buffer.append("\"method\": \"").append(method).append("\", ");
    buffer.append("\"updater-depth\": \"").append(updater).append("\" }");
    auto path(_createDirectory(directory / PROFILE_DIRECTORY / profile) / PROFILE_CONFIG);
    StringEditor::write(path.c_str(), buffer);
}



void Pipeline::_cmdProfileRemove(const std::string& profile, const std::filesystem::path& directory)
{
    auto path(directory / PROFILE_DIRECTORY / profile);
    if (std::filesystem::exists(path)) {

        std::filesystem::remove_all(path);
        std::cout << ('"'+profile+'"') << " is deleted.\n";
    }
    else
        std::cout << ('"'+profile+'"') << " is not existed.\n";
}



void Pipeline::_cmdProfileReset(const std::string& profile, const std::filesystem::path& directory)
{
    auto path(directory / PROFILE_DIRECTORY / profile / MODEL_BIN);
    if (std::filesystem::exists(path)) {

        std::filesystem::remove(path);
        std::cout << ('"'+profile+'"') << " model is deleted.\n";
    }
    else
        std::cout << ('"'+profile+'"') << " model is not existed.\n";
}



int Pipeline::_cmdCaching(const std::string& language, const std::filesystem::path& test_dir)
{
    auto suite = _makeTestSuite(_identifyLanguage(language));
    if (_load(suite.get(), test_dir))
        return 1;
    writeCereal(*suite, _createDirectory(test_dir / _PAFL_) / TESTSUITE_BIN);
    return 0;
}



void Pipeline::_cmdToCovmatrix(const std::string& language, const std::filesystem::path& test_dir, const std::filesystem::path& output_dir)
{
}



void Pipeline::_cmdHelp()
{
    auto message = 
R"(help: print this help

run-base: run baseline fault localization
    -P, --profile [prf]             | select profile
    -S, --source-dir [dir]          | program source directory
    -T, --test-dir [dir]            | testsuite directory
    --suspiciousness-path [path]    | path of suspiciousness data (when method is custom)
    -c, --cache-testsuite           | load testsuite from cache. path is "{testsuite directory}/__pafl__/cache.cereal"

run-pafl: run Project-Aware Fault Localization
    -P, --profile [prf]             | select profile
    -S, --source-dir [dir]          | program source directory
    -T, --test-dir [dir]            | testsuite directory
    --suspiciousness-path [path]    | path of suspiciousness data (when method is custom)
    --thread [num]                  | set the number of thread to use. default is 1
    -c, --cache-testsuite           | load testsuite from cache. path is "{testsuite directory}/__pafl__/cache.cereal"
    -l, --log                       | store log in directory "{testsuite directory}/__pafl__/{prf}/log/"

train: train pafl profile using fault location
    -P, --profile [prf]             | select profile
    -S, --source-dir [dir]          | program source directory
    -T, --test-dir [dir]            | testsuite directory
    -O, --oracle-path [path]        | path of fault location oracle
    --thread [num]                  | set the number of thread to use. default is 1
    -c, --cache-testsuite           | load testsuite from cache. path is "{testsuite directory}/__pafl__/cache.cereal"
    -l, --log                       | store log in directory "{testsuite directory}/__pafl__/{prf}/log/"

profile: create or edit profile
    profile [prf] [lang] [method]   | configuration of profile's path is "profile/{prf}/config.json"
        lang: cpp, python, java
        method: tarantula, ochiai, dstar, barinel, custom

profile-rm: delete profile
    profile-rm [prf]                | profile's directory is "profile/{prf}"

profile-reset: delete Project-Aware Fault Localization model
    profile-reset [prf]             | model of profile's path is "profile/{prf}/model.cereal"

caching: caching testsuite
    caching [lang] [dir]            | cache's path is "{testsuite directory}/__pafl__/cache.cereal"
        lang: cpp, python, java
        
to-covmatrix-from-cache
    to-covmatrix-from-cache [lang] [testsuite-dir] [output-dir]
)";
    std::cout.write(message, std::strlen(message));
}



void Pipeline::_printProfile() const
{
    std::string buffer;
    buffer.append(">\n");
    StringEditor::append(buffer.append(" profile: "), _profile).push_back('\n');
    buffer.append(" source directory: ").append(_source_dir).push_back('\n');
    buffer.append(" test suite directory: ").append(_test_dir).push_back('\n');
    buffer.append(">\n");
    std::cout.write(buffer.c_str(), buffer.size());
}



const std::filesystem::path& Pipeline::_createDirectory(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path) && !path.empty()) {
        
        _createDirectory(path.parent_path());
        std::filesystem::create_directory(path);
    }
    return path;
}



Pipeline::Language Pipeline::_identifyLanguage(std::string language)
{
    std::transform(language.begin(), language.end(), language.begin(), tolower);
    if (language == "cpp" || language == "c" || language == "c++")
        return Language::CPP;
    else if (language == "python")
        return Language::PYTHON;
    else if (language == "java")
        return Language::JAVA;
    return Language::OTHERWISE;
}



int Pipeline::_readProfileConfig(const std::string& profile)
{
    _profile = profile;
    rapidjson::Document doc;
    doc.Parse(StringEditor::read((_directory / PROFILE_DIRECTORY / profile / PROFILE_CONFIG).c_str()).c_str());

    // Set test suite & graphs builder
    switch (_identifyLanguage(doc["language"].GetString())) {

    case Language::CPP:
        _suite.reset(new TestSuiteGcov());
        _builder.reset(new CppBuilder(_args[{"-S", "--source-dir"}]));
        break;
    case Language::PYTHON:
        _suite.reset(new TestSuitePycov());
        _builder.reset(new PyBuilder());
        break;
    default:
        return 1;
    }

    // Set method
    std::string method(doc["method"].GetString());
    std::transform(method.begin(), method.end(), method.begin(), tolower);
    if (method == "tarantula")
        _method.reset(new Tarantula());
    else if (method == "ochiai")
        _method.reset(new Ochiai());
    else if (method == "dstar")
        _method.reset(new Dstar());
    else if (method == "barinel")
        _method.reset(new Barinel());
    else if (method == "ones")
        _method.reset(new Ones());
    else if (method == "custom") {

        if (!_args.contains("--suspiciousness-path"))
            return 1;
        _method.reset(new CusmtomMethod(_args["--suspiciousness-path"]));
    }
    else
        return 1;

    // Set updater depth
    auto depth = doc["updater-depth"].GetString();
    _depth.target_depth = depth[0] - '0';
    _depth.pred_depth = depth[1] - '0';
    _depth.succ_depth = depth[2] - '0';
    _depth.parent_depth = depth[3] - '0';
    _depth.child_depth = depth[4] - '0';
    return 0;
}



stmt_graph::Graph::vector_t Pipeline::_makeGraphs() const
{
    std::cout << "Creating statement graphs ...\n";
    stmt_graph::Graph::vector_t graphs(_suite->maxIndex());

    // single thread
    if (_thread_num <= 1)
        for (TestSuite::index_t index = 0; index != _suite->maxIndex(); ++index) {
            
            std::cout << "  " << _suite->getFileFromIndex(index) << std::endl;
            graphs[index].reset(_builder->build(_source_dir / _suite->getFileFromIndex(index)));
        }
    
    // multi thread
    else {

        BS::thread_pool pool(_thread_num);
        pool.detach_loop<TestSuite::index_t>(0, _suite->maxIndex(),
            [this, &graphs](TestSuite::index_t index)
            {
                graphs[index].reset(_builder->build(_source_dir / _suite->getFileFromIndex(index)));
            });
        pool.wait();
    }
    
    // Saving statements graphs
    std::cout << "Saving statement graphs ...\n";
    auto graphs_dir(_createDirectory(_test_dir / _PAFL_ / GRAPH_DIRECTORY));
    for (TestSuite::index_t index = 0; index != _suite->maxIndex(); ++index)
        StringEditor::write((graphs_dir / (std::to_string(index) + ".json")).c_str(),
            graphs.at(index)->toJSON(_suite->getFileFromIndex(index)));
    return graphs;
}



stmt_graph::Graph::vector_t Pipeline::_loadGraphs() const
{
    std::cout << "Loading statement graphs ...";
    auto graphs_dir(_test_dir / _PAFL_ / GRAPH_DIRECTORY);
    if (!std::filesystem::exists(graphs_dir)) {

        std::cout << " is failed\n";
        return _makeGraphs();
    }
    
    // Load cache
    stmt_graph::Graph::vector_t graphs(_suite->maxIndex());
    for (TestSuite::index_t index = 0; index != _suite->maxIndex(); ++index) {

        auto path(graphs_dir / (std::to_string(index) + ".json"));
        if (!std::filesystem::exists(path)) {

            std::cout << " is failed\n";
            return _makeGraphs();
        }
        graphs[index].reset(new stmt_graph::Graph());
        rapidjson::Document doc;
        doc.Parse(StringEditor::read(path.c_str()).c_str());
        graphs[index]->fromJSON(doc);
    }

    std::cout.put('\n');
    return graphs;
}



std::unique_ptr<TestSuite> Pipeline::_makeTestSuite(Pipeline::Language lang)
{
    switch (lang) {

    case Language::CPP:
        return std::make_unique<TestSuiteGcov>();
    case Language::PYTHON:
        return std::make_unique<TestSuitePycov>();
    default:
        return nullptr;
    }
}



int Pipeline::_load(TestSuite* suite, const std::filesystem::path& test_dir)
{
    std::cout << "Loading test suite ...\n";
    std::filesystem::path path;
    
    for (int i = 1; std::filesystem::exists(path = test_dir / std::to_string(i)); ++i) {
        
        std::cout << "  case " << i << std::endl;
        auto buffer(StringEditor::read((path / (std::to_string(i) + ".test")).c_str()));
        rapidjson::Document doc;
        doc.Parse(StringEditor::read((path / "summary.json").c_str()).c_str());

        // failing test case
        if (buffer.starts_with("fail"))
            suite->addTestCase(doc, false);
        // passing test case
        else if (buffer.starts_with("pass"))
            suite->addTestCase(doc, true);
        else
            return 1;
    }
    return 0;
}



int Pipeline::_loadCache(TestSuite* suite, const std::filesystem::path& test_dir)
{
    std::cout << "Loading test suite cache ...";
    if (readCereal(*suite, test_dir / _PAFL_ / TESTSUITE_BIN)) {

        std::cout << " is failed\n";
        return _load(suite, test_dir);
    }
    std::cout.put('\n');
    return 0;
}
}
