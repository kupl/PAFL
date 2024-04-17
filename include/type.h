#ifndef __TYPE_H__
#define __TYPE_H__

#include <filesystem>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>


namespace fs = std::filesystem;

namespace PAFL
{
using line_t = uint32_t;
using index_t = uint16_t;
using time_t = std::chrono::seconds;
using fault_loc = std::unordered_map<std::string, std::unordered_set<line_t>>;
using string_set = std::set<std::string>;

enum class PrgLang{ CPP, PYTHON, JAVA };

const fs::path& createDirRecursively(const fs::path& path);
}
#endif
