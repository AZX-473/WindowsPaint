// Project1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Project1.h"
#include <graphics.h>

#define MAX_LOADSTRING 100
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND  hWnd;                                     // HWND
POINT MousePos;                                 // 鼠标位置
bool  CNC=false;                                // 不能点
bool  CWT=true;                                 // 窗口名显示
bool  CWR = true;                               // 鼠标窗口边框
bool  DML = true;                               // 定位鼠标线
bool  IsKeyDown[256];                           // 防止重复判定
HWND  MouseHwnd;                                // 鼠标所在窗口的HWND
wchar_t  title[1024];                           // 所在窗口的标题
INT_PTR ColorTime;                              // 时间
COLORREF Colorful;
RECT  MouseWindowRect;                          // 鼠标窗口边框
RECT NowRect;                                   // 显示边框
POINT FastMouse[256]; INT_PTR FMP;              // 连点器
LONG Bottom, Top, Left, Right,width=1280,height=720;               // 单击

//  此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCWSTR text, INT_PTR x, INT_PTR y);
void                DrawRect(HDC hdc, RECT Rect);
void                RectGoToNew(RECT NewRect);
void                DrawMouseLine(HDC hdc);
void                FastMousePos(HDC hdc, POINT point);
void                SimulateLeftClick(int x, int y);
void                NFT(LONG *Old, LONG ToNew, double Tnum);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowExW(WS_EX_LAYERED, szWindowClass, szTitle, WS_POPUP,
       CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), (BYTE)0, LWA_COLORKEY);//设置黑色透明色
   // 去除标题栏
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);
   // 更新窗口位置和大小
   SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
   // 窗口置顶
   SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
   // 设置一个每30毫秒触发一次的定时器
   SetTimer(hWnd, 1, 30, NULL); 
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);

        // 2. 创建兼容缓冲区
        HDC mdc = CreateCompatibleDC(hdc);
        if (!mdc) break;

        HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);

        HGDIOBJ hOldSel = SelectObject(mdc, bmp);

        // 4. 创建绘图资源
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HBRUSH hBrush = CreateSolidBrush(Colorful);

        // 保存旧对象并选入新的
        HGDIOBJ hOldPen = SelectObject(mdc, hPen);
        HGDIOBJ hOldBrush = SelectObject(mdc, hBrush);

        // 5. 绘制图形
        RectGoToNew(MouseWindowRect);
        if (CWR) DrawRect(mdc, NowRect);
        if (CNC) Rectangle(mdc, MousePos.x - 5, MousePos.y - 5, MousePos.x + 5, MousePos.y + 5);
        if (CWT) DrawTextAZX(mdc, Colorful, RGB(0, 0, 0), title, MousePos.x + 5, MousePos.y + 5); 
        if (DML) DrawMouseLine(mdc);
        for (int i = 0; i < FMP; i++) FastMousePos(mdc, FastMouse[i]);

        // 6. 恢复旧对象并删除资源
        SelectObject(mdc, hOldBrush);
        SelectObject(mdc, hOldPen);
        DeleteObject(hBrush);      // 删除笔刷
        DeleteObject(hPen);        // 删除画笔

        // 7. 复制到屏幕
        BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);

        // 8. 清理内存DC
        SelectObject(mdc, hOldSel);  // 恢复原来的位图
        DeleteObject(bmp);           // 删除位图
        DeleteDC(mdc);               // 删除内存DC

        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE); // 使整个窗口无效

        GetCursorPos(&MousePos);
        ColorTime += 3;
        ColorTime %= 360;
        Colorful = HSLtoRGB(ColorTime, 1, 0.5f);
        MouseHwnd = WindowFromPoint(MousePos);
        GetWindowTextW(MouseHwnd, title, 512);
        GetWindowRect(MouseHwnd, &MouseWindowRect);//获取功能相关数据

        if (!IsKeyDown[VK_MENU] && !IsKeyDown[VK_F2]&&KEY_DOWN(VK_MENU)&&KEY_DOWN(VK_F2)) {//Alt+F2取消/重启
            IsKeyDown[VK_MENU] = IsKeyDown[VK_F2] = true;
            CNC = (bool)((CNC + 1) % 2);
        }
        else if (IsKeyDown[VK_MENU] && IsKeyDown[VK_F2] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(VK_F2)) {
            IsKeyDown[VK_MENU] = IsKeyDown[VK_F2] = false;//防止多次判断
        }

        if (!IsKeyDown[VK_MENU] && !IsKeyDown[0x57] && KEY_DOWN(VK_MENU) && KEY_DOWN(0x57)) {//Alt+W取消/重启
            IsKeyDown[VK_MENU] = IsKeyDown[0x57] = true;
            CWT = (bool)((CWT + 1) % 2);
        }
        else if (IsKeyDown[VK_MENU] && IsKeyDown[0x57] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(0x57)) {
            IsKeyDown[VK_MENU] = IsKeyDown[0x57] = false;//防止多次判断
        }

        if (!IsKeyDown[VK_MENU] && !IsKeyDown[0x52] && KEY_DOWN(VK_MENU) && KEY_DOWN(0x52)) {//Alt+R取消/重启
            IsKeyDown[VK_MENU] = IsKeyDown[0x52] = true;
            CWR = (bool)((CWR + 1) % 2);
        }
        else if (IsKeyDown[VK_MENU] && IsKeyDown[0x52] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(0x52)) {
            IsKeyDown[VK_MENU] = IsKeyDown[0x52] = false;//防止多次判断
        }

        if (!IsKeyDown[VK_MENU] && !IsKeyDown[0x4C] && KEY_DOWN(VK_MENU) && KEY_DOWN(0x4C)) {//Alt+L取消/重启
            IsKeyDown[VK_MENU] = IsKeyDown[0x4C] = true;
            DML = (bool)((DML + 1) % 2);
        }
        else if (IsKeyDown[VK_MENU] && IsKeyDown[0x4C] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(0x4C)) {
            IsKeyDown[VK_MENU] = IsKeyDown[0x4C] = false;//防止多次判断
        }

        if (!IsKeyDown[VK_MENU] && !IsKeyDown[VK_OEM_4] && KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_4)) {//Alt+[取消/重启
            IsKeyDown[VK_MENU] = IsKeyDown[VK_OEM_4] = true;
            FastMouse[FMP++] = MousePos;
        }
        else if (IsKeyDown[VK_MENU] && IsKeyDown[VK_OEM_4] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(VK_OEM_4)) {
            IsKeyDown[VK_MENU] = IsKeyDown[VK_OEM_4] = false;//防止多次判断
        }

        if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_6)) FMP = 0;//Alt+]清除

        if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_1))
            for (int i = 0; i < FMP; i++)
                SimulateLeftClick(FastMouse[i].x, FastMouse[i].y);//Alt+:连点
        if (KEY_DOWN(VK_LBUTTON)) {
            NFT(&Bottom, (LONG)0, (double)0.5);
            NFT(&Top, width, (double)0.5);
            NFT(&Left, (LONG)0, (double)0.5);
            NFT(&Right, height, (double)0.5);
        }
        else {
            NFT(&Bottom, MousePos.x, (double)0.5);
            NFT(&Top, MousePos.x, (double)0.5);
            NFT(&Left, MousePos.y, (double)0.5);
            NFT(&Right, MousePos.y, (double)0.5);
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
void DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCWSTR text, INT_PTR x, INT_PTR y) {
    //for (int i = 0; text[i]; i++) TextLong++;
    COLORREF LastTextColor = SetTextColor(hdc, TextColor);
    COLORREF LastBackGroundColor = SetBkColor(hdc, BackGroundColor);
    // TextOutW 需要 int 长度参数，显式转换以消除 C4244 警告
    TextOutW(hdc, (int)x, (int)y, text, wcslen(text));
    SetTextColor(hdc, LastTextColor);
    SetBkColor(hdc, LastBackGroundColor);
}

