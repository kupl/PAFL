#include "./py_graph.h"

namespace stmt_graph
{
PyGraph::PyGraph(const std::filesystem::path& source_path) :
    Graph()
{
    Builder(*this, StringEditor::read(source_path.c_str()));
    setIndexer();
}



PyGraph::Builder::Builder(PyGraph& graph, const std::string& source) :
    _graph(graph), _source(source), _root(graph._root.get()), _node_ptr{nullptr, nullptr, _root},
    _terminal_set{":=", "'", "\"", "=", "[", "]", "(", ")", "{", "}", ",", ".", ":", "->", "ellipsis", "else", "comment"},
    _literal_set{"integer", "float", "true", "false", "none"},
    _non_terminal_set{"string", "concatenated_string"},

    _non_terminal_map{
        /*
            Block -> function_definition | class_definition
        */
        {"function_definition", &Builder::block}, {"class_definition", &Builder::block},
        /*
            Statement -> simple statements | decorator
        */
        {"future_import_statement", &Builder::statement}, {"import_statement", &Builder::statement}, {"import_from_statement", &Builder::statement}, {"print_statement", &Builder::statement}, {"assert_statement", &Builder::statement}, {"expression_statement", &Builder::statement},
        {"return_statement", &Builder::statement}, {"delete_statement", &Builder::statement}, {"raise_statement", &Builder::statement}, {"pass_statement", &Builder::statement}, {"break_statement", &Builder::statement}, {"continue_statement", &Builder::statement},
        {"global_statement", &Builder::statement}, {"nonlocal_statement", &Builder::statement}, {"exec_statement", &Builder::statement}, {"type_alias_statement", &Builder::statement},
        {"decorator", &Builder::statement},
        /*
            Otherwise
        */
        {"for_statement", &Builder::for_statement},
        {"while_statement", &Builder::while_match_statement}, {"match_statement", &Builder::while_match_statement},
        {"if_statement", &Builder::if_statement},
        {"try_statement", &Builder::try_statement},
        {"with_statement", &Builder::with_statement},

        {"if_clause", &Builder::if_clause},
        // else_clause | finally_clause
        {"else_clause", &Builder::else_clause}, {"finally_clause", &Builder::else_clause},
        // except_clause | except_group_clause
        {"except_clause", &Builder::except_clause}, {"except_group_clause", &Builder::except_clause},
        {"case_clause", &Builder::case_clause},
        {"conditional_expression", &Builder::conditional_expression},
        {"for_in_clause", &Builder::for_in_clause}
    },
    
