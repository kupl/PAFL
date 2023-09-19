#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include "flmodel_type.h"



namespace PAFL
{
class Predictor
{
public:
    using count_t = unsigned long long;
    using feature_vector = std::unordered_map<std::string, float>;

    class TargetInfo
    { public:
        using value_type = std::pair<pattern, float>;

        TargetInfo() = default;
        TargetInfo(TargetInfo& rhs) = delete;
        TargetInfo& operator=(TargetInfo& rhs) = delete;
        TargetInfo(TargetInfo&& rhs) : targets(std::move(rhs.targets)) {}

        std::list<value_type> targets;
    };
    

    Predictor() : _passing_cnt(0) {}

    TargetInfo predict(const TestSuite::test_suite& test_suite, const TokenTree::Vector& tkt_vec);
    TargetInfo step(const TestSuite::test_suite& test_suite, const TokenTree::Vector& tkt_vec);


private:
    float _getDistance(const feature_vector& lhs, const feature_vector& rhs) const;
    TargetInfo _setTargetInfo(const feature_vector& failing_vec, size_t k) const;

    std::unordered_set<std::string> _dimension;

    std::list<feature_vector> _feature_vectors;
    feature_vector _passing_feature;
    unsigned short _passing_cnt;

    const unsigned short _cnt_ub = 64;
    const size_t K = 4;
};
}



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
                
                auto ptr_tokens = tkt_vec[item.first].getTokens(item.second);
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
    feature_vector failing_vec;
    failing_vec.reserve(counter.size());
    for (auto& item : counter)
        failing_vec.emplace(item.first, (item.second / (float)max_cnt));

    TargetInfo info(_setTargetInfo(failing_vec, std::numeric_limits<size_t>::max()));

    return info;
}



Predictor::TargetInfo Predictor::step(const TestSuite::test_suite& test_suite, const TokenTree::Vector& tkt_vec)
{
    static size_t debug = 0;
    count_t max_cnt = 1;
    count_t passing_max_cnt = 1;
    std::unordered_map<std::string, count_t> counter;
    std::unordered_map<std::string, count_t> passing_counter;
    counter.reserve(_dimension.size() + 64);
    passing_counter.reserve(_dimension.size() + 64);
    
    for (auto& test_case : test_suite) {

        if(!test_case.is_passed)
            for (auto item : test_case.lines) {
                
                auto ptr_tokens = tkt_vec[item.first].getTokens(item.second);
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

        else
            for (auto item : test_case.lines) {
                
                auto ptr_tokens = tkt_vec[item.first].getTokens(item.second);
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
    feature_vector failing_vec;
    failing_vec.reserve(counter.size());
    for (auto& item : counter)
        failing_vec.emplace(item.first, (item.second / (float)max_cnt));

    TargetInfo info(_setTargetInfo(_feature_vectors.emplace_back(std::move(failing_vec)), K));


    // Update passing
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
    _passing_cnt = _passing_cnt == _cnt_ub ? _cnt_ub : _passing_cnt + 1;


    return info;
}



float Predictor::_getDistance(const feature_vector& lhs, const feature_vector& rhs) const
{
    float dist = 0.0f;
    for (auto& str : _dimension) {

        float lhval = (lhs.contains(str) ? lhs.at(str) : 0.0f);
        float rhval = (rhs.contains(str) ? rhs.at(str) : 0.0f);
        dist += (lhval - rhval) * (lhval - rhval);
    }

    return dist;
}

Predictor::TargetInfo Predictor::_setTargetInfo(const feature_vector& failing_vec, size_t k) const
{
    TargetInfo info;
    float max_dist = _getDistance(failing_vec, _passing_feature);
    if (max_dist <= 0.0f)
        return info;

    // Set coefficient
    pattern ptt = 0;
    for (auto& vec : _feature_vectors) {

        float dist = _getDistance(failing_vec, vec);
        if (dist < max_dist)
            info.targets.emplace_back(ptt, max_dist - dist);
        ptt++;
    }

    // Cut low coef
    info.targets.sort([](const auto& lhs, const auto& rhs){ return lhs.second > rhs.second; });
    auto iter = info.targets.begin();
    for (size_t i = 0; i != k && iter != info.targets.end(); i++, iter++);

    if (iter != info.targets.end())
        info.targets.erase(iter, info.targets.end());


    // Normalize
    float total = 0.0f;
    for (auto& item : info.targets)
        total += item.second;
    for (auto& item : info.targets)
        item.second /= total;

    return info;
}
}
#endif
