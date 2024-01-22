#ifndef __ARGPARSER_H__
#define __ARGPARSER_H__

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <filesystem>


class ArgParser
{
public:
    ArgParser(int argc, char *argv[]);
    std::string operator[](const std::string& key) const                    { return _next.contains(key) ? _next.at(key) : std::string(); }
    std::string operator[](std::initializer_list<std::string> keys) const;
    bool contains(const std::string& key) const                             { return _set.contains(key); }
    bool contains(std::initializer_list<std::string> keys) const;
    const std::filesystem::path& getDirectoryPath() const                   { return _directory_path; }

private:
    std::unordered_map<std::string, std::string> _next;
    std::unordered_set<std::string> _set;
    const std::filesystem::path _directory_path;
};
#endif
