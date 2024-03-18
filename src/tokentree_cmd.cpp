#include "tokentree/tokentree_cmd.h"

namespace PAFL
{
namespace Command
{
std::string dumpTokens(const char* file)
{
    return std::string("clang++ -fsyntax-only -dump-tokens ") + file + " 2>&1";
}



#ifdef _WIN32
#else
    std::string exec(const char* cmd)
    {
        std::array<char, 4 * 1024 * 1024> buffer;
        std::string ret;
        FILE* pipe = popen(cmd, "r");
        while (fgets(buffer.data(), 4 * 1024 * 1024, pipe) != NULL)
            ret.append(buffer.data());
        pclose(pipe);
        return ret;
    }
#endif
}
}
