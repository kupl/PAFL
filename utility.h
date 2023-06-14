#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <filesystem>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;



namespace PAFL
{
using PathInfo = std::tuple<std::filesystem::path, std::filesystem::path, std::string>;

void Parse(Document& doc, const std::filesystem::path& json_path);
bool IsTestPassed(const std::filesystem::path& extention_test_path, const std::string& num);
}



namespace PAFL
{
void Parse(Document& doc, const std::filesystem::path& json_path)
{
    std::ifstream ifs(json_path / "summary.json");
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();

    char* buf = (char*)std::calloc(size, sizeof(char));
    if (!buf)
        throw std::range_error("malloc failed");

    ifs.seekg(0);
    ifs.read(buf, size);
    ifs.close();

    doc.Parse(buf);
    std::free(buf);
}

bool IsTestPassed(const std::filesystem::path& extention_test_path, const std::string& num)
{
    std::ifstream ifs(extention_test_path / (num + ".test"));
    std::string buf;
    ifs >> buf;
    return buf == "passed";
}
}
#endif
