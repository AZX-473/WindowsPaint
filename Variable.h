/*
    这段代码旨在创建全局变量以方便使用
*/

#pragma once
#include <windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
const int N = 1e6 + 10;
#define MAX_LOADSTRING 100
// 全局变量:
struct DoKeyDown {
    int Down_Key[26], TickDownNum;
    int Downx, Downy;
}DoKeyThing[N];//按键录制
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND  hWnd;                                     // HWND
POINT MousePos;                                 // 鼠标位置
bool  CNC = false;                                // 不能点
bool  CWT = true;                                 // 窗口名显示
bool  CWR = true;                               // 鼠标窗口边框
bool  DML = true;                               // 定位鼠标线
bool  VPR = false;                              // 录制模式
bool  SKV = false, DKV = false;                 // 录制键盘模式
bool  IsKeyDown[256];                           // 防止重复判定
HWND  MouseHwnd;                                // 鼠标所在窗口的HWND
wchar_t  title[1024];                           // 所在窗口的标题
INT_PTR ColorTime;                              // 时间
COLORREF Colorful;
RECT  MouseWindowRect;                          // 鼠标窗口边框
RECT NowRect;                                   // 显示边框
POINT FastMouse[256]; INT_PTR FMP, VKN;         // 连点器和键盘录制
LONG width = 1280, height = 720;
LONG Bottom, Top, Left, Right, b1;              // 这里是一些临时的变量