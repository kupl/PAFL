#ifndef __ARGPARSER_H__
#define __ARGPARSER_H__

#include <set>
#include <vector>
#include <unordered_map>
#include <filesystem>
#ifdef _WIN32
#else
    #include <unistd.h>
    #include <limits.h>
#endif


class ArgParser
{
public:
    ArgParser(int argc, const char *argv[])
    {
        // Set directoray path
        char buffer[PATH_MAX];
        readlink("/proc/self/exe", buffer, PATH_MAX);
        _executable_path = std::filesystem::path(buffer);

        // Parse arguments
        std::string prev;
        for (int i = 0; i != argc; ++i) {

            std::string arg(argv[i]);
            _argv.push_back(arg);
            _set.insert(arg);
            _next.emplace(prev, arg);
            prev = std::move(arg);
        }
    }


    const std::string& operator[](unsigned index) const
    {
        return index < _argv.size() ? _argv.at(index) : _null;
    }


    const std::string& operator[](const std::string& key) const
    {
        return _next.contains(key) ? _next.at(key) : _null;
    }


    const std::string& operator[](std::initializer_list<std::string> keys) const
    {
        for (auto& key : keys)
            if (_next.contains(key))
                return _next.at(key);
        return _null;
    }


    bool contains(const std::string& key) const
    {
        return _set.contains(key);
    }


    bool contains(std::initializer_list<std::string> keys) const
    {
        for (auto& key : keys)
            if (_set.contains(key))
                return true;
        return false;
    }


    const std::filesystem::path& getExecutablePath() const
    {
        return _executable_path;
    }


    size_t size() const
    {
        return _argv.size();
    }


private:
    std::filesystem::path _executable_path;
    std::unordered_map<std::string, std::string> _next;
    std::set<std::string> _set;
    std::vector<std::string> _argv;
    const std::string _null;
};
#endif
