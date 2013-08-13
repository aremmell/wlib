#ifndef _WINDOWING_H
#define _WINDOWING_H

#include "stdafx.h"

typedef struct tagWINDOWING {

  tagWINDOWING() {

    RtlFillMemory(&rcClient, sizeof(RECT), 0x00);
    RtlFillMemory(&rcScreen, sizeof(RECT), 0x00);
    iWidth  = 0;
    iHeight = 0;

  }

  RECT rcClient;
  RECT rcScreen;
  int iWidth;
  int iHeight;

} WINDOWING, *PWINDOWING;

bool GetWindowCoords(HWND hWnd, PWINDOWING pw);
bool CenterWindow(HWND hWndContainer, HWND hWndMove);
bool ScreenToClientRect(HWND hWndClient, LPRECT pRect);
bool ClientToScreenRect(HWND hWndClient, LPRECT pRect);

#define RectCX(x) (x.right - x.left)
#define RectCY(x) (x.bottom - x.top)

#endif // _WINDOWING_H
