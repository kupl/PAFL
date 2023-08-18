namespace PAFL
{
class Localizer::TokenWeight
{
public:
    class Logger;
    struct WeightInfo { float weight; float reservation; };
    using weight_map = std::unordered_map<std::string, WeightInfo>;

    void CalculateSus(TokenTree& tkt, TestSuite& cov, index_t index, Option opt);
    void Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines,
                size_t step_size , float threshold, float inc_coef, float dec_coef);

    void Log(std::ostream& os);


private:
    void _Reservation(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines,
                        line_t ranking_sum, float inc_coef, float dec_coef);

    float _max_weight = 0.0f;
    weight_map _weight;

    std::unique_ptr<BaseLogger> _logger;
};
}






namespace PAFL
{
class Localizer::TokenWeight::Logger : public BaseLogger
{
    void log(const void* obj) override
    {
        auto ptr_weight = static_cast<const Localizer::TokenWeight::weight_map*>(obj);
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");

        os << "## size = " << ptr_weight->size() << '\n';
        for (auto& pair : *ptr_weight)
            os << pair.first << " : \tval = " << pair.second.weight << '\n';
    }
public:
    Logger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};
}






namespace PAFL
{
void Localizer::TokenWeight::CalculateSus(TokenTree& tkt, TestSuite& cov, index_t index, Option opt)
{
    auto highest = std::sqrtf(cov.GetHighestOchiaiSus());
    //highest = cov.GetHighestOchiaiSus();

    for (auto iter = cov.begin(index); iter != cov.end(index); iter++) {
        
        auto ptr_tok_set = tkt.GetTokenSet(iter->first);
        if (!ptr_tok_set || iter->second.Ncf == 0)
            continue;

        float sus = 0.0f;
        for (auto token : *ptr_tok_set)
            if (_weight.contains(token->name)) {

                float val = _weight.at(token->name).weight;
                if (val > sus)
                    sus = val;
            }

        // Assign suspiciousness of line
        if (opt == Option::assign_to_coverage)
            iter->second.ptr_ranking->sus = std::sqrtf(iter->second.ptr_ranking->ochiai_sus) + highest * sus;//iter->second.ptr_ranking->ochiai_sus + highest * sus;
        else if (opt == Option::maximize_coverage)
            iter->second.ptr_ranking->sus = std::sqrtf(iter->second.ptr_ranking->sus) + highest * sus;//iter->second.ptr_ranking->sus + highest * sus;
    }
}



void Localizer::TokenWeight::_Reservation(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines,
                                        line_t ranking_sum, float inc_coef, float dec_coef)
{
    for (auto& item : _weight) {

        auto& weight_ref = item.second;
        weight_ref.weight = 1.0f;

        for (index_t idx = 0; idx != cov.MaxIndex(); idx++)
            CalculateSus(tkt_vec[idx], cov, idx, Option::assign_to_coverage);
        cov.Rank();
        line_t new_ranking_sum = cov.GetRankingSum(index, buggy_lines);
        weight_ref.weight = weight_ref.reservation;

        // Update reservation
        if (new_ranking_sum < ranking_sum) {

            float gradient = (ranking_sum - new_ranking_sum) / (float)ranking_sum;
            weight_ref.reservation = weight_ref.reservation + (1.0f - weight_ref.reservation) * inc_coef * gradient;
        }
        else {

            weight_ref.weight = 0.0f;

            for (index_t idx = 0; idx != cov.MaxIndex(); idx++)
                CalculateSus(tkt_vec[idx], cov, idx, Option::assign_to_coverage);
            cov.Rank();
            line_t new_ranking_sum = cov.GetRankingSum(index, buggy_lines);
            weight_ref.weight = weight_ref.reservation;

            if (new_ranking_sum < ranking_sum) {

                float gradient = (ranking_sum - new_ranking_sum) / (float)ranking_sum;
                weight_ref.reservation = weight_ref.reservation * weight_ref.reservation * dec_coef * gradient + weight_ref.reservation * (1.0f - dec_coef * gradient);
            }
        }
    }
}



void Localizer::TokenWeight::Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines,
                                size_t step_size, float threshold, float inc_coef, float dec_coef)
{
    // Log
    static size_t debug = 0;

    // New positive tokens
    for (auto line : buggy_lines) {
        
        auto ptr_token_set = tkt_vec[index].GetTokenSet(line);
        if (ptr_token_set)
            for (auto token : *ptr_token_set)

                if (!_weight.contains(token->name))
                    _weight.emplace(token->name, WeightInfo{ threshold, threshold });
    }

    // Snapshot
    CalculateSus(tkt_vec[index], cov, index, Option::assign_to_coverage);
    cov.Rank();
    const line_t ranking_sum_snapshot = cov.GetRankingSum(index, buggy_lines);

    // Step
    for (size_t i = 0; i != step_size; i++) {

        // Reservation
        _Reservation(tkt_vec, cov, index, buggy_lines, ranking_sum_snapshot, inc_coef, dec_coef);
        // Update
        for (auto& item : _weight)
            item.second.weight = item.second.reservation;
        // Delete weight under threshold
        std::erase_if(_weight, [=](const auto& item){ return item.second.weight <= threshold; });
    }

    std::ofstream ofs("_log/log_token_weight_" + std::to_string(++debug));
    Log(ofs);
    ofs.close();
}



void Localizer::TokenWeight::Log(std::ostream& os)
{
    os << "## size = " << _weight.size() << '\n';
    for (auto& pair : _weight)
        os << pair.first << " : \tval = " << pair.second.weight << '\n';
}
}
