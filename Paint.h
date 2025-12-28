/*
    这段代码旨在绘画每一帧的图像
*/
#pragma once
void Paint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);

    // 2. 创建兼容缓冲区
    HDC mdc = CreateCompatibleDC(hdc);
    if (!mdc) return;

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
    if (VPR) {
        hBrush = CreateSolidBrush(RGB(0, 177, 64));
        SelectObject(mdc, hBrush);

        Rectangle(mdc, 0, 0, width, height);

        hBrush = CreateSolidBrush(Colorful);
    }
    if (CWR) DrawRect(mdc, NowRect);
    if (CNC) Rectangle(mdc, MousePos.x - 5, MousePos.y - 5, MousePos.x + 5, MousePos.y + 5);
    if (CWT) DrawTextAZX(mdc, Colorful, RGB(0, 0, 0), title, MousePos.x + 5, MousePos.y + 5);
    if (DML) DrawMouseLine(mdc);
    if (SKV) DrawTextAZX(mdc, Colorful, RGB(0, 0, 0), L"正在录制键盘", MousePos.x + 5, MousePos.y - 5);
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