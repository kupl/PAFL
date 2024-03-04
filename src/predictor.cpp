#include "predictor.h"

namespace PAFL
{
Predictor::TargetInfo Predictor::predict(const TestSuite::test_suite& test_suite, const TokenTree::Vector& tkt_vec)
{
    static size_t debug = 0;
    count_t max_cnt = 1;
    std::unordered_map<std::string, count_t> counter;
    counter.reserve(_dimension.size() + 64);
    
    for (auto& test_case : test_suite)
        if(!test_case.is_passed)
            for (auto item : test_case.lines) {
                
                auto ptr_tokens = tkt_vec[item.first]->getTokens(item.second);
                if (ptr_tokens)
                    for (auto& token : *ptr_tokens)
                        if (token.name != "") {

                            _dimension.emplace(token.name);
                            if (counter.contains(token.name))
                                max_cnt == counter.at(token.name)++ ? max_cnt++ : 0;
                            else
                                counter.emplace(token.name, 1);
                        }
                }


    // Set target info
    feature_vector target_vec;
    target_vec.reserve(counter.size());
    for (auto& item : counter)
        target_vec.emplace(item.first, (item.second / (float)max_cnt));

    TargetInfo info(_setTargetInfo(target_vec, K));

    return info;
}



Predictor::TargetInfo Predictor::step(const TestSuite::test_suite& test_suite, const TokenTree::Vector& tkt_vec, const target_tokens& targets)
{
    TargetInfo ret;
    ret.targets.emplace_back(0, 1.0f);
    return ret;

    /**/

    static size_t debug = 0;
    count_t max_cnt = 1;
    count_t passing_max_cnt = 1;
    std::unordered_map<std::string, count_t> counter;
    std::unordered_map<std::string, count_t> passing_counter;
    counter.reserve(_dimension.size() + 64);
    passing_counter.reserve(_dimension.size() + 64);
    
    for (auto& test_case : test_suite) {

        // Failing test
        if(!test_case.is_passed)
            for (auto item : test_case.lines) {
                
                auto ptr_tokens = tkt_vec[item.first]->getTokens(item.second);
                if (ptr_tokens)
                    for (auto& token : *ptr_tokens)
                        if (token.name != "") {

                            _dimension.insert(token.name);
                            if (counter.contains(token.name))
                                max_cnt == counter.at(token.name)++ ? max_cnt++ : 0;
                            else
                                counter.emplace(token.name, 1);
                        }
            }

        // Passing test
        else
            for (auto item : test_case.lines) {
                
                auto ptr_tokens = tkt_vec[item.first]->getTokens(item.second);
                if (ptr_tokens)
                    for (auto& token : *ptr_tokens)
                        if (token.name != "") {

                            _dimension.insert(token.name);
                            if (passing_counter.contains(token.name))
                                passing_max_cnt == passing_counter.at(token.name)++ ? passing_max_cnt++ : 0;
                            else
                                passing_counter.emplace(token.name, 1);
                        }
            }
    }


    // Set target info
    feature_vector target_vec;
    target_vec.reserve(counter.size());
    for (auto& item : counter)
        target_vec.emplace(item.first, (item.second / (float)max_cnt));
    
    auto& feature = _features.emplace_back(std::move(target_vec), CrossWord());
    for (auto ptr : targets)
        feature.second.insertToken(*ptr);
    
    TargetInfo info(_setTargetInfo(feature.first, K+1));
    if (_features.size() > SIZE)
        _features.pop_front();


    // Update passing
    // Use past passing
    for (auto& item : passing_counter) {

        float new_val = (item.second / (float)passing_max_cnt);

        if (_passing_feature.contains(item.first)) {

            float lhsqrt = std::sqrt(_passing_cnt);
            float denom = lhsqrt + 1.0f;

            auto& ref = _passing_feature.at(item.first);
            ref = lhsqrt / denom * ref + new_val / denom;
        }
        else
            _passing_feature.emplace(item.first, new_val);
    }
    _passing_cnt = _passing_cnt == UPPERBOUND ? UPPERBOUND : _passing_cnt + 1;


    return info;
}



float Predictor::_getDistance(const feature_vector& target_vec, const feature_vector& feature_vec, const CrossWord& word) const
{
    float dist = 0.0f;
    for (auto& str : _dimension) {

        float lhval = std::sqrt(target_vec.contains(str) ? target_vec.at(str) : 0.0f);
        float rhval = std::sqrt(feature_vec.contains(str) ? feature_vec.at(str) : 0.0f);
        float euclid = (lhval - rhval);
        dist += euclid * euclid;
        
        /*float sub = 0.0f;
        if (lhval < rhval)
            sub = 1.0f - lhval / rhval;
        else if (lhval != rhval)// lhval > rhval
            sub = 1.0f - rhval / lhval;
        dist += sub * sub*/
    }

    return dist;

    /*float denom = 0.0f;
    auto end(word.cend());
    for (auto iter(word.cbegin()); iter != end; ++iter) {

        auto& str = iter->first;
        float target_val = target_vec.contains(str) ? target_vec.at(str) : 0.0f;
        float feature_val = feature_vec.contains(str) ? feature_vec.at(str) : 0.0f;
        float passing_val = _passing_feature.contains(str) ? _passing_feature.at(str) : 0.0f;

        dist += (target_val - feature_val) * (target_val - feature_val);
        denom += (target_val - passing_val) * (target_val - passing_val);
    }

    return denom > 0 ? dist / denom : 0.0f;*/
}



Predictor::TargetInfo Predictor::_setTargetInfo(const feature_vector& target_vec, size_t k) const
{
    TargetInfo info;
    float max_dist = _getDistance(target_vec, _passing_feature, CrossWord());
    if (max_dist <= 0.0f)
        return info;
    //float max_dist = 1.0f;

    {// Set coefficient
        pattern ptt = 0;
        for (auto& vec : _features) {

            float dist = _getDistance(target_vec, vec.first, vec.second);
            if (dist < max_dist)
                info.targets.emplace_back(ptt, max_dist - dist);
            ptt++;
        }
    }

    {// Cut low coef
        info.targets.sort([](const auto& lhs, const auto& rhs){ return lhs.second > rhs.second; });
        auto iter = info.targets.begin();
        for (size_t i = 0; i != k && iter != info.targets.end(); i++, iter++);
        if (iter != info.targets.end())
            info.targets.erase(iter, info.targets.end());
    }

    {// Normalize
        float total = 0.0f;
        for (auto& item : info.targets)
            total += item.second;
        for (auto& item : info.targets)
            item.second /= total;
    }

    return info;
}
}
