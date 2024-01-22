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
    class Logger : public BaseLogger
    {
    public:
        Logger(const fs::path& path, StopWatch<time_t>& timer);
        void log(const void* obj) const override;

    private:
        void _llz_log(const FLModel* model) const;
        void _pdt_log(const Predictor::TargetInfo* info) const;
    };

public:
    FLModel() { _localizers.reserve(64); }

    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec);
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);

    void setLogger(std::unique_ptr<BaseLogger> logger) { _logger = std::move(logger); }


private:
    Predictor _predictor;
    std::vector<std::unique_ptr<Localizer>> _localizers;

    std::unique_ptr<BaseLogger> _logger;
};

template <class Func>
void normalizeBaseSus(TestSuite& suite, Func func);
}
#include "flmodel.hpp"
#endif
