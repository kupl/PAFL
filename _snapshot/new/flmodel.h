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

    FLModel() : _localizers(std::numeric_limits<char>::max()) {}

    void Localize(TokenTree::Vector& tkt_vec, TestSuite& cov);
    void Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines);

    void setLogger(const std::string& log_path, const std::string& project);


private:
    Predictor _predictor;
    std::vector<Localizer> _localizers;
    std::unique_ptr<BaseLogger> _logger;
};
}



namespace PAFL
{
class FLModel::Logger : public BaseLogger
{
    // obj : Predictor::step_info
    void log(const void* obj) override
    {
        auto* ptr_info = static_cast<const Predictor::step_info*>(obj);
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");
        os << "Predcit '" << (int)ptr_info->updated_pattern << "'\n";
    }
public:
    Logger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};
}



namespace PAFL
{
void FLModel::Localize(TokenTree::Vector& tkt_vec, TestSuite& cov)
{
    auto pattern = _predictor.Predict(tkt_vec, cov.GetTestSuite());

    if (pattern < 0) {

        cov.CalculateSus();
        cov.Rank();
    }
    else {
        
        _localizers[pattern].Localize(tkt_vec, cov);
        cov.Rank();
    }
}


void FLModel::Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines)
{
    auto step_info {_predictor.Step(tkt_vec, cov.GetTestSuite(), buggy_lines)};
    _localizers[step_info.updated_pattern].Step(tkt_vec, cov, index, buggy_lines);

    // Log
    if (_logger)
        _logger->log(&step_info);
    _predictor.log();
}

void FLModel::setLogger(const std::string& log_path, const std::string& project)
{
    _logger = std::make_unique<FLModel::Logger>(log_path, project);
    _predictor.setLogger(std::make_unique<Predictor::Logger>(log_path + "/_predictor", project));
    _predictor.setActionLogger(std::make_unique<Predictor::ActionLogger>(log_path + "/_predictor", project + "_action"));
}
}
#endif
