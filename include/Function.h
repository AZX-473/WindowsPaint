#pragma once
#include "framework.h"
#include "Project1.h"
#include "Variable.h"

void NFT(LONG *Old, LONG ToNew, double Tnum);
void DrawTextAZX(HDC hdc, COLORREF TextColor, COLORREF BackGroundColor, LPCSTR text, INT_PTR x, INT_PTR y);
void DrawRect(HDC hdc, RECT Rect);
void RectGoToNew(RECT NewRect);
void DrawMouseLine(HDC hdc);
void FastMousePos(HDC hdc, POINT point);
void SimulateLeftClick(int x, int y, bool leftorright);
