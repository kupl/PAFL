#ifndef __TOKENTREE_CPP_H__
#define __TOKENTREE_CPP_H__

#include <iostream>
#include "tokentree/cpppda.h"


namespace PAFL
{
namespace Command
{
    constexpr auto TEMPORARY_CPP = "___temp.cpp";
    constexpr auto TEMPORARY_TXT = "___temp.txt";
    constexpr auto DUMP_COMMAND = "clang++ -fsyntax-only -Xclang -dump-tokens ___temp.cpp 2>&1 | tee ___temp.txt";
#ifdef _WIN32
    constexpr auto CLEAR = "cls";
#elif _WIN64
    constexpr auto CLEAR = "cls";
#else
    constexpr auto CLEAR = "clear";
#endif
}


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
