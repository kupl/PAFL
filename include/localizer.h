#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <algorithm>
#include "flmodel_type.h"
#include "cross_word.h"



namespace PAFL
{
class Localizer
{
public:
    Localizer() : _isFresh(false), _maturity(0) {}
    Localizer(const Localizer& rhs) : _word(rhs._word), _isFresh(true), _maturity(0.0f) {}
    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef) const;
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const target_tokens& targets, float coef);

    void log(const fs::path& _path) const
        { _word.log(_path); }

private:
    CrossWord _word;

    bool _isFresh;
    float _maturity;
};


void _localize(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef);
line_t _newRankingSum(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);

constexpr float _gradientFormula(size_t base_ranking, size_t new_ranking, float coef, float max = 1.0f)
    { float grad = coef * (base_ranking - new_ranking) / (float)base_ranking; return grad > max ? max : grad; }
}






namespace PAFL
{
void Localizer::localize(TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef) const
{
    _localize(_word, suite, tkt_vec, coef * (_maturity / (float)K));
}



void Localizer::step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const target_tokens& targets, float coef)
{
    if (_isFresh)
        _isFresh = false;
    else
        _maturity += coef;

    auto base_rankingsum = _newRankingSum(_word, suite, tkt_vec, faults);
    
    // New tokens from fault
    for (auto token : targets)
        _word.insertToken(*token, 0.0f);

    // Reserve future weight
    auto end(_word.end());
    for (auto iter = _word.begin(); iter != end; ++iter) {
        
        auto& ref = iter->second;
        ref.weight = 1.0f;
        auto rankingsum = _newRankingSum(_word, suite, tkt_vec, faults);
        ref.weight = ref.future;

        // Positive update
        if (rankingsum < base_rankingsum)
            ref.future += (1.0f - ref.future) * _gradientFormula(base_rankingsum, rankingsum, coef, (1.0f / K));
        
        // Negative update
        else if (rankingsum > base_rankingsum) {

            auto grad = _gradientFormula(rankingsum, base_rankingsum, coef, (1.0f / K));
            ref.future *= (ref.future * grad + (1.0f - grad));
            //ref.future *= 1.0f - coef * gradient;
        }
    }
    // future to weight
    _word.assignFuture();
    // Delete weight under threshold
    _word.eraseIf(0.1f);
}
}






namespace PAFL
{
void _localize(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef)
{
    index_t idx = 0;
    for (auto& file : suite) {
        
        std::unordered_map<Token::string_set*, float> last;
        for (auto& line_param : file) {

            std::unordered_map<Token::string_set*, float> archive;
            float max_sim = 0.0f;

            auto list_ptr = tkt_vec[idx].getTokens(line_param.first);
            if (list_ptr)
                for (auto& token : *list_ptr) {
                    
                    auto key = token.neighbors.get();
                    float similarity;

                    if (archive.contains(key))
                        similarity = archive.at(key);
                    
                    else if (last.contains(key)) {

                        similarity = last.at(key);
                        archive.emplace(key, similarity);
                    }
                    else {

                        similarity = word.similarity(token);
                        archive.emplace(key, similarity);
                    }

                    max_sim = similarity > max_sim ? similarity : max_sim;
                }

            last = std::move(archive);
            if (line_param.second.ptr_ranking->sus > 0.0f)
                line_param.second.ptr_ranking->sus += 1.0f * coef * max_sim;
        }
        idx++;
    }
}



line_t _newRankingSum(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    suite.assignSbfl();
    _localize(word, suite, tkt_vec, 1.0f);
    suite.rank();
    return suite.getRankingSum(faults);
}
}
#endif
