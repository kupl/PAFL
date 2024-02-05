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
    TokenTreeCpp(const std::filesystem::path& src_file, std::shared_ptr<TokenTree::Matcher> matcher);

private:
    std::list<Token> _getRawStream(const std::filesystem::path& path, std::shared_ptr<TokenTree::Matcher> matcher) const;
    static void _eraseInclude(const std::filesystem::path& path);
};
}
#endif
