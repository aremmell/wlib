#include "stdafx.h"
#include "wnd.hpp"
#include "util.hpp"

//
// _Wnd : Public
//
LONG_PTR _Wnd::SendMsg(UINT uiMsg, WPARAM wParam, LPARAM lParam) {

  return SendMessage(m_hWnd, uiMsg, wParam, lParam);
}

BOOL _Wnd::PostMsg(UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam) {

  return PostMessage(m_hWnd, uiMsg, wParam, lParam);
}

LONG_PTR _Wnd::SendDlgItemMsg(INT_PTR iDlgItem, UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam) {

  return ::SendDlgItemMessage(m_hWnd, iDlgItem, uiMsg, wParam, lParam);
}

void _Wnd::Show(void) { _ShowWindow(SW_SHOW); }

void _Wnd::Hide(void) { _ShowWindow(SW_HIDE); }

void _Wnd::Minimize(void) { _ShowWindow(SW_MINIMIZE); }

void _Wnd::Maximize(void) { _ShowWindow(SW_MAXIMIZE); }

void _Wnd::Restore(void) { _ShowWindow(SW_RESTORE); }

void _Wnd::Enable(void) { EnableWindow(m_hWnd, TRUE); }

void _Wnd::Disable(void) { EnableWindow(m_hWnd, FALSE); }

bool _Wnd::SetWindowPos(HWND hWndInsert, INT_PTR x, INT_PTR y, INT_PTR cx, 
                        INT_PTR cy, UINT_PTR uiFlags)
{
  return WND_TRUE(::SetWindowPos(m_hWnd, hWndInsert, x, y, cx, cy, uiFlags));
}

bool _Wnd::MoveWindow(INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy, bool bRepaint) {

  return WND_TRUE(::MoveWindow(m_hWnd, x, y, cx, cy, bRepaint ? TRUE : FALSE));
}

