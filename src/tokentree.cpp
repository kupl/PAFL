#include "tokentree/tokentree.h"

namespace PAFL
{
TokenTree::TokenTree(const fs::path& src_file, const fs::path& bin, const std::string& exe)
{
    fs::path temp_json(bin / (src_file.filename().string() + ".json"));
    std::string cmd = exe + " " + src_file.string() + " " + temp_json.c_str();
    std::system(cmd.c_str());
    load(temp_json);
    std::remove(temp_json.c_str());
    setIndexer();
}



void TokenTree::save(const fs::path& path) const
{
    IdGenerator token_id;
    IdGenerator node_id;
    token_id[nullptr];              // token_id[0]  -> nullptr
    node_id[nullptr];               // node_id[0]   -> nullptr
    std::unordered_set<Token::List*> node_set;

    for (auto& list : _stream)
        for (auto& tok : list) {

            token_id[&tok];
            for (auto ptr : {tok.neighbor.get(), tok.parent.get(), tok.child.get(), tok.pred.get(), tok.succ.get()})
                if (ptr) {

                    node_id[ptr];
                    node_set.insert(ptr);
                }
        }


    // Initialize buffer
    std::string buffer("{\n");
    buffer.reserve(StringEditor::MiB(64));

    // "total_tokens"
    buffer.append("\"total_tokens\": ");
    StringEditor::append(buffer, token_id.size() - 1).append(",\n");

    // "tokens"
    buffer.append("\"tokens\": [");
    for (auto& list : _stream) {
        
        buffer.append("{\"loc\":");
        StringEditor::append(buffer, list.begin()->loc).append(",\"tokens\":[");

        // "tokens": "tokens"
        for (auto& tok : list) {
            
            StringEditor::append(buffer, token_id[&tok]).push_back(',');
            buffer.append(tok.name).push_back(',');
            for (auto ptr : {tok.neighbor.get(), tok.parent.get(), tok.child.get(), tok.pred.get(), tok.succ.get()})
                StringEditor::append(buffer, node_id[ptr]).push_back(',');
            buffer.pop_back();
            buffer.append("],");
        }
        
        StringEditor::eraseEndIf(buffer, ',');
        buffer.append("]},");
    }
    StringEditor::eraseEndIf(buffer, ',');
    buffer.append("],\n");


    // "total_nodes"
    buffer.append("\"total_nodes\": ");
    StringEditor::append(buffer, node_id.size() - 1).append(",\n");

    // "nodes"
    buffer.append("\"nodes\": [");
    for (auto ptr : node_set) {

        buffer.append("\"id\":");
        StringEditor::append(buffer, node_id[ptr]).append(",\"elems\":[");
        StringEditor::append(buffer, ptr->size()).push_back(' ');

        // token id list
        for (auto tok : *ptr)
            StringEditor::append(buffer, token_id[tok]).push_back(',');

        StringEditor::eraseEndIf(buffer, ',');
        buffer.append("]},");
    }
    StringEditor::eraseEndIf(buffer, ',');
    buffer.append("],\n");

    // Write buffer to path
    buffer.pop_back(); buffer.pop_back();
    buffer.append("\n}");
    std::ofstream(path).write(buffer.c_str(), buffer.size());
}



void TokenTree::load(const fs::path& path)
{
    // Initialize token tree
    _stream.clear();
    setIndexer();

    // Parse saved JSON
    rapidjson::Document doc;
    doc.Parse(StringEditor::read(path.c_str()).c_str());

    // Initialize token
    std::vector<Token*> token_id(doc["total_tokens"].GetUint64() + 1);
    token_id[0] = nullptr;      // node_id[0]  -> nullptr

    // Initialize tokenlist
    std::vector<Token::Node> node_id(doc["total_nodes"].GetUint64() + 1);
    node_id[0] = nullptr;       // node_id[0]  -> nullptr

    // Load tokens to _stream
    for (const auto& tokens_obj : doc["tokens"].GetArray()) {

        const auto& tokens = tokens_obj.GetObject();
        auto lineno = tokens["lineno"].GetUint();
        auto& list_ref = _stream.emplace_back();

        for (const auto& token_info_arr : tokens["tokens"].GetArray()) {
            
            // New token
            const auto& token_info = token_info_arr.GetArray();
            auto token = &list_ref.emplace_back(token_info[NAME].GetString(), lineno);
            token_id[token_info[ID].GetUint64()] = token;

            // Set token's context
            token->neighbor = node_id[token_info[NEIGH].GetUint64()];
            token->parent = node_id[token_info[PARENT].GetUint64()];
            token->child = node_id[token_info[CHILD].GetUint64()];
            token->pred = node_id[token_info[PRED].GetUint64()];
            token->succ = node_id[token_info[SUCC].GetUint64()];
        }
    }
    setIndexer();

    // Set token list
    for (const auto& nodes_obj : doc["nodes"].GetArray()) {

        const auto& nodes = nodes_obj.GetObject();
        auto list_ptr = node_id[nodes["id"].GetUint64()].get();
        for (const auto& elem_uint64 : nodes["elems"].GetArray())
            list_ptr->push_back(token_id[elem_uint64.GetUint64()]);
    }
}



std::string TokenTree::log() const
{
    std::string buffer;
    for (auto& list : _stream)
        for (auto& tok : list) {
            
            buffer.append("=== ");
            StringEditor::append(buffer, tok.loc).append(", \"");
            buffer.append(tok.name).append("\" ===\n");
            auto appendNode = [&buffer](const Token::List* node, const std::string& name) {
                if (node) {

                    buffer.append(name).append(": [ ");
                    for (auto tok : *node)
                        buffer.append(tok->name).append(", ");
                    buffer.pop_back();
                    StringEditor::eraseEndIf(buffer, ',');
                    buffer.append(" ]\n");
                }
                else
                    StringEditor::append(buffer, name).append(": NULL\n");
            };

            appendNode(tok.neighbor.get(), "NEIGHBOR\t");
            appendNode(tok.parent.get(), "PARENT\t\t");
            appendNode(tok.child.get(), "CHILD\t\t");
            appendNode(tok.pred.get(), "PRED\t\t");
            appendNode(tok.succ.get(), "SUCC\t\t");
        }
    StringEditor::eraseEndIf(buffer, '\n');
    
    return buffer;
}



void TokenTree::setIndexer()
{
    _indexer.clear();
    _indexer.reserve(_stream.size());
    for (auto& list : _stream)
        _indexer.emplace(list.begin()->loc, &list);
}



TokenTree::IdGenerator::id_t TokenTree::IdGenerator::operator[](const void* ptr)
{
    if (id_list.contains(ptr))
        return id_list.at(ptr);
    id_list.emplace(ptr, id++);
    return id;
}
}
