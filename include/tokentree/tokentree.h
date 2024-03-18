#ifndef __TOKENTREE_H__
#define __TOKENTREE_H__
/*
namespace -> {...}
enum ->
    | class | struct | union ->
        {...} | ;
    | {...}
*/
#include <fstream>
#include <memory>
#include <vector>

#include "type.h"


namespace PAFL
{
class Token
{
public:
    using List = std::list<Token*>;

public:
    Token(const std::string& name, line_t loc) :
        name(name), loc(loc), root(nullptr), parent(nullptr) {}
    
public:
    // Token Relation
    Token* root;
    Token* parent;
    std::shared_ptr<Token::List> neighbors;
    std::shared_ptr<Token::List> children;
    std::shared_ptr<Token::List> predecessor;
    std::shared_ptr<Token::List> successor;

    // Token Info
    const std::string name;
    const line_t loc;
};



class TokenTree
{
public:
    using Vector = std::vector<TokenTree*>;

public:
    TokenTree();
    TokenTree(TokenTree& rhs) = delete;
    TokenTree& operator=(TokenTree& rhs) = delete;
    TokenTree(TokenTree&& rhs) : _root(std::move(rhs._root)), _stream(std::move(rhs._stream)),
                                _tokens_indexer(std::move(rhs._tokens_indexer)) {}

    const Token* getRoot() const                { return _root.get(); }
    decltype(auto) getTokens(line_t line) const { return _tokens_indexer.contains(line) ? _tokens_indexer.at(line) : nullptr; }
    void log(const fs::path& path) const;

protected:
    void setIndexr();

protected:
    std::unique_ptr<Token> _root;
    std::list<std::list<Token>> _stream;
    std::unordered_map<line_t, decltype(_stream)::value_type*> _tokens_indexer;
};
}
#endif
