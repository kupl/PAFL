#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <algorithm>
#include "tokentree.h"
#include "testsuite.h"
#include "logger.h"



namespace PAFL
{
class Localizer
{
public:
    enum class Option
        { constant_coverage, assign_to_coverage, maximize_coverage };

    Localizer() :
        _weight(std::make_unique<TokenWeight>()), _lang(std::make_unique<Lang>()) {}

    void Localize(TokenTree::Vector& tkt_vec, TestSuite& suite);
    void Step(TokenTree::Vector& tkt_vec, TestSuite& suite, index_t index, const std::list<line_t>& buggy_lines);
    

private:
    class Lang;
    
    std::unique_ptr<Lang> _lang;




    class TokenWeight;
    std::unique_ptr<TokenWeight> _weight;
};
//void standardizeOchiai(TestSuite& suite);
void initTreeVecWithCoverage(TokenTree::Vector& tkt_vec, const TestSuite& suite);
}
#include "feature_lang.hpp"
#include "feature_weight.hpp"






namespace PAFL
{

void Localizer::Step(TokenTree::Vector& tkt_vec, TestSuite& suite, index_t index, const std::list<line_t>& buggy_lines)
{
    size_t lang_step = 2;

    suite.CalculateSus();

    // Localizer::Lang
    for (size_t i = 0; i != lang_step; i++) 
        if (!_lang->Step(tkt_vec, suite, index, buggy_lines))
            break;

    // Localizer::TokenWeight
    _weight->Step(tkt_vec, suite, index, buggy_lines, 3, 0.1f, 0.25f, 0.25f);
}

void Localizer::Localize(TokenTree::Vector& tkt_vec, TestSuite& suite)
{   
    for (index_t idx = 0; idx != suite.MaxIndex(); idx++) {

        _lang->CalculateSus(tkt_vec[idx], suite, idx, Option::maximize_coverage);
         _weight->CalculateSus(tkt_vec[idx], suite, idx, Option::maximize_coverage);
    }
}

void initTreeVecWithCoverage(TokenTree::Vector& tkt_vec, const TestSuite& suite)
{
    for (index_t idx = 0; idx != suite.MaxIndex(); idx++)
        for (auto& tok_list : tkt_vec[idx]) {

            float sus = suite.GetOchiaiSus(idx, tok_list.begin()->loc);
            for (auto& tok : tok_list)
                tok.ochiai_sus = sus;
        }
}
/*void standardizeOchiai(TestSuite& suite)
{
    suite.CalculateSus();
    auto highest = suite.GetHighestOchiaiSus();

    for (index_t idx = 0; idx != suite.MaxIndex(); idx++)
        for (auto iter = suite.begin(idx); iter != suite.end(idx); iter++)
            if (iter->second.ptr_ranking->ochiai_sus > 0)
                iter->second.ptr_ranking->ochiai_sus = std::cbrtf(iter->second.ptr_ranking->ochiai_sus / highest);
}*/
}
#endif
