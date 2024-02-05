#include "flmodel_type.h"

namespace PAFL
{
target_tokens toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults)
{
    target_tokens ret;
    for (auto& item : faults) {

        std::unordered_set<Token::List*> marking;
        index_t index = suite.getIndexFromFile(item.first);

        for (auto line : item.second) {

            auto list_ptr = tkt_vec[index]->getTokens(line);
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
