#include "com_interpre.h"
#include "tasks.h"
#include "run_task.h"
#include "waiting.h"
#include "adjuster.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <shellapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    puts("A message.");
    // MessageBox(NULL, "Hello, GUI World!", "MyGuiApp", MB_OK);

    // ----- Analyse arguments -----
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if(argv == nullptr)
    {
        MessageBoxW(NULL, L"Failed to parse command line!", L"Sigejure", MB_ICONERROR);
        return 1;
    }

    bool flag_full_screen = 0;
    int full_screen_delay = 10;

    int a, b, c, d;
    a = b = -1;
    c = d = 0;
    std::wstring cmmd = L"";

    for(int i=0;i < argc;i++)
    {
        if(std::wstring(argv[i]) == L"--fullscreen")
        {
            flag_full_screen = 1;
        }
        else if(std::wstring(argv[i]) == L"-h")
        {
            i++;
            a = _wtoi(argv[i]);
        }
        else if(std::wstring(argv[i]) == L"-m")
        {
            i++;
            b = _wtoi(argv[i]);
        }
        else if(std::wstring(argv[i]) == L"-s")
        {
            i++;
            c = _wtoi(argv[i]);
        }
        else if(std::wstring(argv[i]) == L"-l")
        {
            i++;
            d = _wtoi(argv[i]);
        }
        else if(std::wstring(argv[i]) == L"-C")
        {
            i++;
            cmmd = std::wstring(argv[i]);
        }
    }
    LocalFree(argv);

    // if(a == -1 || b == -1 || cmmd == L"")
    // {
    //     MessageBoxW(NULL, L"Error arguments in command line!", L"Sigejure", MB_ICONERROR);
    //     return 1;
    // }

    if(a == -1)
    {
        MessageBoxW(NULL, L"Error hour arguments in command line!", L"Sigejure", MB_ICONERROR);
        return 1;
    }
    else if(b == -1)
    {
        MessageBoxW(NULL, L"Error minute arguments in command line!", L"Sigejure", MB_ICONERROR);
        return 1;
    }
    else if(cmmd == L"")
    {
        MessageBoxW(NULL, L"Error command arguments in command line!", L"Sigejure", MB_ICONERROR);
        return 1;
    }
    
    // ----- Just do it! -----
    Task mycmd(cmmd);
    mycmd.set_hms(a, b, c);
    mycmd.set_lst(d);

    if(d == 0 || mycmd.get_next_end() > mycmd.get_next())
    {
        // MessageBox(NULL, "666", "MyGuiApp", MB_OK);
        sig_time::waiting_to(mycmd.get_next());
    }

    Starter test(mycmd);
    if(!test.start())
    {
        MessageBoxW(NULL, L"Failed to execute command!", L"Sigejure", MB_ICONERROR);
        return 1;
    }

    if(flag_full_screen)
    {
        // test.setWindowFullScreen(10000);
        sig_time::waiting_duration(full_screen_delay);
        test.setWindowFullScreen(10000);
    }

    if(test.WaitforExit())
    {
        // OUTPUT - TEST
        puts("A meanless output.");
    }

    return 0;
}
