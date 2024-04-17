#ifndef __CPPTOKENTREE_H__
#define __CPPTOKENTREE_H__

#include <iostream>
#include "tokentree/cpppda.h"
#include "stringeditor.h"


namespace PAFL
{
class CppTokenTree : public TokenTree
{
public:
    CppTokenTree(const fs::path& src_file, const fs::path& bin, index_t index, const std::list<std::string>& macro, size_t macro_size);
    static std::string collectMacro(const fs::path& src_file, const fs::path& bin, const std::string& temp_file);
    static std::string readMacroFromBuffer(const std::string& buffer);

private:
    struct Item
    {
        CppPda::Matcher::Type ttype; Token token;
        Item(CppPda::Matcher::Type ttype, const std::string& name, line_t loc) : ttype(ttype), token(name, loc) {} 
    };

private:
    std::list<Item> _getRawStream(const fs::path& path, const fs::path& temp_src, const std::list<std::string>& macro, size_t macro_size) const;
    static std::string _eraseInclude(const fs::path& path);
    static std::string exec(const char* cmd);
};
}
#endif
