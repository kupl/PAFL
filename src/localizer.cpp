#include "localizer.h"

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

    auto base_rankingsum = _newFirstRanking(_word, suite, tkt_vec, faults);
    
    // New tokens from fault
    for (auto token : targets)
        _word.insertToken(*token, 0.0f);

    // Reserve future weight
    const auto fault_set(suite.toFaultSet(faults));
    auto end(_word.end());
    for (auto iter = _word.begin(); iter != end; ++iter) {
        
        auto& ref = iter->second;
        ref.weight = 1.0f;
        auto rankingsum = _newFirstRanking(_word, suite, tkt_vec, faults, &fault_set);
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



void _localize(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef, const TestSuite::FaultSet* fault_set)
{
    index_t idx = 0;
    for (auto& file : suite) {
        
        std::unordered_map<Token::List*, float> last;
        for (auto& line_param : file) {

            std::unordered_map<Token::List*, float> archive;
            float max_sim = 0.0f;

            auto list_ptr = tkt_vec[idx]->getTokens(line_param.first);
            if (list_ptr)
                for (auto& token : *list_ptr) {
                    
                    auto key = token.neighbor.get();
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
            if (line_param.second.ranking_ptr->sus > 0.0f || fault_set && fault_set->contains(&line_param.second))
                line_param.second.ranking_ptr->sus += 1.0f * coef * max_sim;
        }
        idx++;
    }
}



line_t _newFirstRanking(const CrossWord& word, TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const TestSuite::FaultSet* fault_set)
{
    suite.assignBaseSus();
    _localize(word, suite, tkt_vec, 1.0f, fault_set);
    suite.rank();
    return suite.getFirstRanking(faults);
}
}
