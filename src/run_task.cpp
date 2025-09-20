#include "run_task.h"

int Starter::start()
{
    if(isrunning)
    {
        return -1;
    }

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&process_info, sizeof(process_info));

    std::wstring fullcommand = processPath + L" " + processArgs;

    std::vector<char> commandLine(fullcommand.begin(), fullcommand.end());
    commandLine.push_back(L'\0');

    if(!CreateProcess(
        NULL,
        commandLine.data(),
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &process_info
    ))
    {
        return 0;
    }

    isrunning = 1;
    return 1;
}

int Starter::terminate()
{
    if(isrunning)
    {
        TerminateProcess(process_info.hProcess, 0);
        WaitForSingleObject(process_info.hProcess, 5000);

        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);

        isrunning = 0;
        return 1;
    }
    return 0;
}

bool Starter::is_running() const
{
    return isrunning;
}

DWORD Starter::getProcessID() const
{
    return process_info.dwProcessId;
}

HANDLE Starter::getProcessHandle() const
{
    return process_info.hProcess;
}

HWND Starter::findMainWindow() const
{
    return FindMainWindowByProcessId(getProcessID());
}

bool Starter::setWindowFullScreen(DWORD timeoutMs)
{
    HWND hwnd = WaitForWindow(getProcessID(), timeoutMs);
    if (!hwnd)
    {
        MessageBoxW(NULL, L"Error Windows!", L"Sigejure", MB_ICONERROR);
        return false;
    }
    
    if (SetWindowFullScreen(hwnd))
    {
        return true;
    }
    else
    {
        MessageBoxW(NULL, L"Error set window to full screen", L"Sigejure", MB_ICONERROR);
        return false;
    }
}

bool Starter::WaitforExit()
{
    if(isrunning)
    {
        WaitForSingleObject(process_info.hProcess, INFINITE);
        isrunning = 0;
        return 1;
    }
    return 0;
}