    _addtional_token_map{
        {"list", "list"}, {"set", "set"}, {"tuple", "tuple"}, {"dictionary", "dict"},
        {"list_comprehension", "list-comp"}, {"dictionary_comprehension", "dict-comp"}, {"set_comprehension", "set-comp"},
        {"generator_expression", "$generator"}
    }
{
    // Create a parser
    TSParser* parser = ts_parser_new();
    auto langauage = tree_sitter_python();
    ts_parser_set_language(parser, langauage);

    // Parse the source
    TSTree* tree = ts_parser_parse_string(parser, nullptr, source.c_str(), source.size());
    auto root = ts_tree_root_node(tree);
    auto cursor = ts_tree_cursor_new(root);
    _cursor = &cursor;
    
    // Build cpp-graph from the source
    walkAST();
    std::cout << printNode(root);

    // Cleanup
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}



void PyGraph::Builder::walkAST()
{
    auto node = ts_tree_cursor_current_node(_cursor);
    const std::string type = ts_node_type(node);

    // Non-Terminal node
    if (ts_node_child_count(node)) {

        if (_non_terminal_map.contains(type)) {

            if (ts_tree_cursor_goto_first_child(_cursor)) {

                (this->*_non_terminal_map.at(type))();
                ts_tree_cursor_goto_parent(_cursor);
            }
        }

        else if (!_non_terminal_set.contains(type) && ts_tree_cursor_goto_first_child(_cursor)) {
            
            if (_addtional_token_map.contains(type))
                addTerminalNode(node, _addtional_token_map.at(type));
            do walkAST();
            while (ts_tree_cursor_goto_next_sibling(_cursor));
            ts_tree_cursor_goto_parent(_cursor);
        }
    }

    // Terminal node
    else
        addTerminalNode(node, type);
}



void PyGraph::Builder::walkChildren()
{
    auto temp = updateNodePtr();
    walkAST();
    _node_ptr = temp;
}



void PyGraph::Builder::walkElif()
{
    auto node = ts_tree_cursor_current_node(_cursor);
    
    // elif_clause
    if (std::strcmp(ts_node_type(node), "elif_clause") == 0) {
        
        auto temp = updateNodePtr(); {

            beginNode();
            ts_tree_cursor_goto_first_child(_cursor); {
                
                // 'elif'
                addTerminalNode(ts_tree_cursor_current_node(_cursor), "if");

                // condition
                ts_tree_cursor_goto_next_sibling(_cursor);
                walkAST();

                // ':'
                ts_tree_cursor_goto_next_sibling(_cursor);

                // consequence
                ts_tree_cursor_goto_next_sibling(_cursor);
                walkChildren();
            }
            ts_tree_cursor_goto_parent(_cursor);

            // next elif
            if (ts_tree_cursor_goto_next_sibling(_cursor))
                walkElif();
            endNode();
        }
        _node_ptr = temp;
    }

    // else_clause
    else
        walkChildren();
}



void PyGraph::Builder::beginNode()
{
    _node_ptr.current = &_graph._node_list.emplace_back(_graph._node_list.size() + Graph::ROOT_ID + 1);
    // Set parent-child relation
    _node_ptr.current->parent = _node_ptr.parent;
    _node_ptr.parent->children.push_back(_node_ptr.current);

    // Set sibling relation
    _node_ptr.current->predecessor = _node_ptr.predecessor;
    if (_node_ptr.predecessor)
        _node_ptr.predecessor->successor = _node_ptr.current;
}



void PyGraph::Builder::addTerminalNode(const TSNode& node, const std::string& type)
{
    if (!_node_ptr.current || _terminal_set.contains(type))
        return;

    if (type == "identifier")
        _node_ptr.current->token_vector.emplace_back(queryName(node));
    else if (!_literal_set.contains(type))
        _node_ptr.current->token_vector.push_back(type);

    // Update line number
    auto begin = ts_node_start_point(node).row + 1;
    auto end = ts_node_end_point(node).row + 1;
    if (_node_ptr.current->begin == 0)
        _node_ptr.current->begin = _node_ptr.current->end = begin;
    if (_node_ptr.current->end < end)
        _node_ptr.current->end = end;
}



std::string PyGraph::Builder::queryName(TSNode node)
{
    auto start = ts_node_start_byte(node);
    auto end = ts_node_end_byte(node);
    return _source.substr(start, end - start);
}



PyGraph::Builder::NodePtr PyGraph::Builder::updateNodePtr()
{
    auto temp = _node_ptr;
    _node_ptr = {nullptr, nullptr, _node_ptr.current};
    return temp;
}



void PyGraph::Builder::block()
{
    beginNode();
    _node_ptr.current->coverable = false;
    do {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "body") == 0)
            break;
        else
            walkAST();
    }
    while (ts_tree_cursor_goto_next_sibling(_cursor));

    // body
    walkChildren();
    endNode();
}



void PyGraph::Builder::statement()
{
    beginNode();
    do walkAST();
    while (ts_tree_cursor_goto_next_sibling(_cursor));
    endNode();
}



