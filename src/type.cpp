#include "type.h"

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
