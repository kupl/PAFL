#include "tokentree/tokentree.h"

namespace PAFL
{
TokenTree::Matcher::Matcher() : _table
{
    // identifier
    { "identifier", Token::Type::IDENTIFIER },

    // branch
    { "if", Token::Type::IF },
    { "catch", Token::Type::CATCH },
    { "for", Token::Type::FOR },
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
    { "tilde", Token::Type::TILDE },

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
    { "in", Token::Type::IN },
    { "is", Token::Type::IS },

    // arithmetic operator
    { "star", Token::Type::STAR },
    { "starequal", Token::Type::STAREQUAL },
    { "starstar", Token::Type::STARSTAR },
    { "plus", Token::Type::PLUS },
    { "plusplus", Token::Type::PLUSPLUS },
    { "plusequal", Token::Type::PLUSEQUAL },
    { "minus", Token::Type::MINUS },
    { "minusminus", Token::Type::MINUSMINUS },
    { "minusequal", Token::Type::MINUSEQUAL },
    { "slash", Token::Type::SLASH },
    { "slashequal", Token::Type::SLASHEQUAL },
    { "slashslash", Token::Type::SLASHSLASH },
    { "slashslashequal", Token::Type::SLASHSLASHEQUAL },
    { "percent", Token::Type::PERCENT },
    { "percentequal", Token::Type::PERCENTEQUAL },
    { "matmul", Token::Type::MATMUL },
    { "colonequal", Token::Type::COLONEQUAL },

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
    { "eof", Token::Type::eof }
} {}



TokenTree::TokenTree() :
    _root(std::make_unique<Token>(Token::Type::ROOT, 0, ""))
{
    _root->root = _root->parent = nullptr;
    _root->predecessor = _root->neighbors = _root->successor = std::make_shared<Token::List>();
}



void TokenTree::log(const fs::path& path) const
{
    std::ofstream ofs(path);
        
    for (auto& list : _stream)
        for (auto& tok : list) {

            ofs << tok.loc << " :\t" << '"' << tok.name << "\"\n";

            // Neighbor
            ofs << "\t\t- NEIGH  = { ";
            for (auto ptr : *tok.neighbors)
                ofs << ptr->name << " , ";
            ofs << "}\n";

            // Parent
            ofs << "\t\t- PARENT = { ";
            for (auto ptr : *tok.parent->neighbors)
                ofs << ptr->name << " , ";
            ofs << "}\n";

            // Children
            ofs << "\t\t- CHILD  = { ";
            if (tok.children)
                for (auto ptr : *tok.children)
                    ofs << ptr->name << " , ";
            ofs << "}\n";

            // Pred
            ofs << "\t\t- PRED   = { ";
            for (auto ptr : *tok.predecessor)
                ofs << ptr->name << " , ";
            ofs << "}\n";
            
            // Succ
            ofs << "\t\t- SUCC   = { ";
            for (auto ptr : *tok.successor)
                ofs << ptr->name << " , ";

            ofs << "}\n\n";
        }
}



void TokenTree::_setIndexr()
{
    _tokens_indexer.reserve(_stream.size());
    for (auto& list : _stream)
        _tokens_indexer.emplace(list.begin()->loc, &list);
}
}
