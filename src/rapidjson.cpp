#include "rapidjson.h"

namespace rapidjson
{
Document parseDoc(const std::filesystem::path& path)
{
    std::FILE* fp = std::fopen(path.c_str(), "rb");
    std::fseek(fp, 0, SEEK_END);
    auto size = std::ftell(fp);
    std::rewind(fp);

    char* buf = (char*)std::calloc(size + 1, sizeof(char));
    if (!buf)
        throw std::range_error("malloc failed");
    std::fread(buf, size, 1, fp);
    std::fclose(fp);

    rapidjson::Document doc;
    doc.Parse(buf);
    std::free(buf);

    return doc;
}
}
