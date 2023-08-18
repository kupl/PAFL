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
constexpr auto TEMPORARY_CPP = "___temp.cpp";
constexpr auto TEMPORARY_TXT = "___temp.txt";
constexpr auto DUMP_COMMAND = "clang++ -fsyntax-only -Xclang -dump-tokens ___temp.cpp 2>&1 | tee ___temp.txt";

enum class TokenType
{
    // identifier
    IDENTIFIER,

    // branch
    FOR,
    IF,
    SWITCH,
    WHILE,
    ELSE,

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
    GOTO,
    THROW,

    // memory allocation
    NEW,
    DELETE,

    // casting
    CONST_CAST,
    DYNAMIC_CAST,
    REINTERPRET_CAST,
    STATIC_CAST,


    // virtual root type
    ROOT,

    // otherwise
    OTHERWISE,

    // End Of File
    eof
};

constexpr bool IsBranch(TokenType ttype)
    { return TokenType::FOR <= ttype && ttype <= TokenType::ELSE; }






class Token
{
public:
    Token(TokenType ttype, line_t loc, const std::string& name,
        Token* root, Token* parent) :
        ttype(ttype), loc(loc), name(name),
        root(root), parent(parent) {}
    
    // Token Relation
    Token* root;
    Token* parent;
    std::shared_ptr<std::unordered_set<std::string>> neighbors;
    std::shared_ptr<std::unordered_set<std::string>> children;

    // Token Info
    TokenType ttype;
    line_t loc;
    std::string name;
};






class TokenTree
{
public:
    class Matcher;
    using Vector = std::vector<TokenTree>;


    TokenTree(const std::filesystem::path& path_with_filename, std::shared_ptr<Matcher> matcher);

    size_t size() const
        { return _stream.size(); }
    size_t getTotalTokenSize() const;

    const Token* getRoot() const
        { return &_root; }
    decltype(auto) getTokens(line_t line) const
        { return _tokens_indexer.contains(line) ? _tokens_indexer.at(line) : nullptr; }
    
    decltype(auto) cbegin() const
        { return _stream.cbegin(); }
    decltype(auto) cend() const
        { return _stream.cend(); }


private:
    Token _root;
    std::list<std::list<Token>> _stream;
    std::unordered_map<line_t, decltype(_stream)::value_type*> _tokens_indexer;

    std::shared_ptr<Matcher> _matcher;
    void _eraseInclude(const std::filesystem::path& path_with_filename) const;
    Token* _emplaceToken(TokenType ttype, const char* pos, line_t& line, Token* parent);
};
}






namespace PAFL
{
class TokenTree::Matcher
{
public:
    Matcher() :
        _table {
            // identifier
            { "identifier", TokenType::IDENTIFIER },

            // branch
            { "for", TokenType::FOR },
            { "if", TokenType::IF },
            { "switch", TokenType::SWITCH },
            { "while", TokenType::WHILE },
            { "else", TokenType::ELSE },

            // class
            { "namespace", TokenType::NAMESPACE },
            { "enum", TokenType::ENUM },
            { "class", TokenType::CLASS },
            { "struct", TokenType::STRUCT },
            { "union", TokenType::UNION },

            // parenthesis
            { "l_paren", TokenType::L_PAREN },
            { "r_paren", TokenType::R_PAREN },
            { "l_brace", TokenType::L_BRACE },
            { "r_brace", TokenType::R_BRACE },
            //{ "l_square", TokenType::L_SQUARE },
            //{ "r_square", TokenType::R_SQUARE },

            // semicolon
            { "semi", TokenType::SEMI },
            // colon
            { "colon", TokenType::COLON },

            // bit operator
            { "amp", TokenType::AMP },
            { "ampequal", TokenType::AMPEQUAL },
            { "pipe", TokenType::PIPE },
            { "pipeequal", TokenType::PIPEEQUAL },
            { "caret", TokenType::CARET },
            { "caretequal", TokenType::CARETEQUAL },

            // shift operator
            { "lessless", TokenType::LESSLESS },
            { "lesslessequal", TokenType::LESSLESSEQUAL },
            { "greatergreater", TokenType::GREATERGREATER },
            { "greatergreaterequal", TokenType::GREATERGREATEREQUAL },

            // boolean operator
            { "ampamp", TokenType::AMPAMP },
            { "exclaim", TokenType::EXCLAIM },
            { "exclaimequal", TokenType::EXCLAIMEQUAL },
            { "less", TokenType::LESS },
            { "lessequal", TokenType::LESSEQUAL },
            { "greater", TokenType::GREATER },
            { "greaterequal", TokenType::GREATEREQUAL },
            { "pipepipe", TokenType::PIPEPIPE },
            { "equalequal", TokenType::EQUALEQUAL },

            // arithmetic operator
            { "star", TokenType::STAR },
            { "starequal", TokenType::STAREQUAL },
            { "plus", TokenType::PLUS },
            { "plusplus", TokenType::PLUSPLUS },
            { "plusequal", TokenType::PLUSEQUAL },
            { "minus", TokenType::MINUS },
            { "minusminus", TokenType::MINUSMINUS },
            { "minusequal", TokenType::MINUSEQUAL },
            { "slash", TokenType::SLASH },
            { "slashequal", TokenType::SLASHEQUAL },
            { "percent", TokenType::PERCENT },
            { "percentequal", TokenType::PERCENTEQUAL },

            // jumping
            { "break", TokenType::BREAK },
            { "continue", TokenType::CONTINUE },
            { "return", TokenType::RETURN },
            { "goto", TokenType::GOTO },
            { "throw", TokenType::THROW },

            // memory allocation
            { "new", TokenType::NEW },
            { "delete", TokenType::DELETE },

            // casting
            { "const_cast", TokenType::CONST_CAST },
            { "dynamic_cast", TokenType::DYNAMIC_CAST },
            { "reinterpret_cast", TokenType::REINTERPRET_CAST },
            { "static_cast", TokenType::STATIC_CAST },
            
            // End Of File
            { "eof", TokenType::eof } } {}
    
