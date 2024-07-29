#ifndef __MODEL_BLOCK_H__
#define __MODEL_BLOCK_H__

#include <unordered_map>
#include <unordered_set>
#include <list>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>

#include "aggregated_ast/node.h"


namespace PAFL
{
class Block
{
public:
    using map_value_t = std::pair<std::string, float>;
    using T = std::unordered_map<std::string, float>;

public:
    Block() = default;
    Block(Block& rhs) : _map(rhs._map), _weight(rhs._weight)                {}
    Block& operator=(const Block& rhs)                                      { _map = rhs._map; _weight = rhs._weight; return *this; }
    Block(Block&& rhs) : _map(std::move(rhs._map)), _weight(rhs._weight)    {}
    Block& operator=(Block&& rhs)                                           { _map = std::move(rhs._map); _weight = rhs._weight; return *this;}
    Block& operator=(T&& map)                                               { _map = std::move(map); return *this; }

    float max(const std::vector<const aggregated_ast::Node*>& nodes, const map_value_t& mutant) const;
    float max(const std::vector<const aggregated_ast::Node*>& nodes) const;
    T makeMutants(const std::vector<const aggregated_ast::Node*>& buggy_nodes, float default_value) const;
    T& data() { return _map; }

    void setValue(const std::string& token, float value)    { _map[token] = value; }
    void setWeight(float weight)                            { _weight = weight; }
    void eraseIf(float threshold)                           { std::erase_if(_map, [threshold](const auto& item){ return item.second <= threshold; }); }

    float getValue(const std::string& token) const          { return _map.contains(token) ? _map.at(token) : 0.0f; }
    float getWeight() const                                 { return _weight; }
    std::vector<map_value_t> getItems() const;
    bool empty() const                                      { return _map.empty(); }

    template <class Archive> void serialize(Archive& ar)    { ar(_map, _weight); }

private:
    T _map;
    float _weight = 1.0f;
};
}
#endif
