#ifndef RUN_TASK_H
#define RUN_TASK_H

#include "tasks.h"
#include "adjuster.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <tlhelp32.h>
#include <memory>
#include <vector>

class Starter
{
    std::wstring processPath, processArgs;
    PROCESS_INFORMATION process_info;
    bool isrunning;

public:

    Starter(const std::wstring path) : processPath(path), processArgs(L""), isrunning(0)
    {
        ZeroMemory(&process_info, sizeof(process_info));
    }

    Starter(const std::wstring path, std::wstring args) : processPath(path), processArgs(args), isrunning(0)
    {
        ZeroMemory(&process_info, sizeof(process_info));
    }

    Starter(const Task T) : processPath(T.getPath()), processArgs(T.getArgs()), isrunning(0)
    {
        ZeroMemory(&process_info, sizeof(process_info));
    }

    ~Starter()
    {
        terminate();
    }

    int start();
    int terminate();
    bool is_running() const;
    DWORD getProcessID() const;
    HANDLE getProcessHandle() const;
    HWND findMainWindow() const;
    bool setWindowFullScreen(DWORD timeoutMs);
    bool WaitforExit();
};

#endif