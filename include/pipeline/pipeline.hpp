#include "pipeline/pipeline.h"

namespace PAFL
{
template <class T>
int Pipeline::readCereal(T& val, const std::filesystem::path& path)
{
    if (std::filesystem::exists(path)) {

        std::ifstream ifs(path, std::ios::binary);
        cereal::BinaryInputArchive archive(ifs);
        archive(val);
        return 0;
    }
    return 1;
}



template <class T>
void Pipeline::writeCereal(T& val, const std::filesystem::path& path)
{
    std::ofstream ofs(path, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    archive(val);
}
}
