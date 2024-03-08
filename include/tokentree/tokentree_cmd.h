#ifndef __TOKENTREE_CMD_H__
#define __TOKENTREE_CMD_H__

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
    std::string dumpTokens(const char* file);

#ifdef _WIN32
#else
    std::string exec(const char* cmd);
#endif
}
}
#endif
