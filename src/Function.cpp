#include "Function.hpp"

void NFT(LONG *Old, LONG ToNew, double Tnum)
{
    *Old = *Old + (LONG)((ToNew - *Old) * Tnum);
    return;
}

void DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCSTR text, INT_PTR x, INT_PTR y)
{
    COLORREF LastTextColor = SetTextColor(hdc, TextColor);
    COLORREF LastBackGroundColor = SetBkColor(hdc, BackGroundColor);
    TextOutA(hdc, (int)x, (int)y, text, strlen(text));
    SetTextColor(hdc, LastTextColor);
    SetBkColor(hdc, LastBackGroundColor);
}

void DrawRect(HDC hdc, RECT Rect)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
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

void RectGoToNew(RECT NewRect)
{
    NFT(&NowRect.bottom, NewRect.bottom, (double)0.5);
    NFT(&NowRect.top, NewRect.top, (double)0.5);
    NFT(&NowRect.left, NewRect.left, (double)0.5);
    NFT(&NowRect.right, NewRect.right, (double)0.5);
    return;
}

void DrawMouseLine(HDC hdc)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
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

void FastMousePos(HDC hdc, POINT point)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, Colorful);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
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

void SimulateLeftClick(int x, int y, bool leftorright)
{
    SetCursorPos(x, y);
    if (!leftorright)
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else
    {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
}
