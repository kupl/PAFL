#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <algorithm>
#include "flmodel_type.h"
#include "crosswords.h"


namespace PAFL
{
class Localizer
{
public:
    Localizer() : _isFresh(false), _maturity(0) {}
    Localizer(const Localizer& rhs) : _word(rhs._word), _isFresh(true), _maturity(0.0f) {}
    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef) const;
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const target_tokens& targets, float coef);

    void log(const fs::path& _path) const { _word.log(_path); }

private:
    CrossWord _word;

    bool _isFresh;
    float _maturity;
};


void _localize(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef, const fault_loc* ptr_faults = nullptr);
line_t _newRankingSum(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);

constexpr float _gradientFormula(size_t base_ranking, size_t new_ranking, float coef, float max = 1.0f)
    { float grad = coef * (base_ranking - new_ranking) / (float)base_ranking; return grad > max ? max : grad; }
}
#endif
