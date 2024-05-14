#ifndef __STATEMENT_GRAPH_NODE_H__
#define __STATEMENT_GRAPH_NODE_H__

#include <string>
#include <vector>


namespace stmt_graph
{
class Node
{
public:
    using line_t = uint32_t;
    using id_t = uint32_t;
    
public:
    Node(id_t id = 0) : id(id), begin(0), end(0), coverable(true), predecessor(nullptr), successor(nullptr), parent(nullptr) {}
    static std::string toString(const Node* node, const std::string& tab, const std::string& child_marker, const std::string& non_child_marker,
                            const std::string& succ_marker, const std::string& indent = "");
    /*
        tab = "  "
        child_marker = "|-"
        succ_marker = " |"
    */ 
    static std::string toString(const Node* node) { return toString(node, "   ", "|-", "| ", " |"); }

public:
    std::vector<std::string> token_vector;
    id_t id;
    line_t begin;
    line_t end;
    bool coverable;

    const Node* predecessor;
    const Node* successor;
    const Node* parent;
    std::vector<const Node*> children;
};
}
#endif
