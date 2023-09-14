#ifndef __CPPPDA_H__
#define __CPPPDA_H__

#include <stack>
#include "tokentree.h"



namespace PAFL
{
class CppPda
{
public:
    CppPda(Token* root);
    void trans(Token* tok);
    bool isTerminated(const Token* root) const;


private:
    enum class _State { ROOT, FUNC, STMT, COND, THEN, TRIAL };
    enum class _Lambda { ROOT, OPERATOR, CAPTURE, ARGS_BEGIN, ARGS, BODY_BEGIN };
    enum class _Struct { ROOT, ID, TBD };

    void _inheritLastIf(Token* tok);
    void _checkLambdaConnector(Token* tok);
    void _detClassType(Token* tok);

    void _setFlatRelation(Token* tok);

    inline void _beginLine(_State state, Token::Type ttype)
        { _state_stack.push(state); _ttype_stack.push(ttype); }
    void _newBlock(_State state);
    inline void _newRoot(Token::Type ttype, Token* root)
        { _beginLine(_State::ROOT, ttype); _parent_stack.push(root); }

    void _endLine();
    void _deleteBlock();
    void _deleteRoot();
    void _deleteWhileBranch();

    // block -> FUNC | THEN
    constexpr bool _isBlock(_State state)
        { return state == _State::FUNC || state == _State::THEN || state == _State::TRIAL; }
    // line -> STMT | COND
    constexpr bool _isLine(_State state)
        { return state == _State::STMT || state == _State::COND; }
    // root -> ROOT | ENUM | CLASS


    decltype(&CppPda::trans) _action[static_cast<size_t>(Token::Type::eof)];

    std::stack<_State> _state_stack;
    std::stack<Token::Type> _ttype_stack;

    std::stack<Token*> _parent_stack;
    Token* _last_if;
    
    std::stack<std::shared_ptr<Token::string_set>> _predecessor_stack;
    std::stack<std::shared_ptr<Token::string_set>> _neighbors_stack;
    std::stack<std::shared_ptr<Token::string_set>> _successor_stack;

    std::stack<_Lambda> _lambda_stack;
    _Struct _struct_state;

    /* Action */
    void _identifier(Token* tok);
    void _branch(Token* tok);
    // case | default
    void _case(Token* tok)
        { if (_state_stack.top() == _State::THEN) _beginLine(_State::STMT, tok->type); }
    void _trial(Token* tok)
        { _beginLine(_State::TRIAL, tok->type); }
    void _operator(Token* tok)
        { if (_lambda_stack.top() == _Lambda::ROOT) _lambda_stack.push(_Lambda::OPERATOR); }
    // enum | class
    void _enum(Token* tok);
    void _class(Token* tok);
    // namespace | l_paren
    void _left(Token* tok)
        { _otherwise(tok); _ttype_stack.push(tok->type); }
    // symbol
    void _l_paren(Token* tok);
    void _r_paren(Token* tok);
    void _l_brace(Token* tok);
    void _r_brace(Token* tok);
    void _l_square(Token* tok);
    void _r_square(Token* tok);
    void _semi(Token* tok);
    void _colon(Token* tok);
    // otherwise
    void _otherwise(Token* tok)
        { if (_isBlock(_state_stack.top())) _beginLine(_State::STMT, Token::Type::STMT); }
};
}






