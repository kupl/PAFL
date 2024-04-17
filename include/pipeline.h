#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <thread_pool/BS_thread_pool.hpp>

#include "ui.h"
#include "flmodel.h"
#include "utility.h"
#include "tokentree/cpptokentree.h"


namespace PAFL
{
class Pipeline
{
public:
    Pipeline(int argc, const char *argv[]);
    void run();
    void makeMatrix(const fs::path& manybugs);

private:
    using time_vector = std::vector<time_t::rep>;

private:
    TestSuite* makeGcovTest()                                       { return new TestSuiteGcov(); }
    TestSuite* makePycovTest()                                      { return new TestSuitePycov(); }

    void loadTestSuite();
    void loadCachedTestSuite();

    std::unique_ptr<BaseLogger> makeEmptyLogger()                   { return nullptr; }
    std::unique_ptr<BaseLogger> makeLogger();

    TokenTree* buildCppTree(const fs::path& file, index_t index)    { return new CppTokenTree(file, _ui.getDirectoryPath() / "bin", index, _macro, _macro_size); }
    TokenTree* buildPyTree(const fs::path& file, index_t index)     { return new TokenTree(file, _ui.getDirectoryPath() / "bin", _ui.getDirectoryPath() / "pytree.py"); }

    void makeTreeParallel(TokenTree::Vector& tkt_vector, size_t thread_size = 1);

    void localizeWithBase(FLModel& model, time_vector& time_vec);
    void localizeWithPAFL(FLModel& model, time_vector& time_vec);

    void logNoneTime(time_vector&) {}
    void logBaseTime(time_vector& time_vec);
    void logPAFLTime(time_vector& time_vec);

private:
    void _updateInfo(TestSuite* suite, Method* method, size_t iter) { _suite = suite; _method = method; _iter = iter; }
    void _updateInfo(TestSuite* suite, size_t iter)                 { _suite = suite; _iter = iter; }
    void _logTime(const fs::path& path, time_t::rep time)           { std::ofstream(path) << time; }


private:
    const UI _ui;
    StopWatch<time_t> _timer;
    
    const Normalizer* _normalizer;
    decltype(&Pipeline::makeGcovTest) _test_factory;
    decltype(&Pipeline::loadTestSuite) _loader;
    decltype(&Pipeline::makeEmptyLogger) _logger_factory;
    decltype(&Pipeline::buildCppTree) _builder;
    decltype(&Pipeline::localizeWithBase) _localizer;
    decltype(&Pipeline::logNoneTime) _time_logger;
    unsigned long long _history;

private:
    // Info
    TestSuite* _suite;
    Method* _method;
    size_t _iter;

    // C/C++ macro
    std::list<std::string> _macro;
    size_t _macro_size;
};
}
#endif
