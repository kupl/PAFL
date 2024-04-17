#ifndef __CPPPDA_H__
#define __CPPPDA_H__

#include <stack>
#include "tokentree/tokentree.h"


namespace PAFL
{
class CppPda
{
public:
    class Matcher
    {
    public:
        enum class Type
        {
            // identifier
            IDENTIFIER,

            // branch
            IF,
            CATCH,
            FOR,
            SWITCH,
            WHILE,
            // else
            ELSE,
            
            // switch
            CASE,
            DEFAULT,
            // trial & error
            DO,
            TRY,

            // eum
            ENUM,
            // class
            CLASS,
            STRUCT,
            UNION,

            // outer
            OPERATOR,
            NAMESPACE,
            TEMPLATE,
            DECLTYPE,

            // parenthesis
            L_PAREN,    // (
            R_PAREN,    // )
            L_BRACE,    // {
            R_BRACE,    // }
            L_SQUARE,   // [
            R_SQUARE,   // ]

            // semicolon 
            SEMI,       // ;
            // colon
            COLON,      // :
            COLONCOLON, // ::
            // pointer operator
            ARROW,      // ->

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
            QUESTION,

            // arithmetic operator
            STAR,           // pointer operator
            STAREQUAL,
            STARSTAR,
            PLUS,
            PLUSPLUS,
            PLUSEQUAL,
            MINUS,
            MINUSMINUS,
            MINUSEQUAL,
            SLASH,
            SLASHEQUAL,
            SLASHSLASH,
            SLASHSLASHEQUAL,
            PERCENT,
            PERCENTEQUAL,

            // jumping
            BREAK,
            CONTINUE,
            RETURN,
            //GOTO,
            THROW,

            // memory allocation
            NEW,
            DELETE,

            // this
            THIS,

            // casting
            CONST_CAST,
            DYNAMIC_CAST,
            REINTERPRET_CAST,
            STATIC_CAST,

            // otherwise
            OTHERWISE,

            // End Of File
            eof,

            // virtual root type
            ROOT,
            // virtual function type
            FUNC,
            // virtual line statement type
            STMT,
            // virtual lambda type
            LAMBDA
        };

    public:
        typedef struct { Token* tok; Type tok_type, future_type; } Args;

    public:
        Matcher();
        Matcher::Type match(const std::string& key) const               { return _table.contains(key) ? _table.at(key) : Matcher::Type::OTHERWISE; }

        // branch -> IF | CATCH | FOR | SWITCH | WHILE | ELSE
        static constexpr bool isBranch(Matcher::Type ttype)             { return Matcher::Type::IF <= ttype && ttype <= Matcher::Type::ELSE; }
        // indepednet branch -> FOR | SWITCH | WHILE | ELSE
        static constexpr bool isIndependentBranch(Matcher::Type ttype)  { return Matcher::Type::FOR <= ttype && ttype <= Matcher::Type::ELSE; }
        // depednet branch -> IF | CATCH
        static constexpr bool isDependentBranch(Matcher::Type ttype)    { return ttype == Matcher::Type::IF || ttype == Matcher::Type::CATCH; }
        // class -> CLASS | STRUCT | UNION
        static constexpr bool isClass(Matcher::Type ttype)              { return Matcher::Type::CLASS <= ttype && ttype <= Matcher::Type::UNION; }
        // ENUM | class
        static constexpr bool isEnumOrClass(Matcher::Type ttype)        { return Matcher::Type::ENUM <= ttype && ttype <= Matcher::Type::UNION; }
        // DO | TRY
        static constexpr bool isTrialError(Matcher::Type ttype)         { return ttype == Matcher::Type::DO || ttype == Matcher::Type::TRY; }
        // Can be covered
        static constexpr bool isCoverable(Type ttype)                   { return ttype < CppPda::Matcher::Type::OTHERWISE && (ttype < CppPda::Matcher::Type::ELSE || CppPda::Matcher::Type::AMP <= ttype); }

