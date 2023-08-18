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

TokenType MatchTokenType(const char* str);

constexpr bool IsBranch(TokenType ttype)
    { return TokenType::FOR <= ttype && ttype <= TokenType::ELSE; }
constexpr bool IsOperatorOverloading(TokenType ttype)
    { return ttype == TokenType::NEW || ttype == TokenType::DELETE; }






class Token
{
public:
    Token(TokenType ttype, line_t loc, const std::string& name, Token* parent, Token* branch) :
        ttype(ttype), loc(loc), name(name), ochiai_sus(0.0f), sus(0.0f), parent(parent), branch(branch) {}
    
    // Token Relation
    Token* parent;
    Token* branch;
    std::list<Token*> conditions;
    std::list<Token*> children;
    std::unordered_set<Token*> condition_set;
    std::unordered_set<Token*> child_set;

    // Token Info
    TokenType ttype;
    line_t loc;
    std::string name;
    float ochiai_sus;
    float sus;


    void pushChild(Token* child)
        { children.push_back(child); child_set.insert(child); }
    void pushCondition(Token* cond)
        { conditions.push_back(cond); condition_set.insert(cond); }
};






class TokenTree
{
public:
    using ptoken_set = std::unordered_set<const Token*>;
    using token_list = std::list<Token>;
    using T = std::list<token_list>;
    using Vector = std::vector<TokenTree>;


    TokenTree(const std::filesystem::path& path_with_filename);

    size_t Size() const
        { return _line2tokens.size(); }
    size_t GetTotalTokenSize() const;

    token_list* GetTokens(line_t line)
        { return _line2tokens.contains(line) ? _line2tokens.at(line) : nullptr; }
    const ptoken_set* GetTokenSet(line_t line) const
        { return _line2token_set.contains(line) ? _line2token_set.at(line) : nullptr; }
    Token* GetRoot()
        { return &_root; }
    
    decltype(auto) begin()
        { return _token_stream.begin(); }
    decltype(auto) end()
        { return _token_stream.end(); }


private:
    T _token_stream;
    Token _root;

    std::unordered_map<line_t, token_list*> _line2tokens;
    std::unordered_map<line_t, ptoken_set*> _line2token_set;
    std::vector<ptoken_set> _ptoken_set;

    void _EraseInclude(const std::filesystem::path& path_with_filename);
    Token* _AddToken(TokenType ttype, const char* pos, line_t& line, Token* parent, Token* branch = nullptr);
    //void _ThrowOutOfMap(line_t line) const
    //    { throw std::out_of_range(std::string("invalid index '") + std::to_string(line) + "' from _index2tokens"); }
};
}