    TokenType match(const std::string& key)
        { return _table.contains(key) ? _table.at(key) : TokenType::OTHERWISE; }

private:
    std::unordered_map<std::string, TokenType> _table;
};






TokenTree::TokenTree(const std::filesystem::path& path_with_filename, std::shared_ptr<Matcher> matcher) :
    _root(TokenType::ROOT, 0, "", &_root, nullptr), _matcher(matcher)
{
    // Erase header info
    _eraseInclude(path_with_filename);
    // clang++ dump-tokens
    std::system(DUMP_COMMAND);
    std::remove(TEMPORARY_CPP);

    // Read .txt file
    std::ifstream ifs(TEMPORARY_TXT);
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();

    char* buf = (char*)std::malloc(size * sizeof(char));
    if (!buf) {

        std::remove(TEMPORARY_TXT);
        throw std::range_error("malloc failed");
    }

    ifs.seekg(0);
    ifs.read(buf, size);
    ifs.close();


    // Tokenize
    {
        line_t line = 0;
        enum class BranchState { INITIAL, COND, STMT, ELSE };
        std::stack<BranchState> state_stack;
        std::stack<TokenType> type_stack;
        std::stack<Token*> parent_stack;
        std::stack<decltype(Token::neighbors)> neighbor_stack;

        state_stack.push(BranchState::INITIAL);
        type_stack.push(TokenType::ROOT);
        parent_stack.push(&_root);
        Token* last_if = nullptr;


        for (const char* pos = buf; ; ++pos) {

            // Read buf
            const char* start = pos;
            for (; *pos != ' '; ++pos) {}
            TokenType ttype = _matcher->match(std::string(start, pos - start));

            // If End Of File, break
            if (ttype == TokenType::eof) {

                _emplaceToken(TokenType::eof, pos, line, parent_stack.top());
                break;
            }

            // Inherit last IF
            if (last_if && ttype == TokenType::ELSE) {

                type_stack.push(ttype);
                state_stack.push(BranchState::STMT);
                parent_stack.push(last_if);
            }
            last_if = nullptr;

            // case
            switch (ttype) {

                // identifier
                case TokenType::IDENTIFIER: {

                    if (state_stack.top() == BranchState::COND) {

                        Token* tok = _emplaceToken(ttype, pos, line, parent_stack.top()->parent);
                        parent_stack.top()->children->insert(tok->name);
                    }
                    else {

                        Token* tok = _emplaceToken(ttype, pos, line, parent_stack.top());
                        if (state_stack.top() == BranchState::STMT)
                            parent_stack.top()->children->insert(tok->name);
                    }
                    break;
                }

                // branch
                case TokenType::FOR:
                case TokenType::IF:
                case TokenType::SWITCH:
                case TokenType::WHILE: {

                    Token* tok = _emplaceToken(ttype, pos, line, parent_stack.top());
                    tok->children = std::make_shared<decltype(Token::children)::element_type>();

                    if (state_stack.top() == BranchState::STMT)
                        parent_stack.top()->children->insert(tok->name);
                    type_stack.push(ttype);
                    state_stack.push(BranchState::COND);
                    parent_stack.push(tok);
                    break;
                }

                case TokenType::ELSE:
                case TokenType::NAMESPACE:
                case TokenType::ENUM:
                case TokenType::CLASS:
                case TokenType::STRUCT:
                case TokenType::UNION:
                    break;

                // parenthesis
                case TokenType::L_PAREN: {

                    type_stack.push(ttype);
                    break;
                }
                case TokenType::R_PAREN: {

                    type_stack.pop();
                    if (state_stack.top() == BranchState::COND && IsBranch(type_stack.top()))
                        state_stack.top() = BranchState::STMT;
                    break;
                }
                case TokenType::L_BRACE: {

                    type_stack.push(ttype);
                    neighbor_stack.emplace();
                    break;
                }
                case TokenType::R_BRACE: {

                    type_stack.pop();
                    if (state_stack.top() == BranchState::STMT && IsBranch(type_stack.top()))
                        while (IsBranch(type_stack.top())) {
                            
                            if (!last_if && type_stack.top() == TokenType::IF)
                                last_if = parent_stack.top();
                            type_stack.pop();
                            state_stack.pop();
                            parent_stack.pop();
                        }
                    break;
                }
                case TokenType::SEMI: {

                    if (state_stack.top() == BranchState::STMT && IsBranch(type_stack.top()))
                        while (IsBranch(type_stack.top())) {
                            
                            if (!last_if && type_stack.top() == TokenType::IF)
                                last_if = parent_stack.top();
                            type_stack.pop();
                            state_stack.pop();
                            parent_stack.pop();
                        }
                    break;
                }

                case TokenType::COLON:
                case TokenType::OTHERWISE:
                    break;
                
                default: {
                    
                    if (state_stack.top() == BranchState::COND) {

                        Token* tok = _emplaceToken(ttype, pos, line, parent_stack.top()->parent);
                        parent_stack.top()->neighbors->insert(tok->name);
                    }
                    else {
                        
                        Token* tok = _emplaceToken(ttype, pos, line, parent_stack.top());
                        if (state_stack.top() == BranchState::STMT)
                            parent_stack.top()->children->insert(tok->name);
                    }
                }
            }
            

            // Move to next line
            for (; *pos != '\n'; ++pos) {}
        }
    }


    // Free & Remove
    std::free(buf);
    std::remove(TEMPORARY_TXT);

    _tokens_indexer.reserve(_stream.size());
    for (auto& list : _stream)
        _tokens_indexer.emplace(list.begin()->loc, &list);
/*
    std::ofstream tok_ofs("token.txt");
    for (auto& tok_list : _token_stream)
        for (auto& tok : tok_list)
            tok_ofs << tok.name << " (" << &tok << ") " << " : line = " << tok.loc << " parent = " << tok.parent << " left_most = " << tok.left_most << " children_size = " << tok.children.size() << '\n';
*/
}



size_t TokenTree::getTotalTokenSize() const
{
    size_t size = 0;
    for (auto& item : _stream)
        size += item.size();
    return size;
}



void TokenTree::_eraseInclude(const std::filesystem::path& path_with_filename) const
{
    /*
    state : 0-11
    (0) -> #(1)
    (1) -> ' '(1) | \t(1) | i(2)
    (2) -> n(3), c(4), l(5), u(6), d(7), e(8)
    (8) -> ' '(8) | \t(8) | <(9) | "(11)
    (9) -> _(9) | >(11)
    (10) -> _(10) | "(11)
    else -> (0)
    */
    static char include_table[11][128] = {
    // # include
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // <header> | "header"
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0 }
    };


