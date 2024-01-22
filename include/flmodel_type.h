#ifndef __FLMODEL_TYPE_H__
#define __FLMODEL_TYPE_H__

#include "tokentree/tokentree_cpp.h"
#include "testsuite/index.h"


namespace PAFL
{
constexpr size_t K = 3;

using pattern = int;

using target_tokens = std::list<Token*>;
target_tokens toTokenFromFault(const TestSuite& suite, const TokenTree::Vector& tkt_vec, const fault_loc& faults);
}
#endif
