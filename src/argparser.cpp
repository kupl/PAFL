#include "argparser.h"

ArgParser::ArgParser(int argc, char *argv[]) :
    _directory_path(std::filesystem::path(argv[0]).parent_path())
{
    std::list<std::string> prev;

    for (int i = 1; i != argc; i++) {

        std::string arg(argv[i]);

        // Add to _next
        for (auto& opt : prev)
            _next.emplace(opt, arg);

        // -<short op 1><short op 2> ...
        if (arg.starts_with('-') && !arg.starts_with("--")) {

            prev.clear();
            arg.erase(arg.begin());
            for (auto opt : arg) {

                prev.push_back(std::string{'-'} + std::string{opt});
                _set.insert(std::string{'-'} + std::string{opt});
            }
        }
        else {

            prev = std::list<std::string>{arg};
            _set.insert(arg);
        }
    }
}



std::string ArgParser::operator[](std::initializer_list<std::string> keys) const
{
    for (auto& key : keys)
        if (_next.contains(key))
            return _next.at(key);
    return std::string();
}



bool ArgParser::contains(std::initializer_list<std::string> keys) const
{
    for (auto& key : keys)
        if (_set.contains(key))
            return true;
    return false;
}
