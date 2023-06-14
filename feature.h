#ifndef __FEATURE_H__
#define __FEATURE_H__
/*
#include "tokenstream.h"
#include "cov.h"

namespace PAFL
{
class Feature
{
public:
    Feature() : _numof_tok(0) {}

    void Add(TokenStream& tks, const std::list<line_type>& buggy_lines);
    void CalculateSus(Coverage& cov, std::vector<TokenStream>& tks_container, float coef = 0.1f);
    

private:
    struct TokenInfo{ TokenType ttype; std::string name; };
    using feature_map = std::unordered_map<TokenInfo, int>;

    float _GetTokenFeature(TokenType ttype, const std::string& name)
        { return _map.contains({ttype, name}) ? _map[{ttype, name}] / _numof_tok : 0.0f; }
    
    feature_map _map;
    uint32_t _numof_tok;
};
}






namespace PAFL
{
void Feature::Add(TokenStream& tks, const std::list<line_type>& buggy_lines)
{
    for (auto line : buggy_lines) {

        auto toklist = tks.GetTokens(line);
        for (auto& tok : *toklist) {
            
            _numof_tok++;
            TokenInfo info{tok.ttype, tok.name};
            if (_map.contains(info))
                _map[info]++;
            else
                _map[info] = 1;
        }
    }
}

void Feature::CalculateSus(Coverage& cov, std::vector<TokenStream>& tks_container, float coef)
{
    for (index_type idx = 0; idx != cov.MaxIndex(); idx++) {
        
        for (auto iter = cov.cbegin(idx); iter != cov.cend(idx); iter++) {
            
            auto ptr_tokenlist = tks_container[idx].GetTokens(iter->first);
            if (ptr_tokenlist)
                for (auto& tok : *ptr_tokenlist) {

                    // Feature
                    iter->second.ptr_ranking->sus += iter->second.ptr_ranking->ochiai_sus * _GetTokenFeature(tok.ttype, tok.name) * coef;
                    
                    // Give advantage to branch condition
                    if (IsBranch(tok.ttype)) {

                        float stm_max_sus = 0.0f;
                        line_type loc = 0;
                        for (auto pchild : tok.stm_children) {
                            
                            if (pchild->loc != loc) {

                                float child_sus = cov.GetOchiaiSus(idx, pchild->loc);
                                if (child_sus > stm_max_sus)
                                    stm_max_sus = child_sus;
                                loc = pchild->loc;
                            }
                        }
                    }
                }
        }
    }
}
}
*/
#endif
