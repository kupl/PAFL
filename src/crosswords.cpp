#include "crosswords.h"

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



void CrossWord::insertToken(const Token& token, float base)
{
    _insert(token.neighbor, _target, base);
    _insert(token.parent, _parent, base);
    _insert(token.child, _child, base);
    _insert(token.pred, _pred, base);
    _insert(token.succ, _succ, base);
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

    float target_weight = _maxWeight(token.neighbor, _target, denom);
    float pred_weight = _maxWeight(token.pred, _pred, denom);
    float succ_weight = _maxWeight(token.succ, _succ, denom);
    float parent_weight = _maxWeight(token.parent, _parent, denom);
    float child_weight = _maxWeight(token.child, _child, denom);

    return denom ? (target_weight + parent_weight + child_weight + pred_weight + succ_weight) / (float)denom : 0.0f;
}



float CrossWord::_maxWeight(Token::Node node, const block& blck, size_t& denom) const
{
    if (!node || blck.empty())
        return 0.0f;
    denom++;
    if (node->empty())
        return 0.0f;
    
    float ret = 0.0f;
    for (auto tok : *node)
        if (blck.contains(tok->name)) {

            auto temp = blck.at(tok->name).weight;
            if (temp > ret)
                ret = temp;
        }
    return ret;
}



void CrossWord::_insert(Token::Node node, block& blck, float base)
{
    if (node)
        for (auto tok : *node)
            if (!blck.contains(tok->name))
                blck.emplace(tok->name, Weight{base, base});
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