    private:
        const std::unordered_map<std::string, Matcher::Type> _table;
    };



public:
    CppPda();
    void trans(Matcher::Args args);
    bool isTerminated() const;

private:
    enum class State { ROOT, FUNC, STMT, COND, THEN };
    enum class Lambda { ROOT, OPERATOR, CAPTURE, ARGS_BEGIN, ARGS, ARGS_END, RETURN_TYPE };
    enum class PostClass { ROOT, TEMPLATE, ID, POST_ID, BASE, POST_BASE };

private:
    decltype(&CppPda::trans) _action[static_cast<size_t>(Matcher::Type::eof)];

    std::stack<State> _state_stack;
    std::stack<Matcher::Type> _type_stack;

    std::stack<Token*> _parent_stack;
    std::stack<Token::Node> _pred_stack;
    std::stack<Token::Node> _neighbor_stack;
    std::stack<Token::Node> _succ_stack;

    std::stack<Matcher::Type> _decltype_stack;
    std::stack<Lambda> _lambda_stack;
    std::stack<Matcher::Type> _template_stack;
    std::stack<PostClass> _postclass_stack;

    bool _skip;

    
private:
    void _checkLambdaConnector(Matcher::Type tok_type);
    void _checkPostClassState(Matcher::Type tok_type);

private:
    void _setContext(Token* tok);
    inline void _beginLine(State state, Matcher::Type ttype)    { _state_stack.push(state); _type_stack.push(ttype); }
    void _newBlock(State state);
    inline void _newRoot(Matcher::Type ttype)                   { _beginLine(State::ROOT, ttype); _parent_stack.push(nullptr); }
    void _endLine();
    void _deleteBlock();
    void _deleteRoot()                                          { _state_stack.pop(); _parent_stack.pop(); }
    void _deleteIfBlock(Matcher::Type future_type);

private:
    // block -> FUNC | THEN
    constexpr bool _isBlock(State state)    { return state == State::FUNC || state == State::THEN; }
    // line -> STMT | COND
    constexpr bool _isLine(State state)     { return state == State::STMT || state == State::COND; }

/*
    Action
*/
private:
    void _identifier(Matcher::Args args);
    void _branch(Matcher::Args args);
    // case | default
    void _case(Matcher::Args args)      { if (_state_stack.top() == State::THEN) _beginLine(State::STMT, args.tok_type); }
    void _do(Matcher::Args args)        { _beginLine(State::THEN, args.tok_type); }
    void _try(Matcher::Args args);
    // enum | class
    void _enum(Matcher::Args args)      { if (args.future_type == Matcher::Type::CLASS) _skip = true; _struct(args); }
    void _class(Matcher::Args args)     { if (_template_stack.empty()) _struct(args); }
    void _struct(Matcher::Args args);
    // outer
    void _operator(Matcher::Args)       { if (_lambda_stack.top() == Lambda::ROOT) _lambda_stack.push(Lambda::OPERATOR); }
    void _namespace(Matcher::Args args);
    void _template(Matcher::Args)       { _template_stack.push(Matcher::Type::TEMPLATE); }
    void _decltype(Matcher::Args args)  { _decltype_stack.push(args.tok_type); _otherwise(args); }
    // symbol
    void _l_paren(Matcher::Args args);
    void _r_paren(Matcher::Args);
    void _l_brace(Matcher::Args args);
    void _r_brace(Matcher::Args args);
    void _l_square(Matcher::Args args);
    void _r_square(Matcher::Args);
    void _semi(Matcher::Args args);
    void _colon(Matcher::Args);
    void _less(Matcher::Args args);
    void _greater(Matcher::Args args);
    // otherwise
    void _otherwise(Matcher::Args)      { if (_isBlock(_state_stack.top())) _beginLine(State::STMT, Matcher::Type::STMT); }
};
}
#endif
