#include "Paint.hpp"

void Paint()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);

    HDC mdc = CreateCompatibleDC(hdc);
    if (!mdc)
        return;

    HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);

    HGDIOBJ hOldSel = SelectObject(mdc, bmp);

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));

    HGDIOBJ hOldPen = SelectObject(mdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(mdc, hBrush);

    RectGoToNew(MouseWindowRect);
    if (VPR)
    {
        hBrush = CreateSolidBrush(RGB(0, 177, 64));
        SelectObject(mdc, hBrush);

        Rectangle(mdc, 0, 0, width, height);

        hBrush = CreateSolidBrush(RGB(0, 255, 0));
    }
    if (CWR)
        DrawRect(mdc, NowRect);
    if (CNC)
        Rectangle(mdc, MousePos.x - 5, MousePos.y - 5, MousePos.x + 5, MousePos.y + 5);
    if (CWT)
        DrawTextAZX(mdc, RGB(0, 255, 0), RGB(0, 0, 0), title, MousePos.x + 5, MousePos.y + 5);
    if (DML)
        DrawMouseLine(mdc);
    if (SKV)
        DrawTextAZX(mdc, Colorful, RGB(0, 0, 0), "正在录制键盘", MousePos.x + 5, MousePos.y - 5);
    for (int i = 0; i < FMP; i++)
        FastMousePos(mdc, FastMouse[i]);

    SelectObject(mdc, hOldBrush);
    SelectObject(mdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);

    SelectObject(mdc, hOldSel);
    DeleteObject(bmp);
    DeleteDC(mdc);

    EndPaint(hWnd, &ps);
}
