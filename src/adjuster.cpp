#include "adjuster.h"

std::vector<HWND> g_foundWindows;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);
    
    if (processId == static_cast<DWORD>(lParam))
    {
        if (IsWindowVisible(hwnd) && GetWindowTextLength(hwnd) > 0)
        {
            g_foundWindows.push_back(hwnd);
        }
    }
    
    return TRUE;
}

HWND FindMainWindowByProcessId(DWORD processId)
{
    g_foundWindows.clear();
    
    EnumWindows(EnumWindowsProc, static_cast<LPARAM>(processId));
    
    if (g_foundWindows.empty())
        return nullptr;

    return g_foundWindows[0];
}

bool SetWindowFullScreen(HWND hwnd)
{
    if (!hwnd) return false;

    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

    SetWindowLongPtr(hwnd, GWL_STYLE, style & ~(WS_CAPTION | WS_THICKFRAME));
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, exStyle & ~(WS_EX_DLGMODALFRAME | 
                                                    WS_EX_WINDOWEDGE | 
                                                    WS_EX_CLIENTEDGE | 
                                                    WS_EX_STATICEDGE));
    
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

    return SetWindowPos(hwnd, HWND_TOP, 
                        workArea.left, 
                        workArea.top, 
                        workArea.right - workArea.left, 
                        workArea.bottom - workArea.top,
                        SWP_FRAMECHANGED | SWP_NOZORDER);
}

HWND WaitForWindow(DWORD processId, DWORD timeoutMs)
{
    HWND hwnd = nullptr;
    DWORD startTime = GetTickCount();
    
    while ((GetTickCount() - startTime) < timeoutMs)
    {
        hwnd = FindMainWindowByProcessId(processId);
        if (hwnd) break;
        
        Sleep(100);
    }
    
    return hwnd;
}