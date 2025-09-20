#include "waiting.h"

namespace sig_time
{

bool check_LeapYear(int year)
{
    if(year % 400 == 0) return 1;
    else if(year % 100) return 0;
    return (year % 4 == 0);
}

time_t get_timestamp()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

time_t get_timestamp(int year, int mon, int date, int hour, int minu, int sec)
{
    std::tm time_struct = {};
    time_struct.tm_year = year - 1990;
    time_struct.tm_mon = mon - 1;
    time_struct.tm_mday = date;
    time_struct.tm_hour = hour;
    time_struct.tm_min = minu;
    time_struct.tm_sec = sec;
    time_struct.tm_isdst = -1;

    std::time_t time_stamp = std::mktime(&time_struct);

    auto time_point = std::chrono::system_clock::from_time_t(time_stamp);
    auto duration = time_point.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);

    return seconds.count();
}


int waiting_duration(time_t duration)
{
    if(duration < 0) return 0;

    auto start = std::chrono::steady_clock::now();
    
    std::chrono::seconds wait_duration(duration);

    auto target = start + wait_duration;

    std::this_thread::sleep_until(target);

    return 1;
}

int waiting_to(time_t target)
{
    if(get_timestamp() > target)
    {
        return 0;
    }

    std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(target));

    return 1;
}

}