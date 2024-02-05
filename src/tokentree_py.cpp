#include "tokentree/tokentree_py.h"

namespace PAFL
{
TokenTreePy::TokenTreePy(const fs::path& src_file, std::shared_ptr<TokenTree::Matcher> matcher, const fs::path& pytree_exe) :
    TokenTree(), _matcher(matcher)
{
    std::string cmd = "python3 " + pytree_exe.string() + " " + src_file.string() + " " + Command::TEMPORARY_TXT;
    std::system(cmd.c_str());
    _makeTree(rapidjson::parseDoc(Command::TEMPORARY_TXT));
    std::remove(Command::TEMPORARY_TXT);
}



void TokenTreePy::_makeTree(const rapidjson::Document& d)
{
    const auto& module = d["module"].GetArray();
    for (auto& stmt_obj : module) {
    
        const auto& stmt = stmt_obj.GetObject();
        auto type(stmt["type"].GetString());
        const auto& tokens = stmt["toks"].GetArray();

        //if (type == "FUNC")
    }
}



void TokenTreePy::_addTokens(const array& tokens, Token* parent)
{
    if (tokens.Empty())
        return;

    // New successor stack
    _predecessor_stack.top() = _neighbors_stack.top();
    _neighbors_stack.top() = _successor_stack.top();
    _successor_stack.pop();
    _successor_stack.emplace();
    _successor_stack.top() = std::make_shared<Token::List>();

    // New stream statement
    auto& stmt = _stream.emplace_back();
    // Add tokens to neighbors_stack
    for (auto& token_arr : tokens) {

        const auto& token = token_arr.GetArray();
        const auto type(token[0].GetString());
        const auto name(token[1].GetString());
        const auto lineno(token[2].GetUint());
        
        auto& tok = stmt.emplace_back(_matcher->match(type), lineno, name);
        tok.root = _root.get();
        tok.parent = parent;
        tok.predecessor = _predecessor_stack.top();
        tok.neighbors = _neighbors_stack.top();
        tok.neighbors->push_back(&tok);
        tok.successor = _successor_stack.top();
        tok.children = _children_stack.top();
    }
}



void TokenTreePy::_caseFunc(const array& tokens, const array& then)
{
}



void TokenTreePy::_caseBranch(const array& tokens, const array& then, const array& orelse)
{

}



void TokenTreePy::_caseStmt(const array& tokens)
{

}
}
