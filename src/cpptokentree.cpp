#include "tokentree/cpptokentree.h"

namespace PAFL
{
CppTokenTree::CppTokenTree(const fs::path& src_file, const fs::path& bin, index_t index, const std::list<std::string>& macro, size_t macro_size) :
    TokenTree()
{
    std::cout << src_file.string() << std::endl;
    // Tokenize
    CppPda pda;
    { // From token list to token tree
        line_t lineno = 0;
        Token* token_buffer = nullptr;
        CppPda::Matcher::Type ttype_buffer = CppPda::Matcher::Type::ROOT;

        auto raw_stream = _getRawStream(src_file, bin / (std::to_string(index) + ".cpp"), macro, macro_size);
        for (auto& item : raw_stream) {
            
            Token* token = &item.token;
            if (CppPda::Matcher::isCoverable(item.ttype)) {

                if (lineno != token->loc) {

                    _stream.emplace_back();
                    lineno = token->loc;
                }
                token = &_stream.rbegin()->emplace_back(token->name, token->loc);
            }
            pda.trans(CppPda::Matcher::Args{token_buffer, ttype_buffer, item.ttype});
            token_buffer = token;
            ttype_buffer = item.ttype;
        }
        pda.trans(CppPda::Matcher::Args{token_buffer, ttype_buffer, CppPda::Matcher::Type::ROOT});
    }
    
    // Check pda termination
    setIndexer();
    _good = pda.isTerminated();
}



std::string CppTokenTree::collectMacro(const fs::path& src_file, const fs::path& bin, const std::string& temp_file)
{
    fs::path temp_src(bin / temp_file);
    {// Erase header info
        auto buffer(_eraseInclude(src_file));
        std::ofstream(temp_src).write(buffer.c_str(), buffer.size());
    }

    // clang collect macro
    std::string buffer(exec((std::string("clang-17 -E -fdirectives-only ") + temp_src.c_str() + " 2>&1").c_str()));
    std::remove(temp_src.c_str());
    return readMacroFromBuffer(buffer);
}



std::string CppTokenTree::readMacroFromBuffer(const std::string& buffer)
{
    // Split buffer
    std::string ret;
    size_t last = 0;
    size_t pos = 0;
    while ((pos = buffer.find('\n', last)) != std::string::npos) {

        auto substr(buffer.substr(last, pos - last + 1));
        if (substr.starts_with("#define"))
            ret.append(substr);
        last = pos + 1;
    }
    auto substr(buffer.substr(last));
    if (substr.starts_with("#define"))
        ret.append(substr);
    return ret;
}



std::string CppTokenTree::_eraseInclude(const fs::path& path)
{
    /*
        state : 0-11
        (0) -> #(1)
        (1) -> ' '(1) | \t(1) | i(2)
        (2) -> n(3)   , c(4)  , l(5) , u(6) , d(7) , e(8)
        (8) -> ' '(8) | \t(8) | <(9) | "(11)
        (9) -> _(9)   | >(11)
        (10) -> _(10) | "(11)
        else -> (0)
    */
    static constexpr char include_table[11][128] = {
    // # include
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // <header> | "header"
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0 }
    };

    // match -> # include <> | # include ""
    std::string buffer(StringEditor::read(path.c_str()));
    auto data = buffer.data();
    int state = 0;
    int start = 0;
    bool was_backslash = false;
    
    for (int i = 0; i != buffer.size(); ++i) {

        if (was_backslash)
            was_backslash = false;

        else if (!was_backslash && data[i] == '\\')
            was_backslash = true;

        else {

            // If #include not in str, update state
            state = include_table[state][data[i]];
            if (state == 0)
                start = i;
            else if (state == 11) {

                state = 0;
                // Preserve line location
                for(char* ptr = data + start; ptr != data + i + 1; ptr++)
                    if (*ptr != '\n')
                        *ptr = ' ';
            }
        }
    }

    return buffer;
}



std::list<CppTokenTree::Item> CppTokenTree::_getRawStream(const fs::path& path, const fs::path& temp_src, const std::list<std::string>& macro, size_t macro_size) const
{
    std::string temp_header(temp_src.string() + ".hpp");
    {// Replace header info
        auto buffer(_eraseInclude(path));
        std::ofstream ofs(temp_src);
        ofs << ("#include \"" + temp_header + "\"\n");
        ofs.write(buffer.c_str(), buffer.size());
    }

    {// Write macro header
        auto buffer(exec((std::string("clang-17 -w -E -fdirectives-only ") + temp_src.c_str() + " 2>&1").c_str()));
        auto this_macro(readMacroFromBuffer(buffer));

        std::string fo_buf;
        fo_buf.reserve(macro_size);
        for (auto& line : macro)
            if (line != this_macro)
                fo_buf.append(line);
        std::ofstream(temp_header).write(fo_buf.c_str(), fo_buf.size());
    }

    // clang dump-tokens
    std::string buffer(exec((std::string("clang-17 -w -fsyntax-only -Xclang -dump-tokens ") + temp_src.c_str() + " 2>&1").c_str()));
    //std::remove(temp_src.c_str());
    //std::remove(temp_header.c_str());

    // Tokenize
    CppPda::Matcher matcher;
    std::list<Item> stream;
    for (const char* pos = buffer.c_str(); ; ++pos) {

        // Read buf
        const char* start = pos;
        for (; *pos != ' '; ++pos) {}
        CppPda::Matcher::Type ttype = matcher.match(std::string(start, pos - start));

        // If End Of File, break
        if (ttype == CppPda::Matcher::Type::eof)
            break;
        
        // Set token name
        for (; *pos != '\''; ++pos) {}
        start = ++pos;
        for (; *pos != '\''; ++pos) {}
        std::string name(start, pos - start);

        // Push token
        for (; *pos != ':'; ++pos) {}
        stream.emplace_back(ttype, name, static_cast<line_t>(std::atoll(pos + 1) - 1));

        // Move to next line
        for (; *pos != '\n'; ++pos) {}
    }
    return stream;
}



std::string CppTokenTree::exec(const char* cmd)
{
    std::array<char, 4 * 1024 * 1024> buffer;
    std::string ret;
    FILE* pipe = popen(cmd, "r");
    while (fgets(buffer.data(), 4 * 1024 * 1024, pipe) != NULL)
        ret.append(buffer.data());
    pclose(pipe);
    return ret;
}
}