void PyGraph::Builder::for_statement()
{
    {// 'async' (optional)
        beginNode();
        auto node = ts_tree_cursor_current_node(_cursor);
        if (std::strcmp(ts_node_type(node), "async") == 0) {

            addTerminalNode(node, "async");
            ts_tree_cursor_goto_next_sibling(_cursor);
        }
    }

    // 'for'
    walkAST();

    // left
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // 'in'
    ts_tree_cursor_goto_next_sibling(_cursor);

    // right
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // ':'
    ts_tree_cursor_goto_next_sibling(_cursor);

    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkChildren();

    // alternative
    if (ts_tree_cursor_goto_next_sibling(_cursor))
        walkChildren();
    endNode();
}



void PyGraph::Builder::while_match_statement()
{
    // condition & body
    beginNode();
    do {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "body") == 0) {

            walkChildren();
            break;
        }
        walkAST();
    }
    while (ts_tree_cursor_goto_next_sibling(_cursor));

    // alternative
    if (ts_tree_cursor_goto_next_sibling(_cursor))
        walkChildren();
    endNode();
}



void PyGraph::Builder::if_statement()
{
    // 'if'
    beginNode();
    walkAST();

    // condition
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // ':'
    ts_tree_cursor_goto_next_sibling(_cursor);

    // consequence
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkChildren();

    // repeat alternative
    if (ts_tree_cursor_goto_next_sibling(_cursor))
        walkElif();
    endNode();
}



void PyGraph::Builder::try_statement()
{
    // 'try'
    beginNode();
    walkAST();

    // ':'
    ts_tree_cursor_goto_next_sibling(_cursor);

    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkChildren();

    // repeat exception
    while (ts_tree_cursor_goto_next_sibling(_cursor))
        walkChildren();
    endNode();
}



void PyGraph::Builder::with_statement()
{
    // with_clause
    beginNode();
    do {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "body") == 0)
            break;
        walkAST();
    }
    while (ts_tree_cursor_goto_next_sibling(_cursor));
    endNode();

    // body
    walkAST();
}



void  PyGraph::Builder::if_clause()
{
    // 'if'
    addTerminalNode(ts_tree_cursor_current_node(_cursor), "if-clause");

    // expression
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();
}



void PyGraph::Builder::else_clause()
{
    // 'else' | 'finally'
    // ':'
    ts_tree_cursor_goto_next_sibling(_cursor);
    
    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();
}



void PyGraph::Builder::except_clause()
{
    // 'except' | 'except*'
    beginNode();
    walkAST();

    // condition & body
    while (ts_tree_cursor_goto_next_sibling(_cursor)) {

        auto node = ts_tree_cursor_current_node(_cursor);
        auto type = ts_node_type(node);
        
        if (type && std::strcmp(type, "block") == 0)
            walkChildren();
        else
            walkAST();
    }
    endNode();
}



void PyGraph::Builder::case_clause()
{
    // 'case'
    beginNode();
    walkAST();

    // condition & consequence
    while (ts_tree_cursor_goto_next_sibling(_cursor)) {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "consequence") == 0)
            walkChildren();
        else
            walkAST();
    }
    endNode();
}



void PyGraph::Builder::conditional_expression()
{
    // expression
    walkAST();

    // 'if'
    ts_tree_cursor_goto_next_sibling(_cursor);
    addTerminalNode(ts_tree_cursor_current_node(_cursor), "ternary-if");

    // expression
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // 'else'
    ts_tree_cursor_goto_next_sibling(_cursor);
    addTerminalNode(ts_tree_cursor_current_node(_cursor), "ternary-else");

    // expression
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();
}



void PyGraph::Builder::for_in_clause()
{
    {// 'async' (optional)
        auto node = ts_tree_cursor_current_node(_cursor);
        if (std::strcmp(ts_node_type(node), "async") == 0) {

            addTerminalNode(node, "async");
            ts_tree_cursor_goto_next_sibling(_cursor);
        }
    }

    // 'for'
    addTerminalNode(ts_tree_cursor_current_node(_cursor), "for-clause");
    
    // left
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // 'in'
    ts_tree_cursor_goto_next_sibling(_cursor);

    // right
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();
}
}
