#ifndef __PYPDA_H__
#define __PYPDA_H__

#include <stack>
#include "tokentree/tokentree.h"


namespace PAFL
{
class PyPda
{
public:
    PyPda(Token* root) { newBlock(root); }
    void addTokens(const Token::List& tokens, std::shared_ptr<Token::List> children = nullptr);
    void newBlock(Token* parent);
    void delBlock();

private:
    std::stack<Token*> _parent_stack;
    std::stack<std::shared_ptr<Token::List>> _predecessor_stack;
    std::stack<std::shared_ptr<Token::List>> _neighbors_stack;
    std::stack<std::shared_ptr<Token::List>> _successor_stack;
};
}
#endif
