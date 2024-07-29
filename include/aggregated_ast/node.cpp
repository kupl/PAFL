#include "./node.h"

namespace aggregated_ast
{
std::string Node::toString(const Node* node, const std::string& tab, const std::string& child_marker, const std::string& non_child_marker,
                        const std::string& succ_marker, const std::string& indentation)
{
    std::string ret;
    if (node) {

        ret += indentation + non_child_marker + (node->predecessor ? succ_marker : "") + "\n";
        ret += indentation + child_marker + "(" + std::to_string(node->begin) + ", " + std::to_string(node->end) + ") - [";
        for (auto& token : node->token_vector)
            ret += token + ", ";
        if (ret.ends_with(", ")) { ret.pop_back(); ret.pop_back(); }
        ret.append("]\n");
        for (auto child : node->children)
            ret.append(toString(child, tab, child_marker, non_child_marker, succ_marker, indentation + tab));
    }
    return ret;
}
}
