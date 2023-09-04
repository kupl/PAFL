#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <algorithm>
#include <queue>
#include "tokentree.h"
#include "testsuite.h"
#include "logger.h"



namespace PAFL
{
class Localizer
{
public:
    class Lang;
    enum class Option
        { constant_coverage, assign_to_coverage, maximize_coverage };

    void Localize(TokenTree::Vector& tkt_vec, TestSuite& suite);
    void Step(TokenTree::Vector& tkt_vec, TestSuite& suite, index_t index, const std::list<line_t>& buggy_lines);
    

private:
    std::unordered_map<std::string, std::unique_ptr<Lang>> _language;
    std::shared_ptr<BaseLogger> _logger;
};
void normalizeOchiai(TestSuite& suite);
}
#include "localizer_lang.hpp"






namespace PAFL
{
void Localizer::Localize(TokenTree::Vector& tkt_vec, TestSuite& suite)
{
    normalizeOchiai(suite);
    
    index_t idx = 0;
    for (auto& file : suite) {

        for (auto& line_param : file) {

            float max_sim = 0.0f;
            for (auto& tok : *tkt_vec[idx].getTokens(idx))
                if (_language.contains(tok.name)) {
                    
                    float similarity = _language.at(tok.name)->similarity(tok);
                    max_sim = similarity > max_sim ? similarity : max_sim;
                }

            line_param.second.ptr_ranking->sus += max_sim;
        }
        idx++;
    }


    




    return;
    for (index_t idx = 0; idx != suite.MaxIndex(); idx++) {
    }
}

void Localizer::Step(TokenTree::Vector& tkt_vec, TestSuite& suite, index_t index, const std::list<line_t>& buggy_lines)
{
}

void normalizeOchiai(TestSuite& suite)
{
    suite.CalculateSus();
    auto highest = suite.GetHighestOchiaiSus();

    for (auto& file : suite)
        for (auto& line_param : file) {

            auto& ref = line_param.second.ptr_ranking->ochiai_sus;
            if (ref > 0)
                ref = std::cbrtf(ref / highest);
        }
}
}
#endif
