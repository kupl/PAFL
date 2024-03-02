#include "tokentree/tokentree_cmd.h"

namespace PAFL
{
namespace Command
{
#ifdef _WIN32
#else
    std::string exec(const char* cmd)
    {
        // Execute command
        std::FILE* fp = popen(cmd, "r");
        std::fseek(fp, 0, SEEK_END);
        auto size = std::ftell(fp);
        std::rewind(fp);
        char* buf = (char*)std::calloc(size + 1, sizeof(char));
        if (!buf)
            throw std::range_error("malloc failed");
        std::fread(buf, size, 1, fp);
        pclose(fp);

        std::string ret(buf);
        std::free(buf);
        return ret;
    }
#endif
}
}
