// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "encoder.h"
#include <iostream>
// just some fun c++ tools!

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


void SetForegroundColorRGB(int r, int g, int b)
{
    char esc[200];
    sprintf_s(esc, "\x1b[38;2;%i;%i;%im", r, g, b);
    std::cout << esc;
}


void SetBackgroundColorRGB(int r, int g, int b)
{
    char esc[200];
    sprintf_s(esc, "\x1b[48;2;%i;%i;%im", r, g, b);
    std::cout << esc;
}


void ResetColors()
{
    std::cout << "\x1b[0m";
}


void ClearConsole()
{
    std::cout << "\x1b[2J";
    std::cout << "\x1b[H";
}
