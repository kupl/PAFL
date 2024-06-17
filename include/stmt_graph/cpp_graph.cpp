#include "./cpp_graph.h"

namespace stmt_graph
{
CppGraph::CppGraph(const std::filesystem::path& source_path, const std::string& include_dir) :
    Graph()
{
    Builder(*this, _resolvePreproccessor(source_path, include_dir));
    setIndexer();
}



std::string CppGraph::collectIncludeDir(const std::filesystem::path dir)
{
    std::string ret;
    ret.reserve(StringEditor::KiB(256));
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir))
        if (std::filesystem::is_directory(entry.path()))
            ret.append(" -I" + entry.path().string());
    return ret;
}



std::string CppGraph::_resolvePreproccessor(const std::filesystem::path& source_path, const std::string& include)
{
    // Execute clang -E
    const std::string source_name(source_path.string());
    std::string command("clang -w -E " + include + " " + source_name + " 2>&1");
    std::string buffer;
    {
        char* array = (char*)std::calloc(sizeof(char), StringEditor::MiB(8));
        if (array) {
            FILE* pipe = popen(command.c_str(), "r");
            while (std::fgets(array, StringEditor::MiB(8), pipe) != NULL)
                buffer.append(array);
            pclose(pipe);
            std::free(array);
        }
    }
    std::string source;
    source.reserve(buffer.size());

    // Remove # line
    line_t line = 1;
    bool at_source = false;
    for (const char* pos = buffer.c_str(); pos[0] != '\0'; ) {

        // Read a line from buffer
        const char* begin = pos;
        pos = StringEditor::readLine(buffer.c_str(), pos);

        // case: prefix "# "
        if (begin[0] == '#') {
            
            if (begin[1] == ' ') {

                // Get line number
                const char* end = begin += 2;
                for (; end[0] != ' '; ++end);
                line_t temp_line;
                std::from_chars(begin, end, temp_line);

                // Get file name
                begin = end += 2;
                for (; end[0] != '"'; ++end);
                if (source_name == std::string(begin, end)) {
                    
                    at_source = true;
                    for (; line < temp_line; ++line)
                        source.push_back('\n');
                }
                else // source_name != std::string(begin, end)
                    at_source = false;
            }
        }
        
        // case: code
        else if (at_source) {

            ++line;
            source.append(begin, pos);
        }
    }

    return source;
}
}



