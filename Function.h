/*
    这段代码旨在创建函数用以方便使用
*/

#pragma once
#include "framework.h"
#include "Project1.h"
#include <graphics.h>
#include "Variable.h"

void NFT(LONG* Old, LONG ToNew, double Tnum) {//使一个变量平滑过渡到另一个
    *Old = *Old + (LONG)((ToNew - *Old) * Tnum);
    return;
}

void DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCWSTR text, INT_PTR x, INT_PTR y) {//更方便的绘画文字
    //for (int i = 0; text[i]; i++) TextLong++;
    COLORREF LastTextColor = SetTextColor(hdc, TextColor);
    COLORREF LastBackGroundColor = SetBkColor(hdc, BackGroundColor);
    // TextOutW 需要 int 长度参数，显式转换以消除 C4244 警告
    TextOutW(hdc, (int)x, (int)y, text, wcslen(text));
    SetTextColor(hdc, LastTextColor);
    SetBkColor(hdc, LastBackGroundColor);
}

void DrawRect(HDC hdc, RECT Rect) {//画一个彩色边框
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful); // 彩色边框
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 透明填充
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
void RectGoToNew(RECT NewRect) {//更新窗口边框
    NFT(&NowRect.bottom, NewRect.bottom, (double)0.5);
    NFT(&NowRect.top, NewRect.top, (double)0.5);
    NFT(&NowRect.left, NewRect.left, (double)0.5);
    NFT(&NowRect.right, NewRect.right, (double)0.5);
    return;
}
void DrawMouseLine(HDC hdc) {//绘制定位鼠标线
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful); // 彩色边框
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 透明填充
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

    MoveToEx(hdc, 0, Left, NULL);
    LineTo(hdc, MousePos.x - 10, MousePos.y - b1);
    MoveToEx(hdc, MousePos.x + 10, MousePos.y + b1, NULL);
    LineTo(hdc, width, Right);

    MoveToEx(hdc, Top, 0, NULL);
    LineTo(hdc, MousePos.x + b1, MousePos.y - 10);
    MoveToEx(hdc, MousePos.x - b1, MousePos.y + 10, NULL);
    LineTo(hdc, Bottom, height);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    return;
}
void FastMousePos(HDC hdc, POINT point) {//禁止鼠标点击
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

void SimulateLeftClick(int x, int y, bool leftorright) {//false left/true right模拟鼠标点击
    // 设置鼠标位置
    SetCursorPos(x, y);
    if (!leftorright) {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
}
/*测试内容
void AddKeyThing() {
    bool tmp = true;
    for (int i = 1; i <= 255; i++) {
        if (KEY_DOWN(i) && i != VK_MENU) {
            VKN += tmp;
            DoKeyThing[VKN].Down_Key[DoKeyThing[VKN].TickDownNum++] = i;
            DoKeyThing[VKN].Downx = MousePos.x;
            DoKeyThing[VKN].Downy = MousePos.y;
            tmp = false;
        }
    }
}

void DoKeyThings() {
    for (int i = 0; i < VKN; i++) {
        for (int j = 0; j < DoKeyThing[i].TickDownNum; j++) {
            int Thing = DoKeyThing[i].Down_Key[j];
            SetCursorPos(DoKeyThing[i].Downx, DoKeyThing[i].Downy);
            //if (Thing == MOUSEEVENTF_LEFTDOWN || Thing == MOUSEEVENTF_LEFTUP || Thing == MOUSEEVENTF_RIGHTDOWN || Thing == MOUSEEVENTF_RIGHTUP) {
            //    mouse_event(Thing, 0, 0, 0, 0);
            //}
            //else 
                keybd_event(Thing, 0, 0, 0);
        }
    }
}*/
