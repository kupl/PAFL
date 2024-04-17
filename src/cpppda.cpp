#include "tokentree/cpppda.h"
#include <iostream>
namespace PAFL
{
CppPda::CppPda() :
    _action{&CppPda::_identifier, nullptr, }, _skip(false)
{
    _newRoot(Matcher::Type::ROOT);
    _lambda_stack.push(Lambda::ROOT);
    _postclass_stack.push(PostClass::ROOT);

    // Set action map
        // id
    for (auto i = static_cast<size_t>(Matcher::Type::AMP); i != static_cast<size_t>(Matcher::Type::OTHERWISE); i++)
        _action[i] = &CppPda::_identifier;
        // branch
    _action[static_cast<size_t>(Matcher::Type::CATCH)] = _action[static_cast<size_t>(Matcher::Type::FOR)]
    = _action[static_cast<size_t>(Matcher::Type::IF)] = _action[static_cast<size_t>(Matcher::Type::SWITCH)]
    = _action[static_cast<size_t>(Matcher::Type::WHILE)] = &CppPda::_branch;
        // switch
    _action[static_cast<size_t>(Matcher::Type::CASE)] = _action[static_cast<size_t>(Matcher::Type::DEFAULT)] = &CppPda::_case;
        // trial and error
    _action[static_cast<size_t>(Matcher::Type::DO)] = &CppPda::_do;
    _action[static_cast<size_t>(Matcher::Type::TRY)] = &CppPda::_try;
        // outer
    _action[static_cast<size_t>(Matcher::Type::NAMESPACE)] = &CppPda::_namespace;
    _action[static_cast<size_t>(Matcher::Type::OPERATOR)] = &CppPda::_operator;
    _action[static_cast<size_t>(Matcher::Type::DECLTYPE)] = &CppPda::_decltype;
        // enum | class
    _action[static_cast<size_t>(Matcher::Type::ENUM)] = &CppPda::_enum;
    _action[static_cast<size_t>(Matcher::Type::CLASS)] = _action[static_cast<size_t>(Matcher::Type::UNION)] = &CppPda::_class; 
    _action[static_cast<size_t>(Matcher::Type::STRUCT)] = &CppPda::_struct;
        // symbol
    _action[static_cast<size_t>(Matcher::Type::L_PAREN)] = &CppPda::_l_paren;
    _action[static_cast<size_t>(Matcher::Type::R_PAREN)] = &CppPda::_r_paren;
    _action[static_cast<size_t>(Matcher::Type::L_BRACE)] = &CppPda::_l_brace;
    _action[static_cast<size_t>(Matcher::Type::R_BRACE)] = &CppPda::_r_brace;
    _action[static_cast<size_t>(Matcher::Type::L_SQUARE)] = &CppPda::_l_square;
    _action[static_cast<size_t>(Matcher::Type::R_SQUARE)] = &CppPda::_r_square;
    _action[static_cast<size_t>(Matcher::Type::SEMI)] = &CppPda::_semi;
    _action[static_cast<size_t>(Matcher::Type::COLON)] = &CppPda::_colon;
        // template
    _action[static_cast<size_t>(Matcher::Type::TEMPLATE)] = &CppPda::_template;
    _action[static_cast<size_t>(Matcher::Type::LESS)] = &CppPda::_less;
    _action[static_cast<size_t>(Matcher::Type::GREATER)] = &CppPda::_greater;
        // otherwise
    _action[static_cast<size_t>(Matcher::Type::OTHERWISE)] = &CppPda::_otherwise;
}



void CppPda::trans(Matcher::Args args)
{
    if (!args.tok)
        return;
    if (_skip) {

        _skip = false;
        return;
    }
    std::cout << args.tok->loc << ", " << args.tok->name << '\n';
    _checkLambdaConnector(args.tok_type);
    if (_action[static_cast<size_t>(args.tok_type)])
        (this->*_action[static_cast<size_t>(args.tok_type)])(args);
    std::cout << " state=" << _state_stack.size() << ", type=" << _type_stack.size() << " parent=" << _parent_stack.size() << ", lambda=" << _lambda_stack.size() << '\n';
    std::cout << " decl=" << _decltype_stack.size() << ", neigh=" << _neighbor_stack.size() << ", pred=" << _pred_stack.size() << ", succ=" << _succ_stack.size() << '\n';
}



bool CppPda::isTerminated() const
{
    if (_state_stack.size() != 1 || _type_stack.size() != 1
        || _parent_stack.size() != 1 || _lambda_stack.size() != 1)
        return false;

    if (_state_stack.top() != State::ROOT || _type_stack.top() != Matcher::Type::ROOT
        || _parent_stack.top() != nullptr || _lambda_stack.top() != Lambda::ROOT)
        return false;

    return _neighbor_stack.empty() && _pred_stack.empty() && _succ_stack.empty() && _decltype_stack.empty();
}



void CppPda::_checkLambdaConnector(Matcher::Type tok_type)
{
    if (_lambda_stack.top() == Lambda::OPERATOR) {

        if (tok_type != Matcher::Type::L_SQUARE)
            _lambda_stack.pop();
    }

    else if (_lambda_stack.top() == Lambda::ARGS_BEGIN)
        if (tok_type == Matcher::Type::L_PAREN)
            _lambda_stack.top() = Lambda::ARGS;
        else {

            _type_stack.pop();
            _lambda_stack.pop();
        }

    else if (_lambda_stack.top() == Lambda::ARGS_END) {

        if (tok_type == Matcher::Type::ARROW)
            _lambda_stack.top() = Lambda::RETURN_TYPE;
        else if (tok_type != Matcher::Type::L_BRACE)
            _lambda_stack.pop();
    }

    else if (_lambda_stack.top() == Lambda::RETURN_TYPE && _decltype_stack.empty())
        if (tok_type == Matcher::Type::L_PAREN || tok_type == Matcher::Type::SEMI)
            _lambda_stack.pop();
}



void CppPda::_checkPostClassState(Matcher::Type tok_type)
{
    if (!_decltype_stack.empty())
        return;
    

}



void CppPda::_setContext(Token* tok)
{
    if (tok->parent && tok->parent->size())
        (*tok->parent->begin())->child->push_back(tok);
    tok->pred = _pred_stack.top();
    tok->neighbor = _neighbor_stack.top();
    tok->succ = _succ_stack.top();
    _neighbor_stack.top()->push_back(tok);
}



void CppPda::_newBlock(State state)
{
    _state_stack.push(state);
    // New contexts
    _pred_stack.emplace();
    _neighbor_stack.emplace();
    _succ_stack.emplace();
    _neighbor_stack.top() = std::make_shared<Token::List>();
    _succ_stack.top() = std::make_shared<Token::List>();
}



void CppPda::_endLine()
{
    _state_stack.pop();
    // Shift    
    _pred_stack.top() = _neighbor_stack.top();
    _neighbor_stack.top() = _succ_stack.top();
    _succ_stack.pop();
    _succ_stack.emplace();
    _succ_stack.top() = std::make_shared<Token::List>();
}



void CppPda::_deleteBlock()
{
    // Delete succ
    if (_pred_stack.top())
        for (auto tok : *_pred_stack.top())
            tok->succ.reset();

    _deleteRoot();
    _pred_stack.pop();
    _neighbor_stack.pop();
    _succ_stack.pop();
}



void CppPda::_deleteIfBlock(Matcher::Type future_type)
{
    // Delete FUNC
    if (_state_stack.top() == State::FUNC) {
        
        if (_type_stack.top() == Matcher::Type::FUNC) { 

            _deleteBlock();
            _type_stack.pop();
        }
        return;
    }

    // Delete branch
    while (_state_stack.top() == State::THEN && Matcher::isBranch(_type_stack.top()))
        if (future_type == Matcher::Type::ELSE && _type_stack.top() == Matcher::Type::IF) {
            
            Token* latest_if = _parent_stack.top();
            _deleteBlock();
            _type_stack.pop();

            // Insert ELSE
            _newBlock(State::THEN);
            _type_stack.push(future_type);
            _parent_stack.push(latest_if);
            _skip = true;
            break;
        }
        else {

            _deleteBlock();
            _type_stack.pop();
        }

    // Delete DO | TRY
    if (_state_stack.top() == State::THEN && Matcher::isTrialError(_type_stack.top())) {

        _state_stack.pop();
        _type_stack.pop();
    }
}



/*
    Action
*/
void CppPda::_identifier(Matcher::Args args)
{
    // New line
    if (_isBlock(_state_stack.top()))
        _beginLine(State::STMT, Matcher::Type::STMT);

    else if (_state_stack.top() == State::ROOT) {
        
        args.tok->neighbor = std::make_shared<Token::List>();
        args.tok->neighbor->push_back(args.tok);
        return;
    }

    // Set hierarchy
    if (_state_stack.top() == State::COND) {

        args.tok->parent = _parent_stack.top()->parent;
        args.tok->child = _parent_stack.top()->child;
    }
    else if(_parent_stack.top()) //_state_stack.top() == State::STMT
        args.tok->parent = _parent_stack.top()->neighbor;

    // Set context
    _setContext(args.tok);
}



void CppPda::_branch(Matcher::Args args)
{
    // Set hierarchy
    if (args.tok->parent)
        args.tok->parent = _parent_stack.top()->neighbor;
    args.tok->child = std::make_shared<Token::List>();
    _parent_stack.push(args.tok);

    // Set context
    _setContext(args.tok);

    // New line
    _beginLine(State::COND, args.tok_type);
}



void CppPda::_try(Matcher::Args args)
{
    // New function
    if (_state_stack.top() == State::ROOT) {

        _type_stack.push(Matcher::Type::FUNC);
        _newBlock(State::FUNC);
        _parent_stack.push(nullptr);
    }
    _beginLine(State::THEN, args.tok_type);
}



void CppPda::_struct(Matcher::Args args)
{
    _postclass_stack.top() = PostClass::ID;
    if (_state_stack.top() == State::ROOT)
        _type_stack.push(args.tok_type);
    else if (_isBlock(_state_stack.top()))
        _beginLine(State::STMT, args.tok_type);
}



void CppPda::_namespace(Matcher::Args args)
{
    // New namespace definition
    if (_state_stack.top() == State::ROOT)
        _type_stack.push(args.tok_type);
    
    // New line
    else if (_isBlock(_state_stack.top()))
        _beginLine(State::STMT, Matcher::Type::STMT);
}



void CppPda::_l_paren(Matcher::Args args)
{
    // End struct decl
    if (!_decltype_stack.empty())
        _decltype_stack.push(args.tok_type);
    else if (_post_class_state) {

        _type_stack.pop();
        if (_state_stack.top() == State::STMT)
            _type_stack.push(Matcher::Type::STMT);
        _post_class_state = false;
    }

    _otherwise(args);
    _type_stack.push(args.tok_type);
}


void CppPda::_r_paren(Matcher::Args)
{
    // Pop type stack
    _type_stack.pop();
    if (_state_stack.top() == State::COND && Matcher::isBranch(_type_stack.top())) {

        _endLine();
        _newBlock(State::THEN);
    }
    else if (_type_stack.top() == Matcher::Type::LAMBDA) {

        _type_stack.pop();
        _lambda_stack.top() = Lambda::ARGS_END;
    }

    // Pop decltype stack
    if (!_decltype_stack.empty()) {

        _decltype_stack.pop();
        if (_decltype_stack.top() == Matcher::Type::DECLTYPE)
            _decltype_stack.pop();
    }
}



void CppPda::_l_brace(Matcher::Args args)
{
    // ENUM | CLASS
    if (Matcher::isEnumOrClass(_type_stack.top()))
        _newRoot(args.tok_type);
        
    // Function | New lambda expression
    else if ((_state_stack.top() == State::ROOT && _type_stack.top() != Matcher::Type::NAMESPACE)
            || (_lambda_stack.top() == Lambda::ARGS_END)
            || (_lambda_stack.top() == Lambda::RETURN_TYPE && _decltype_stack.empty())) {
        
        if (_lambda_stack.top() == Lambda::ARGS_END || _lambda_stack.top() == Lambda::RETURN_TYPE)
            _lambda_stack.pop();

        _type_stack.push(Matcher::Type::FUNC);
        _newBlock(State::FUNC);
        _type_stack.push(args.tok_type);
        _parent_stack.push(nullptr);
    }

    // Otherwise,
    else
        _type_stack.push(args.tok_type);
}



void CppPda::_r_brace(Matcher::Args args)
{
    // FUNC {  STMT  }
    if (_type_stack.top() != Matcher::Type::L_BRACE) {

        _state_stack.pop(); // State - STMT
        _type_stack.pop(); // TType - STMT
    }
    _type_stack.pop(); // TType - {
    
    // Delete ROOT
    if (Matcher::isEnumOrClass(_type_stack.top()))
        _deleteRoot();

    // namespace
    else if (_type_stack.top() == Matcher::Type::NAMESPACE)
        _type_stack.pop();

    // Delete catch
    else if (_state_stack.top() == State::THEN && _type_stack.top() == Matcher::Type::CATCH) {

        _deleteBlock();
        _type_stack.pop();

        if (args.future_type != Matcher::Type::CATCH)
            _deleteIfBlock(args.future_type);
    }

    // Delete block
    else
        _deleteIfBlock(args.future_type);
}



void CppPda::_l_square(Matcher::Args args)
{
    // New line
    if (_isBlock(_state_stack.top()))
        _beginLine(State::STMT, Matcher::Type::STMT);

    else if (_lambda_stack.top() == Lambda::OPERATOR)
        _lambda_stack.pop();

    else if (_decltype_stack.empty()) { // _lambda_stack.top() != Lambda::OPERATOR

        _lambda_stack.push(Lambda::CAPTURE);
        _type_stack.push(Matcher::Type::LAMBDA);
    }

    _type_stack.push(args.tok_type);
}



void CppPda::_r_square(Matcher::Args)
{
    _type_stack.pop();
    if (_type_stack.top() == Matcher::Type::LAMBDA)
        _lambda_stack.top() = Lambda::ARGS_BEGIN;
}



void CppPda::_semi(Matcher::Args args)
{
    // End line
    if (_state_stack.top() == State::ROOT) {

        if (Matcher::isEnumOrClass(_type_stack.top()) || _type_stack.top() == Matcher::Type::NAMESPACE)
            _type_stack.pop();
    }

    else if (_state_stack.top() == State::STMT) {

        if (Matcher::isEnumOrClass(_type_stack.top()) || _type_stack.top() == Matcher::Type::STMT) {

            _endLine();
            _type_stack.pop();
        }
    }

    _deleteIfBlock(args.future_type);
}



void CppPda::_colon(Matcher::Args)
{
    if (_type_stack.top() == Matcher::Type::CASE || _type_stack.top() == Matcher::Type::DEFAULT) {

        _type_stack.pop();
        _endLine();
    }
}



void CppPda::_less(Matcher::Args args)
{
    if (!_template_stack.empty())
        _template_stack.push(Matcher::Type::LESS);
    _identifier(args);
}



void CppPda::_greater(Matcher::Args args)
{
    if (!_template_stack.empty()) {

        _template_stack.pop();
        if (_template_stack.top() == Matcher::Type::TEMPLATE)
            _template_stack.pop();
    }
    _identifier(args);
}
}



