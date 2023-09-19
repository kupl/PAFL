#ifndef __TYPE_H__
#define __TYPE_H__

#include <filesystem>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>

namespace fs = std::filesystem;

namespace PAFL
{
using line_t = unsigned long;
using index_t = unsigned short;
using fault_loc = std::unordered_map<std::string, std::unordered_set<line_t>>;

enum class PrgLang{ CPP, PYTHON, JAVA };

const fs::path& createDirRecursively(const fs::path& path);
}



namespace PAFL
{
const fs::path& createDirRecursively(const fs::path& path)
{
    auto parent(path.parent_path());
    if (!fs::exists(path) && parent != path.root_path()) {
        
        createDirRecursively(parent);
        fs::create_directory(path);
    }
    return path;
}
}
#endif
