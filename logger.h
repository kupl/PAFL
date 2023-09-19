#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <filesystem>

namespace PAFL
{
class BaseLogger
{
public:
    virtual ~BaseLogger() = default;
    virtual void log(const void*, size_t) const = 0;
};
}

#endif