/*
    Matcher's map
*/
namespace PAFL
{
CppPda::Matcher::Matcher() : _table
{
    // identifier
    { "identifier", Type::IDENTIFIER },

    // branch
    { "if", Type::IF },
    { "catch", Type::CATCH },
    { "for", Type::FOR },
    { "switch", Type::SWITCH },
    { "while", Type::WHILE },
    // else
    { "else", Type::ELSE },

    // switch
    { "case", Type::CASE },
    { "default", Type::DEFAULT },
    // trial & error
    { "do", Type::DO },
    { "try", Type::TRY },

    // class
    { "enum", Type::ENUM },
    { "class", Type::CLASS },
    { "struct", Type::STRUCT },
    { "union", Type::UNION },

    // outer
    { "operator", Type::OPERATOR },
    { "namespace", Type::NAMESPACE },
    { "template", Type::TEMPLATE },
    { "decltype", Type::DECLTYPE },

    // parenthesis
    { "l_paren", Type::L_PAREN },
    { "r_paren", Type::R_PAREN },
    { "l_brace", Type::L_BRACE },
    { "r_brace", Type::R_BRACE },
    { "l_square", Type::L_SQUARE },
    { "r_square", Type::R_SQUARE },

    // semicolon
    { "semi", Type::SEMI },
    // colon
    { "colon", Type::COLON },
    { "coloncolon", Type::COLONCOLON },
    // pointer operator
    { "arrow", Type::ARROW },

    // bit operator
    { "amp", Type::AMP },
    { "ampequal", Type::AMPEQUAL },
    { "pipe", Type::PIPE },
    { "pipeequal", Type::PIPEEQUAL },
    { "caret", Type::CARET },
    { "caretequal", Type::CARETEQUAL },

    // shift operator
    { "lessless", Type::LESSLESS },
    { "lesslessequal", Type::LESSLESSEQUAL },
    { "greatergreater", Type::GREATERGREATER },
    { "greatergreaterequal", Type::GREATERGREATEREQUAL },

    // boolean operator
    { "ampamp", Type::AMPAMP },
    { "exclaim", Type::EXCLAIM },
    { "exclaimequal", Type::EXCLAIMEQUAL },
    { "less", Type::LESS },
    { "lessequal", Type::LESSEQUAL },
    { "greater", Type::GREATER },
    { "greaterequal", Type::GREATEREQUAL },
    { "pipepipe", Type::PIPEPIPE },
    { "equalequal", Type::EQUALEQUAL },
    { "question", Type::QUESTION },

    // arithmetic operator
    { "star", Type::STAR },
    { "starequal", Type::STAREQUAL },
    { "starstar", Type::STARSTAR },
    { "plus", Type::PLUS },
    { "plusplus", Type::PLUSPLUS },
    { "plusequal", Type::PLUSEQUAL },
    { "minus", Type::MINUS },
    { "minusminus", Type::MINUSMINUS },
    { "minusequal", Type::MINUSEQUAL },
    { "slash", Type::SLASH },
    { "slashequal", Type::SLASHEQUAL },
    { "slashslash", Type::SLASHSLASH },
    { "slashslashequal", Type::SLASHSLASHEQUAL },
    { "percent", Type::PERCENT },
    { "percentequal", Type::PERCENTEQUAL },

    // jumping
    { "break", Type::BREAK },
    { "continue", Type::CONTINUE },
    { "return", Type::RETURN },
    { "throw", Type::THROW },

    // memory allocation
    { "new", Type::NEW },
    { "delete", Type::DELETE },

    // this
    { "this", Type::THIS },

    // casting
    { "const_cast", Type::CONST_CAST },
    { "dynamic_cast", Type::DYNAMIC_CAST },
    { "reinterpret_cast", Type::REINTERPRET_CAST },
    { "static_cast", Type::STATIC_CAST },
    
    // End Of File
    { "eof", Type::eof }
} {}
}
