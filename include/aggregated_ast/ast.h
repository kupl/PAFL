#ifndef __AGGREGATED_AST_AST_H__
#define __AGGREGATED_AST_AST_H__

#include <list>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <tree_sitter/api.h>
#include <stringeditor.h>
#include <rapidjson/document.h>

#include "./node.h"


namespace aggregated_ast
{
/*
    * id (0) = NULL

    JSON format
    {
        "name": "FILE_NAME",
        "size": uint,
        "root-id": uint,
        "nodes": [
            {
                "id": uint,
                "beg": uint,
                "end": uint,
                "coverable": bool,
                "pred": uint,
                "succ": uint,
                "parent": uint,
                "toks": [ str, ... ]
            },
            ...
        ]
    }
*/
class Ast
{
public:
    using line_t = Node::line_t;
    using vector_t = std::vector<std::unique_ptr<Ast>>;
    static constexpr Node::id_t ROOT_ID = 1;

public:
    Ast() : _root(std::make_unique<Node>(ROOT_ID)) {}
    Ast(Ast&) = delete;
    Ast& operator=(const Ast&) = delete;
    Ast(Ast&& rhs) : _root(std::move(rhs._root)), _node_list(std::move(rhs._node_list)) { setIndexer(); }

    // ROOT = Node with line number 0
    const Node* getRoot() const                             { return _root.get(); }
    const std::vector<const Node*>* at(line_t line) const   { return _indexer.contains(line) ? &_indexer.at(line) : nullptr; }

    // Convert JSON format to Aggregated AST
    void fromJSON(const rapidjson::Document& doc);
    // Convert this to JSON format
    std::string toJSON(const std::string& name) const;
    // Convert this to string
    std::string toString() const                    { return Node::toString(_root.get()); }

    std::list<Node>::const_iterator begin() const   { return _node_list.cbegin(); }
    std::list<Node>::const_iterator end() const     { return _node_list.cend(); }

public:
    static std::string printNode(TSNode node, const std::string& indent = "");

protected:
    void setIndexer();

protected:
    std::unique_ptr<Node> _root;
    std::list<Node> _node_list;
    std::unordered_map<line_t, std::vector<const Node*>> _indexer;
};
}
#endif
