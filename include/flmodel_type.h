#ifndef __FLMODEL_TYPE_H__
#define __FLMODEL_TYPE_H__

#include "tokentree_cpp.h"
#include "testsuite.h"



namespace PAFL
{
constexpr size_t K = 3;

using pattern = int;

using target_tokens = std::list<Token*>;
target_tokens toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);
}



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
                    if (!marking.contains(token.neighbors.get())) {

                        ret.emplace_back(&token);
                        marking.insert(token.neighbors.get());
                    }
        }
    }

    return ret;
}
}

#endif
