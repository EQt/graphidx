#pragma once
#include <chrono>


/**
   Measure the time, no matter of TimerQuiet
*/
class PerfTimer
{
public:
    void start() {
        time0 = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        time1 = std::chrono::high_resolution_clock::now();
    }

    operator double() const {
        using nsec = std::chrono::duration<double, std::nano>;
        return double(std::nano::num) / std::nano::den * 
            std::chrono::duration_cast<nsec>(time1 - time0).count();
    }

private:
    std::chrono::high_resolution_clock::time_point time0, time1;
};


/**
   As we cannot parse a pointer via pybind11, we create a wrapper class for it
*/
struct Seconds
{
    double d;
    Seconds() : d(std::nan("")) { }
};
