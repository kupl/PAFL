#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <filesystem>
#include "type.h"
#include "stopwatch.h"


namespace PAFL
{
class BaseLogger
{
public:
    BaseLogger(const fs::path& path, StopWatch<time_t>& timer) : path(path), _timer(timer) {}
    virtual ~BaseLogger() = default;
    virtual void log(const void*) const = 0;

protected:
    void beginLog() const   { _timer.stop(); }
    void endLog() const     { _timer.start(); }

protected:
    const fs::path path;

private:
    StopWatch<time_t>& _timer;
};
}

#endif
