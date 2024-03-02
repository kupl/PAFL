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
    enum class Type
    {
        // identifier
        IDENTIFIER,

        // branch
        IF,
        CATCH,
        FOR,
        SWITCH,
        WHILE,
        // else
        ELSE,
        
        // switch
        CASE,
        DEFAULT,
        // trial & error
        DO,
        TRY,

        // class
        ENUM,
        CLASS,
        STRUCT,
        UNION,

        // outer
        OPERATOR,
        NAMESPACE,

        // parenthesis
        L_PAREN,    // (
        R_PAREN,    // )
        L_BRACE,    // {
        R_BRACE,    // }
        L_SQUARE,   // [
        R_SQUARE,   // ]

        // semicolon 
        SEMI,   // ;
        // colon
        COLON,  // :

        // bit operator
        AMP,            // address operator
        AMPEQUAL,
        PIPE,
        PIPEEQUAL,
        CARET,
        CARETEQUAL,
        TILDE,

        // shift operator
        LESSLESS,
        LESSLESSEQUAL,
        GREATERGREATER,
        GREATERGREATEREQUAL,

        // boolean operator
        AMPAMP,
        EXCLAIM,
        EXCLAIMEQUAL,
        LESS,
        LESSEQUAL,
        GREATER,
        GREATEREQUAL,
        PIPEPIPE,
        EQUALEQUAL,
        IN,
        IS,

        // arithmetic operator
        STAR,           // pointer operator
        STAREQUAL,
        STARSTAR,
        PLUS,
        PLUSPLUS,
        PLUSEQUAL,
        MINUS,
        MINUSMINUS,
        MINUSEQUAL,
        SLASH,
        SLASHEQUAL,
        SLASHSLASH,
        SLASHSLASHEQUAL,
        PERCENT,
        PERCENTEQUAL,
        MATMUL,
        COLONEQUAL,

        // jumping
        BREAK,
        CONTINUE,
        RETURN,
        //GOTO,
        THROW,

        // memory allocation
        NEW,
        DELETE,

        // this
        THIS,

        // casting
        CONST_CAST,
        DYNAMIC_CAST,
        REINTERPRET_CAST,
        STATIC_CAST,

        // otherwise
        OTHERWISE,

        // End Of File
        eof,


        // virtual root type
        ROOT,
        // virtual function type
        FUNC,
        // virtual line statement type
        STMT,
        // virtual lambda type
        LAMBDA
    };
    using List = std::list<Token*>;

public:
    Token(Type type, line_t loc, const std::string& name) :
        type(type), loc(loc), name(name), root(nullptr), parent(nullptr) {}
    
public:
    // Token Relation
    Token* root;
    Token* parent;
    std::shared_ptr<Token::List> neighbors;
    std::shared_ptr<Token::List> children;
    std::shared_ptr<Token::List> predecessor;
    std::shared_ptr<Token::List> successor;

    // Token Info
    Type type;
    line_t loc;
    std::string name;
};

// branch -> IF | CATCH | FOR | SWITCH | WHILE | ELSE
constexpr bool isBranch(Token::Type ttype)              { return Token::Type::IF <= ttype && ttype <= Token::Type::ELSE; }

// indepednet branch -> FOR | SWITCH | WHILE | ELSE
constexpr bool isIndependentBranch(Token::Type ttype)   { return Token::Type::FOR <= ttype && ttype <= Token::Type::ELSE; }

// depednet branch -> IF | CATCH
constexpr bool isDependentBranch(Token::Type ttype)     { return ttype == Token::Type::IF || ttype == Token::Type::CATCH; }

// class -> CLASS | STRUCT | UNION
constexpr bool isClass(Token::Type ttype)               { return Token::Type::CLASS <= ttype && ttype <= Token::Type::UNION; }
    
// ENUM | class
constexpr bool isEnumOrClass(Token::Type ttype)         { return Token::Type::ENUM <= ttype && ttype <= Token::Type::UNION; }

// DO | TRY
constexpr bool isTrialError(Token::Type ttype)          { return ttype == Token::Type::DO || ttype == Token::Type::TRY; }



class TokenTree
{
public:
    class Matcher;
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


class TokenTree::Matcher
{
public:
    Matcher();
    Token::Type match(const std::string& key) const { return _table.contains(key) ? _table.at(key) : Token::Type::OTHERWISE; }
    std::string toString(const Token* token) const  { return token ? std::string("{ name: ") + token->name + ", loc: " + std::to_string(token->loc) + " }" : "NULL token"; }

private:
    const std::unordered_map<std::string, Token::Type> _table;
};
}
#endif
