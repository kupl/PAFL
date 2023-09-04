#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <filesystem>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>

#include "type.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;



namespace PAFL
{
using PathInfo = std::tuple<std::filesystem::path, std::filesystem::path, std::string>;

void Parse(Document& doc, const std::filesystem::path& location);
bool IsTestPassed(const std::filesystem::path& extention_test_location, const std::string& num);

std::vector<std::pair<std::string, std::list<line_t>>> ReadBugList(const std::filesystem::path& path);
}






namespace PAFL
{
void Parse(Document& doc, const std::filesystem::path& path)
{
    std::ifstream ifs(path);
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



bool IsTestPassed(const std::filesystem::path& extention_test_location, const std::string& num)
{
    std::ifstream ifs(extention_test_location / (num + ".test"));
    std::string buf;
    ifs >> buf;
    return buf == "passed";
}



std::vector<std::pair<std::string, std::list<line_t>>> ReadBugList(const std::filesystem::path& path)
{
    Document doc;
    Parse(doc, path);
    std::vector<std::pair<std::string, std::list<line_t>>> ret;

    const auto& taxes = doc["taxes"].GetArray();
    ret.reserve(taxes.Size());

    for (SizeType i = 0; i != taxes.Size(); i++) {
        
        const auto& tax = taxes[i].GetObject();
        const auto& lines = tax["lines"].GetArray();

        ret.emplace_back(tax["file"].GetString(), std::list<line_t>());
        for (SizeType j = 0; j != lines.Size(); j++)
            ret[i].second.push_back(lines[j].GetUint());
    }

    return ret;
}
}
#endif
