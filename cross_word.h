#ifndef __CROSS_WORD_H__
#define __CROSS_WORD_H__

#include "flmodel_type.h"



namespace PAFL
{
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
        iterator(block& target, block& parent, block& child, block& pred, block& succ) :
            _transition{ {&target, &parent}, {&parent, &child}, {&child, &pred}, {&pred, &succ} },
            _iter(target.begin()), _ptr(&target), _end(&succ), _block(BLOCK::TARGET) { _skip(); }

        iterator& operator++()
            { ++_iter; _skip(); return *this; }
        block::value_type& operator*()
            { return *_iter; }
        block::iterator& operator->()
            { return _iter; }
        bool operator==(block::iterator iter)
            { return _iter == iter; }
        bool operator!=(block::iterator iter)
            { return _iter != iter; }
 
        // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
        unsigned char getCurrentBlock() const
            { return _block; }

    private:
        void _skip()
            { while (_ptr != _end && _iter == _ptr->end())
            { _iter = (_ptr = _transition[_ptr])->begin(); _block <<= 1; }}

        block::iterator _iter;
        block* _ptr;
        block* _end;
        std::unordered_map<block*, block*> _transition;
        unsigned char _block;
    };

    class const_iterator
    {
    public:
        const_iterator(const block& target, const block& parent, const block& child, const block& pred, const block& succ) :
            _transition{ {&target, &parent}, {&parent, &child}, {&child, &pred}, {&pred, &succ} },
            _iter(target.begin()), _ptr(&target), _end(&succ), _block(BLOCK::TARGET) { _skip(); }

        const_iterator& operator++()
            { ++_iter; _skip(); return *this; }
        const block::value_type& operator*()
            { return *_iter; }
        block::const_iterator& operator->()
            { return _iter; }
        bool operator==(block::const_iterator iter)
            { return _iter == iter; }
        bool operator!=(block::const_iterator iter)
            { return _iter != iter; }

        // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
        unsigned char getCurrentBlock() const
            { return _block; }

    private:
        void _skip()
            { while (_ptr != _end && _iter == _ptr->end())
            { _iter = (_ptr = _transition[_ptr])->begin(); _block <<= 1; }}

        block::const_iterator _iter;
        const block* _ptr;
        const block* _end;
        std::unordered_map<const block*, const block*> _transition;
        unsigned char _block;
    };



    CrossWord() = default;
    // BLOCK:: TARGET = 0x01 | PARENT = 0x02 | CHILD = 0x04 | PRED = 0x08 | SUCC = 0x10
    CrossWord(const std::string& tok, float weight, unsigned char flag);


    void insertToken(const Token& token, float base);
    void eraseIf(float threshold);

    void assignFuture();

    float similarity(const Token& token) const;
    bool empty() const
        { return _target.empty() && _parent.empty() && _child.empty() && _pred.empty() && _succ.empty(); }


    decltype(auto) begin()
        { return iterator(_target, _parent, _child, _pred, _succ); }
    decltype(auto) end()
        { return _succ.end(); }
    decltype(auto) cbegin() const
        { return const_iterator(_target, _parent, _child, _pred, _succ); }
    decltype(auto) cend() const
        { return _succ.cend(); }
    
    void log(const fs::path& path) const;

    
private:
    void _insert(decltype(Token::neighbors) set_ptr, block& blck, float base);
    float _maxWeight(decltype(Token::neighbors) set_ptr, const block& blck, size_t& denom) const;

    block _target;
    block _parent;
    block _child;
    block _pred;
    block _succ;
};
}






namespace PAFL
{
CrossWord::CrossWord(const std::string& tok, float weight, unsigned char flag)
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
    std::erase_if(_target, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_parent, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_child, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_pred, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_succ, [=](const auto& item){ return item.second.weight <= threshold; });
}



void CrossWord::assignFuture()
{
    for (auto& item : _target) item.second.weight = item.second.future;
    for (auto& item : _parent) item.second.weight = item.second.future;
    for (auto& item : _child) item.second.weight = item.second.future;
    for (auto& item : _pred) item.second.weight = item.second.future;
    for (auto& item : _succ) item.second.weight = item.second.future;
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

    return (target_weight + parent_weight + child_weight + pred_weight + succ_weight) / (float)denom;
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
