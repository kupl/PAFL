#ifndef __CPPPDA_H__
#define __CPPPDA_H__

#include <stack>
#include "tokentree.h"



namespace PAFL
{
class HierarchyPda
{
public:
    HierarchyPda(Token* root);
    void trans(Token* tok);


private:
    enum class _State { ROOT, COND, THEN };

    void _inheritLastIf(Token* tok);

    decltype(&HierarchyPda::trans) _action[static_cast<size_t>(Token::Type::eof)];

    std::stack<_State> _state_stack;
    std::stack<Token::Type> _ttype_stack;
    std::stack<Token*> _parent_stack;
    Token* _last_if;

    /* Action */
    void _identifier(Token* tok);
    void _branch(Token* tok);
    // l_paren | l_brace
    void _left(Token* tok)
        { _ttype_stack.push(tok->type); }
    void _r_paren(Token* tok);
    void _r_brace(Token* tok)
        {  _ttype_stack.pop(); _semi(tok); }
    void _semi(Token* tok);
};
}



namespace PAFL
{
HierarchyPda::HierarchyPda(Token* root) :
    _action{ &HierarchyPda::_identifier, nullptr, }, _last_if(nullptr)
{
    _state_stack.push(_State::ROOT);
    _ttype_stack.push(Token::Type::ROOT);
    _parent_stack.push(root);

    // Set action map
    for (auto i = static_cast<size_t>(Token::Type::AMP); i != static_cast<size_t>(Token::Type::OTHERWISE); i++)
        _action[i] = &HierarchyPda::_identifier;
    _action[static_cast<size_t>(Token::Type::FOR)] = _action[static_cast<size_t>(Token::Type::IF)]
    = _action[static_cast<size_t>(Token::Type::SWITCH)] = _action[static_cast<size_t>(Token::Type::WHILE)] = &HierarchyPda::_branch;
    _action[static_cast<size_t>(Token::Type::L_PAREN)] = _action[static_cast<size_t>(Token::Type::L_BRACE)] = &HierarchyPda::_left;
    _action[static_cast<size_t>(Token::Type::R_PAREN)] = &HierarchyPda::_r_paren;
    _action[static_cast<size_t>(Token::Type::R_BRACE)] = &HierarchyPda::_r_brace;
    _action[static_cast<size_t>(Token::Type::SEMI)] = &HierarchyPda::_semi;
}

void HierarchyPda::trans(Token* tok)
{
    _inheritLastIf(tok);
    if (_action[static_cast<size_t>(tok->type)])
        (this->*_action[static_cast<size_t>(tok->type)])(tok);
}

void HierarchyPda::_inheritLastIf(Token* tok)
{
    if (_last_if && tok->type == Token::Type::ELSE) {

        _ttype_stack.push(tok->type);
        _state_stack.push(_State::THEN);
        _parent_stack.push(_last_if);
    }
    _last_if = nullptr;
}

  ////////////
 /* Action */
////////////
void HierarchyPda::_identifier(Token* tok)
{
    if (_state_stack.top() == _State::COND) {

        tok->parent = _parent_stack.top()->parent;
        tok->children = _parent_stack.top()->children;
        _parent_stack.top()->children->insert(tok->name);
    }
    else {

        tok->parent = _parent_stack.top();
        if (_state_stack.top() == _State::THEN)
            _parent_stack.top()->children->insert(tok->name);
    }
}

void HierarchyPda::_branch(Token* tok)
{
    tok->parent = _parent_stack.top();
    tok->children = std::make_shared<decltype(Token::children)::element_type>();

    if (_state_stack.top() == _State::THEN)
        _parent_stack.top()->children->insert(tok->name);
    _state_stack.push(_State::COND);
    _ttype_stack.push(tok->type);
    _parent_stack.push(tok);
}

void HierarchyPda::_r_paren(Token* tok)
{
    _ttype_stack.pop();
    if (_state_stack.top() == _State::COND && isBranch(_ttype_stack.top()))
        _state_stack.top() = _State::THEN;
}

void HierarchyPda::_semi(Token* tok)
{
    if (_state_stack.top() == _State::THEN && isBranch(_ttype_stack.top()))
        while (isBranch(_ttype_stack.top())) {
            
            if (!_last_if && _ttype_stack.top() == Token::Type::IF)
                _last_if = _parent_stack.top();
            _ttype_stack.pop();
            _state_stack.pop();
            _parent_stack.pop();
        }
}
}






namespace PAFL
{
class FlatPda
{
public:
    FlatPda() : 
        __block_table{ false, true, false, false, true, false } { _newRoot(Token::Type::ROOT); }
    void trans(Token* tok)
        { if (_action[static_cast<size_t>(tok->type)]) (this->*_action[static_cast<size_t>(tok->type)])(tok); }


private:
    enum class _State { ROOT, FUNC, STMT, COND, THEN, CASE };

    void _setRelation(Token* tok);
    void _newBlock(_State state, Token::Type ttype);
    void _newRoot(Token::Type ttype);
    void _endLine();
    void _deleteBlock();
    // BLOCK -> FUNC | THEN
    inline bool _isBlock(_State state)
        { return __block_table[static_cast<size_t>(state)]; }
    // ROOT -> ROOT | ENUM | CLASS
    inline bool _isRoot()
        { return !_neighbors_stack.top(); }

    decltype(&FlatPda::trans) _action[static_cast<size_t>(Token::Type::eof)];

    const bool __block_table[static_cast<size_t>(_State::CASE) + 1];

