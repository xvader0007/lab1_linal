#include "timer.h"

void Timer::start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed_ms() const
{
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start_time).count();
}