    // Read file (.c | .cc | .cpp | .h | .hpp)
    std::ifstream ifs(path_with_filename);
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();

    char* buf = (char*)std::malloc(size * sizeof(char));
    if (!buf)
        throw std::range_error("malloc failed");

    ifs.seekg(0);
    ifs.read(buf, size);
    ifs.close();


    // match -> # include <> | # include ""
    int state = 0;
    unsigned long long start = 0;
    bool was_backslash = false;
    bool is_in_str = false;
    
    for (unsigned long long i = 0; i != size; ++i) {

        if (was_backslash)
            was_backslash = false;

        else if (!was_backslash && buf[i] == '\\')
            was_backslash = true;

        else {

            // If #include not in str, update state
            state = include_table[state][buf[i]];
            if (state == 0)
                start = i;
            else if (state == 11) {

                state = 0;
                // Preserve line location
                for(char* ptr = buf + start; ptr != buf + i + 1; ptr++)
                    if (*ptr != '\n')
                        *ptr = ' ';
            }
        }
    }


    std::cout.write(buf, size);
    std::ofstream ofs(TEMPORARY_CPP);
    ofs.write(buf, size);
    ofs.close();
    std::free(buf);
}



Token* TokenTree::_emplaceToken(TokenType ttype, const char* pos, line_t& line, Token* parent)
{
    // Set token name
    for (; *pos != '\''; ++pos) {}
    const char* start = ++pos;
    size_t str_size = 0;
    for (; *pos != '\''; ++pos)
    ++str_size;
    std::string name(start, str_size);

    // Set token loc
    for (; *pos != ':'; ++pos) {}
    line_t loc = static_cast<line_t>(std::atoll(pos + 1));

    // Push new token_list
    if (line != loc) {

        _stream.emplace_back();
        line = loc;
    }

    // Push token
    return &_stream.rbegin()->emplace_back(ttype, loc, name, &_root, parent);
}
}
#endif