    std::stack<_State> _state_stack;
    std::stack<Token::Type> _ttype_stack;
    std::stack<std::shared_ptr<Token::string_set>> _predecessor_stack;
    std::stack<std::shared_ptr<Token::string_set>> _neighbors_stack;
    std::stack<std::shared_ptr<Token::string_set>> _successor_stack;
    

    /* Action */
    void _identifier(Token* tok);
    void _branch(Token* tok);
    void _else(Token* tok)
        { _newBlock(_State::THEN, tok->type); }
    // case | default
    void _case(Token* tok);
    void _enum(Token* tok);
    void _class(Token* tok);
    // namespace | l_paren
    void _left(Token* tok)
        { _ttype_stack.push(tok->type); }
    void _r_paren(Token* tok);
    void _l_brace(Token* tok);
    void _r_brace(Token* tok);
    void _semi(Token* tok);
    void _colon(Token* tok);
};
}



namespace PAFL
{
void FlatPda::_setRelation(Token* tok)
{
    tok->predecessor = _predecessor_stack.top();
    tok->neighbors = _neighbors_stack.top();
    tok->successor = _successor_stack.top();
    _neighbors_stack.top()->insert(tok->name);
}

void FlatPda::_newBlock(_State state, Token::Type ttype)
{
    _state_stack.push(state);
    _ttype_stack.push(ttype);

    _predecessor_stack.emplace();
    _neighbors_stack.emplace();
    _successor_stack.emplace();
    _predecessor_stack.top() = std::make_shared<Token::string_set>();
    _neighbors_stack.top() = std::make_shared<Token::string_set>();
    _successor_stack.top() = std::make_shared<Token::string_set>();
}

void FlatPda::_newRoot(Token::Type ttype)
{
    _state_stack.push(_State::ROOT);
    _ttype_stack.push(ttype);

    _predecessor_stack.push(nullptr);
    _neighbors_stack.push(nullptr);
    _successor_stack.push(nullptr);
}

void FlatPda::_endLine()
{
    _state_stack.pop();
    
    _predecessor_stack.top() = _neighbors_stack.top();
    _neighbors_stack.top() = _successor_stack.top();

    _successor_stack.pop();
    _successor_stack.emplace();
    _successor_stack.top() = std::make_shared<Token::string_set>();
}

void FlatPda::_deleteBlock()
{
    _state_stack.pop();

    _predecessor_stack.pop();
    _neighbors_stack.pop();
    _successor_stack.pop();
}

  ////////////
 /* Action */
////////////
void FlatPda::_identifier(Token* tok)
{
    if (_isRoot()) {

        tok->neighbors = std::make_shared<Token::string_set>();
        tok->neighbors->insert(tok->name);
        tok->predecessor = tok->successor = tok->root->neighbors;
        return;
    }
        
    _setRelation(tok);
    if (_isBlock(_state_stack.top())) {

        _state_stack.push(_State::STMT);
        _ttype_stack.push(Token::Type::STMT);
    }
}

void FlatPda::_branch(Token* tok)
{
    _setRelation(tok);
    _state_stack.push(_State::COND);
    _ttype_stack.push(tok->type);
}

void FlatPda::_case(Token* tok)
{
    _state_stack.push(_State::CASE);
    _ttype_stack.push(tok->type);
}

void FlatPda::_enum(Token* tok)
{
    _ttype_stack.push(tok->type);

    if (_isBlock(_state_stack.top()))
        _state_stack.push(_State::STMT);
}

void FlatPda::_class(Token* tok)
{
    if (_ttype_stack.top() != Token::Type::ENUM)
        _ttype_stack.push(tok->type);

    if (_isBlock(_state_stack.top()))
        _state_stack.push(_State::STMT);
}

void FlatPda::_r_paren(Token* tok)
{
    _ttype_stack.pop();

    if (_state_stack.top() == _State::COND && isBranch(_ttype_stack.top())) {

        _endLine();
        _newBlock(_State::THEN, tok->type);
    }
}

void FlatPda::_l_brace(Token* tok)
{
    auto top_ttype = _ttype_stack.top();

    // ENUM | CLASS
    if (isClass(top_ttype) || top_ttype == Token::Type::ENUM)
        _newRoot(tok->type);
        
    // New function
    else if (_isRoot() && top_ttype != Token::Type::NAMESPACE) {

        _ttype_stack.push(Token::Type::FUNC);
        _newBlock(_State::FUNC, tok->type);
    }

    // Otherwise
    else
        _ttype_stack.push(tok->type);
}

void FlatPda::_r_brace(Token* tok)
{
    // FUNC {  STMT  }
    if (_ttype_stack.top() != Token::Type::L_BRACE) {

        _state_stack.pop(); // _State - STMT
        _ttype_stack.pop(); // TType - }
        _ttype_stack.pop(); // TType - STMT
        _ttype_stack.pop(); // TType - {
        _deleteBlock();
        return;
    }

    _ttype_stack.pop();
    auto top_ttype = _ttype_stack.top();

    // Delete ROOT
    if (isClass(top_ttype) || top_ttype == Token::Type::ENUM)
        _deleteBlock();

    // Delete BLOCK
    else if (_isBlock(_state_stack.top())) {

        _deleteBlock();
        _ttype_stack.pop();
    }

    // namespace
    else if (top_ttype == Token::Type::NAMESPACE)
        _ttype_stack.pop();
}

void FlatPda::_semi(Token* tok)
{

}

void FlatPda::_colon(Token* tok)
{
    if (_ttype_stack.top() == Token::Type::CASE || _ttype_stack.top() == Token::Type::DEFAULT);
}
}
#endif
