#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include "ui.h"
#include "flmodel.h"
#include "utility.h"
#include "tokentree/tokentree_cpp.h"
#include "tokentree/tokentree_py.h"


namespace PAFL
{
class Pipeline
{
public:
    Pipeline(int argc, char *argv[]);
    void run();
    void makeMatrix(const fs::path& manybugs);

private:
    using time_vector = std::vector<time_t::rep>;

private:
    TestSuite* makeGcovTest()                                   { return new TestSuiteGcov(); }
    TestSuite* makePycovTest()                                  { return new TestSuitePycov(); }

    void loadTestSuite();
    void loadCachedTestSuite();

    std::unique_ptr<BaseLogger> makeEmptyLogger()               { return nullptr; }
    std::unique_ptr<BaseLogger> makeLogger();

    void buildCppTree(TokenTree*& tree, const fs::path& file)   { tree = new TokenTreeCpp(file, _matcher); }
    void buildPyTree(TokenTree*& tree, const fs::path& file)    { tree = new TokenTreePy(file, _matcher, _ui.getDirectoryPath() / "pytree.py"); }

    void localizeWithBase(FLModel& model, time_vector& time_vec);
    void localizeWithPAFL(FLModel& model, time_vector& time_vec);

    void logNoneTime(time_vector&) {}
    void logBaseTime(time_vector& time_vec);
    void logPAFLTime(time_vector& time_vec);

    void setTarantula()                                         { _suite->setBaseSus(Coef::Tarantula); }
    void setOchiai()                                            { _suite->setBaseSus(Coef::Ochiai); }
    void setDstar()                                             { _suite->setBaseSus(Coef::Dstar); }
    void setBarinel()                                           { _suite->setBaseSus(Coef::Barinel); }
    void setOnes()                                              { _suite->setBaseSus(Coef::Ones); }
    void setCNN()                                               {}
    void setRNN()                                               {}
    void setMLP()                                               {}

private:
    void _updateInfo(TestSuite* suite, UI::Method method, size_t iter)  { _suite = suite; _method = method; _iter = iter; }
    void _updateInfo(TestSuite* suite, size_t iter)                     { _suite = suite; _iter = iter; }
    void _logTime(const fs::path& path, time_t::rep time)          { std::ofstream(path) << time; }


private:
    const UI _ui;
    StopWatch<time_t> _timer;
    std::shared_ptr<PAFL::TokenTree::Matcher> _matcher;

    decltype(&Pipeline::makeGcovTest) _test_factory;
    decltype(&Pipeline::loadTestSuite) _loader;
    decltype(&Pipeline::makeEmptyLogger) _logger_factory;
    decltype(&Pipeline::setOchiai) _setter;
    decltype(&Pipeline::buildCppTree) _builder;
    decltype(&Pipeline::localizeWithBase) _localizer;
    decltype(&Pipeline::logNoneTime) _time_logger;

    const std::map<UI::Method, decltype(&Pipeline::setOchiai)> _method_setter_map;
    const std::map<UI::Method, std::string> _method_string_map;

private: // Info
    TestSuite* _suite;
    UI::Method _method;
    size_t _iter;
};
}
#endif
