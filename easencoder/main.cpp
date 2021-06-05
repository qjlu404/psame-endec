#include "../Encoder/Encoder.h"
#include <windows.h>
#include <string>
#include <new>
#define ID_BUTTON1 0x6901
#define ID_BUTTON2 0x6902
#define ID_BUTTON3 0x6903
#define ID_EDIT1 0x6904
struct StateInfo
{

};
struct ProgramData
{
    bool filled, attntype;
    int attntime, initialdelay, attndelay, eomdelay, afteomdelay, windowtxtlen;
    HWND button1, button2, button3, edit1;
    HANDLE myhandle;
    DWORD mythreadid;
    std::string whole, preamble, origionator, alert, counties, time, date, timestart, csig;
};
wchar_t text[500];
ProgramData pdata;
DWORD WINAPI stoppb()
{
    return PlaySound(NULL, 0, 0);
}
DWORD WINAPI playback()
{
    return PlaySound(L"pcm.wav", NULL, SND_ASYNC);
}
void encode()
{
    /*std::string alert = "ZCZC" + pdata.origionator + pdata.alert + pdata.counties +
        pdata.time + pdata.timestart + pdata.csig;*/
    char ctext[500];
    wcstombs(ctext, text, 500);
    std::string alert = ctext;
    Encoder e;
    e.encode(alert, pdata.attntype, pdata.attntime, pdata.initialdelay, pdata.attndelay, pdata.eomdelay, pdata.afteomdelay);
}
void OnResize(HWND hwnd)
{
    SetWindowPos(hwnd, NULL, NULL, NULL, 600, 300, SWP_NOMOVE | SWP_NOOWNERZORDER);
}
void CreateControls(HWND hwnd)
{
    pdata.button1 = CreateWindowW(L"BUTTON", L"Play Alert", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120, 220, 100, 30, hwnd, (HMENU)ID_BUTTON1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    pdata.button2 = CreateWindowW(L"BUTTON", L"Encode", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 220, 100, 30, hwnd, (HMENU)ID_BUTTON2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    pdata.button3 = CreateWindowW(L"BUTTON", L"Stop Alert", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        230, 220, 100, 30, hwnd, (HMENU)ID_BUTTON3, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    pdata.edit1 = CreateWindowW(L"EDIT", L"Alert Text (Not Implemented yet)", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT,
        10, 20, 550, 20, hwnd, (HMENU)ID_EDIT1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}
StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    StateInfo* pState;
    if (pdata.filled) EnableWindow(pdata.button2, 1);
    else EnableWindow(pdata.button2, 0);
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
    }
    else
    {
        pState = GetAppState(hwnd);
    }
    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    if (uMsg == WM_PAINT)
    {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);

        return 0;
    }
    if (uMsg == WM_SIZE)
    {
        OnResize(hwnd);
    }
    if (uMsg == WM_COMMAND)
    {
        WORD wmid = LOWORD(wParam);
        WORD wmEvent = HIWORD(wParam);
        if (wmEvent == EN_CHANGE)
        {
            GetWindowText(pdata.edit1, text, 100);
            HANDLE myhandle;
            DWORD mythreadid;
            myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)encode, 0, 0, &mythreadid);
        }
        if (wmEvent == BN_CLICKED)
        {
            if (wmid == ID_BUTTON1)
            {
                pdata.myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)playback, 0, 0, &pdata.mythreadid);
            }
            if (wmid == ID_BUTTON2)
            {
                HANDLE myhandle;
                DWORD mythreadid;
                myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)encode, 0, 0, &mythreadid);
            }
            if (wmid == ID_BUTTON3)
            {
                HANDLE myhandle;
                DWORD mythreadid;
                myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)stoppb, 0, 0, &mythreadid);
            }
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"main";

    WNDCLASS wc = { };
    pdata.filled = 1;
    pdata.origionator = "WXR";
    pdata.alert = "TOR";
    pdata.counties = "081376-081353-081324-234523-232542-3279yt7hgbihjb9442352-33";
    pdata.time = "+0015";
    pdata.timestart = "1231212";
    pdata.csig = "12345678";
    pdata.attntype = 1;
    pdata.attntime = 8;
    pdata.initialdelay = 0;
    pdata.attndelay = 3;
    pdata.eomdelay = 1;
    pdata.afteomdelay = 1;

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    StateInfo* pState;
    pState = new (std::nothrow) StateInfo;

    HWND hwnd = CreateWindowEx( 0, CLASS_NAME, L"vuytr",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, NULL, NULL, hInstance, pState);
    CreateControls(hwnd);
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
