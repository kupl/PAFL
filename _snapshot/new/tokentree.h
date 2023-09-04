#ifndef __TOKENTREE_H__
#define __TOKENTREE_H__
/*
namespace -> {...}
enum ->
    | class | struct | union ->
        {...} | ;
    | {...}
*/

#include <filesystem>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <list>
#include <unordered_set>
#include <memory>

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
        FOR,
        IF,
        SWITCH,
        WHILE,
        ELSE,
        // switch
        CASE,
        DEFAULT,

        // class
        NAMESPACE,
        ENUM,
        CLASS,
        STRUCT,
        UNION,

        // parenthesis
        L_PAREN,
        R_PAREN,
        L_BRACE,
        R_BRACE,
        //L_SQUARE,
        //R_SQUARE,

        // semicolon
        SEMI,
        // colon
        COLON,

        // bit operator
        AMP,            // address operator
        AMPEQUAL,
        PIPE,
        PIPEEQUAL,
        CARET,
        CARETEQUAL,

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

        // arithmetic operator
        STAR,           // pointer operator
        STAREQUAL,
        PLUS,
        PLUSPLUS,
        PLUSEQUAL,
        MINUS,
        MINUSMINUS,
        MINUSEQUAL,
        SLASH,
        SLASHEQUAL,
        PERCENT,
        PERCENTEQUAL,

        // jumping
        BREAK,
        CONTINUE,
        RETURN,
        //GOTO,
        THROW,

        // memory allocation
        NEW,
        DELETE,

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
        STMT
    };
    using string_set = std::unordered_set<std::string>;


    Token(Type type, line_t loc, const std::string& name) :
        type(type), loc(loc), name(name),
        root(nullptr), parent(nullptr) {}
    
    // Token Relation
    Token* root;
    Token* parent;
    std::shared_ptr<string_set> neighbors;
    std::shared_ptr<string_set> children;
    std::shared_ptr<string_set> predecessor;
    std::shared_ptr<string_set> successor;

    // Token Info
    Type type;
    line_t loc;
    std::string name;
};

constexpr bool isBranch(Token::Type ttype)
        { return Token::Type::FOR <= ttype && ttype <= Token::Type::ELSE; }
constexpr bool isClass(Token::Type ttype)
        { return Token::Type::CLASS <= ttype && ttype <= Token::Type::UNION; }






class TokenTree
{
public:
    using Vector = std::vector<TokenTree>;

    TokenTree(const std::filesystem::path& path_with_filename);

    const Token* getRoot() const
        { return &_root; }
    decltype(auto) getTokens(line_t line) const
        { return _tokens_indexer.contains(line) ? _tokens_indexer.at(line) : nullptr; }

    void log(std::ofstream& ofs);


protected:
    Token _root;
    std::list<std::list<Token>> _stream;
    std::unordered_map<line_t, decltype(_stream)::value_type*> _tokens_indexer;
    
};
}



namespace PAFL
{
TokenTree::TokenTree(const std::filesystem::path& path_with_filename) :
        _root(Token::Type::ROOT, 0, "") 
{ 
    _root.root = _root.parent = nullptr;
    _root.predecessor = _root.neighbors = _root.successor = std::make_shared<Token::string_set>();
}

void TokenTree::log(std::ofstream& ofs)
{
    for (auto& list : _stream)
        for (auto& tok : list) {

            ofs << tok.name << " (" << &tok << ") " << " : line = " << tok.loc
            << "\n\tparent = " << tok.parent << '\n';
            
            if (tok.children) {

                ofs << "\tchildren_size = " << tok.children->size()
                << "\n\t\t( ";
                for (auto& str : *tok.children)
                    ofs << str << " , ";
                ofs << ")\n";
            }

            ofs << '\n';
        }
}
}
#endif
