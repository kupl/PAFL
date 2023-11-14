#ifndef __CROSS_WORD_H__
#define __CROSS_WORD_H__

#include "flmodel_type.h"



namespace PAFL
{
#define FOR_BLOCK(i) for(i = 0; i != 5; i++)

class CrossWord
{
public:
    typedef struct { float weight; float future; } Weight;
    using block = std::unordered_map<std::string, Weight>;
    using fragment = std::pair<CrossWord, Weight*>;

    enum BLOCK { TARGET = 0x01, PARENT = 0x02, CHILD = 0x04, PRED = 0x08, SUCC = 0x10 };



    class iterator
    {
    public:
        iterator(block* const blocks[]) :
            _transition{ {blocks[0], blocks[1]}, {blocks[1], blocks[2]}, {blocks[2], blocks[3]}, {blocks[3], blocks[4]} },
            _iter(blocks[0]->begin()), _ptr(blocks[0]), _end(blocks[4]), _block(BLOCK::TARGET) { _skip(); }

        iterator& operator++()                  { ++_iter; _skip(); return *this; }
        block::value_type& operator*()          { return *_iter; }
        block::iterator& operator->()           { return _iter; }
        bool operator==(block::iterator iter)   { return _iter == iter; }
        bool operator!=(block::iterator iter)   { return _iter != iter; }
 
        // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
        unsigned char getCurrentBlock() const   { return _block; }

    private:
        void _skip()    { while (_ptr != _end && _iter == _ptr->end()) { _iter = (_ptr = _transition[_ptr])->begin(); _block <<= 1; }}

        block::iterator _iter;
        block* _ptr;
        block* _end;
        std::unordered_map<block*, block*> _transition;
        unsigned char _block;
    };

    class const_iterator
    {
    public:
        const_iterator(block* const blocks[]) :
            _transition{ {blocks[0], blocks[1]}, {blocks[1], blocks[2]}, {blocks[2], blocks[3]}, {blocks[3], blocks[4]} },
            _iter(blocks[0]->cbegin()), _ptr(blocks[0]), _end(blocks[4]), _block(BLOCK::TARGET) { _skip(); }

        const_iterator& operator++()                { ++_iter; _skip(); return *this; }
        const block::value_type& operator*()        { return *_iter; }
        block::const_iterator& operator->()         { return _iter; }
        bool operator==(block::const_iterator iter) { return _iter == iter; }
        bool operator!=(block::const_iterator iter) { return _iter != iter; }

        // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
        unsigned char getCurrentBlock() const       { return _block; }

    private:
        void _skip()    { while (_ptr != _end && _iter == _ptr->end()) { _iter = (_ptr = _transition[_ptr])->begin(); _block <<= 1; }}

        block::const_iterator _iter;
        block* _ptr;
        block* _end;
        std::unordered_map<block*, block*> _transition;
        unsigned char _block;
    };



    CrossWord() : _blocks{&_target, &_parent, &_child, &_pred, &_succ} {}
    // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
    CrossWord(const std::string& tok, float weight, unsigned char flag);
    CrossWord(const CrossWord& rhs) : _target(rhs._target), _parent(rhs._parent), _child(rhs._child), _pred(rhs._pred), _succ(rhs._succ), _blocks{&_target, &_parent, &_child, &_pred, &_succ} {}

    void insertToken(const Token& token, float base);
    void eraseIf(float threshold);

    void assignFuture();

    float similarity(const Token& token) const;
    bool contains(const std::string& tok) const { int i = 0; FOR_BLOCK(i) if (_blocks[i]->contains(tok)) return true; return false; }
    bool empty() const                          { return _target.empty() && _parent.empty() && _child.empty() && _pred.empty() && _succ.empty(); }


    decltype(auto) begin()                      { return iterator(_blocks); }
    decltype(auto) end()                        { return _succ.end(); }
    decltype(auto) cbegin() const               { return const_iterator(_blocks); }
    decltype(auto) cend() const                 { return _succ.cend(); }
    
