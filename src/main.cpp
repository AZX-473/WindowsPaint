#include "WindowsFunction.hpp"

int APIENTRY WinMain(HINSTANCE hInstance,
                     [[maybe_unused]] HINSTANCE hPrevInstance,
                     [[maybe_unused]] LPSTR lpCmdLine,
                     int nCmdShow)
{
    strcpy_s(szTitle, MAX_LOADSTRING, "WindowsPaint");
    strcpy_s(szWindowClass, MAX_LOADSTRING, "WindowsPaintClass");
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
