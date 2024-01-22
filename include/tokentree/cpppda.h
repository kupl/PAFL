#ifndef __CPPPDA_H__
#define __CPPPDA_H__

#include <stack>
#include "tokentree/tokentree.h"



namespace PAFL
{
class CppPda
{
public:
    CppPda(Token* root);
    void trans(Token* tok, Token* future);
    bool isTerminated(const Token* root) const;


private:
    enum class _State { ROOT, FUNC, STMT, COND, THEN };
    enum class _Lambda { ROOT, OPERATOR, CAPTURE, ARGS_BEGIN, ARGS, BODY_BEGIN };
    enum class _Prefix { ROOT, ID, TBD };

private:
    decltype(&CppPda::trans) _action[static_cast<size_t>(Token::Type::eof)];

    std::stack<_State> _state_stack;
    std::stack<Token::Type> _ttype_stack;
    std::stack<Token*> _parent_stack;

    std::stack<std::shared_ptr<Token::string_set>> _predecessor_stack;
    std::stack<std::shared_ptr<Token::string_set>> _neighbors_stack;
    std::stack<std::shared_ptr<Token::string_set>> _successor_stack;

    std::stack<_Lambda> _lambda_stack;
    _Prefix _prefix_state;

    bool _skip;
    
    
private:
    void _checkLambdaConnector(Token* tok);
    void _detPrefixType(Token* tok);

private:
    void _setFlatRelation(Token* tok);
    inline void _beginLine(_State state, Token::Type ttype) { _state_stack.push(state); _ttype_stack.push(ttype); }
    void _newBlock(_State state);
    inline void _newRoot(Token::Type ttype, Token* root)    { _beginLine(_State::ROOT, ttype); _parent_stack.push(root); }
    void _endLine();
    void _deleteBlock();
    void _deleteRoot()                                      { _state_stack.pop(); _parent_stack.pop(); }
    void _deleteIfBlock(Token* future);

private:
    // block -> FUNC | THEN
    constexpr bool _isBlock(_State state)   { return state == _State::FUNC || state == _State::THEN; }
    // line -> STMT | COND
    constexpr bool _isLine(_State state)    { return state == _State::STMT || state == _State::COND; }


private:// Action
    void _identifier(Token* tok, Token* future);
    void _branch(Token* tok, Token* future);
    // case | default
    void _case(Token* tok, Token* future)       { if (_state_stack.top() == _State::THEN) _beginLine(_State::STMT, tok->type); }
    void _do(Token* tok, Token* future)         { _beginLine(_State::THEN, tok->type); }
    void _try(Token* tok, Token* future);
    void _operator(Token* tok, Token* future)   { if (_lambda_stack.top() == _Lambda::ROOT) _lambda_stack.push(_Lambda::OPERATOR); }
    // enum | class
    void _enum(Token* tok, Token* future);
    void _class(Token* tok, Token* future)      { if (_ttype_stack.top() != Token::Type::ENUM) _enum(tok, future); }
    // namespace
    void _namespace(Token* tok, Token* future);
    // l_paren
    void _l_paren(Token* tok, Token* future)    { _otherwise(tok, future); _ttype_stack.push(tok->type); }
    // symbol
    void _r_paren(Token* tok, Token* future);
    void _l_brace(Token* tok, Token* future);
    void _r_brace(Token* tok, Token* future);
    void _l_square(Token* tok, Token* future);
    void _r_square(Token* tok, Token* future);
    void _semi(Token* tok, Token* future);
    void _colon(Token* tok, Token* future);
    // otherwise
    void _otherwise(Token* tok, Token* future)  { if (_isBlock(_state_stack.top())) _beginLine(_State::STMT, Token::Type::STMT); }
};
}
#endif