    void log(const fs::path& path) const;

private:
    void _insert(decltype(Token::neighbors) set_ptr, block& blck, float base);
    float _maxWeight(decltype(Token::neighbors) set_ptr, const block& blck, size_t& denom) const;

    block* const _blocks[5];
    block _target;
    block _parent;
    block _child;
    block _pred;
    block _succ;
};
}






namespace PAFL
{
CrossWord::CrossWord(const std::string& tok, float weight, unsigned char flag) :
    _blocks{&_target, &_parent, &_child, &_pred, &_succ}
{
    if (flag & BLOCK::TARGET)
        _target.emplace(tok, Weight{weight, weight});
    if (flag & BLOCK::PARENT)
        _parent.emplace(tok, Weight{weight, weight});
    if (flag & BLOCK::CHILD)
        _child.emplace(tok, Weight{weight, weight});
    if (flag & BLOCK::PRED)
        _pred.emplace(tok, Weight{weight, weight});
    if (flag & BLOCK::SUCC)
        _succ.emplace(tok, Weight{weight, weight});
}



void CrossWord::insertToken(const Token& token, float base = 0.0f)
{
    _insert(token.neighbors, _target, base);

    if (token.parent != token.root)
        _insert(token.parent->neighbors, _parent, base);
    if (token.children)
        _insert(token.children, _child, base);

    _insert(token.predecessor, _pred, base);
    _insert(token.successor, _succ, base);
}

void CrossWord::eraseIf(float threshold)
{
    auto lambda = [threshold](const auto& item){ return item.second.weight <= threshold; };
    int i = 0; FOR_BLOCK(i)
        std::erase_if(*_blocks[i], lambda);
}



void CrossWord::assignFuture()
{
    int i = 0; FOR_BLOCK(i)
        for (auto& item : *_blocks[i])
            item.second.weight = item.second.future;
}



float CrossWord::similarity(const Token& token) const
{
    size_t denom = 0;

    float target_weight = _maxWeight(token.neighbors, _target, denom);
    float pred_weight = _maxWeight(token.predecessor, _pred, denom);
    float succ_weight = _maxWeight(token.successor, _succ, denom);

    float parent_weight = 0.0f;
    if (token.parent != token.root)
        parent_weight = _maxWeight(token.parent->neighbors, _parent, denom);

    float child_weight = 0.0f;
    if (token.children)
        child_weight = _maxWeight(token.children, _child, denom);

    return denom ? (target_weight + parent_weight + child_weight + pred_weight + succ_weight) / (float)denom : 0.0f;
}



float CrossWord::_maxWeight(decltype(Token::neighbors) set_ptr, const block& blck, size_t& denom) const
{
    if (blck.empty() || set_ptr->empty())
        return 0.0f;
    denom++;
    float ret = 0.0f;

    for (auto& tok : *set_ptr)
        if (blck.contains(tok)) {

            auto temp = blck.at(tok).weight;
            if (temp > ret)
                ret = temp;
        }
    return ret;
}

void CrossWord::_insert(decltype(Token::neighbors) set_ptr, block& blck, float base)
{
    for (auto& tok : *set_ptr)
        if (!blck.contains(tok))
            blck.emplace(tok, Weight{base, base});
}



void CrossWord::log(const fs::path& path) const
{
    std::ofstream ofs(path);

    auto _logBlock = [](std::ofstream& ofs, const CrossWord::block& block)
        { for (auto& item : block) ofs << "  -:\"" << item.first << "\"  ->  " << item.second.weight << '\n'; };
    ofs << "\n<Target>\n\n"; _logBlock(ofs, _target);
    ofs << "\n<Parent>\n\n"; _logBlock(ofs, _parent);
    ofs << "\n<Child>\n\n"; _logBlock(ofs, _child);
    ofs << "\n<Pred>\n\n"; _logBlock(ofs, _pred);
    ofs << "\n<Succ>\n\n"; _logBlock(ofs, _succ);
}
}
#endif
