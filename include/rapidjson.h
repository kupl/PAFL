#ifndef __RAPIDJSON_H__
#define __RAPIDJSON_H__

#include <filesystem>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"


namespace rapidjson
{
Document parseDoc(const std::filesystem::path& path);
}
#endif
