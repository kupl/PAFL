#include "./graph.h"


namespace stmt_graph
{
void Graph::fromJSON(const rapidjson::Document& doc)
{
    _node_list.clear();
    _indexer.clear();

    // Set _root
    auto root_id = doc["root-id"].GetUint();
    _root.reset(new Node(root_id));

    // Initialize id2node
    struct NodeInfo { Node* ptr; Node::id_t pred, succ, parent; };
    std::unordered_map<Node::id_t, NodeInfo> id2node;
    id2node.reserve(doc["size"].GetUint() + 1);
    id2node.emplace(root_id, NodeInfo{_root.get(), 0, 0, 0});

    // Load node list
    for (const auto& doc_node_obj : doc["nodes"].GetArray()) {

        const auto& doc_node = doc_node_obj.GetObject();
        // id
        auto& node = _node_list.emplace_back(doc_node["id"].GetUint());
        // beg
        node.begin = doc_node["beg"].GetUint();
        // end
        node.end = doc_node["end"].GetUint();
        // coverable
        node.coverable = doc_node["coverable"].GetBool();
        // pred & succ & parent
        id2node.emplace(node.id, NodeInfo{&node, doc_node["pred"].GetUint(), doc_node["succ"].GetUint(), doc_node["parent"].GetUint()});
        // toks
        for (const auto& doc_tok_str : doc_node["toks"].GetArray())
            node.token_vector.emplace_back(doc_tok_str.GetString());
    }
    
    // Set node relation
    id2node.erase(root_id);
    for (auto& item : id2node) {

        auto& info = item.second;
        if (info.pred)
            info.ptr->predecessor = id2node.at(info.pred).ptr;
        if (info.succ)
            info.ptr->successor = id2node.at(info.succ).ptr;
        if (info.parent == root_id) {

            info.ptr->parent = _root.get();
            _root->children.push_back(info.ptr);
        }
        else {

            info.ptr->parent = id2node.at(info.parent).ptr;
            id2node.at(info.parent).ptr->children.push_back(info.ptr);
        }
    }
    setIndexer();
}



std::string Graph::toJSON(const std::string& name) const
{
    std::string buffer;
    buffer.reserve(StringEditor::MiB(16));
    // name
    buffer.append("{\n\"name\": \"").append(name).append("\",\n");
    // size
    StringEditor::append(buffer.append("\"size\": "), _node_list.size()).append(",\n");
    // root-id
    StringEditor::append(buffer.append("\"root-id\": "), _root->id).append(",\n");

    // nodes
    buffer.append("\"nodes\": [");
    for (auto& node : _node_list) {
        
        // id
        StringEditor::append(buffer.append("{\"id\":"), node.id).push_back(',');
        // begin
        StringEditor::append(buffer.append("\"beg\":"), node.begin).push_back(',');
        // end
        StringEditor::append(buffer.append("\"end\":"), node.end).push_back(',');
        // coverable
        buffer.append("\"coverable\":").append(node.coverable ? "true," : "false,");
        // predecessor
        StringEditor::append(buffer.append("\"pred\":"), node.predecessor ? node.predecessor->id : 0).push_back(',');
        // successor
        StringEditor::append(buffer.append("\"succ\":"), node.successor ? node.successor->id : 0).push_back(',');
        // parent
        StringEditor::append(buffer.append("\"parent\":"), node.parent ? node.parent->id : 0).push_back(',');

        // toks
        buffer.append("\"toks\":[");
        for (auto& tok : node.token_vector)
            buffer.append("\"").append(tok).append("\",");
        StringEditor::eraseEndIf(buffer, ',');
        buffer.append("]},");
    }

    StringEditor::eraseEndIf(buffer, ',');
    buffer.append("]\n}");
    return buffer;
}



void Graph::setIndexer()
{
    _indexer.clear();
    _indexer.reserve(_node_list.size() * 2);
    for (auto& node : _node_list)
        for (auto line = node.begin; line <= node.end; ++line)
            _indexer[line].push_back(&node);
}



std::string Graph::printNode(TSNode node, const std::string& indent)
{
    std::string ret;
    std::string type = ts_node_type(node);
    auto start = ts_node_start_point(node);
    auto end = ts_node_end_point(node);

    // Print node property
    StringEditor::append(ret.append(indent).append(type).append(" ("), start.row + 1);
    StringEditor::append(ret.append(", "), end.row + 1).append(")\n");

    uint32_t childCount = ts_node_child_count(node);
    for (uint32_t i = 0; i < childCount; ++i) {
        TSNode child = ts_node_child(node, i);
        ret.append(printNode(child, indent + "  "));
    }
    return ret;
}
}
