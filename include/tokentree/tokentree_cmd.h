#ifndef __TOKENTREE_CMD_H__
#define __TOKENTREE_CMD_H__

#include <string>
#include <stdexcept>
#include <array>
#ifdef _WIN32
#else
    #include <cstdio>
#endif


namespace PAFL
{
namespace Command
{
    constexpr auto TEMPORARY_CPP = "___temp.cpp";
    constexpr auto TEMPORARY_JSON = "___temp.json";
    constexpr auto DUMP_COMMAND = "clang++ -fsyntax-only -Xclang -dump-tokens ___temp.cpp 2>&1";

#ifdef _WIN32
    constexpr auto CLEAR = "cls";
#else
    constexpr auto CLEAR = "clear";
    std::string exec(const char* cmd);
#endif
}
}
#endif