namespace stmt_graph
{
CppGraph::Builder::Builder(CppGraph& graph, const std::string& source) :
    _graph(graph), _source(source), _root(graph._root.get()), _node_ptr{nullptr, nullptr, _root},
    _terminal_set{"'", "\"", "\"\"", "=", "[", "]", "(", ")", "{", "}",
                  ",", ".", "...", "->", ":", ";", ".*", "->*", "::"},
    _literal_set{"number_literal"},
    _non_terminal_set{"char_literal", "string_literal", "raw_string_literal"},
    _non_terminal_map{
        /*
            Block -> enum_specifier | strcut_specifier | union_specifier | class_specifier | function_definition
        */
        {"enum_specifier", &Builder::block}, {"strcut_specifier", &Builder::block}, {"union_specifier", &Builder::block}, {"class_specifier", &Builder::block}, {"function_definition", &Builder::block},
        /*
            Statement ->    Decl | Stmt
            Decl ->         using_declaration | alias_declaration
            Stmt ->         namespace_alias_definition | | expression_statement | return_statement
                            | break_statement | continue_statement | goto_statement
                            | co_return_statement | co_yield_statement | throw_statement
        */
        {"using_declaration", &Builder::statement}, {"alias_declaration", &Builder::statement},
        {"namespace_alias_definition", &Builder::statement}, {"expression_statement", &Builder::statement}, {"return_statement", &Builder::statement},
        {"break_statement", &Builder::statement}, {"continue_statement", &Builder::statement}, {"goto_statement", &Builder::statement},
        {"co_return_statement", &Builder::statement}, {"co_yield_statement", &Builder::statement}, {"throw_statement", &Builder::statement},
        /*
            Branch -> if_statement | switch_statement | while_statement
        */
        {"if_statement", &Builder::branch}, {"switch_statement", &Builder::branch}, {"while_statement", &Builder::branch},
        /*
            Otherwise
        */
        {"case_statement", &Builder::case_statement},
        {"do_statement", &Builder::do_statement},
        {"for_statement", &Builder::for_family},
        {"for_range_loop", &Builder::for_family},
        {"try_statement", &Builder::try_statement},
        {"catch_clause", &Builder::catch_clause},
        {"lambda_expression", &Builder::lambda_expression},
        {"declaration", &Builder::declaration},
        {"field_initializer_list", &Builder::field_initializer_list}
    }

{
    // Create a parser
    TSParser* parser = ts_parser_new();
    auto langauage = tree_sitter_cpp();
    ts_parser_set_language(parser, langauage);

    // Parse the source
    TSTree* tree = ts_parser_parse_string(parser, nullptr, source.c_str(), source.size());
    auto root = ts_tree_root_node(tree);
    auto cursor = ts_tree_cursor_new(root);
    _cursor = &cursor;
    
    // Build cpp-graph from the source
    walkAST();

    // Cleanup
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}



void CppGraph::Builder::walkAST()
{
    auto node = ts_tree_cursor_current_node(_cursor);
    const std::string type = ts_node_grammar_type(node);

    // Non-Terminal node
    if (ts_node_child_count(node)) {

        if (_non_terminal_map.contains(type)) {

            if (ts_tree_cursor_goto_first_child(_cursor)) {

                (this->*_non_terminal_map.at(type))();
                ts_tree_cursor_goto_parent(_cursor);
            }
        }
        else if (!_non_terminal_set.contains(type) && ts_tree_cursor_goto_first_child(_cursor)) {

            do walkAST();
            while (ts_tree_cursor_goto_next_sibling(_cursor));
            ts_tree_cursor_goto_parent(_cursor);
        }
    }

    // Terminal node
    else
        addTerminalNode(node, type);
}



void CppGraph::Builder::walkTrivial()
{
    auto node = ts_tree_cursor_current_node(_cursor);
    const std::string type = ts_node_grammar_type(node);

    // Non-Terminal node
    if (ts_node_child_count(node)) {

        if (ts_tree_cursor_goto_first_child(_cursor)) {

            do walkTrivial();
            while (ts_tree_cursor_goto_next_sibling(_cursor));
            ts_tree_cursor_goto_parent(_cursor);
        }
    }

    // Terminal node
    else
        addTerminalNode(node, type);
}



void CppGraph::Builder::walkChildren()
{
    auto temp = updateNodePtr();
    walkAST();
    _node_ptr = temp;
}



void CppGraph::Builder::beginNode()
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



void CppGraph::Builder::addTerminalNode(const TSNode& node, const std::string& type)
{
    if (!_node_ptr.current || _terminal_set.contains(type))
        return;

    if (type == "identifier")
        _node_ptr.current->token_vector.emplace_back(queryName(node));
    else if (type == "primitive_type")
        _node_ptr.current->token_vector.emplace_back(queryName(node));
    else if (!_literal_set.contains(type)) {

        const std::string parent_type(ts_node_grammar_type(ts_node_parent(node)));
        if (!(
                type == "*" && parent_type == "pointer_expression"
                || (type == "<"  || type == ">") && parent_type == "template_argument_list"
            ))
            _node_ptr.current->token_vector.push_back(type);
    }

    // Update line number
    auto begin = ts_node_start_point(node).row + 1;
    auto end = ts_node_end_point(node).row + 1;
    if (_node_ptr.current->begin == 0)
        _node_ptr.current->begin = _node_ptr.current->end = begin;
    if (_node_ptr.current->end < end)
        _node_ptr.current->end = end;
}



std::string CppGraph::Builder::queryName(TSNode node)
{
    auto start = ts_node_start_byte(node);
    auto end = ts_node_end_byte(node);
    return _source.substr(start, end - start);
}



CppGraph::Builder::NodePtr CppGraph::Builder::updateNodePtr()
{
    auto temp = _node_ptr;
    _node_ptr = {nullptr, nullptr, _node_ptr.current};
    return temp;
}



CppGraph::Builder::NodePtr CppGraph::Builder::updateNodePtr(NodePtr update)
{
    auto temp = _node_ptr;
    _node_ptr = update;
    return temp;
}



void CppGraph::Builder::block()
{
    beginNode();
    _node_ptr.current->coverable = false;
    do {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "body") == 0)
            walkChildren();
        else
            walkAST();
    }
    while (ts_tree_cursor_goto_next_sibling(_cursor));
    endNode();
}



