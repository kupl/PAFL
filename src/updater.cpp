#include "model/updater.h"

namespace PAFL
{
Updater::Updater(Depth depth) : 
    _block_map{&_target, &_pred, &_succ, &_parent, &_child},
    _depth_map{depth.target_depth, depth.pred_depth, depth.succ_depth, depth.parent_depth, depth.child_depth},
    _direction_map{&Updater::_stay, &Updater::_left, &Updater::_right, &Updater::_up, &Updater::_down} {}



float Updater::max(const aggregated_ast::Node* node, const Mutant& mutant) const
{
    float max = 0.0f;
    float denom = 0.0f;
    if (node)
        for (int i = 0; i != BLOCK_NUM; ++i)
            // block is not empty
            if (!_block_map[i]->empty() || _block_map[i] == mutant.block) {
                
                denom += _block_map[i]->getWeight();
                std::vector<const aggregated_ast::Node*> node_vector;
                (this->*_direction_map[i])(node_vector, node, _depth_map[i]);
                max += _block_map[i] == mutant.block ? _block_map[i]->max(node_vector, std::make_pair(mutant.token, mutant.mutated_value)) : _block_map[i]->max(node_vector);
            }

    if (denom <= 0.0f)
        return 0.0f;
    return max / denom;
}



float Updater::max(const aggregated_ast::Node* node) const
{
    float max = 0.0f;
    float denom = 0.0f;
    if (node)
        for (int i = 0; i != BLOCK_NUM; ++i)
            // block is not empty
            if (!_block_map[i]->empty()) {
                
                denom += _block_map[i]->getWeight();
                std::vector<const aggregated_ast::Node*> node_vector;
                (this->*_direction_map[i])(node_vector, node, _depth_map[i]);
                max += _block_map[i]->max(node_vector);
            }

    if (denom <= 0.0f)
        return 0.0f;
    return max / denom;
}



std::vector<Updater::Mutant> Updater::makeMutant(std::vector<const aggregated_ast::Node*> buggy_nodes, float default_original_value, float mutated_value) const
{
    std::vector<Mutant> ret;
    for (int i = 0; i != BLOCK_NUM; ++i) {

        std::vector<const aggregated_ast::Node*> node_vector;
        for (auto buggy_node : buggy_nodes)
            (this->*_direction_map[i])(node_vector, buggy_node, _depth_map[i]);
        for (auto& item : _block_map[i]->makeMutants(node_vector, default_original_value))
            ret.emplace_back(Mutant{_block_map[i], item.first, item.second, mutated_value});
    }
    return ret;
}



void Updater::_stay(std::vector<const aggregated_ast::Node*>& node_vector, const aggregated_ast::Node* cursor, size_t iter) const
{
    if (iter && cursor)
        node_vector.push_back(cursor);
}



void Updater::_left(std::vector<const aggregated_ast::Node*>& node_vector, const aggregated_ast::Node* cursor, size_t iter) const
{
    if (cursor)
        for (cursor = cursor->predecessor; iter && cursor; cursor = cursor->predecessor, --iter)
            node_vector.push_back(cursor);
}



void Updater::_right(std::vector<const aggregated_ast::Node*>& node_vector, const aggregated_ast::Node* cursor, size_t iter) const
{
    if (cursor)
        for (cursor = cursor->successor; iter && cursor; cursor = cursor->successor, --iter)
            node_vector.push_back(cursor);
}



void Updater::_up(std::vector<const aggregated_ast::Node*>& node_vector, const aggregated_ast::Node* cursor, size_t iter) const
{
    if (cursor)
        for (cursor = cursor->parent; iter && cursor; cursor = cursor->parent, --iter)
            node_vector.push_back(cursor);
}



void Updater::_down(std::vector<const aggregated_ast::Node*>& node_vector, const aggregated_ast::Node* cursor, size_t iter) const
{
    std::vector<const aggregated_ast::Node*> queue{cursor};
    while(iter && !queue.empty()) {

        decltype(queue) new_queue;
        for (auto node : queue)
            if (node)
                for(auto& child : node->children)
                    if (child) {

                        new_queue.push_back(child);
                        node_vector.push_back(child);
                    }
        --iter;
        queue = std::move(new_queue);
    }
}



std::string Updater::toString() const
{
    std::string buffer;
    const char* name[] = {"target", "predecessor", "successor", "parent", "child"};
    for (int i = 0; i != BLOCK_NUM; ++i) {

        buffer.append(" ").append(name[i]).append(":\n");
        auto items(_block_map[i]->getItems());
        for (auto& item : items)
            StringEditor::append(buffer.append("  " + item.first).append(", "), item.second).push_back('\n');
    }
    StringEditor::eraseEndIf(buffer, '\n');
    return buffer;
}
}
