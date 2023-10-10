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
        CATCH,
        FOR,
        IF,
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

// branch -> CATCH | FOR | IF | WHILE | ELSE
constexpr bool isBranch(Token::Type ttype)
    { return Token::Type::CATCH <= ttype && ttype <= Token::Type::ELSE; }
// class -> CLASS | STRUCT | UNION
constexpr bool isClass(Token::Type ttype)
    { return Token::Type::CLASS <= ttype && ttype <= Token::Type::UNION; }
// ENUM | class
constexpr bool isEnumOrClass(Token::Type ttype)
     { return Token::Type::ENUM <= ttype && ttype <= Token::Type::UNION; }
// DO | TRY
constexpr bool isTrialError(Token::Type ttype)
     { return ttype == Token::Type::DO || ttype == Token::Type::TRY; }






class TokenTree
{
public:
    class Matcher;
    using Vector = std::vector<TokenTree>;

    TokenTree(const std::filesystem::path& path_with_filename, std::shared_ptr<TokenTree::Matcher> matcher);
    TokenTree(TokenTree& rhs) = delete;
    TokenTree& operator=(TokenTree& rhs) = delete;
    TokenTree(TokenTree&& rhs) : _root(std::move(rhs._root)), _stream(std::move(rhs._stream)),
                                _tokens_indexer(std::move(rhs._tokens_indexer)) {}

    const Token* getRoot() const
        { return &*_root; }
    decltype(auto) getTokens(line_t line) const
        { return _tokens_indexer.contains(line) ? _tokens_indexer.at(line) : nullptr; }

    void log(const fs::path& path) const;


protected:
    std::unique_ptr<Token> _root;
    std::list<std::list<Token>> _stream;
    std::unordered_map<line_t, decltype(_stream)::value_type*> _tokens_indexer;
};



TokenTree::TokenTree(const fs::path& path_with_filename, std::shared_ptr<TokenTree::Matcher> matcher) :
        _root(std::make_unique<Token>(Token::Type::ROOT, 0, ""))
{ 
    _root->root = _root->parent = nullptr;
    _root->predecessor = _root->neighbors = _root->successor = std::make_shared<Token::string_set>();
}
}






namespace PAFL
{
class TokenTree::Matcher
{
public:
    Matcher() :
        _table {
            // identifier
            { "identifier", Token::Type::IDENTIFIER },

            // branch
            { "catch", Token::Type::CATCH },
            { "for", Token::Type::FOR },
            { "if", Token::Type::IF },
            { "switch", Token::Type::SWITCH },
            { "while", Token::Type::WHILE },
            // else
            { "else", Token::Type::ELSE },

            // switch
            { "case", Token::Type::CASE },
            { "default", Token::Type::DEFAULT },
            // trial & error
            { "do", Token::Type::DO },
            { "try", Token::Type::TRY },

            // class
            { "enum", Token::Type::ENUM },
            { "class", Token::Type::CLASS },
            { "struct", Token::Type::STRUCT },
            { "union", Token::Type::UNION },

            // outer
            { "operator", Token::Type::OPERATOR },
            { "namespace", Token::Type::NAMESPACE },

            // parenthesis
            { "l_paren", Token::Type::L_PAREN },
            { "r_paren", Token::Type::R_PAREN },
            { "l_brace", Token::Type::L_BRACE },
            { "r_brace", Token::Type::R_BRACE },
            { "l_square", Token::Type::L_SQUARE },
            { "r_square", Token::Type::R_SQUARE },

            // semicolon
            { "semi", Token::Type::SEMI },
            // colon
            { "colon", Token::Type::COLON },

            // bit operator
            { "amp", Token::Type::AMP },
            { "ampequal", Token::Type::AMPEQUAL },
            { "pipe", Token::Type::PIPE },
            { "pipeequal", Token::Type::PIPEEQUAL },
            { "caret", Token::Type::CARET },
            { "caretequal", Token::Type::CARETEQUAL },

            // shift operator
            { "lessless", Token::Type::LESSLESS },
            { "lesslessequal", Token::Type::LESSLESSEQUAL },
            { "greatergreater", Token::Type::GREATERGREATER },
            { "greatergreaterequal", Token::Type::GREATERGREATEREQUAL },

            // boolean operator
            { "ampamp", Token::Type::AMPAMP },
            { "exclaim", Token::Type::EXCLAIM },
            { "exclaimequal", Token::Type::EXCLAIMEQUAL },
            { "less", Token::Type::LESS },
            { "lessequal", Token::Type::LESSEQUAL },
            { "greater", Token::Type::GREATER },
            { "greaterequal", Token::Type::GREATEREQUAL },
            { "pipepipe", Token::Type::PIPEPIPE },
            { "equalequal", Token::Type::EQUALEQUAL },

            // arithmetic operator
            { "star", Token::Type::STAR },
            { "starequal", Token::Type::STAREQUAL },
            { "plus", Token::Type::PLUS },
            { "plusplus", Token::Type::PLUSPLUS },
            { "plusequal", Token::Type::PLUSEQUAL },
            { "minus", Token::Type::MINUS },
            { "minusminus", Token::Type::MINUSMINUS },
            { "minusequal", Token::Type::MINUSEQUAL },
            { "slash", Token::Type::SLASH },
            { "slashequal", Token::Type::SLASHEQUAL },
            { "percent", Token::Type::PERCENT },
            { "percentequal", Token::Type::PERCENTEQUAL },

            // jumping
            { "break", Token::Type::BREAK },
            { "continue", Token::Type::CONTINUE },
            { "return", Token::Type::RETURN },
            { "throw", Token::Type::THROW },

            // memory allocation
            { "new", Token::Type::NEW },
            { "delete", Token::Type::DELETE },

            // this
            { "this", Token::Type::THIS },

            // casting
            { "const_cast", Token::Type::CONST_CAST },
            { "dynamic_cast", Token::Type::DYNAMIC_CAST },
            { "reinterpret_cast", Token::Type::REINTERPRET_CAST },
            { "static_cast", Token::Type::STATIC_CAST },
            
            // End Of File
            { "eof", Token::Type::eof } } {}
    
    Token::Type match(const std::string& key) const
        { return _table.contains(key) ? _table.at(key) : Token::Type::OTHERWISE; }

private:
    const std::unordered_map<std::string, Token::Type> _table;
};




void TokenTree::log(const fs::path& path) const
{
    std::ofstream ofs(path);
        
    for (auto& list : _stream)
        for (auto& tok : list) {

            ofs << tok.loc << " :\t" << '"' << tok.name << "\"\n";

            // Neighbor
            ofs << "\t\t- NEIGH  = { ";
            for (auto& str : *tok.neighbors)
                ofs << str << " , ";
            ofs << "}\n";

            // Parent
            ofs << "\t\t- PARENT = { ";
            for (auto& str : *tok.parent->neighbors)
                ofs << str << " , ";
            ofs << "}\n";

            // Children
            ofs << "\t\t- CHILD  = { ";
            if (tok.children)
                for (auto& str : *tok.children)
                    ofs << str << " , ";
            ofs << "}\n";

            // Pred
            ofs << "\t\t- PRED   = { ";
            for (auto& str : *tok.predecessor)
                ofs << str << " , ";
            ofs << "}\n";
            
            // Succ
            ofs << "\t\t- SUCC   = { ";
            for (auto& str : *tok.successor)
                ofs << str << " , ";

            ofs << "}\n\n";
        }
}
}
#endif
