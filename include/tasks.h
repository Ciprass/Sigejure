#ifndef TASKS_H
#define TASKS_H

#include "waiting.h"

#include <string>
#include <time.h>

class Task
{
    int hour, minute, sec;
    int lst;

    std::wstring path;
    std::wstring arguments;
public:
    Task(std::wstring pth): path(pth), arguments(L"") {}
    Task(std::wstring pth, std::wstring args): path(pth), arguments(args) {}

    int set_hms(int h, int m, int s);
    int set_lst(int t);

    std::wstring getPath() const;
    std::wstring getArgs() const;

    time_t get_next();
    time_t get_next_end();
};

#endif