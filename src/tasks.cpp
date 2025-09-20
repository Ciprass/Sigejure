#include "tasks.h"

int Task::set_hms(int h, int m, int s)
{
    hour = h;
    minute = m;
    sec = s;
    return 1;
}

int Task::set_lst(int t)
{
    lst = t;
    return lst;
}

std::wstring Task::getPath() const
{
    return path;
}

std::wstring Task::getArgs() const
{
    return arguments;
}

time_t Task::get_next()
{
    time_t now = std::time(nullptr);
    tm* local = std::localtime(&now);

    time_t ret = sig_time::get_timestamp(local->tm_year+1990, local->tm_mon+1, local->tm_mday, hour, minute, sec);

    while(ret < now)
    {
        ret += (time_t)24 * 60 * 60;
    }

    return ret;
}

time_t Task::get_next_end()
{
    time_t now = std::time(nullptr);
    tm* local = std::localtime(&now);

    time_t ret = sig_time::get_timestamp(local->tm_year+1990, local->tm_mon+1, local->tm_mday, hour, minute, sec) + lst;
    // printf("%d\n", lst);

    while(ret < now)
    {
        ret += (time_t)24 * 60 * 60;
    }

    return ret;
}