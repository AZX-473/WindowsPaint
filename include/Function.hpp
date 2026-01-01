#pragma once
#include "framework.hpp"
#include "Project1.hpp"
#include "Variable.hpp"

void NFT(LONG *Old, LONG ToNew, double Tnum);
void DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCSTR text, INT_PTR x, INT_PTR y);
void DrawRect(HDC hdc, RECT Rect);
void RectGoToNew(RECT NewRect);
void DrawMouseLine(HDC hdc);
void FastMousePos(HDC hdc, POINT point);
void SimulateLeftClick(int x, int y, bool leftorright);
