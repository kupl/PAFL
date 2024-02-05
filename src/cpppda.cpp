#include "tokentree/cpppda.h"

namespace PAFL
{
CppPda::CppPda(Token* root) :
    _action{ &CppPda::_identifier, nullptr, }, _prefix_state(_Prefix::ROOT), _skip(false)
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
    _action[static_cast<size_t>(Token::Type::DO)] = &CppPda::_do;
    _action[static_cast<size_t>(Token::Type::TRY)] = &CppPda::_try;
        // operator overriding
    _action[static_cast<size_t>(Token::Type::OPERATOR)] = &CppPda::_operator;
        // enum | class
    _action[static_cast<size_t>(Token::Type::ENUM)] = &CppPda::_enum;
    _action[static_cast<size_t>(Token::Type::CLASS)] =  _action[static_cast<size_t>(Token::Type::STRUCT)]
    = _action[static_cast<size_t>(Token::Type::UNION)] = &CppPda::_class;
        // namespace | l_paren
    _action[static_cast<size_t>(Token::Type::NAMESPACE)] = &CppPda::_namespace;
    _action[static_cast<size_t>(Token::Type::L_PAREN)] = &CppPda::_l_paren;
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



void CppPda::trans(Token* tok, Token* future)
{
    if (!tok)
        return;
    if (_skip) {

        _skip = false;
        return;
    }
    if (!future)
        future = tok->root;

    _checkLambdaConnector(tok);
    _detPrefixType(tok);
    if (_action[static_cast<size_t>(tok->type)])
        (this->*_action[static_cast<size_t>(tok->type)])(tok, future);
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



void CppPda::_checkLambdaConnector(Token* tok)
{
    if (_lambda_stack.top() == _Lambda::OPERATOR) {

        if (tok->type != Token::Type::L_SQUARE)
            _lambda_stack.pop();
    }

    else if (_lambda_stack.top() == _Lambda::ARGS_BEGIN)
        if (tok->type == Token::Type::L_PAREN)
            _lambda_stack.top() = _Lambda::ARGS;

        else {

            _ttype_stack.pop();
            _lambda_stack.pop();
        }

    else if (_lambda_stack.top() == _Lambda::BODY_BEGIN && tok->type != Token::Type::L_BRACE)
        _lambda_stack.pop();
}



void CppPda::_detPrefixType(Token* tok)
{
    if (_prefix_state == _Prefix::ROOT)
        return;

    if (_prefix_state == _Prefix::ID && tok->type == Token::Type::IDENTIFIER) {

        _prefix_state = _Prefix::TBD;
        return;
    }

    if (tok->type != Token::Type::SEMI && tok->type != Token::Type::COLON && tok->type != Token::Type::L_BRACE) {

        _ttype_stack.pop();
        if (_state_stack.top() == _State::STMT)
            _ttype_stack.push(Token::Type::STMT);
    }
    _prefix_state = _Prefix::ROOT;
}



void CppPda::_setFlatRelation(Token* tok)
{
    tok->predecessor = _predecessor_stack.top();
    tok->neighbors = _neighbors_stack.top();
    tok->successor = _successor_stack.top();
    _neighbors_stack.top()->push_back(tok);
}



void CppPda::_newBlock(_State state)
{
    _state_stack.push(state);

    _predecessor_stack.emplace();
    _neighbors_stack.emplace();
    _successor_stack.emplace();
    _predecessor_stack.top() = std::make_shared<Token::List>();
    _neighbors_stack.top() = std::make_shared<Token::List>();
    _successor_stack.top() = std::make_shared<Token::List>();
}



void CppPda::_endLine()
{
    _state_stack.pop();
    
    _predecessor_stack.top() = _neighbors_stack.top();
    _neighbors_stack.top() = _successor_stack.top();

    _successor_stack.pop();
    _successor_stack.emplace();
    _successor_stack.top() = std::make_shared<Token::List>();
}



void CppPda::_deleteBlock()
{
    _deleteRoot();

    _predecessor_stack.pop();
    _neighbors_stack.pop();
    _successor_stack.pop();
}



void CppPda::_deleteIfBlock(Token* future)
{
    // Delete FUNC
    if (_state_stack.top() == _State::FUNC) {
        
        if (_ttype_stack.top() == Token::Type::FUNC) { 

            _deleteBlock();
            _ttype_stack.pop();
        }
        return;
    }

    // Delete branch
    while (_state_stack.top() == _State::THEN && isBranch(_ttype_stack.top()))
        if (future->type == Token::Type::ELSE && _ttype_stack.top() == Token::Type::IF) {
            
            Token* latest_if = _parent_stack.top();
            _deleteBlock();
            _ttype_stack.pop();

            // Insert ELSE
            _newBlock(_State::THEN);
            _ttype_stack.push(future->type);
            _parent_stack.push(latest_if);
            _skip = true;
            break;
        }
        else {

            _deleteBlock();
            _ttype_stack.pop();
        }

    // Delete DO | TRY
    if (_state_stack.top() == _State::THEN && isTrialError(_ttype_stack.top())) {

        _state_stack.pop();
        _ttype_stack.pop();
    }
}



  ////////////
 /* Action */
////////////
void CppPda::_identifier(Token* tok, Token* future)
{
    // New line
    if (_isBlock(_state_stack.top()))
        _beginLine(_State::STMT, Token::Type::STMT);

    else if (_state_stack.top() == _State::ROOT) {
        
        tok->parent = tok->root;
        tok->neighbors = std::make_shared<Token::List>();
        tok->neighbors->push_back(tok);
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
        tok->parent->children->push_back(tok);

    // Set Flat
    _setFlatRelation(tok);
}



void CppPda::_branch(Token* tok, Token* future)
{
    // Set hierarchy
    tok->parent = _parent_stack.top();
    tok->children = std::make_shared<Token::List>();
    if (tok->parent != tok->root)
        tok->parent->children->push_back(tok);
    
    _parent_stack.push(tok);

    // Set Flat
    _setFlatRelation(tok);

    // New line
    _beginLine(_State::COND, tok->type);
}



void CppPda::_try(Token* tok, Token* future)
{
    // New function
    if (_state_stack.top() == _State::ROOT) {

        _ttype_stack.push(Token::Type::FUNC);
        _newBlock(_State::FUNC);
        _parent_stack.push(tok->root);
    }
    _beginLine(_State::THEN, tok->type);
}



void CppPda::_enum(Token* tok, Token* future)
{
    if (_state_stack.top() == _State::ROOT) {

        _ttype_stack.push(tok->type);
        _prefix_state = _Prefix::ID;
    }
    else if (_isBlock(_state_stack.top())) {

        _beginLine(_State::STMT, tok->type);
        _prefix_state = _Prefix::ID;
    }
}



void CppPda::_namespace(Token* tok, Token* future)
{
    // New namespace definition
    if (_state_stack.top() == _State::ROOT)
        _ttype_stack.push(tok->type);
    
    // New line
    else if (_isBlock(_state_stack.top()))
        _beginLine(_State::STMT, Token::Type::STMT);
}



void CppPda::_r_paren(Token* tok, Token* future)
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



void CppPda::_l_brace(Token* tok, Token* future)
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



void CppPda::_r_brace(Token* tok, Token* future)
{
    // FUNC {  STMT  }
    if (_ttype_stack.top() != Token::Type::L_BRACE) {

        _state_stack.pop(); // _State - STMT
        _ttype_stack.pop(); // TType - STMT
    }
    _ttype_stack.pop(); // TType - {

    // Delete ROOT
    if (isEnumOrClass(_ttype_stack.top()))
        _deleteRoot();

    // namespace
    else if (_ttype_stack.top() == Token::Type::NAMESPACE)
        _ttype_stack.pop();

    // Delete catch
    else if (_state_stack.top() == _State::THEN && _ttype_stack.top() == Token::Type::CATCH) {

        _deleteBlock();
        _ttype_stack.pop();

        if (future->type != Token::Type::CATCH)
            _deleteIfBlock(future);
    }

    // Delete block
    else
        _deleteIfBlock(future);
}



void CppPda::_l_square(Token* tok, Token* future)
{
    // New line
    if (_isBlock(_state_stack.top()))
        _beginLine(_State::STMT, Token::Type::STMT);

    else if (_lambda_stack.top() == _Lambda::OPERATOR)
        _lambda_stack.pop();

    else { // _lambda_stack.top() != _Lambda::OPERATOR

        _lambda_stack.push(_Lambda::CAPTURE);
        _ttype_stack.push(Token::Type::LAMBDA);
    }

    _ttype_stack.push(tok->type);
}



void CppPda::_r_square(Token* tok, Token* future)
{
    _ttype_stack.pop();
    if (_ttype_stack.top() == Token::Type::LAMBDA)
        _lambda_stack.top() = _Lambda::ARGS_BEGIN;
}



void CppPda::_semi(Token* tok, Token* future)
{
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

    _deleteIfBlock(future);
}



void CppPda::_colon(Token* tok, Token* future)
{
    if (_ttype_stack.top() == Token::Type::CASE || _ttype_stack.top() == Token::Type::DEFAULT) {

        _ttype_stack.pop();
        _endLine();
    }
}
}
