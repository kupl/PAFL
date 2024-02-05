#ifndef __TOKENTREE_PY_H__
#define __TOKENTREE_PY_H__

#include "tokentree/pypda.h"
#include "tokentree/tokentree_cmd.h"
#include "rapidjson.h"


namespace PAFL
{
class TokenTreePy : public TokenTree
{
private:
    const char* TYPE_CLASS = "CLASS";
    const char* TYPE_FUNC = "FUNC";
    const char* TYPE_BRANCH = "BRANCH";
    const char* TYPE_STMT = "STMT";

public:
    TokenTreePy(const fs::path& src_file, std::shared_ptr<TokenTree::Matcher> matcher, const fs::path& pytree_exe);

private:
    using Array = rapidjson::GenericArray<true, rapidjson::Value>;
    using Object = rapidjson::GenericObject<true, rapidjson::Value>;

private:
    void _switchObject(PyPda& pda, const Array& statements);
    // CLASS | FUNC
    void _caseFunc(PyPda& pda, const Array& tokens, const Array& then);
    // BRANCH
    void _caseBranch(PyPda& pda, const Array& tokens, const Array& then, const Array& orelse);
    void _addTokens(PyPda& pda, const Array& tokens);
    Token* _addBranchTokens(PyPda& pda, const Array& tokens);

private:
    std::shared_ptr<TokenTree::Matcher> _matcher;
};
}
#endif
