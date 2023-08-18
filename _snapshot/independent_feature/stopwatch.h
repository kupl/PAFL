#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__
#include <chrono>
#include <memory>

template <class T>
class StopWatch
{
public:
    StopWatch() : _is_running(false), _accumulation(0), _timer(std::chrono::high_resolution_clock::now()) {}

    void start()
    {
        if (_is_running)
            return;

        _is_running = true;
        _timer = std::chrono::high_resolution_clock::now();
    }
    
    typename T::rep lap()
    {
        if (_is_running) {

            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<T>(_accumulation + (now - _timer)).count();
        }
        else
            return std::chrono::duration_cast<T>(_accumulation).count();
    }

    typename T::rep stop()
    {
        if (!_is_running)
            return std::chrono::duration_cast<T>(_accumulation).count();

        _is_running = false;
        auto now = std::chrono::high_resolution_clock::now();
        _accumulation += now - _timer;
        return std::chrono::duration_cast<T>(_accumulation).count();
    }

    void reset()
    {
        _is_running = false;
        _accumulation -= _accumulation;
    }
    

private:
    bool _is_running;
    std::chrono::nanoseconds _accumulation;
    decltype(std::chrono::high_resolution_clock::now()) _timer;
};

#endif
