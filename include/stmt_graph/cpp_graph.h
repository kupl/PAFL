#ifndef __STATEMENT_GRAPH_CPPGRAPH_H__
#define __STATEMENT_GRAPH_CPPGRAPH_H__

#include <filesystem>
#include <charconv>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <tree_sitter/api.h>
#include <tree-sitter-cpp.h>

#include "./graph.h"


namespace stmt_graph
{
class CppGraph : public Graph
{
public:
    CppGraph(const std::filesystem::path& source_path, const std::string& include_dir);
    static std::string collectIncludeDir(const std::filesystem::path dir);

private:
    std::string _resolvePreproccessor(const std::filesystem::path& source_path, const std::string& include);
    
private:
    class Builder;
};


// Build graph of the AST
class CppGraph::Builder
{
public:
    Builder(CppGraph& graph, const std::string& source);

private:
    struct NodePtr { Node* current, *predecessor, *parent; };

private:
    void walkAST();
    void walkTrivial();
    void walkChildren();
    void beginNode();
    void endNode() { _node_ptr.predecessor = _node_ptr.current; }

    void addTerminalNode(const TSNode& node, const std::string& type);
    std::string queryName(TSNode node);
    // Update node pointers and return original pointers
    NodePtr updateNodePtr();
    NodePtr updateNodePtr(NodePtr update);

private:
    CppGraph& _graph;
    const std::string& _source;
    TSTreeCursor* _cursor;
    Node* _root;
    NodePtr _node_ptr;
    
    const std::unordered_map<std::string, decltype(&Builder::walkAST)> _non_terminal_map;
    const std::unordered_set<std::string> _terminal_set;
    const std::unordered_set<std::string> _non_terminal_set;
    const std::unordered_set<std::string> _literal_set;

private:
    //  Block -> enum_specifier | strcut_specifier | union_specifier | class_specifier | function_definition
    void block();
    /*
        Statement ->    Decl | Stmt
        Decl ->         using_declaration | alias_declaration
        Stmt ->         namespace_alias_definition | attributed_statement | expression_statement
                        | return_statement | break_statement | continue_statement | goto_statement
                        | co_return_statement | co_yield_statement | throw_statement
    */
    void statement();
    //  Branch -> if_statement | switch_statement | while_statement
    void branch();
    
    void case_statement();
    void do_statement();
    void for_family();
    void try_statement();
    void catch_clause();
    void lambda_expression();
    void declaration();
    void field_initializer_list();
};
}
#endif