void DrawRect(HDC hdc, RECT Rect) {
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful); // 彩色边框
    HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0)); // 透明填充
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
    
    INT_PTR left = Rect.left, right = Rect.right, top = Rect.top, bottom = Rect.bottom;
    Rectangle(hdc, left, top, right, bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    return;
}
void RectGoToNew(RECT NewRect) {
    NFT(&NowRect.bottom, NewRect.bottom, (double)0.5);
    NFT(&NowRect.top, NewRect.top, (double)0.5);
    NFT(&NowRect.left, NewRect.left, (double)0.5);
    NFT(&NowRect.right, NewRect.right, (double)0.5);
    return;
}
void DrawMouseLine(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful); // 彩色边框
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 透明填充
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

    bool tmp = KEY_DOWN(VK_LBUTTON);
    MoveToEx(hdc, 0, Left, NULL);
    LineTo(hdc, MousePos.x - 10, MousePos.y-tmp*10);
    MoveToEx(hdc, MousePos.x+10, MousePos.y+ tmp * 10, NULL);
    LineTo(hdc, width, Right);

    MoveToEx(hdc, Top, 0, NULL);
    LineTo(hdc, MousePos.x+ tmp * 10, MousePos.y-10);
    MoveToEx(hdc, MousePos.x- tmp * 10, MousePos.y+10, NULL);
    LineTo(hdc, Bottom, height);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    return;
}
void FastMousePos(HDC hdc, POINT point) {
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful); // 彩色边框
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 透明填充
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

    MoveToEx(hdc, point.x - 7, point.y - 7, NULL);
    LineTo(hdc, point.x - 3, point.y - 3);
    MoveToEx(hdc, point.x + 7, point.y + 7, NULL);
    LineTo(hdc, point.x + 3, point.y + 3);
    MoveToEx(hdc, point.x + 7, point.y - 7, NULL);
    LineTo(hdc, point.x + 3, point.y - 3);
    MoveToEx(hdc, point.x - 7, point.y + 7, NULL);
    LineTo(hdc, point.x - 3, point.y + 3);
    Ellipse(hdc, point.x - 5, point.y - 5, point.x + 5, point.y + 5);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    return;
}

void SimulateLeftClick(int x, int y) {
    // 设置鼠标位置
    SetCursorPos(x, y);
    // 模拟左键按下和释放
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void NFT(LONG *Old, LONG ToNew, double Tnum) {
    *Old = *Old + (LONG)((ToNew - *Old) * Tnum);
    return;
}