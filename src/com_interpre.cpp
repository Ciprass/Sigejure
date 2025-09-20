#include "com_interpre.h"

char* wcharToAscii(const wchar_t* wideStr, char replaceChar = '?')
{
    if (wideStr == nullptr) return nullptr;
    
    size_t len = wcslen(wideStr);
    char* narrowStr = new char[len + 1];
    
    for (size_t i = 0; i < len; ++i)
    {
        wchar_t wc = wideStr[i];
        if (wc >= 0 && wc <= 127)
        {
            narrowStr[i] = static_cast<char>(wc);
        }
        else
        {
            narrowStr[i] = replaceChar;
        }
    }
    
    // narrowStr[len] = '\0';
    return narrowStr;
}