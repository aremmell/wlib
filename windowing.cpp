#include "stdafx.h"
#include "windowing.hpp"

bool GetWindowCoords(HWND hWnd, PWINDOWING pw) {

  bool r = false;

  if (IsWindow(hWnd) && (NULL != pw)) {

    if (GetWindowRect(hWnd, &pw->rcScreen)) {

      CopyMemory(&pw->rcClient, &pw->rcScreen, sizeof(RECT));

      pw->iWidth  = (pw->rcScreen.right - pw->rcScreen.left);
      pw->iHeight = (pw->rcScreen.bottom - pw->rcScreen.top);

      if (ScreenToClientRect(GetParent(hWnd), &pw->rcClient)) {

        r = true;

      }

    }

  }

  return r;
}

bool CenterWindow(HWND hWndContainer, HWND hWndMove) {

  bool r = false;

  if (IsWindow(hWndMove)) {

    WINDOWING wContainer;
    WINDOWING wMove;

    if (NULL == hWndContainer) { hWndContainer = GetDesktopWindow(); }

    if (GetWindowCoords(hWndContainer, &wContainer)) {

      if (GetWindowCoords(hWndMove, &wMove)) {

        int x = wContainer.rcScreen.left + (wContainer.iWidth / 2) - (wMove.iWidth / 2);
        int y = wContainer.rcScreen.top + (wContainer.iHeight / 2) - (wMove.iHeight / 2);

        if (SetWindowPos(hWndMove, NULL, x, y, 0L, 0L, SWP_NOSIZE | SWP_NOZORDER)) {

          r = true;

        }

      }

    }

  }

  return r;
}

bool ScreenToClientRect(HWND hWndClient, LPRECT pRect) {

  bool r = false;

  if (NULL == hWndClient) { return true; }

  POINT pt1 = {0};
  POINT pt2 = {0};

  pt1.x = pRect->left;
  pt1.y = pRect->top;

  pt2.x = pRect->right;
  pt2.y = pRect->bottom;

  if (ScreenToClient(hWndClient, &pt1)) {

    if (ScreenToClient(hWndClient, &pt2)) {

      pRect->left   = pt1.x;
      pRect->top    = pt1.y;
      pRect->right  = pt2.x;
      pRect->bottom = pt2.y;

      r = true;

    }

  }

  return r;
}

bool ClientToScreenRect(HWND hWndClient, LPRECT pRect) {

  bool r = false;

  if (NULL == hWndClient) { return true; }

  POINT pt1 = {0};
  POINT pt2 = {0};

  pt1.x = pRect->left;
  pt1.y = pRect->top;

  pt2.x = pRect->right;
  pt2.y = pRect->bottom;

  if (ClientToScreen(hWndClient, &pt1)) {

    if (ClientToScreen(hWndClient, &pt2)) {

      pRect->left   = pt1.x;
      pRect->top    = pt1.y;
      pRect->right  = pt2.x;
      pRect->bottom = pt2.y;

      r = true;

    }

  }

  return r;
}
