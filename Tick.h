/*
    这段代码旨在处理每一帧的数据
*/
#pragma once
void Tick() {
    InvalidateRect(hWnd, NULL, TRUE); // 使整个窗口无效,从而触发绘画

    GetCursorPos(&MousePos);
    ColorTime += 3;
    ColorTime %= 360;
    Colorful = HSLtoRGB(ColorTime, 1, 0.5f);
    MouseHwnd = WindowFromPoint(MousePos);
    GetWindowTextW(MouseHwnd, title, 512);
    GetWindowRect(MouseHwnd, &MouseWindowRect);//获取功能相关数据

    if (!IsKeyDown[VK_MENU] && !IsKeyDown[VK_F2] && KEY_DOWN(VK_MENU) && KEY_DOWN(VK_F2)) {//Alt+F2取消/重启
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

    if (!IsKeyDown[VK_MENU] && !IsKeyDown[0x50] && KEY_DOWN(VK_MENU) && KEY_DOWN(0x50)) {//Alt+P取消/重启
        IsKeyDown[VK_MENU] = IsKeyDown[0x50] = true;
        VPR = (bool)((VPR + 1) % 2);
    }
    else if (IsKeyDown[VK_MENU] && IsKeyDown[0x50] && !KEY_DOWN(VK_MENU) && !KEY_DOWN(0x50)) {
        IsKeyDown[VK_MENU] = IsKeyDown[0x50] = false;//防止多次判断
    }

    if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_6)) FMP = 0;//Alt+]清除

    if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_COMMA)) {
        for (int i = 0; i < FMP; i++) {
            SimulateLeftClick(FastMouse[i].x, FastMouse[i].y, false);//Alt+<左键 连点
        }
    }

    if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_OEM_PERIOD)) {
        for (int i = 0; i < FMP; i++) {
            SimulateLeftClick(FastMouse[i].x, FastMouse[i].y, true);//Alt+>右键 连点右键
        }
    }

    if (KEY_DOWN(VK_LBUTTON)) {
        NFT(&Bottom, (LONG)0, (double)0.3);
        NFT(&Top, width, (double)0.3);
        NFT(&Left, (LONG)0, (double)0.3);
        NFT(&Right, height, (double)0.3);
        NFT(&b1, 10, (double)0.2);
    }
    else if (KEY_DOWN(VK_RBUTTON)) {
        NFT(&Bottom, width, (double)0.3);
        NFT(&Top, (LONG)0, (double)0.3);
        NFT(&Left, height, (double)0.3);
        NFT(&Right, (LONG)0, (double)0.3);
        NFT(&b1, -10, (double)0.2);
    }
    else {
        NFT(&Bottom, MousePos.x, (double)0.5);
        NFT(&Top, MousePos.x, (double)0.5);
        NFT(&Left, MousePos.y, (double)0.5);
        NFT(&Right, MousePos.y, (double)0.5);
        NFT(&b1, 0, (double)0.5);
    }

    if (KEY_DOWN(VK_MENU) && KEY_DOWN(VK_ESCAPE)) {
        DestroyWindow(hWnd);
        return;
    }
}