namespace PAFL
{
CppPda::CppPda(Token* root) :
    _action{ &CppPda::_identifier, nullptr, }, _struct_state(_Struct::ROOT)
{
    _newRoot(Token::Type::ROOT, root);
    _lambda_stack.push(_Lambda::ROOT);

    // Set action map
        // id
    for (auto i = static_cast<size_t>(Token::Type::AMP); i != static_cast<size_t>(Token::Type::OTHERWISE); i++)
        _action[i] = &CppPda::_identifier;
        // branch
    _action[static_cast<size_t>(Token::Type::CATCH)] = _action[static_cast<size_t>(Token::Type::FOR)]
    = _action[static_cast<size_t>(Token::Type::IF)] = _action[static_cast<size_t>(Token::Type::SWITCH)]
    = _action[static_cast<size_t>(Token::Type::WHILE)] = &CppPda::_branch;
        // switch
    _action[static_cast<size_t>(Token::Type::CASE)] = _action[static_cast<size_t>(Token::Type::DEFAULT)] = &CppPda::_case;
        // trial and error
    _action[static_cast<size_t>(Token::Type::DO)] = _action[static_cast<size_t>(Token::Type::TRY)] = &CppPda::_trial;
        // operator overriding
    _action[static_cast<size_t>(Token::Type::OPERATOR)] = &CppPda::_operator;
        // enum | class
    _action[static_cast<size_t>(Token::Type::ENUM)] = &CppPda::_enum;
    _action[static_cast<size_t>(Token::Type::CLASS)] =  _action[static_cast<size_t>(Token::Type::STRUCT)]
    = _action[static_cast<size_t>(Token::Type::UNION)] = &CppPda::_class;
        // namespace | l_paren
    _action[static_cast<size_t>(Token::Type::NAMESPACE)] = _action[static_cast<size_t>(Token::Type::L_PAREN)] = &CppPda::_left;
        // symbol
    _action[static_cast<size_t>(Token::Type::R_PAREN)] = &CppPda::_r_paren;
    _action[static_cast<size_t>(Token::Type::L_BRACE)] = &CppPda::_l_brace;
    _action[static_cast<size_t>(Token::Type::R_BRACE)] = &CppPda::_r_brace;
    _action[static_cast<size_t>(Token::Type::L_SQUARE)] = &CppPda::_l_square;
    _action[static_cast<size_t>(Token::Type::R_SQUARE)] = &CppPda::_r_square;
    _action[static_cast<size_t>(Token::Type::SEMI)] = &CppPda::_semi;
    _action[static_cast<size_t>(Token::Type::COLON)] = &CppPda::_colon;
        // otherwise
    _action[static_cast<size_t>(Token::Type::OTHERWISE)] = &CppPda::_otherwise;
}

void CppPda::trans(Token* tok)
{
    _inheritLastIf(tok);
    _checkLambdaConnector(tok);
    _detClassType(tok);
    if (_action[static_cast<size_t>(tok->type)])
        (this->*_action[static_cast<size_t>(tok->type)])(tok);
}

bool CppPda::isTerminated(const Token* root) const
{
    if (_state_stack.size() != 1 || _ttype_stack.size() != 1
        || _parent_stack.size() != 1 || _lambda_stack.size() != 1)
        return false;

    if (_state_stack.top() != _State::ROOT || _ttype_stack.top() != Token::Type::ROOT
        || _parent_stack.top() != root || _lambda_stack.top() != _Lambda::ROOT)
        return false;
    
    if (!_neighbors_stack.empty() || !_predecessor_stack.empty() || !_successor_stack.empty())
        return false;

    return true;
}






void CppPda::_inheritLastIf(Token* tok)
{
    if (_last_if && tok->type == Token::Type::ELSE) {

        _newBlock(_State::THEN);
        _ttype_stack.push(tok->type);
        _parent_stack.push(_last_if);
    }
    _last_if = nullptr;
}

void CppPda::_checkLambdaConnector(Token* tok)
{
    if (_lambda_stack.top() == _Lambda::OPERATOR) {

        if (tok->type != Token::Type::L_SQUARE)
            _lambda_stack.pop();
    }

    else if (_lambda_stack.top() == _Lambda::ARGS_BEGIN) {

        if (tok->type == Token::Type::L_PAREN)
            _lambda_stack.top() = _Lambda::ARGS;

        else {

            _ttype_stack.pop();
            _lambda_stack.pop();
        }
    }

    else if (_lambda_stack.top() == _Lambda::BODY_BEGIN && tok->type != Token::Type::L_BRACE)
        _lambda_stack.pop();
}

void CppPda::_detClassType(Token* tok)
{
    if (_struct_state == _Struct::ROOT)
        return;

    if (_struct_state == _Struct::ID && tok->type == Token::Type::IDENTIFIER) {

        _struct_state = _Struct::TBD;
        return;
    }

    if (tok->type != Token::Type::SEMI && tok->type != Token::Type::COLON && tok->type != Token::Type::L_BRACE) {

        _ttype_stack.pop();
        if (_state_stack.top() == _State::STMT)
            _ttype_stack.push(Token::Type::STMT);
    }
    _struct_state = _Struct::ROOT;
}






void CppPda::_setFlatRelation(Token* tok)
{
    tok->predecessor = _predecessor_stack.top();
    tok->neighbors = _neighbors_stack.top();
    tok->successor = _successor_stack.top();
    _neighbors_stack.top()->insert(tok->name);
}

void CppPda::_newBlock(_State state)
{
    _state_stack.push(state);

    _predecessor_stack.emplace();
    _neighbors_stack.emplace();
    _successor_stack.emplace();
    _predecessor_stack.top() = std::make_shared<Token::string_set>();
    _neighbors_stack.top() = std::make_shared<Token::string_set>();
    _successor_stack.top() = std::make_shared<Token::string_set>();
}



void CppPda::_endLine()
{
    _state_stack.pop();
    
    _predecessor_stack.top() = _neighbors_stack.top();
    _neighbors_stack.top() = _successor_stack.top();

    _successor_stack.pop();
    _successor_stack.emplace();
    _successor_stack.top() = std::make_shared<Token::string_set>();
}

void CppPda::_deleteBlock()
{
    _state_stack.pop();

    _predecessor_stack.pop();
    _neighbors_stack.pop();
    _successor_stack.pop();
}

void CppPda::_deleteRoot()
{
    _state_stack.pop();
    _parent_stack.pop();
}

void CppPda::_deleteWhileBranch()
{
    // Delete branch
    if (_state_stack.top() == _State::THEN && isBranch(_ttype_stack.top()))
        while (isBranch(_ttype_stack.top())) {
            
            if (!_last_if && _ttype_stack.top() == Token::Type::IF)
                _last_if = _parent_stack.top();
            _deleteBlock();
            _ttype_stack.pop();
            _parent_stack.pop();
        }

    // Delete DO | TRY
    if (_state_stack.top() == _State::TRIAL && isTrialError(_ttype_stack.top())) {

        _state_stack.pop();
        _ttype_stack.pop();
    }
}






