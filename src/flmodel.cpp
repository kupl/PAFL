#include "flmodel.h"

namespace PAFL
{
void FLModel::localize(TestSuite& suite, const TokenTree::Vector& tkt_vec)
{
    auto info(_predictor.predict(suite.getTotalTestCase(), tkt_vec));
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
    auto targets(toTokenFromFault(suite, tkt_vec, faults));
    auto info(_predictor.step(suite.getTotalTestCase(), tkt_vec, targets));

    _localizers.emplace_back(std::make_unique<Localizer>());
    for (auto& item : info.targets)// Update target localizers
        _localizers[item.first]->step(suite, tkt_vec, faults, targets, item.second);

    if (_localizers.size() > Predictor::SIZE)
        _localizers.erase(_localizers.begin());
}



target_tokens FLModel::toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    target_tokens ret;
    for (auto& item : faults) {

        std::unordered_set<Token::List*> marking;
        index_t index = suite.getIndexFromFile(item.first);

        for (auto line : item.second) {

            auto list_ptr = tkt_vec[index]->getTokens(line);
            if (list_ptr)
                for (auto& token : *list_ptr)
                    if (!marking.contains(token.neighbor.get())) {

                        ret.emplace_back(&token);
                        marking.insert(token.neighbor.get());
                    }
        }
    }

    return ret;
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
