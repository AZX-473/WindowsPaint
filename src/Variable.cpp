#include "Variable.h"

HINSTANCE hInst;
char szTitle[MAX_LOADSTRING];
char szWindowClass[MAX_LOADSTRING];
HWND hWnd;
POINT MousePos;
bool CNC = false;
bool CWT = true;
bool CWR = true;
bool DML = true;
bool VPR = false;
bool SKV = false, DKV = false;
bool IsKeyDown[256];
HWND MouseHwnd;
char title[1024];
INT_PTR ColorTime;
COLORREF Colorful;
RECT MouseWindowRect;
RECT NowRect;
POINT FastMouse[256];
INT_PTR FMP = 0, VKN = 0;
LONG width = 1280, height = 720;
LONG Bottom = 0, Top = 0, Left = 0, Right = 0, b1 = 0;
