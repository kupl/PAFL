#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <unordered_set>

#include "testsuite.h"
#include "tokentree.h"
#include "logger.h"



namespace PAFL
{
class Predictor
{
public:
    class Logger;
    class ActionLogger;

    using count_t = unsigned long long;
    using pattern = char;
    struct step_info { bool act_delete; pattern updated_pattern, deleted_pattern; };
    using feature_vector = std::unordered_map<std::string, float>;

    Predictor();

    pattern Predict(TokenTree::Vector& tkt_vec, const TestSuite::test_suite& test_suite);
    step_info Step(TokenTree::Vector& tkt_vec, const TestSuite::test_suite& test_suite, const std::list<line_t>& buggy_lines);

    void setLogger(std::unique_ptr<BaseLogger> logger)
        { this->_logger = std::move(logger); }
    void setActionLogger(std::unique_ptr<BaseLogger> action_logger)
        { this->_action_logger = std::move(action_logger); }
    void log()
        { if (_logger) _logger->log(this); }


private:
    float _GetDistance(const feature_vector& lhs, const feature_vector& rhs) const;

    std::vector<std::pair<std::unique_ptr<feature_vector>, count_t>> _feature_vectors;
    feature_vector _passing_feature;
    count_t _passing_size;
    std::unordered_set<std::string> _dimension;

    std::unique_ptr<BaseLogger> _logger;
    std::unique_ptr<BaseLogger> _action_logger;
};
}






namespace PAFL
{
class Predictor::Logger : public BaseLogger
{
    void log(const void* obj) override
    {
        auto ptr_predictor = static_cast<const Predictor*>(obj);
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");

        os << ">> Passing: " << ptr_predictor->_passing_size << '\n';
        for (auto& item : ptr_predictor->_passing_feature)
            os << ' ' << item.first << ": " << item.second << '\n';
        
        for (pattern iter = 0; iter != ptr_predictor->_feature_vectors.size(); iter++)
            if (ptr_predictor->_feature_vectors[iter].first) {

                os << "\n\n\n>> Feature " << (int)iter << ": " << ptr_predictor->_feature_vectors[iter].second << '\n';
                for (auto& item : *ptr_predictor->_feature_vectors[iter].first)
                    os << ' ' << item.first << ": " << item.second << '\n';
            }
    }
public:
    Logger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};

class Predictor::ActionLogger : public BaseLogger
{
    void log(const void* obj) override
    {
        auto ptr_pattern = static_cast<const Predictor::pattern*>(obj);
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");
        
        os << (int)*ptr_pattern;
    }
public:
    ActionLogger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};
}