bool _Wnd::StayOnTop(void) {

  return SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

bool _Wnd::NotOnTop(void) {

  return SetWindowPos(HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

HWND _Wnd::SetFocus(void) { return ::SetFocus(m_hWnd); }

bool _Wnd::Center(HWND hWndContainer) {

  return CenterWindow(hWndContainer, m_hWnd);
}

void _Wnd::SetFont(HFONT hFont, bool bRepaint) {

  SendMsg(WM_SETFONT, (WPARAM)hFont, MAKELONG(bRepaint ? 1 : 0, 0));
}

HFONT _Wnd::GetFont(void) {

  return reinterpret_cast<HFONT>(SendMsg(WM_GETFONT, 0L, 0L));
}

void _Wnd::SetSmIcon(HICON hIcon) { _SetIcon(hIcon, ICON_SMALL); }

void _Wnd::SetLgIcon(HICON hIcon) { _SetIcon(hIcon, ICON_BIG); }

HICON _Wnd::GetSmIcon(void) { return _GetIcon(ICON_SMALL); }

HICON _Wnd::GetLgIcon(void) { return _GetIcon(ICON_BIG); }

bool _Wnd::SetMenu(HMENU hMenu) {
  
  return WND_TRUE(::SetMenu(m_hWnd, hMenu));
}

HMENU _Wnd::GetMenu(void) { return ::GetMenu(m_hWnd); }

bool _Wnd::SetWindowText(CTSTRING &tsText) {

  return WND_TRUE(::SetWindowText(m_hWnd, tsText.c_str()));
}

bool _Wnd::GetWindowText(TSTRING &tsOut) {

  return GetWindowText(m_hWnd, tsOut);
}

bool _Wnd::GetWindowText(HWND hWnd, TSTRING &tsOut) {

  bool r  = false;

  if (::IsWindow(hWnd)) {

    INT_PTR iLen = ::GetWindowTextLength(hWnd);

    if (0 != iLen) {

      TCHAR *pBuf = new TCHAR[iLen + 1];

      if (NULL != pBuf) {

        if (0 != ::GetWindowText(hWnd, pBuf, iLen + 1)) {

          tsOut = pBuf;
          r     = true;

        }

        delete[] pBuf;
      }

    }

  }

  return r;
}

INT_PTR _Wnd::GetTextLength(void) {

  return ::GetWindowTextLength(m_hWnd);
}

bool _Wnd::SetDlgItemText(INT_PTR iDlgItem, CTSTRING &tsText) {

  return WND_TRUE(::SetDlgItemText(m_hWnd, iDlgItem, tsText.c_str()));
}

bool _Wnd::GetDlgItemText(INT_PTR iDlgItem, TSTRING &tsOut) {

    return GetWindowText(::GetDlgItem(m_hWnd, iDlgItem), tsOut);
}

bool _Wnd::GetClass(TSTRING &tsClass) {

  bool r                    = false;
  TCHAR pBuf[WND_MAXCLASS]  = {0};

  if (WND_TRUE(RealGetWindowClass(m_hWnd, pBuf, WND_MAXCLASS))) {

    tsClass = pBuf;
    r       = true;

  }

  return r;
}

INT_PTR _Wnd::GetID(void) {

  return static_cast<INT_PTR>(GetLongPtr(GWLP_ID));
}

HDC _Wnd::GetDC(void) { return ::GetDC(m_hWnd); }

HDC _Wnd::GetWinDC(void) { return GetWindowDC(m_hWnd); }

bool _Wnd::GetInfo(PWINDOWINFO pwi) {

  return ((NULL != pwi) && WND_TRUE(GetWindowInfo(m_hWnd, pwi)));
}

bool _Wnd::GetCoords(PWINDOWING pw) {

  return GetWindowCoords(m_hWnd, pw);
}

bool _Wnd::GetWindowRect(LPRECT pr) {

  return ((NULL != pr) && (WND_TRUE(::GetWindowRect(m_hWnd, pr))));
}

bool _Wnd::GetClientRect(LPRECT pr) {

  return ((NULL != pr) && (WND_TRUE(::GetClientRect(m_hWnd, pr))));
}

bool _Wnd::GetPlacement(WINDOWPLACEMENT *pwp) {

  return ((NULL != pwp) && WND_TRUE(GetWindowPlacement(m_hWnd, pwp)));
}

bool _Wnd::SetPlacement(WINDOWPLACEMENT *pwp) {

  return ((NULL != pwp) && WND_TRUE(SetWindowPlacement(m_hWnd, pwp)));
}

bool _Wnd::Slide(DWORD_PTR dwMsec, DWORD_PTR dwFlags) {

  return _AnimateWindow(dwMsec, dwFlags | AW_SLIDE);
}

bool _Wnd::Blend(DWORD_PTR dwMsec, DWORD_PTR dwFlags) {

  return _AnimateWindow(dwMsec, dwFlags | AW_BLEND);
}

bool _Wnd::BringToTop(void) {

  return WND_TRUE(::BringWindowToTop(m_hWnd));
}

LONG_PTR _Wnd::GetLongPtr(INT_PTR iIndex) {

  return GetWindowLongPtr(m_hWnd, iIndex);
}

LONG_PTR _Wnd::SetLongPtr(INT_PTR iIndex, LONG_PTR lNewVal) {

  return SetWindowLongPtr(m_hWnd, iIndex, lNewVal);
}

DWORD_PTR _Wnd::GetStyles(void) {

  return static_cast<DWORD_PTR>(GetLongPtr(GWL_STYLE));
}

DWORD_PTR _Wnd::SetStyles(DWORD_PTR dwStyles) {

  return static_cast<DWORD_PTR>(SetLongPtr(GWL_STYLE, 
         static_cast<LONG_PTR>(dwStyles)));
}

DWORD_PTR _Wnd::GetExStyles(void) {

  return static_cast<DWORD_PTR>(GetLongPtr(GWL_EXSTYLE));
}

DWORD_PTR _Wnd::SetExStyles(DWORD_PTR dwExStyles) {

  return static_cast<DWORD_PTR>(SetLongPtr(GWL_EXSTYLE,
         static_cast<LONG_PTR>(dwExStyles)));
}

HWND _Wnd::GetParent(void) { return ::GetParent(m_hWnd); }

bool _Wnd::SetParent(HWND hWnd) {

  return WND_TRUE(::SetParent(m_hWnd, hWnd));
}

HWND _Wnd::GetDlgItem(INT_PTR iID) { return ::GetDlgItem(m_hWnd, iID); }

HWND _Wnd::GetOwner(void) { return _GetWindow(GW_OWNER); }

bool _Wnd::SetProp(CTSTRING &tsProp, void *pData) {

  return WND_TRUE(::SetProp(m_hWnd, tsProp.c_str(), pData));
}

void *_Wnd::GetProp(CTSTRING &tsProp) {

  return ::GetProp(m_hWnd, tsProp.c_str());
}

bool _Wnd::SetInstance(HINSTANCE hInst) {

  return WND_TRUE(SetLongPtr(GWLP_HINSTANCE, reinterpret_cast<LONG_PTR>(hInst)));
}

HINSTANCE _Wnd::GetInstance(void) {

  return reinterpret_cast<HINSTANCE>(GetLongPtr(GWLP_HINSTANCE));
}

bool _Wnd::IsChild(HWND hWnd) {

  return WND_TRUE(::IsChild(hWnd, m_hWnd));
}

bool _Wnd::IsChild(_Wnd *pWnd) {

  return ((NULL != pWnd) && IsChild(pWnd->m_hWnd));
}

bool _Wnd::IsMinimized(void) {

  return WND_TRUE(IsIconic(m_hWnd));
}

bool _Wnd::IsMaximized(void) {

  return WND_TRUE(IsZoomed(m_hWnd));
}

bool _Wnd::IsWindow(void) {

  return WND_TRUE(::IsWindow(m_hWnd));
}

bool _Wnd::IsUnicode(void) {

  return WND_TRUE(IsWindowUnicode(m_hWnd));
}

bool _Wnd::IsVisible(void) {

  return WND_TRUE(IsWindowVisible(m_hWnd));
}

bool _Wnd::IsEnabled(void) {

  return WND_TRUE(IsWindowEnabled(m_hWnd));
}

bool _Wnd::IsStayOnTop(void) {

  return (0UL != (GetExStyles() & WS_EX_TOPMOST));
}

bool _Wnd::InvalidateRect(LPRECT pRect, bool bErase) {

  BOOL bArg = bErase ? TRUE : FALSE;

  return WND_TRUE(::InvalidateRect(m_hWnd, pRect, bArg));
}

bool _Wnd::UpdateWindow(void) {

  return WND_TRUE(::UpdateWindow(m_hWnd));
}

bool _Wnd::Refresh(LPRECT pRect) {

  return (InvalidateRect(pRect, true) && UpdateWindow());
}

#if (_WIN32_WINNT >= 0x0500)

bool _Wnd::SetLayeredAttributes(COLORREF clrKey, BYTE bAlpha, DWORD_PTR dwFlags) {

  return WND_TRUE(SetLayeredWindowAttributes(m_hWnd, clrKey, bAlpha, dwFlags));
}

#endif // !_WIN32_WINNT >= 0x0500

bool _Wnd::Detach(void) {

  bool r              = false;
  LONG_PTR lpWndProc  = _GetWndProc(m_hWnd);

  if (NULL != lpWndProc) {

    LONG_PTR lpRetVal = 0L;

    SetLastError(0UL);

    lpRetVal = SetWindowLongPtr(m_hWnd, GWL_WNDPROC, lpWndProc);

    if (0L != lpRetVal || 0UL == GetLastError()) {

      if (_SetClass(m_hWnd, NULL)) {

        if (_SetWndProc(m_hWnd, 0L)) {

          m_hWnd  = NULL;
          r       = true;

        }

      }

    }

  }

  return r;
}

bool _Wnd::Destroy(void) { return WND_TRUE(DestroyWindow(m_hWnd)); }

//
// _Wnd : Private
//
bool _Wnd::_AnimateWindow(DWORD_PTR dwMsec, DWORD_PTR dwFlags) {

  return WND_TRUE(::AnimateWindow(m_hWnd, dwMsec, dwFlags));
}

void _Wnd::_ShowWindow(INT_PTR iCmdShow) {

  ::ShowWindow(m_hWnd, iCmdShow);
}

HWND _Wnd::_GetWindow(UINT_PTR uType) {

  return GetWindow(m_hWnd, uType);
}

HICON _Wnd::_GetIcon(DWORD_PTR dwFlag) {

  return reinterpret_cast<HICON>(SendMsg(WM_GETICON, dwFlag, 0L));
}

void _Wnd::_SetIcon(HICON hIcon, DWORD_PTR dwFlag) {

  SendMsg(WM_SETICON, dwFlag, (LPARAM)hIcon);
}

//
// _Wnd : Protected
//
bool _Wnd::_SubclassWindow(HWND hWnd, LONG_PTR lpWndProc) {

  bool r = false;

  if (::IsWindow(hWnd)) {

    if (_SetClass(hWnd, this)) {

      SetLastError(0UL);

      LONG_PTR lpRetVal = SetWindowLongPtr(hWnd, GWL_WNDPROC, lpWndProc);

      if (0L != lpRetVal || 0UL == GetLastError()) {

        if (_SetWndProc(hWnd, lpRetVal)) {

          r       = true;
          m_hWnd  = hWnd;

        }

      }

    }

  }

  return r;
}

bool _Wnd::_OnCreate(HWND hWnd, _Wnd *pWnd) {

  bool r = false;

  if (_SetClass(hWnd, pWnd)) {

    if (NULL != pWnd) {

      pWnd->m_hWnd  = hWnd;
      r             = true;
    }

  }

  return r;
}

bool _Wnd::_SetClass(HWND hWnd, _Wnd *pWnd) {

  bool r = false;

  if ((::IsWindow(hWnd))) {

    LONG_PTR lpRetVal = 0L;

    SetLastError(0UL);

    lpRetVal = SetWindowLongPtr(hWnd, GWL_USERDATA,
                                reinterpret_cast<LONG_PTR>(pWnd));

    if (0L != lpRetVal || 0UL == GetLastError()) {

      r = true;

    }

  }

  return r;
}

_Wnd *_Wnd::_GetClass(HWND hWnd) {

  _Wnd *r = NULL;

  if (::IsWindow(hWnd)) {

    r = reinterpret_cast<_Wnd *>(GetWindowLongPtr(hWnd, GWL_USERDATA));

  }

  return r;
}

bool _Wnd::_SetWndProc(HWND hWnd, LONG_PTR lpWndProc) {

  bool r = false;

  if (::IsWindow(hWnd)) {

    if (0L != lpWndProc) {

      r = WND_TRUE(::SetProp(hWnd, WND_WNDPROC_PROP,
                             reinterpret_cast<HANDLE>(lpWndProc)));

    } else {

      r = WND_TRUE(::RemoveProp(hWnd, WND_WNDPROC_PROP));

    }

  }

  return r;
}

LONG_PTR _Wnd::_GetWndProc(HWND hWnd) {

  if (::IsWindow(hWnd)) {

    return reinterpret_cast<LONG_PTR>(::GetProp(hWnd, WND_WNDPROC_PROP));

  } else {

    return static_cast<LONG_PTR>(NULL);

  }

}
