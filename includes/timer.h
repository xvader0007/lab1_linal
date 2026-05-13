#ifndef LAB1_LINAL_TIMER_H
#define LAB1_LINAL_TIMER_H

#include <chrono>

class Timer
{
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start();
    double elapsed_ms() const;
};

#endif //LAB1_LINAL_TIMER_H