#ifndef __MODEL_UPDATER_H__
#define __MODEL_UPDATER_H__

#include <stringeditor.h>
#include "model/block.h"


namespace PAFL
{
class Updater
{
public:
    struct Depth { bool target_depth; size_t pred_depth, succ_depth, parent_depth, child_depth; };
    struct Mutant { Block* block; std::string token; float original_value, mutated_value; };

public:
    Updater(Depth depth);
    Updater(Updater& rhs) = delete;
    Updater& operator=(Updater& rhs) = delete;
    Updater(Updater&& rhs) = delete;

    float max(const stmt_graph::Node* node, const Mutant& mutant) const;
    float max(const stmt_graph::Node* node) const;
    std::vector<Mutant> makeMutant(std::vector<const stmt_graph::Node*> buggy_nodes, float default_original_value, float mutated_value) const;
    void eraseIf(float threshold)   { for (int i = 0; i != BLOCK_NUM; ++i) _block_map[i]->eraseIf(threshold); }

    std::string toString() const;
    template <class Archive> void serialize(Archive& ar)
    {
        ar(_target, _pred, _succ, _parent, _child, _depth_map[0], _depth_map[1], _depth_map[2], _depth_map[3], _depth_map[4]);
    }

private:
    static constexpr int BLOCK_NUM = 5;

private:
    void _stay(std::vector<const stmt_graph::Node*>& node_vector, const stmt_graph::Node* cursor, size_t iter) const;
    void _left(std::vector<const stmt_graph::Node*>& node_vector, const stmt_graph::Node* cursor, size_t iter) const;
    void _right(std::vector<const stmt_graph::Node*>& node_vector, const stmt_graph::Node* cursor, size_t iter) const;
    void _up(std::vector<const stmt_graph::Node*>& node_vector, const stmt_graph::Node* cursor, size_t iter) const;
    void _down(std::vector<const stmt_graph::Node*>& node_vector, const stmt_graph::Node* cursor, size_t iter) const;

private:
    Block _target;
    Block _pred;
    Block _succ;
    Block _parent;
    Block _child;
    Block* _block_map[BLOCK_NUM];
    size_t _depth_map[BLOCK_NUM];
    decltype(&Updater::_stay) _direction_map[BLOCK_NUM];
};
}
#endif
