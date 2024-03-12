#include "tokentree/tokentree_py.h"

namespace PAFL
{
TokenTreePy::TokenTreePy(const fs::path& src_file, const fs::path& bin, std::shared_ptr<TokenTree::Matcher> matcher, const fs::path& pytree_exe) :
    TokenTree(), _matcher(matcher)
{
    // Make python AST
    std::cout << src_file << '\n';
    fs::path temp_json(bin / Command::TEMPORARY_JSON);
    std::string cmd = "python3 " + pytree_exe.string() + " " + src_file.string() + " " + temp_json.c_str();
    std::system(cmd.c_str());
    
    { // Make Tree
        const auto doc(rapidjson::parseDoc(temp_json.c_str()));
        const auto& module = doc["module"].GetArray();
        PyPda pda(_root.get());
        _switchObject(pda, module);
    }
    std::remove(temp_json.c_str());
    setIndexr();
}



void TokenTreePy::_switchObject(PyPda& pda, const Array& statements)
{
    for (auto& stmt_obj : statements) {
    
        const auto& stmt = stmt_obj.GetObject();
        std::string type(stmt["type"].GetString());
        const auto& tokens = stmt["toks"].GetArray();

        // case: STMT
        if (type == TYPE_STMT)
            _addTokens(pda, tokens);
        // case: BRANCH
        else if (type == TYPE_BRANCH) {
            
            const auto& then = stmt["then"].GetArray();
            const auto& orelse = stmt["else"].GetArray();
            _caseBranch(pda, tokens, then, orelse);
        }
        // case: CLASS | FUNC
        else {

            const auto& then = stmt["then"].GetArray();
            _caseFunc(pda, tokens, then);
        }
    }
}



void TokenTreePy::_caseFunc(PyPda& pda, const Array& tokens, const Array& then)
{
    _addTokens(pda, tokens);
    pda.newBlock(_root.get());
    _switchObject(pda, then);
    pda.delBlock();
}



void TokenTreePy::_caseBranch(PyPda& pda, const Array& tokens, const Array& then, const Array& orelse)
{
    pda.newBlock(_addBranchTokens(pda, tokens));
    _switchObject(pda, then);
    _switchObject(pda, orelse);
    pda.delBlock();
}



void TokenTreePy::_addTokens(PyPda& pda, const Array& tokens)
{
    if (tokens.Empty())
        return;

    Token::List line;
    auto& stmt = _stream.emplace_back();
    for (auto& token_arr : tokens) {

        const auto& token = token_arr.GetArray();
        const auto ttype(token[0].GetString());
        const auto name(token[1].GetString());
        const auto lineno(token[2].GetUint());

        auto tok = &stmt.emplace_back(_matcher->match(ttype), lineno, name);
        tok->root = _root.get();
        line.push_back(tok);
    }

    pda.addTokens(line);
}



Token* TokenTreePy::_addBranchTokens(PyPda& pda, const Array& tokens)
{
    // Return future parent ( IF | FOR | MATCH | ... )
    Token* parent = nullptr;
    bool is_async = false;
    bool check_branch_keyword = true;

    Token::List line;
    auto& stmt = _stream.emplace_back();
    for (auto& token_arr : tokens) {

        const auto& token = token_arr.GetArray();
        const auto ttype(token[0].GetString());
        const auto name(token[1].GetString());
        const auto lineno(token[2].GetUint());

        auto tok = &stmt.emplace_back(_matcher->match(ttype), lineno, name);
        tok->root = _root.get();
        line.push_back(tok);

        if (check_branch_keyword) {

            // async -> [KEYWORD]
            if (is_async) {

                check_branch_keyword = false;
                parent = tok;
            }
            else {

                // -> async [KEYWORD]
                if (tok->name == "async")
                    is_async = true;
                // -> [KEYWORD]
                else {

                    check_branch_keyword = false;
                    parent = tok;
                }
            }
        }
    }

    pda.addTokens(line, std::make_shared<Token::List>());
    return parent;
}
}
