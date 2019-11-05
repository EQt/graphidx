#pragma once
#include <chrono>


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
        return std::chrono::duration_cast<std::chrono::duration<double>>
            (time1 - time0).count();
    }

private:
    std::chrono::high_resolution_clock::time_point time0, time1;
};