namespace PAFL
{
TokenType MatchTokenType(const std::string& str)
{
    static std::unordered_map<std::string, TokenType> table;
    static bool is_uninitialized = true;
    if (is_uninitialized) {

        // Reserve mapping table
        table.reserve(static_cast<size_t>(TokenType::OTHERWISE) + 1);
        
        // identifier
        table.emplace(std::string("identifier"), TokenType::IDENTIFIER);

        // branch
        table.emplace(std::string("for"), TokenType::FOR);
        table.emplace(std::string("if"), TokenType::IF);
        table.emplace(std::string("switch"), TokenType::SWITCH);
        table.emplace(std::string("while"), TokenType::WHILE);
        table.emplace(std::string("else"), TokenType::ELSE);

        // class
        table.emplace(std::string("namespace"), TokenType::NAMESPACE);
        table.emplace(std::string("enum"), TokenType::ENUM);
        table.emplace(std::string("class"), TokenType::CLASS);
        table.emplace(std::string("struct"), TokenType::STRUCT);
        table.emplace(std::string("union"), TokenType::UNION);

        // parenthesis
        table.emplace(std::string("l_paren"), TokenType::L_PAREN);
        table.emplace(std::string("r_paren"), TokenType::R_PAREN);
        table.emplace(std::string("l_brace"), TokenType::L_BRACE);
        table.emplace(std::string("r_brace"), TokenType::R_BRACE);
        //table.emplace(std::string("l_square"), TokenType::L_SQUARE);
        //table.emplace(std::string("r_square"), TokenType::R_SQUARE);

        // semicolon
        table.emplace(std::string("semi"), TokenType::SEMI);
        // colon
        table.emplace(std::string("colon"), TokenType::COLON);

        // bit operator
        table.emplace(std::string("amp"), TokenType::AMP);
        table.emplace(std::string("ampequal"), TokenType::AMPEQUAL);
        table.emplace(std::string("pipe"), TokenType::PIPE);
        table.emplace(std::string("pipeequal"), TokenType::PIPEEQUAL);
        table.emplace(std::string("caret"), TokenType::CARET);
        table.emplace(std::string("caretequal"), TokenType::CARETEQUAL);

        // shift operator
        table.emplace(std::string("lessless"), TokenType::LESSLESS);
        table.emplace(std::string("lesslessequal"), TokenType::LESSLESSEQUAL);
        table.emplace(std::string("greatergreater"), TokenType::GREATERGREATER);
        table.emplace(std::string("greatergreaterequal"), TokenType::GREATERGREATEREQUAL);

        // boolean operator
        table.emplace(std::string("ampamp"), TokenType::AMPAMP);
        table.emplace(std::string("exclaim"), TokenType::EXCLAIM);
        table.emplace(std::string("exclaimequal"), TokenType::EXCLAIMEQUAL);
        table.emplace(std::string("less"), TokenType::LESS);
        table.emplace(std::string("lessequal"), TokenType::LESSEQUAL);
        table.emplace(std::string("greater"), TokenType::GREATER);
        table.emplace(std::string("greaterequal"), TokenType::GREATEREQUAL);
        table.emplace(std::string("pipepipe"), TokenType::PIPEPIPE);
        table.emplace(std::string("equalequal"), TokenType::EQUALEQUAL);

        // arithmetic operator
        table.emplace(std::string("star"), TokenType::STAR);
        table.emplace(std::string("starequal"), TokenType::STAREQUAL);
        table.emplace(std::string("plus"), TokenType::PLUS);
        table.emplace(std::string("plusplus"), TokenType::PLUSPLUS);
        table.emplace(std::string("plusequal"), TokenType::PLUSEQUAL);
        table.emplace(std::string("minus"), TokenType::MINUS);
        table.emplace(std::string("minusminus"), TokenType::MINUSMINUS);
        table.emplace(std::string("minusequal"), TokenType::MINUSEQUAL);
        table.emplace(std::string("slash"), TokenType::SLASH);
        table.emplace(std::string("slashequal"), TokenType::SLASHEQUAL);
        table.emplace(std::string("percent"), TokenType::PERCENT);
        table.emplace(std::string("percentequal"), TokenType::PERCENTEQUAL);

        // jumping
        table.emplace(std::string("break"), TokenType::BREAK);
        table.emplace(std::string("continue"), TokenType::CONTINUE);
        table.emplace(std::string("return"), TokenType::RETURN);
        table.emplace(std::string("goto"), TokenType::GOTO);
        table.emplace(std::string("throw"), TokenType::THROW);

        // memory allocation
        table.emplace(std::string("new"), TokenType::NEW);
        table.emplace(std::string("delete"), TokenType::DELETE);

        // casting
        table.emplace(std::string("const_cast"), TokenType::CONST_CAST);
        table.emplace(std::string("dynamic_cast"), TokenType::DYNAMIC_CAST);
        table.emplace(std::string("reinterpret_cast"), TokenType::REINTERPRET_CAST);
        table.emplace(std::string("static_cast"), TokenType::STATIC_CAST);
        
        // End Of File
        table.emplace(std::string("eof"), TokenType::eof);
        is_uninitialized = false;
    }

    return table.contains(str) ? table.at(str) : TokenType::OTHERWISE;
}






TokenTree::TokenTree(const std::filesystem::path& path_with_filename) :
    _root(TokenType::ROOT, 0, "", nullptr, nullptr)
{
    // Erase header info
    _EraseInclude(path_with_filename);
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
        state_stack.push(BranchState::INITIAL);
        type_stack.push(TokenType::ROOT);
        parent_stack.push(&_root);
        Token* last_if = nullptr;


        for (const char* pos = buf; ; ++pos) {

            // Read buf
            const char* start = pos;
            for (; *pos != ' '; ++pos) {}
            TokenType ttype = MatchTokenType(std::string(start, pos - start));

            // If End Of File, break
            if (ttype == TokenType::eof) {

                _AddToken(TokenType::eof, pos, line, parent_stack.top());
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

                        Token* tok = _AddToken(ttype, pos, line, parent_stack.top()->parent, parent_stack.top());
                        parent_stack.top()->pushCondition(tok);
                    }
                    else {

                        Token* tok = _AddToken(ttype, pos, line, parent_stack.top());
                        if (state_stack.top() == BranchState::STMT)
                            parent_stack.top()->pushChild(tok);
                    }
                    break;
                }

                // branch
                case TokenType::FOR:
                case TokenType::IF:
                case TokenType::SWITCH:
                case TokenType::WHILE: {

                    Token* tok = _AddToken(ttype, pos, line, parent_stack.top());
                    tok->branch = tok;
                    if (state_stack.top() == BranchState::STMT)
                        parent_stack.top()->pushChild(tok);
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

                        Token* tok = _AddToken(ttype, pos, line, parent_stack.top()->parent, parent_stack.top());
                        parent_stack.top()->pushCondition(tok);
                    }
                    else {
                        
                        Token* tok = _AddToken(ttype, pos, line, parent_stack.top());
                        if (state_stack.top() == BranchState::STMT)
                            parent_stack.top()->pushChild(tok);
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

    // Build _line2tokens
    _line2tokens.reserve(_token_stream.size());
    // Build _line2token_set
    _ptoken_set.resize(_token_stream.size());
    _line2token_set.reserve(_token_stream.size());

    size_t i = 0;
    for (auto& iter : _token_stream) {

        _line2tokens.emplace(iter.begin()->loc, &iter);
        
        for (auto& tok : iter)
            _ptoken_set[i].insert(&tok);
        _line2token_set.emplace(iter.begin()->loc, &_ptoken_set[i++]);
    }
/*
    std::ofstream tok_ofs("token.txt");
    for (auto& tok_list : _token_stream)
        for (auto& tok : tok_list)
            tok_ofs << tok.name << " (" << &tok << ") " << " : line = " << tok.loc << " parent = " << tok.parent << " branch = " << tok.branch << " children_size = " << tok.children.size() << '\n';
*/
}



size_t TokenTree::GetTotalTokenSize() const
{
    size_t size = 0;
    for (auto& iter : _token_stream)
        size += iter.size();
    return size;
}



void TokenTree::_EraseInclude(const std::filesystem::path& path_with_filename)
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



Token* TokenTree::_AddToken(TokenType ttype, const char* pos, line_t& line, Token* parent, Token* branch)
{
    // Set token name
    for (; *pos != '\''; ++pos) {}
    const char* start = ++pos;
    size_t str_size = 0;
    for (; *pos != '\''; ++pos)
    ++str_size;

    // Set token loc
    for (; *pos != ':'; ++pos) {}
    line_t loc = static_cast<line_t>(std::atoll(pos + 1));

    // Push new token_list
    if (line != loc) {

        _token_stream.emplace_back();
        line = loc;
    }

    // Push token
    return &(_token_stream.rbegin()->emplace_back(ttype, loc, std::string(start, str_size), parent, branch));
}
}
#endif
