#ifndef __FLMODEL_H__
#define __FLMODEL_H__

#include "localizer.h"
#include "predictor.h"



namespace PAFL
{
class FLModel
{
public:
    class Logger;

    FLModel()
        { _localizers.reserve(256); }

    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec);
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);


private:
    Predictor _predictor;
    std::vector<Localizer> _localizers;
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
    else
        for (auto& item : info.targets)
            _localizers[item.first].localize(suite, tkt_vec, item.second);
}



void FLModel::step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    auto info(_predictor.step(suite.getTestSuite(), tkt_vec));
    auto targets(toTokenFromFault(suite, tkt_vec, faults));

    for (auto& item : info.targets) {

        // New localizer
        if (item.first == _localizers.size())
            _localizers.emplace_back();
        // Update target localizers
        _localizers[item.first].step(suite, tkt_vec, faults, targets, item.second);
    }
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
#endif
