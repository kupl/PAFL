#include "pipeline.h"

namespace PAFL
{
Pipeline::Pipeline(int argc, char *argv[]) :
    _ui(argc, argv),
    _matcher(std::make_shared<TokenTree::Matcher>()),

    _normalizer(_ui.getNormalizer()),
    _loader(_ui.hasCache() ? &Pipeline::loadCachedTestSuite : &Pipeline::loadTestSuite),
    _logger_factory(_ui.hasDebugger() ? &Pipeline::makeLogger : &Pipeline::makeEmptyLogger),
    _localizer(_ui.isProjectAware() ? &Pipeline::localizeWithPAFL : &Pipeline::localizeWithBase),
    _time_logger(!_ui.hasDebugger() ? &Pipeline::logNoneTime : 
                (_ui.isProjectAware() ? &Pipeline::logPAFLTime : &Pipeline::logBaseTime))
{
    switch (_ui.getLanguage()) {
    
    case PrgLang::CPP:
        _test_factory = &Pipeline::makeGcovTest;
        _builder = &Pipeline::buildCppTree;
        return;
    
    case PrgLang::PYTHON:
        _test_factory = &Pipeline::makePycovTest;
        _builder = &Pipeline::buildPyTree;
        return;

    case PrgLang::JAVA:
        return;
    }
}



void Pipeline::run()
{
    std::vector<TestSuite*> suite;
    suite.reserve(_ui.numVersion());
    time_vector loading_time(_ui.numVersion(), 0);

    // Load Test cases
    for (size_t iter = 0; iter != _ui.numVersion(); iter++) {
        
        _timer.restart();

            _updateInfo(suite.emplace_back((this->*_test_factory)()), iter);
            (this->*_loader)();

        loading_time[iter] = _timer.stop();
    }

    // Localize
    createDirRecursively(_ui.getDirectoryPath() / "coverage");
    for (auto& method : _ui.getMethodList()) {

        time_vector running_time(loading_time);

            FLModel model;
            for (size_t iter = 0; iter != _ui.numVersion(); iter++) {
                
                _updateInfo(suite[iter], method.get(), iter);
                model.setLogger((this->*_logger_factory)());
                (this->*_localizer)(model, running_time);
            }

        (this->*_time_logger)(running_time);
    }

    // Destroy test suite
    for (auto ptr : suite)
        delete ptr;
}



void Pipeline::makeMatrix(const fs::path& manybugs)
{
    // Load Test cases
    for (size_t iter = 0; iter != _ui.numVersion(); iter++) {

        auto suite = (this->*_test_factory)();
        _updateInfo(suite, iter);
        (this->*_loader)();
        suite->toCovMatrix(createDirRecursively(manybugs / (_ui.getProject() + "-" + std::to_string(iter + 1))), _ui.getFaultLocation(iter));
        delete suite;
    }
}



void Pipeline::loadTestSuite()
{
    // Collect Coverage data
    for (auto& item : _ui.getCoverageList(_iter))
        _suite->addTestCase(item.first, item.second, _ui.getExtensions());
    std::cout << _ui.getProject() << '-' << _ui.getVersion(_iter) << " is loaded\n\n";
}



void Pipeline::loadCachedTestSuite()
{
    const auto path(createDirRecursively(_ui.getDirectoryPath() / "cache" / _ui.getProject())
                    / (std::string("v") + std::to_string(_ui.getVersion(_iter)) + ".txt"));
    // Caching failure
    if (_suite->loadCache(path)) {

        loadTestSuite();
        _suite->caching(path);
    }
    // Caching success
    else
        std::cout << _ui.getProject() << '-' << _ui.getVersion(_iter) << " is loaded from cache\n\n";
}



std::unique_ptr<BaseLogger> Pipeline::makeLogger()
{
    return std::make_unique<FLModel::Logger>(createDirRecursively(
        _ui.getDirectoryPath() / "log/model" / (std::string("pafl-") + _method->getName()) / _ui.getProject())
        / std::to_string(_iter + 1), _timer);
}



void Pipeline::localizeWithBase(FLModel&, time_vector& time_vec)
{
    _timer.restart();

        std::cout << '\n' << _ui.getProject() << " : " << _method->getName() << '\n';
        std::cout << "[ " << (_iter + 1) << " ] -> Localizing\n";
        _method->setBaseSus(_suite, _ui.getProject(), std::to_string(_ui.getVersion(_iter)), std::to_string(_iter + 1));
        _suite->rank();

        // Save as json
        std::cout << "[ " << (_iter + 1) << " ] -> Saving\n";
        fs::path dir(createDirRecursively(_ui.getDirectoryPath() / "coverage" / _method->getName() / _ui.getProject()));
        _suite->toJson(dir / (std::to_string(_iter + 1) + ".json"));

    time_vec[_iter] += _timer.stop();
}



void Pipeline::localizeWithPAFL(FLModel& model, time_vector& time_vec)
{
    _timer.restart();

        std::cout << "Load base sus\n";
        _method->setBaseSus(_suite, _ui.getProject(), std::to_string(_ui.getVersion(_iter)), std::to_string(_iter + 1));
        _normalizer->normalize(_suite);

        // Make token tree
        TokenTree::Vector tkt_vector(_suite->maxIndex());
        for (index_t idx = 0; idx != _suite->maxIndex(); idx++)
            (this->*_builder)(tkt_vector[idx], _ui.getFilePath(_iter, _suite->getFileFromIndex(idx)));

        // New sus of FL Model
        std::cout << '\n' << _ui.getProject() << " : " << _method->getName() << "-pafl\n";
        std::cout << "[ " << (_iter + 1) << " ] -> Localizing\n";
        model.localize(*_suite, tkt_vector);

        // Save as json
        std::cout << "[ " << (_iter + 1) << " ] -> Saving\n";
        fs::path dir(createDirRecursively(_ui.getDirectoryPath() / "coverage" / (std::string("pafl-") + _method->getName()) / _ui.getProject()));
        _suite->toJson(dir / (std::to_string(_iter + 1) + ".json"));

    time_vec[_iter] += _timer.stop();
        

    _timer.restart();

        // Learning
        if (_iter + 1 != _ui.numVersion()) {

            std::cout << "Learning...\n";
            model.step(*_suite, tkt_vector, _ui.getFaultLocation(_iter));
        }
        // Destroy token tree
        for (auto ptr : tkt_vector)
            delete ptr;

    time_vec[_iter + 1] += _timer.stop();
}



void Pipeline::logBaseTime(time_vector& time_vec)
{
    const auto dir(createDirRecursively(
        _ui.getDirectoryPath() / "log/time" / _method->getName() / _ui.getProject()));
    for (auto i = 0; i != time_vec.size(); ++i)
        _logTime(dir / (std::to_string(i + 1) + ".txt"), time_vec[i]);
}



void Pipeline::logPAFLTime(time_vector& time_vec)
{
    const auto dir(createDirRecursively(
        _ui.getDirectoryPath() / "log/time" / (std::string("pafl-") + _method->getName()) / _ui.getProject()));
    for (auto i = 0; i != time_vec.size(); ++i)
        _logTime(dir / (std::to_string(i + 1) + ".txt"), time_vec[i]);
}
}
