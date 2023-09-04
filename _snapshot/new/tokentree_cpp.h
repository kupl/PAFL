#ifndef __TOKENTREE_CPP_H__
#define __TOKENTREE_CPP_H__

#include "cpppda.h"

namespace PAFL
{
constexpr auto TEMPORARY_CPP = "___temp.cpp";
constexpr auto TEMPORARY_TXT = "___temp.txt";
constexpr auto DUMP_COMMAND = "clang++ -fsyntax-only -Xclang -dump-tokens ___temp.cpp 2>&1 | tee ___temp.txt";


class CppTokenTree : public TokenTree
{
public:
    class Matcher;

    CppTokenTree(const std::filesystem::path& path_with_filename, std::shared_ptr<CppTokenTree::Matcher> matcher);

private:
    std::list<Token> _getRawStream(const std::filesystem::path& path_with_filename, std::shared_ptr<CppTokenTree::Matcher> matcher) const;
};

void _eraseInclude(const std::filesystem::path& path_with_filename);
}






namespace PAFL
{
class CppTokenTree::Matcher
{
public:
    Matcher() :
        _table {
            // identifier
            { "identifier", Token::Type::IDENTIFIER },

            // branch
            { "for", Token::Type::FOR },
            { "if", Token::Type::IF },
            { "switch", Token::Type::SWITCH },
            { "while", Token::Type::WHILE },
            { "else", Token::Type::ELSE },
            // switch
            { "case", Token::Type::CASE },
            { "default", Token::Type::DEFAULT },

            // class
            { "namespace", Token::Type::NAMESPACE },
            { "enum", Token::Type::ENUM },
            { "class", Token::Type::CLASS },
            { "struct", Token::Type::STRUCT },
            { "union", Token::Type::UNION },

            // parenthesis
            { "l_paren", Token::Type::L_PAREN },
            { "r_paren", Token::Type::R_PAREN },
            { "l_brace", Token::Type::L_BRACE },
            { "r_brace", Token::Type::R_BRACE },
            //{ "l_square", Token::Type::L_SQUARE },
            //{ "r_square", Token::Type::R_SQUARE },

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

            // casting
            { "const_cast", Token::Type::CONST_CAST },
            { "dynamic_cast", Token::Type::DYNAMIC_CAST },
            { "reinterpret_cast", Token::Type::REINTERPRET_CAST },
            { "static_cast", Token::Type::STATIC_CAST },
            
            // End Of File
            { "eof", Token::Type::eof } } {}
    
    Token::Type match(const std::string& key)
        { return _table.contains(key) ? _table.at(key) : Token::Type::OTHERWISE; }

private:
    std::unordered_map<std::string, Token::Type> _table;
};
}






namespace PAFL
{
CppTokenTree::CppTokenTree(const std::filesystem::path& path_with_filename, std::shared_ptr<CppTokenTree::Matcher> matcher) :
    TokenTree(path_with_filename)
{
    // Tokenize
    HierarchyPda hierarchy(&_root);
    line_t line = 0;

    for (auto& token : _getRawStream(path_with_filename, matcher)) {
            
        Token* tok = &token;
        if (token.type < Token::Type::OTHERWISE &&
            (token.type < Token::Type::ELSE || Token::Type::COLON < token.type)) {

            if (line != token.loc) {

                _stream.emplace_back();
                line = token.loc;
            }

            tok = &_stream.rbegin()->emplace_back(token.type, line, token.name);
        }
        tok->root = &_root;

        hierarchy.trans(tok);
    }

    
    _tokens_indexer.reserve(_stream.size());
    for (auto& list : _stream)
        _tokens_indexer.emplace(list.begin()->loc, &list);
}






void _eraseInclude(const std::filesystem::path& path_with_filename)
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
    static constexpr char include_table[11][128] = {
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



std::list<Token> CppTokenTree::_getRawStream(const std::filesystem::path& path_with_filename, std::shared_ptr<CppTokenTree::Matcher> matcher) const
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
    std::remove(TEMPORARY_TXT);


    // Tokenize
    std::list<Token> stream;
    for (const char* pos = buf; ; ++pos) {

        // Read buf
        const char* start = pos;
        for (; *pos != ' '; ++pos) {}
        Token::Type ttype = matcher->match(std::string(start, pos - start));
        std::cout << (size_t)ttype << '\n';

        // If End Of File, break
        if (ttype == Token::Type::eof)
            break;
        
        // Set token name
        for (; *pos != '\''; ++pos) {}
        start = ++pos;
        for (; *pos != '\''; ++pos) {}
        std::string name(start, pos - start);

        // Push token
        for (; *pos != ':'; ++pos) {}
        stream.emplace_back(ttype, static_cast<line_t>(std::atoll(pos + 1)), name);

        // Move to next line
        for (; *pos != '\n'; ++pos) {}
    }


    std::free(buf);
    return stream;
}
}
#endif
