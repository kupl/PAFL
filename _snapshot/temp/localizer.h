#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <algorithm>
#include "tokentree_cpp.h"
#include "testsuite.h"
#



namespace PAFL
{
using target_tokens = std::list<Token*>;
target_tokens toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);



class Localizer
{
public:
    class Lang;

    Localizer() :
        _language(std::make_unique<Lang>()) {}
     
    void localize(TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef) const;
    void step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const target_tokens& targets, float coef);

private:
    line_t _newRankingSum(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults) const;

    std::unique_ptr<Lang> _language;
};
}
#include "localizer_lang.hpp"






namespace PAFL
{
target_tokens toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    target_tokens ret;
    for (auto& item : faults) {

        std::unordered_set<Token::string_set*> marking;
        index_t index = suite.getIndexFromFile(item.first);

        for (auto line : item.second) {

            auto list_ptr = tkt_vec[index].getTokens(line);
            if (list_ptr)
                for (auto& token : *list_ptr)
                    if (!marking.contains(&*token.neighbors)) {

                        ret.emplace_back(&token);
                        marking.insert(&*token.neighbors);
                    }
        }
    }

    return ret;
}



void Localizer::localize(TestSuite& suite, const TokenTree::Vector& tkt_vec, float coef) const
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
                    
                    auto key = &*token.neighbors;
                    float similarity;

                    if (archive.contains(key))
                        similarity = archive.at(key);
                    
                    else if (last.contains(key)) {

                        similarity = last.at(key);
                        archive.emplace(key, similarity);
                    }
                    else {

                        similarity = _language->similarity(token);
                        archive.emplace(key, similarity);
                    }

                    max_sim = similarity > max_sim ? similarity : max_sim;
                }

            last = std::move(archive);
            line_param.second.ptr_ranking->sus += coef * max_sim;
        }
        idx++;
    }
}



void Localizer::step(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults, const target_tokens& targets, float coef)
{
    suite.assignSbfl();
    suite.rank();
    auto sbfl_rankingsum = suite.getRankingSum(faults);
    
    // New tokens from fault
    for (auto token : targets)
        _language->insertToken(*token, 0.1f);

    // Reserve future weight
    auto end(_language->end());
    for (auto iter = _language->begin(); iter != end; ++iter) {
        
        auto& ref = iter->second;
        ref.weight = 1.0f;
        auto rankingsum = _newRankingSum(suite, tkt_vec, faults);
        ref.weight = ref.future;

        // Positive update
        if (rankingsum < sbfl_rankingsum) {

            float gradient = (sbfl_rankingsum - rankingsum) / (float)sbfl_rankingsum;
            ref.future += (1.0f - ref.future) * coef * gradient;
        }
        else { // Nonpositive

            ref.weight = 0.0f;
            auto rankingsum = _newRankingSum(suite, tkt_vec, faults);
            ref.weight = ref.future;
            
            // Negative update
            if (rankingsum < sbfl_rankingsum) {

                float gradient = (sbfl_rankingsum - rankingsum) / (float)sbfl_rankingsum;
                ref.future *= (ref.future * coef * gradient + (1.0f - coef * gradient));
            }
        }
    }

    // future to weight
    _language->assignFuture();
    // Delete weight under threshold
    _language->eraseIf(0.1f);
}



line_t Localizer::_newRankingSum(TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults) const
{
    suite.assignSbfl();
    localize(suite, tkt_vec, 1.0f);
    suite.rank();
    return suite.getRankingSum(faults);
}
}
#endif
