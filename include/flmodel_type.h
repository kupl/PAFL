#ifndef __FLMODEL_TYPE_H__
#define __FLMODEL_TYPE_H__

#include "tokentree/tokentree.h"
#include "testsuite/index.h"


namespace PAFL
{
constexpr size_t K = 3;
using pattern = int;
using target_tokens = std::list<const Token*>;
}
#endif
