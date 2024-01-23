#ifndef __TOKENTREE_PY_H__
#define __TOKENTREE_PY_H__

#include "tokentree/tokentree.h"

namespace PAFL
{
class TokenTreePy : public TokenTree
{
public:
    TokenTreePy(const std::filesystem::path& src_file, std::shared_ptr<TokenTree::Matcher> matcher);

private:
    std::list<Token> _getAST(const std::filesystem::path& path, std::shared_ptr<TokenTree::Matcher> matcher) const;
};
}
#endif