namespace PAFL
{
Predictor::Predictor() :
    _passing_size(0)
{
    _feature_vectors.reserve(std::numeric_limits<char>::max());
    for (size_t i = 0; i != std::numeric_limits<char>::max(); i++)
        _feature_vectors.emplace_back(nullptr, 0);
}



Predictor::step_info Predictor::Step(TokenTree::Vector& tkt_vec, const TestSuite::test_suite& test_suite, const std::list<line_t>& buggy_lines)
{
    static size_t debug = 0;
    step_info info{ false, -1, -1 };
    count_t max_cnt = 1;
    count_t passing_max_cnt = 1;
    count_t failing_tc = 0;
    count_t passing_tc = 0;
    std::unordered_map<std::string, count_t> counter;
    std::unordered_map<std::string, count_t> passing_counter;
    counter.reserve(_dimension.size() + 64);
    passing_counter.reserve(_dimension.size() + 64);
    

    for (auto& test_case : test_suite) {

        if(!test_case.is_passed) {

            failing_tc++;
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
        }

        else {

            passing_tc++;
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
    }


    // Failing
    auto ptr_failing_vec(std::make_unique<feature_vector>());
    ptr_failing_vec->reserve(counter.size());
    for (auto& item : counter)
        ptr_failing_vec->emplace(item.first, 10.0f * (item.second / (float)max_cnt));

    // Feature distance
    float min_dist = 0.75f * _GetDistance(*ptr_failing_vec, _passing_feature);
    pattern nearest = -1;
    for (pattern iter = 0; iter != _feature_vectors.size(); iter++)
        if (_feature_vectors[iter].first) {
            float dist = _GetDistance(*ptr_failing_vec, *_feature_vectors[iter].first);
            if (dist < min_dist) {

                min_dist = dist;
                nearest = iter;
            }
        }


    // New feature_vector
    if (nearest == -1) {

        pattern updated_pattern = -1;
        auto iter = std::find_if(_feature_vectors.begin(), _feature_vectors.end(), [&](const std::pair<std::unique_ptr<feature_vector>, count_t>& item){ updated_pattern++; return item.first == nullptr; });
        iter->first = std::move(ptr_failing_vec);
        iter->second = failing_tc;

        // Update info
        unsigned long i = 0;
        for (auto jter = _feature_vectors.begin(); jter != iter; jter++, i++);
        info.updated_pattern = updated_pattern;
    }
     // Update feature_vectors
    else {

        for (auto& str : _dimension) {

            float new_val = ptr_failing_vec->contains(str) ? ptr_failing_vec->at(str) : 0.0f;

            if (_feature_vectors[nearest].first->contains(str)) {

                float lhs = _feature_vectors[nearest].second;
                float rhs = failing_tc;
                float denom = lhs + rhs;

                auto& ref = _feature_vectors[nearest].first->at(str);
                ref = lhs / denom * ref + 1 / denom * new_val;
            }
            else if (ptr_failing_vec->contains(str)) {

                float lhs = _feature_vectors[nearest].second;
                float rhs = failing_tc;
                float denom = lhs + rhs;

                _feature_vectors[nearest].first->emplace(str, rhs / denom * new_val);
            }
        }
        _feature_vectors[nearest].second += failing_tc;
        info.updated_pattern = nearest;
    }


    // Update passing
    for (auto& item : passing_counter) {

        float new_val = 10.0f * (item.second / (float)passing_max_cnt);

        if (_passing_feature.contains(item.first)) {

            float lhsqrt = std::sqrt(_passing_size);
            float rhsqrt = std::sqrt(passing_tc);
            float denom = lhsqrt + rhsqrt;

            auto& ref = _passing_feature.at(item.first);
            ref = lhsqrt / denom * ref + rhsqrt / denom * new_val;
        }
        else
            _passing_feature.emplace(item.first, new_val);
    }
    _passing_size += passing_tc;

    // Merge
    return info;
}



Predictor::pattern Predictor::Predict(TokenTree::Vector& tkt_vec, const TestSuite::test_suite& test_suite)
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

    // Failing
    feature_vector failing_vec;
    failing_vec.reserve(counter.size());
    for (auto& item : counter)
        failing_vec.emplace(item.first, 10.0f * (item.second / (float)max_cnt));
    
    // Feature distance
    float min_dist = 0.75f * _GetDistance(failing_vec, _passing_feature);
    pattern nearest = -1;
    for (pattern iter = 0; iter != _feature_vectors.size(); iter++)
        if (_feature_vectors[iter].first) {
            float dist = _GetDistance(failing_vec, *_feature_vectors[iter].first);
            if (dist < min_dist) {

                min_dist = dist;
                nearest = iter;
            }
        }
        
    if (_action_logger)
        _action_logger->log(&nearest);
    return nearest;
}



float Predictor::_GetDistance(const feature_vector& lhs, const feature_vector& rhs) const
{
    float dist = 0.0f;
    for (auto& str : _dimension) {

        float lhval = (lhs.contains(str) ? lhs.at(str) : 0.0f);
        float rhval = (rhs.contains(str) ? rhs.at(str) : 0.0f);
        dist += (lhval - rhval) * (lhval - rhval);
    }

    return dist;
}
}
#endif