  ////////////
 /* Action */
////////////
void CppPda::_identifier(Token* tok)
{
    if (_state_stack.top() == _State::ROOT) {
        
        tok->parent = tok->root;
        tok->neighbors = std::make_shared<Token::string_set>();
        tok->neighbors->insert(tok->name);
        tok->predecessor = tok->successor = tok->root->neighbors;
        return;
    }

    // Set hierarchy
    if (_state_stack.top() == _State::COND) {

        tok->parent = _parent_stack.top()->parent;
        tok->children = _parent_stack.top()->children;
    }
    else
        tok->parent = _parent_stack.top();

    if (tok->parent != tok->root)
        tok->parent->children->insert(tok->name);

    // Set Flat
    _setFlatRelation(tok);

    // New line
    if (_isBlock(_state_stack.top()))
        _beginLine(_State::STMT, Token::Type::STMT);
}

void CppPda::_branch(Token* tok)
{
    // Set hierarchy
    tok->parent = _parent_stack.top();
    tok->children = std::make_shared<Token::string_set>();
    if (tok->parent != tok->root)
        tok->parent->children->insert(tok->name);
    
    _parent_stack.push(tok);

    // Set Flat
    _setFlatRelation(tok);

    // New line
    _beginLine(_State::COND, tok->type);
}

void CppPda::_enum(Token* tok)
{
    if (_state_stack.top() == _State::ROOT)
        _ttype_stack.push(tok->type);

    else if (_isBlock(_state_stack.top()))
        _beginLine(_State::STMT, tok->type);
}

void CppPda::_class(Token* tok)
{
    if (_ttype_stack.top() == Token::Type::ENUM)
        return;

    if (_state_stack.top() == _State::ROOT) {

        _ttype_stack.push(tok->type);
        _struct_state = _Struct::ID;
    }
    else if (_isBlock(_state_stack.top())) {

        _beginLine(_State::STMT, tok->type);
        _struct_state = _Struct::ID;
    }
}



void CppPda::_r_paren(Token* tok)
{
    _ttype_stack.pop();

    if (_state_stack.top() == _State::COND && isBranch(_ttype_stack.top())) {

        _endLine();
        _newBlock(_State::THEN);
    }

    else if (_ttype_stack.top() == Token::Type::LAMBDA) {

        _ttype_stack.pop();
        _lambda_stack.top() = _Lambda::BODY_BEGIN;
    }
}

void CppPda::_l_brace(Token* tok)
{
    // ENUM | CLASS
    if (isEnumOrClass(_ttype_stack.top()))
        _newRoot(tok->type, tok->root);
        
    // New lambda expression | function
    else if ((_lambda_stack.top() == _Lambda::BODY_BEGIN)
            || (_state_stack.top() == _State::ROOT && _ttype_stack.top() != Token::Type::NAMESPACE)) {
        
        if (_lambda_stack.top() == _Lambda::BODY_BEGIN)
            _lambda_stack.pop();

        _ttype_stack.push(Token::Type::FUNC);
        _newBlock(_State::FUNC);
        _ttype_stack.push(tok->type);
        _parent_stack.push(tok->root);
    }

    // Otherwise,
    else
        _ttype_stack.push(tok->type);
}

void CppPda::_r_brace(Token* tok)
{
    // FUNC {  STMT  }
    if (_ttype_stack.top() != Token::Type::L_BRACE) {

        _state_stack.pop(); // _State - STMT
        _ttype_stack.pop(); // TType - }
        _ttype_stack.pop(); // TType - STMT
        _ttype_stack.pop(); // TType - {
        _deleteBlock();
        _parent_stack.pop();
        return;
    }
    _ttype_stack.pop();

    // Delete ROOT
    if (isEnumOrClass(_ttype_stack.top()))
        _deleteRoot();

    // namespace
    else if (_ttype_stack.top() == Token::Type::NAMESPACE)
        _ttype_stack.pop();

    // Delete FUNC
    else if (_state_stack.top() == _State::FUNC) {
        
        if (_ttype_stack.top() == Token::Type::FUNC) { 

            _deleteBlock();
            _ttype_stack.pop();
            _parent_stack.pop(); // Pop root
        }
    }

    // Delete branch
    else
        _deleteWhileBranch();
}

void CppPda::_l_square(Token* tok)
{
    _otherwise(tok);

    if (_lambda_stack.top() == _Lambda::OPERATOR)
        _lambda_stack.pop();

    else { // _lambda_stack.top() != _Lambda::OPERATOR

        _lambda_stack.push(_Lambda::CAPTURE);
        _ttype_stack.push(Token::Type::LAMBDA);
    }

    _ttype_stack.push(tok->type);
}

void CppPda::_r_square(Token* tok)
{
    _ttype_stack.pop();
    if (_ttype_stack.top() == Token::Type::LAMBDA)
        _lambda_stack.top() = _Lambda::ARGS_BEGIN;
}

void CppPda::_semi(Token* tok)
{
    _otherwise(tok);

    // End line
    if (_state_stack.top() == _State::ROOT) {

        if (isEnumOrClass(_ttype_stack.top()) || _ttype_stack.top() == Token::Type::NAMESPACE)
            _ttype_stack.pop();
    }

    else if (_state_stack.top() == _State::STMT) {

        if (isEnumOrClass(_ttype_stack.top()) || _ttype_stack.top() == Token::Type::STMT) {

            _endLine();
            _ttype_stack.pop();
        }   
    }

    _deleteWhileBranch();
}

void CppPda::_colon(Token* tok)
{
    _otherwise(tok);

    if (_ttype_stack.top() == Token::Type::CASE || _ttype_stack.top() == Token::Type::DEFAULT) {

        _ttype_stack.pop();
        _endLine();
    }
}
}
#endif
