#ifndef __FLMODEL_H__
#define __FLMODEL_H__

//#include "feature.h"
#include "tokenstream.h"
#include "cov.h"

namespace PAFL
{
class FlModel : public Coverage
{
public:
    FlModel() :
        Coverage() {}
    FlModel(const Coverage& cov) :
        Coverage(cov) {}
    
    void CalculateSus(std::vector<TokenStream>& tokens4file, float coef = 0.1f);
};
}






namespace PAFL
{
void FlModel::CalculateSus(std::vector<TokenStream>& tks_container, float coef)
{
    Coverage::CalculateSus();
    for (index_type idx = 0; idx != MaxIndex(); idx++) {
        
        for (auto iter = cbegin(idx); iter != cend(idx); iter++) {
            
            auto ptr_tokenlist = tks_container[idx].GetTokens(iter->first);
            if (ptr_tokenlist)
                for (auto& tok : *ptr_tokenlist) {

                    // Give advantage to branch condition
                    if (IsBranch(tok.ttype)) {

                        float stm_max_sus = 0.0f;
                        line_type loc = 0;
                        for (auto pchild : tok.stm_children) {
                            
                            if (pchild->loc != loc) {

                                float child_sus = GetOchiaiSus(idx, pchild->loc);
                                if (child_sus > stm_max_sus)
                                    stm_max_sus = child_sus;
                                loc = pchild->loc;
                            }
                        }
                        
                        loc = 0;
                        for (auto pchild : tok.cond_children) {

                            if (pchild->loc != loc) {

                                float cond_sus = GetOchiaiSus(idx, pchild->loc);
                                if (_line_param[idx].contains(pchild->loc) && cond_sus < stm_max_sus) {
                                    _line_param[idx][pchild->loc].ptr_ranking->sus = (stm_max_sus + cond_sus) / 2.0f;
                                loc = pchild->loc;
                            }
                        }
                    }
                }
            }
        }
    }
    /*
    std::string str_if("if");
    std::string str_Token("Token");
    std::string str_tok("tok");
    std::string str_Match("Match");
    Coverage::CalculateSus();

    for (index_type idx = 0; idx != _line_param.size(); idx++) {
        
        for (auto& p : _line_param[idx]) {
            
            auto ptr_tokenlist = tokens4file[idx].GetTokens(p.first);
            if (ptr_tokenlist)
                for (auto& tok : *ptr_tokenlist) {

                    if (tok.name.find(str_if) != std::string::npos)
                        p.second.ptr_ranking->sus += p.second.ptr_ranking->ochiai_sus * 0.12;
                    if (tok.name.find(str_Token) != std::string::npos)
                        p.second.ptr_ranking->sus += p.second.ptr_ranking->ochiai_sus * 0.1;
                    if (tok.name.find(str_tok) != std::string::npos)
                        p.second.ptr_ranking->sus += p.second.ptr_ranking->ochiai_sus * 0.1;
                    if (tok.name.find(str_Match) != std::string::npos)
                        p.second.ptr_ranking->sus += p.second.ptr_ranking->ochiai_sus * 0.1;
                }
        }
    }*/
}
}

#endif
