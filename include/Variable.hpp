#pragma once
#include <windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
const int N = 1000;
#define MAX_LOADSTRING 100

struct DoKeyDown
{
    int Down_Key[26], TickDownNum;
    int Downx, Downy;
};

extern HINSTANCE hInst;
extern char szTitle[MAX_LOADSTRING];
extern char szWindowClass[MAX_LOADSTRING];
extern HWND hWnd;
extern POINT MousePos;
extern bool CNC;
extern bool CWT;
extern bool CWR;
extern bool DML;
extern bool VPR;
extern bool SKV, DKV;
extern bool IsKeyDown[256];
extern HWND MouseHwnd;
extern char title[1024];
extern INT_PTR ColorTime;
extern COLORREF Colorful;
extern RECT MouseWindowRect;
extern RECT NowRect;
extern POINT FastMouse[256];
extern INT_PTR FMP, VKN;
extern LONG width, height;
extern LONG Bottom, Top, Left, Right, b1;
