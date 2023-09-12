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
}
#endif
