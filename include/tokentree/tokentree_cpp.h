#ifndef __TOKENTREE_CPP_H__
#define __TOKENTREE_CPP_H__

#include <iostream>
#include "tokentree/cpppda.h"
#include "tokentree/tokentree_cmd.h"


namespace PAFL
{
class TokenTreeCpp : public TokenTree
{
public:
    TokenTreeCpp(const fs::path& src_file, const fs::path& bin, std::shared_ptr<TokenTree::Matcher> matcher);

private:
    std::list<Token> _getRawStream(const fs::path& path, const fs::path& bin, std::shared_ptr<TokenTree::Matcher> matcher) const;
    static void _eraseInclude(const fs::path& path, const fs::path& bin);
};
}
#endif
