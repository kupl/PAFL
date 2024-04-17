#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <cmath>
#include "flmodel_type.h"
#include "crosswords.h"


namespace PAFL
{
class Predictor
{
public:
    static constexpr size_t SIZE = 64;
    using count_t = unsigned long long;
    using feature_vector = std::unordered_map<std::string, float>;
    using feature = std::pair<feature_vector, CrossWord>;

    class TargetInfo
    { public:
        using value_type = std::pair<pattern, float>;

        TargetInfo() = default;
        TargetInfo(TargetInfo&) = delete;
        TargetInfo& operator=(TargetInfo&) = delete;
        TargetInfo(TargetInfo&& rhs) : targets(std::move(rhs.targets)) {}

        std::list<value_type> targets;
    };
    
public:
    Predictor() : _passing_cnt(0) {}

    TargetInfo predict(const TestSuite::TotalTestCase& test_suite, const TokenTree::Vector& tkt_vec);
    TargetInfo step(const TestSuite::TotalTestCase& test_suite, const TokenTree::Vector& tkt_vec, const target_tokens& targets);


private:
    static constexpr unsigned short UPPERBOUND = 4;

private:
    float _getDistance(const feature_vector& target_vec, const feature_vector& feature_vec, const CrossWord& word) const;
    TargetInfo _setTargetInfo(const feature_vector& target_vec, size_t k) const;

    std::unordered_set<std::string> _dimension;

    std::list<feature> _features;
    feature_vector _passing_feature;
    unsigned short _passing_cnt;
};
}
#endif
