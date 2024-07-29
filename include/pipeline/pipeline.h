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
Commands:
  help                             Print this help message

  run-base                         Run baseline fault localizer
    -P, --profile <prf>            Select profile
    -S, --source-dir <dir>         Program source directory
    -T, --test-dir <dir>           Test suite directory
    --suspiciousness-path <path>   Path to suspiciousness data (optional, required if method is 'custom')
    -c, --cache-testsuite          Load test suite from cache (optional). Path: "<test-dir>/__pafl__/cache.cereal"

  run-pafl                         Run PAFL
    -P, --profile <prf>            Select profile
    -S, --source-dir <dir>         Program source directory
    -T, --test-dir <dir>           Test suite directory
    --suspiciousness-path <path>   Path to suspiciousness data (optional, required if method is 'custom')
    --thread <num>                 Set the number of threads to use (optional, default: 1)
    -c, --cache-testsuite          Load test suite from cache (optional). Path: "<test-dir>/__pafl__/cache.cereal"
    -l, --log                      Enable logging and save logs (optional). Path: "<test-dir>/__pafl__/<prf>/log/"

  train                            Train model of profile using fault locations oracle
    -P, --profile <prf>            Select profile
    -S, --source-dir <dir>         Program source directory
    -T, --test-dir <dir>           Test suite directory
    -O, --oracle-path <path>       Path to fault locations oracle
    --thread <num>                 Set the number of threads to use (optional, default: 1)
    -c, --cache-testsuite          Load test suite from cache (optional). Path: "<test-dir>/__pafl__/cache.cereal"
    -l, --log                      Enable logging and save logs (optional). Path: "<test-dir>/__pafl__/<prf>/log/"

  profile                          Create or edit profile
    profile <prf> <lang> <method>  Profile configuration. Path: "profile/<prf>/config.json"
      lang:   cpp, python, java
      method: tarantula, ochiai, dstar, barinel, jaccard, custom

  profile-rm                       Delete profile
    profile-rm <prf>

  profile-reset                    Delete model of profile (reset model version to 0)
    profile-reset <prf>

  caching                          Cache coverage data of test suite for faster loading
    caching <lang> <dir>           Cache path. Path: "<test-dir>/__pafl__/cache.cereal"
      lang:   cpp, python, java

  to-covmatrix-from-cache          Generate coverage matrix from cached test suite
    to-covmatrix-from-cache <lang> [testsuite-dir] [oracle-path] [output-dir]
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
    static constexpr std::string_view TREE_DIRECTORY = "trees";
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
    aggregated_ast::Ast::vector_t _makeTrees() const;
    aggregated_ast::Ast::vector_t _loadTrees() const;
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
