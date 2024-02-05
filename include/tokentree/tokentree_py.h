#ifndef __TOKENTREE_PY_H__
#define __TOKENTREE_PY_H__

#include <map>
#include "tokentree/tokentree.h"
#include "tokentree/tokentree_cmd.h"
#include "rapidjson.h"


namespace PAFL
{
class TokenTreePy : public TokenTree
{
private:
    const char* TYPE_CLASS = "CLASS";
    const char* TYPE_FUNC = "FUNC";


public:
    TokenTreePy(const fs::path& src_file, std::shared_ptr<TokenTree::Matcher> matcher, const fs::path& pytree_exe);

private:
    using array = rapidjson::GenericArray<true, rapidjson::Value>;
    using object = rapidjson::GenericObject<true, rapidjson::Value>;

private:
    void _makeTree(const rapidjson::Document& d);
    void _addTokens(const array& tokens, Token* parent);
    void _caseFunc(const array& tokens, const array& then);
    void _caseBranch(const array& tokens, const array& then, const array& orelse);
    void _caseStmt(const array& tokens);

private:
    std::shared_ptr<TokenTree::Matcher> _matcher;
    std::stack<std::shared_ptr<Token::List>> _predecessor_stack;
    std::stack<std::shared_ptr<Token::List>> _neighbors_stack;
    std::stack<std::shared_ptr<Token::List>> _successor_stack;
    std::stack<std::shared_ptr<Token::List>> _children_stack;
};
}
#endif
