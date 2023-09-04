#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

namespace PAFL
{
class BaseLogger
{
public:
    virtual ~BaseLogger() = default;
    virtual void log(const void*) = 0;

protected:
    void init(const std::string& log_path, const std::string& name)
        { _path = log_path + '/' + name; _counter = 0; }

    std::string _path;
    size_t _counter;
};
}

#endif
