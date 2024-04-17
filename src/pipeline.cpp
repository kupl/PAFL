#include "pipeline.h"

namespace PAFL
{
Pipeline::Pipeline(int argc, const char *argv[]) :
    _ui(argc, argv),
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
            _history = 0;
            for (size_t iter = 0; iter != _ui.numVersion(); iter++) {
                
                _updateInfo(suite[iter], method.get(), iter);
                model.setLogger((this->*_logger_factory)());
                _history++;
                (this->*_localizer)(model, running_time);
                std::cout << '\n';
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
                    / (std::string("v") + std::to_string(_ui.getVersion(_iter)) + ".cereal"));
    // Caching failure
    if (_suite->readCache(path)) {

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



void Pipeline::makeTreeParallel(TokenTree::Vector& tkt_vector, size_t thread_size)
{
    // Single thread
    if (thread_size <= 1) {

        // Init macro info
        _macro.clear();
        _macro_size = 0;
        // Collect macro
        if (_ui.getLanguage() == PrgLang::CPP) {

            auto bin_path(_ui.getDirectoryPath() / "bin");
            size_t iter = 0;

            for (auto entry_iter = fs::recursive_directory_iterator(_ui.getProjectPath(_iter)); entry_iter != fs::recursive_directory_iterator(); ++entry_iter) {

                const auto& path = entry_iter->path();
                // Exclude subdirectory {tests, test} from iteration
                if (path.parent_path() == _ui.getProjectPath(_iter))
                    if (path.filename() == "tests" || path.filename() == "test") {
                        entry_iter.disable_recursion_pending();
                        continue;
                    }
                
                auto extension(path.extension().string());
                if (extension == ".h" || extension == ".hpp")
                    _macro_size += _macro.emplace_back(CppTokenTree::collectMacro(path, bin_path, std::to_string(iter++) + ".hpp")).size();
            }
        }

        // Make tree
        for (index_t idx = 0; idx != _suite->maxIndex(); idx++) {
            tkt_vector[idx] = (this->*_builder)(_ui.getFilePath(_iter, _suite->getFileFromIndex(idx)), idx);
            if (!tkt_vector[idx]->good())
                throw std::range_error("Not good");
        }
    }

    // Multi thread
    else {
        BS::thread_pool pool(thread_size);
        auto future = pool.submit_sequence<size_t>(0, tkt_vector.size(),
            [this, &tkt_vector](const size_t idx)
            {
                tkt_vector[idx] = (this->*_builder)(_ui.getFilePath(_iter, _suite->getFileFromIndex(idx)), idx);
            });
        future.get();
    }
}



void Pipeline::localizeWithBase(FLModel&, time_vector& time_vec)
{
    _timer.restart();

        std::cout << _ui.getProject() << " : " << _method->getName() << " [" << _iter + 1 << "]\n";
        _method->setBaseSus(_suite, _ui.getProject(), std::to_string(_ui.getVersion(_iter)), std::to_string(_iter + 1));
        _suite->rank();
        
        fs::path dir(createDirRecursively(_ui.getDirectoryPath() / "coverage" / _method->getName() / _ui.getProject()));
        _suite->toJson(dir / (std::to_string(_iter + 1) + ".json"));

    time_vec[_iter] += _timer.stop();
}



void Pipeline::localizeWithPAFL(FLModel& model, time_vector& time_vec)
{
    _timer.restart();

        // Make token tree
        std::cout << "[ " << (_iter + 1) << " ] -> Tokenizing ...\n";
        TokenTree::Vector tkt_vector(_suite->maxIndex());
        makeTreeParallel(tkt_vector, 1);
        std::cout << "done" << std::endl;

        // New sus of FL Model
        std::cout << '\n' << _ui.getProject() << " : " << _method->getName() << "-pafl\n";
        std::cout << "[ " << (_iter + 1) << " ] -> Localizing ..." << std::flush;
        _method->setBaseSus(_suite, _ui.getProject(), std::to_string(_ui.getVersion(_iter)), std::to_string(_iter + 1));

        // Save as json
        if (_history <= 2) {
            
            _suite->rank();
            fs::path dir(createDirRecursively(_ui.getDirectoryPath() / "coverage" / (std::string("pafl-") + _method->getName()) / _ui.getProject()));
            _suite->toJson(dir / (std::to_string(_iter + 1) + ".json"));
        }
        _normalizer->normalize(_suite);
        model.localize(*_suite, tkt_vector);

        // Save as json
        if (_history > 2) {

            fs::path dir(createDirRecursively(_ui.getDirectoryPath() / "coverage" / (std::string("pafl-") + _method->getName()) / _ui.getProject()));
            _suite->toJson(dir / (std::to_string(_iter + 1) + ".json"));
        }
        std::cout << " done" << std::endl;

    time_vec[_iter] += _timer.stop();
        

    _timer.restart();

        // Learning
        std::cout << "[ " << (_iter + 1) << " ] -> Learning ..." << std::flush;
        if (_iter + 1 != _ui.numVersion())
            model.step(*_suite, tkt_vector, _ui.getFaultLocation(_iter));

        // Destroy token tree
        for (auto ptr : tkt_vector)
            delete ptr;
        std::cout << " done\n" << std::endl;

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
