#include "model/block.h"

namespace PAFL
{
float Block::max(const std::vector<const stmt_graph::Node*>& nodes, const map_value_t& mutant) const
{
    float max = 0.0f;
    for (auto node : nodes)
        if (node)
            for (auto& tok : node->token_vector)
                // Mutated mapped value
                if (mutant.first == tok && mutant.second > max)
                    max = mutant.second;
                // Mapped value
                else if (_map.contains(tok)) {

                    float val = _map.at(tok);
                    if (val > max)
                        max = val;
                }
    return _weight * max;
}



float Block::max(const std::vector<const stmt_graph::Node*>& nodes) const
{
    float max = 0.0f;
    for (auto node : nodes)
        if (node)
            for (auto& tok : node->token_vector)
                // Mapped value
                if (_map.contains(tok)) {

                    float val = _map.at(tok);
                    if (val > max)
                        max = val;
                }
    return _weight * max;
}



Block::T Block::makeMutants(const std::vector<const stmt_graph::Node*>& buggy_nodes, float default_value) const
{
    auto ret = _map;
    ret.reserve(_map.size() * 2);

    for (auto buggy_node : buggy_nodes)
        if (buggy_node)
            for (auto tok : buggy_node->token_vector)
                ret.try_emplace(tok, default_value);
    return ret;
}



std::vector<Block::map_value_t> Block::getItems() const
{
    std::vector<map_value_t> ret;
    ret.reserve(_map.size());
    for (auto& item : _map)
        ret.push_back(item);
    std::sort(ret.begin(), ret.end(), [](const T::value_type& lhs, const T::value_type& rhs){ return lhs.second > rhs.second; });
    return ret;
}
}
