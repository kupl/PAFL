#ifndef __FLMODEL_H__
#define __FLMODEL_H__

#include "localizer.h"
#include "predictor.h"
#include "logger.h"



namespace PAFL
{
class FLModel
{
public:
    class Logger;

    FLModel() :
        _iter(0) { _localizers.reserve(256); }

    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec);
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);

    void setLogger(std::unique_ptr<BaseLogger> logger)
        { _logger = std::move(logger); }


private:
    Predictor _predictor;
    std::vector<Localizer> _localizers;

    std::unique_ptr<BaseLogger> _logger;
    size_t _iter;
};

template <class Func>
void normalizeSbfl(TestSuite& suite, Func func);
}






namespace PAFL
{
void FLModel::localize(TestSuite& suite, const TokenTree::Vector& tkt_vec)
{
    auto info(_predictor.predict(suite.getTestSuite(), tkt_vec));

    if (info.targets.empty()) {

        suite.assignSbfl();
        suite.rank();
    }
    else {

        for (auto& item : info.targets)
            _localizers[item.first].localize(suite, tkt_vec, item.second);
        suite.rank();
    }

    if (_logger) {

        const auto obj(std::make_pair<>(this, &info));
        _logger->log(&obj, _iter);
    }
}



void FLModel::step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    auto info(_predictor.step(suite.getTestSuite(), tkt_vec));
    auto targets(toTokenFromFault(suite, tkt_vec, faults));

    for (auto& item : info.targets) {

        // New localizer
        if (item.first == _localizers.size())
            _localizers.emplace_back(item.first);
        // Update target localizers
        _localizers[item.first].step(suite, tkt_vec, faults, targets, item.second);
    }
    _iter++;
}



template <class Func>
void normalizeSbfl(TestSuite& suite, Func func)
{
    auto highest = suite.getHighestSbflSus();

    for (auto& file : suite)
        for (auto& line_param : file) {

            auto& ref = line_param.second.ptr_ranking->sbfl_sus;
            ref = func(ref, highest);
        }
}
}






namespace PAFL
{
class FLModel::Logger : public BaseLogger
{
public:
    Logger(const fs::path& path) : _path(path) {}
    void log(const void* obj, size_t iter) const override
    {
        auto pair = static_cast<const std::pair<const FLModel*, const Predictor::TargetInfo*>*>(obj);
        _llz_log(pair->first, iter);
        _pdt_log(pair->second, iter);
    }
private:
    void _llz_log(const FLModel* model, size_t iter) const
    {
        auto path(createDirRecursively(_path / ('#' + std::to_string(iter+1)) / "localizer"));

        for (size_t i = 0; i != model->_localizers.size(); i++)
            model->_localizers[i].log(path / ("llz_" + std::to_string(i)));
    }
    void _pdt_log(const Predictor::TargetInfo* info, size_t iter) const
    {
        std::ofstream ofs((createDirRecursively(_path / ('#' + std::to_string(iter+1)))) / "predictor.txt");

        ofs << " total = " << info->targets.size() << "\n\n";
        for (auto& item : info->targets)
            ofs << " [" << item.first << "] : " << std::to_string(item.second) << '\n';
        ofs << '\n';
    }
    const fs::path _path;
};
}
#endif