void CppGraph::Builder::statement()
{
    beginNode();
    do walkAST();
    while (ts_tree_cursor_goto_next_sibling(_cursor));
    endNode();
}



void CppGraph::Builder::branch()
{
    // keyword
    beginNode();
    walkAST();

    // condition
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // consequence
    ts_tree_cursor_goto_next_sibling(_cursor);
    auto field = ts_tree_cursor_current_field_name(_cursor);
    if (!field) {// 'constexpr'
        
        walkAST();
        ts_tree_cursor_goto_next_sibling(_cursor);
    }
    walkChildren();

    // alternative
    if (ts_tree_cursor_goto_next_sibling(_cursor))
        walkChildren();
    endNode();
}



void CppGraph::Builder::case_statement()
{
    // 'case' | 'default'
    beginNode();
    walkAST();

    // value
    ts_tree_cursor_goto_next_sibling(_cursor);
    auto field = ts_tree_cursor_current_field_name(_cursor);
    if (field && std::strcmp(field, "value") == 0) {

        walkAST();
        ts_tree_cursor_goto_next_sibling(_cursor);
    }
    endNode();

    // REPEAT
    while (ts_tree_cursor_goto_next_sibling(_cursor))
        walkAST();
}



void CppGraph::Builder::do_statement()
{
    // 'do'
    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // 'while'
    ts_tree_cursor_goto_next_sibling(_cursor);
    beginNode();
    _node_ptr.current->token_vector.push_back("do-while");

    // condition
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();
    endNode();
}



void CppGraph::Builder::for_family()
{
    // 'for'
    beginNode();
    walkAST();

    // '('
    ts_tree_cursor_goto_next_sibling(_cursor);
    
    // initializer
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkTrivial();

    // body
    while (ts_tree_cursor_goto_next_sibling(_cursor)) {

        auto field = ts_tree_cursor_current_field_name(_cursor);
        if (field && std::strcmp(field, "body") == 0) {

            walkChildren();
            break;
        }
        else
            walkAST();
    }
    endNode();
}



void CppGraph::Builder::try_statement()
{
    // 'try'
    beginNode();
    walkAST();

    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkChildren();

    // catch_clause
    while (ts_tree_cursor_goto_next_sibling(_cursor))
        walkChildren();
    endNode();
}



void CppGraph::Builder::catch_clause()
{
    // 'catch'
    beginNode();
    walkAST();

    // parameters
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkAST();

    // body
    ts_tree_cursor_goto_next_sibling(_cursor);
    walkChildren();
    endNode();
}



void CppGraph::Builder::lambda_expression()
{
    auto temp = updateNodePtr({nullptr, nullptr, _root}); {
        
        // Walk repeatedly
        beginNode();
        do {

            auto field = ts_tree_cursor_current_field_name(_cursor);
            if (field && std::strcmp(field, "body") == 0)
                walkChildren();
            else
                walkAST();
        }
        while (ts_tree_cursor_goto_next_sibling(_cursor));
        endNode();
    }
    _node_ptr = temp;
}



void CppGraph::Builder::declaration()
{
    auto node = ts_tree_cursor_current_node(_cursor);
    // for (declaration; ...; ...)
    if (ts_node_grammar_type(ts_node_parent(node)) == "for_statement") {

        do walkAST();
        while (ts_tree_cursor_goto_next_sibling(_cursor));
        return;
    }

    // class CLASS {} VAR;
    auto type = ts_node_grammar_type(node);
    if (type == "enum_specifier" || type == "strcut_specifier" || type == "class_specifier") {

        walkAST();
        beginNode();
        while (ts_tree_cursor_goto_next_sibling(_cursor))
            walkAST();
    }
    
    // Otherwise
    else {

        beginNode();
        do walkAST();
        while (ts_tree_cursor_goto_next_sibling(_cursor));
    }
    endNode();
}



void CppGraph::Builder::field_initializer_list()
{
    auto temp = updateNodePtr(); {

        // Walk repeatedly
        beginNode();
        do walkAST();
        while (ts_tree_cursor_goto_next_sibling(_cursor));
        endNode();
    }
    _node_ptr = temp;
}
}
