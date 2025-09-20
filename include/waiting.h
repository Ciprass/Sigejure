#ifndef WAITING_H
#define WAITING_H

#include <vector>
#include <chrono>
#include <thread>

namespace sig_time
{
    const int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool check_LeapYear(int year);

    time_t get_timestamp();
    time_t get_timestamp(int, int, int, int, int, int);

    int waiting_duration(time_t);
    int waiting_to(time_t);

}


#endif