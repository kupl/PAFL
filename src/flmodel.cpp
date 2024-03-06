#include "flmodel.h"

namespace PAFL
{
void FLModel::localize(TestSuite& suite, const TokenTree::Vector& tkt_vec)
{
    /*suite.assignBaseSus();
    if (_localizers.size())
        _localizers[0]->localize(suite, tkt_vec, 1.0f);
    suite.rank();
    return;*/

    auto info(_predictor.predict(suite.getTestSuite(), tkt_vec));
    for (auto& item : info.targets)
        _localizers[item.first]->localize(suite, tkt_vec, item.second);
    suite.rank();

    if (_logger) {

        const auto obj(std::make_pair<>(this, &info));
        _logger->log(&obj);
    }
}



void FLModel::step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    /*auto _targets(toTokenFromFault(suite, tkt_vec, faults));
    if (!_localizers.size())
        _localizers.emplace_back(std::make_unique<Localizer>());
    _localizers[0]->step(suite, tkt_vec, faults, _targets, 1.0f);
    return;*/

    /**/

    auto targets(toTokenFromFault(suite, tkt_vec, faults));
    auto info(_predictor.step(suite.getTestSuite(), tkt_vec, targets));

    _localizers.emplace_back(std::make_unique<Localizer>());
    for (auto& item : info.targets)// Update target localizers
        _localizers[item.first]->step(suite, tkt_vec, faults, targets, item.second);

    if (_localizers.size() > Predictor::SIZE)
        _localizers.erase(_localizers.begin());
}
}



namespace PAFL
{
FLModel::Logger::Logger(const fs::path& path, StopWatch<time_t>& timer) : BaseLogger(path, timer) {}



void FLModel::Logger::log(const void* obj) const
{
    beginLog();
    {
        auto pair = static_cast<const std::pair<const FLModel*, const Predictor::TargetInfo*>*>(obj);
        _llz_log(pair->first);
        _pdt_log(pair->second);
    }
    endLog();
}



void FLModel::Logger::_llz_log(const FLModel* model) const
{
    auto llz_path(createDirRecursively(path / "localizer"));

    for (size_t i = 0; i != model->_localizers.size(); i++)
        model->_localizers[i]->log(llz_path / ("llz_" + std::to_string(i + 1)));
}



void FLModel::Logger::_pdt_log(const Predictor::TargetInfo* info) const
{
    std::ofstream ofs(path / "predictor.txt");

    ofs << " total = " << info->targets.size() << "\n\n";
    for (auto& item : info->targets)
        ofs << " [" << item.first + 1 << "] : " << std::to_string(item.second) << '\n';
    ofs << '\n';
}
}
