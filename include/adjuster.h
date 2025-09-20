#ifndef ADJUSTER_H
#define ADJUSTER_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND FindMainWindowByProcessId(DWORD processId);
bool SetWindowFullScreen(HWND hwnd);
HWND WaitForWindow(DWORD processId, DWORD timeoutMs);

#endif