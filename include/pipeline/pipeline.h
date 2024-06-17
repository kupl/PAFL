#ifndef __MODEL_PIPELINE_H__
#define __MODEL_PIPELINE_H__

#include <iostream>
#include <thread_pool/BS_thread_pool.hpp>
#include <cereal/archives/binary.hpp>

#include "testsuite/index.h"
#include "argparser.h"
#include "pipeline/method.h"
#include "pipeline/normalizer.h"
#include "pipeline/builder.h"
#include "model/flmodel.h"
#include "stopwatch.h"


namespace PAFL
{
class Pipeline
{
static constexpr std::string_view HELP = 
R"(
help: print this help

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
    profile ... [updater]           | Set depth of updater
        updater: 5 number sequence (11111, 11012, ... ). default is '11111'

profile-rm: delete profile
    profile-rm [prf]                | profile's directory is "profile/{prf}"

profile-reset: delete Project-Aware Fault Localization model
    profile-reset [prf]             | model of profile's path is "profile/{prf}/model.cereal"

caching: caching testsuite
    caching [lang] [dir]            | cache's path is "{testsuite directory}/__pafl__/cache.cereal"
        lang: cpp, python, java

to-covmatrix-from-cache
    to-covmatrix-from-cache [lang] [testsuite-dir] [oracle-path] [output-dir]
)";



public:
    Pipeline(int argc, const char *argv[]) :
        _args(argc, argv), _directory(_args.getExecutablePath().parent_path().parent_path().parent_path()), _normalizer(new CbrtNormalizer()) {}
    void run();

    template <class T>
    static int readCereal(T& val, const std::filesystem::path& path);
    template <class T>
    static void writeCereal(T& val, const std::filesystem::path& path);

private:
    enum class Language { CPP, PYTHON, JAVA, OTHERWISE };
    static constexpr std::string_view _PAFL_ = "__pafl__";
    static constexpr std::string_view PROFILE_CONFIG = "config.json";
    static constexpr std::string_view MODEL_BIN = "model.cereal";
    static constexpr std::string_view TESTSUITE_BIN = "cache.cereal";
    static constexpr std::string_view PROFILE_DIRECTORY = "profile";
    static constexpr std::string_view GRAPH_DIRECTORY = "graphs";
    static constexpr std::string_view LOG_DIRECTORY = "logs";
    static constexpr std::string_view TIME_LOG_DIRECTORY = "time";

private:
    int _cmdRunBase();
    int _cmdRunPafl();
    int _cmdTrain();
    static void _cmdProfile(const std::string& profile, const std::string& language, const std::string& method, const std::string& updater, const std::filesystem::path& directory);
    static void _cmdProfileRemove(const std::string& profile, const std::filesystem::path& directory);
    static void _cmdProfileReset(const std::string& profile, const std::filesystem::path& directory);
    static int _cmdCaching(const std::string& language, const std::filesystem::path& test_dir);
    static int _cmdToCovmatrix(const std::filesystem::path& test_dir, const std::filesystem::path& oracle_path, const std::filesystem::path& output_dir);
    static void _cmdHelp() {
        std::cout << HELP;
    }

    void _printProfile() const;

private:
    static void _assert(bool condition, const char* msg) {
        if (!condition) {std::cerr.write(msg, std::strlen(msg)); throw;}
    }
    static const std::filesystem::path& _createDirectory(const std::filesystem::path& path);
    static Language _identifyLanguage(std::string language);

    int _readProfileConfig(const std::string& profile);
    stmt_graph::Graph::vector_t _makeGraphs() const;
    stmt_graph::Graph::vector_t _loadGraphs() const;
    static std::unique_ptr<TestSuite> _makeTestSuite(Language lang);
    static int _load(TestSuite* suite, const std::filesystem::path& test_dir);
    static int _loadCache(TestSuite* suite, const std::filesystem::path& test_dir);
    
private:
    const ArgParser _args;
    const std::filesystem::path _directory;

private:
    std::string _profile;
    std::unique_ptr<TestSuite> _suite;
    std::unique_ptr<Method> _method;
    Updater::Depth _depth;
    std::unique_ptr<BuilderBase> _builder;
    std::unique_ptr<Normalizer> _normalizer;
    std::filesystem::path _source_dir;
    std::filesystem::path _test_dir;
    std::filesystem::path _oracle_path;
    bool _cache_testsuite;
    std::filesystem::path _sus_path;
    size_t _thread_num;
    bool _log;
};
}
#include "pipeline/pipeline.hpp"
#endif
