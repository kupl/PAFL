#include "tokentree/pypda.h"

namespace PAFL
{
void PyPda::addTokens(const Token::List& tokens, std::shared_ptr<Token::List> children)
{
    if (tokens.empty())
        return;

    // New line
    _predecessor_stack.top() = _neighbors_stack.top();
    _neighbors_stack.top() = _successor_stack.top();
    _successor_stack.pop();
    _successor_stack.emplace(std::make_shared<Token::List>());

    // Set token's relation
    for (auto tok : tokens) {

        tok->parent = _parent_stack.top();
        tok->predecessor = _predecessor_stack.top();
        tok->neighbors = _neighbors_stack.top();
        tok->neighbors->push_back(tok);
        tok->successor = _successor_stack.top();
        tok->children = children;
        if (_parent_stack.top() != tok->root)
            _parent_stack.top()->children->push_back(tok);
    }
}



void PyPda::newBlock(Token* parent)
{
    _parent_stack.push(parent);
    _predecessor_stack.emplace();
    _neighbors_stack.emplace(std::make_shared<Token::List>());
    _successor_stack.emplace(std::make_shared<Token::List>());
}



void PyPda::delBlock()
{
    _parent_stack.pop();
    _predecessor_stack.pop();
    _neighbors_stack.pop();
    _successor_stack.pop();
}
}
