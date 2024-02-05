#ifndef __TOKENTREE_CMD_H__
#define __TOKENTREE_CMD_H__


namespace PAFL
{
namespace Command
{
    constexpr auto TEMPORARY_CPP = "___temp.cpp";
    constexpr auto TEMPORARY_TXT = "___temp.txt";
    constexpr auto DUMP_COMMAND = "clang++ -fsyntax-only -Xclang -dump-tokens ___temp.cpp 2>&1 | tee ___temp.txt";

#ifdef _WIN32
    constexpr auto CLEAR = "cls";
#elif _WIN64
    constexpr auto CLEAR = "cls";
#else
    constexpr auto CLEAR = "clear";
#endif
}
}
#endif
