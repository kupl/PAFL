#include "tokentree/tokentree_cmd.h"

namespace PAFL
{
namespace Command
{
#ifdef _WIN32
#else
    std::string exec(const char* cmd)
    {
        std::array<char, 16 * 1024 * 1024> buffer;
        std::string ret;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe)
            throw std::runtime_error("popen() failed!");
        while (fgets(buffer.data(), buffer.size(), pipe.get()))
            ret.append(buffer.data());
        return ret;
    }
#endif
}
}
