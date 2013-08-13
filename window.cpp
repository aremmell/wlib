#include "stdafx.h"
#include "window.hpp"

HWND Window::Create(DWORD_PTR dwStyleEx, CTSTRING &tsClass, CTSTRING &tsTitle, DWORD_PTR dwStyle, 
                    INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy, HWND hWndParent,
                    INT_PTR iID, HINSTANCE hInst)
{

  HWND hWnd = NULL;

  hInst = ((NULL != hInst) ? hInst : GetModuleHandle(NULL));

  hWnd = CreateWindowEx(dwStyleEx,
                        tsClass.c_str(),
                        tsTitle.c_str(),
                        dwStyle,
                        x,
                        y,
                        cx,
                        cy, 
                        hWndParent,
                        reinterpret_cast<HMENU>(iID),
                        hInst,
                        this);

  if (NULL != hWnd) {

    if (_IntendedWndProc(hInst, tsClass) != WindowProc) {

      if (!_SubclassWindow(hWnd, reinterpret_cast<LONG_PTR>(WindowProc))) {

        return NULL;

      }

      if (-1L == OnCreate(0L, reinterpret_cast<LPARAM>(this))) {

        Detach();
        DestroyWindow(hWnd);

        return NULL;

      }

    }

  }
    
  return hWnd;  
}

HWND Window::Create(PWINDOWINIT pw) {

  if (NULL != pw) {

    return Create(pw->dwStyleEx, pw->tsClass, pw->tsCaption, pw->dwStyle, 
            pw->x, pw->y, pw->cx, pw->cy, pw->hWndParent, pw->iID, pw->hInst);

  }

  return NULL;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

  Window *pThis = reinterpret_cast<Window *>(_GetClass(hWnd));

  if (pThis || msg == WM_CREATE) {

    switch(msg) {

      case WM_CREATE:
      {

        CREATESTRUCT *lpCreateStruct = reinterpret_cast<CREATESTRUCT *>(lParam);

        if (NULL != lpCreateStruct) {

          pThis = reinterpret_cast<Window *>(lpCreateStruct->lpCreateParams);

          if (_OnCreate(hWnd, pThis)) {

            pThis->OnCreate(wParam, lParam);

          }

        }

        break;
      }
      case WM_COMMAND:        return pThis->OnCommand(wParam, lParam);
      case WM_PAINT:          return pThis->OnPaint(wParam, lParam);
      case WM_NCPAINT:        return pThis->OnNCPaint(wParam, lParam);
      case WM_SIZE:           return pThis->OnSize(wParam, lParam);
      case WM_DESTROY:        return pThis->OnDestroy(wParam, lParam);
      case WM_CLOSE:          return pThis->OnClose(wParam, lParam);
      case WM_DRAWITEM:       return pThis->OnDrawItem(wParam, lParam);
      case WM_NOTIFY:         return pThis->OnNotify(wParam, lParam);
      case WM_LBUTTONDOWN:    return pThis->OnLButtonDown(wParam, lParam);
      case WM_LBUTTONUP:      return pThis->OnLButtonUp(wParam, lParam);
      case WM_LBUTTONDBLCLK:  return pThis->OnLButtonDblClk(wParam, lParam);
      case WM_RBUTTONDOWN:    return pThis->OnRButtonDown(wParam, lParam);
      case WM_RBUTTONUP:      return pThis->OnRButtonUp(wParam, lParam);
      case WM_CHAR:           return pThis->OnChar(wParam, lParam);
      case WM_SETCURSOR:      return pThis->OnSetCursor(wParam, lParam);
      case WM_CAPTURECHANGED: return pThis->OnCaptureChanged(wParam, lParam);
      case WM_MOUSEMOVE:      return pThis->OnMouseMove(wParam, lParam);
      case WM_MOUSEHOVER:     return pThis->OnMouseHover(wParam, lParam);
      case WM_MOUSELEAVE:     return pThis->OnMouseLeave(wParam, lParam);
      case WM_MEASUREITEM:    return pThis->OnMeasureItem(wParam, lParam);
      case WM_KEYDOWN:        return pThis->OnKeyDown(wParam, lParam);
      case WM_KILLFOCUS:      return pThis->OnKillFocus(wParam, lParam);
      case WM_SETFOCUS:       return pThis->OnSetFocus(wParam, lParam);
      case WM_SETFONT:        return pThis->OnSetFont(wParam, lParam);
      case WM_NCMOUSELEAVE:   return pThis->OnNCMouseLeave(wParam, lParam);
      case WM_NCHITTEST:      return pThis->OnNCHitTest(wParam, lParam);
      case WM_PARENTNOTIFY:   return pThis->OnParentNotify(wParam, lParam);
      case WM_SHOWWINDOW:     return pThis->OnShowWindow(wParam, lParam);
      case WM_TIMER:          return pThis->OnTimer(wParam, lParam);
      case WM_COPYDATA:       return pThis->OnCopyData(wParam, lParam);

    }

  }
  
  return _RouteMsg(pThis, hWnd, msg, wParam, lParam);
}

LRESULT Window::OnCreate(WPARAM wParam, LPARAM lParam) {

  return 0L;
}

LRESULT Window::OnCommand(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_COMMAND, wParam, lParam);
}

LRESULT Window::OnPaint(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_PAINT, wParam, lParam);
}

LRESULT Window::OnNCPaint(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_NCPAINT, wParam, lParam);
}

LRESULT Window::OnSize(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_SIZE, wParam, lParam);
}

LRESULT Window::OnDestroy(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_DESTROY, wParam, lParam);
}

LRESULT Window::OnClose(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_CLOSE, wParam, lParam);
}

LRESULT Window::OnDrawItem(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_DRAWITEM, wParam, lParam);
}

LRESULT Window::OnNotify(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_NOTIFY, wParam, lParam);
}

LRESULT Window::OnLButtonDown(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

LRESULT Window::OnLButtonUp(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_LBUTTONUP, wParam, lParam);
}

LRESULT Window::OnLButtonDblClk(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT Window::OnRButtonDown(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_RBUTTONDOWN, wParam, lParam);
}

LRESULT Window::OnRButtonUp(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_RBUTTONUP, wParam, lParam);
}

LRESULT Window::OnChar(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_CHAR, wParam, lParam);
}

LRESULT Window::OnSetCursor(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_SETCURSOR, wParam, lParam);
}

LRESULT Window::OnCaptureChanged(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_CAPTURECHANGED, wParam, lParam);
}

LRESULT Window::OnMouseMove(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

LRESULT Window::OnMouseHover(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_MOUSEHOVER, wParam, lParam);
}

LRESULT Window::OnMouseLeave(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_MOUSELEAVE, wParam, lParam);
}

LRESULT Window::OnMeasureItem(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_MEASUREITEM, wParam, lParam);
}

LRESULT Window::OnKeyDown(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_KEYDOWN, wParam, lParam);
}

LRESULT Window::OnKillFocus(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_KILLFOCUS, wParam, lParam);
}

LRESULT Window::OnSetFocus(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_SETFOCUS, wParam, lParam);
}

LRESULT Window::OnSetFont(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_SETFONT, wParam, lParam);
}

LRESULT Window::OnNCMouseLeave(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_NCMOUSELEAVE, wParam, lParam);
}

LRESULT Window::OnNCHitTest(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_NCHITTEST, wParam, lParam);
}

LRESULT Window::OnParentNotify(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_PARENTNOTIFY, wParam, lParam);
}

LRESULT Window::OnActivate(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_ACTIVATE, wParam, lParam);
}

LRESULT Window::OnShowWindow(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_SHOWWINDOW, wParam, lParam);
}

LRESULT Window::OnTimer(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_TIMER, wParam, lParam);
}

LRESULT Window::OnCopyData(WPARAM wParam, LPARAM lParam) {

  return _RouteMsg(this, m_hWnd, WM_COPYDATA, wParam, lParam);
}

bool Window::Attach(HWND hWnd) {

  Detach();

  return (_SubclassWindow(hWnd, reinterpret_cast<LONG_PTR>(WindowProc)));
}

//
// Window : Private
//
LRESULT Window::_RouteMsg(Window *pThis, HWND hWnd, UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam) {

  LONG_PTR lpWndProc = _GetWndProc(hWnd);

  if ((NULL != pThis) && (NULL != lpWndProc)) {

    return CallWindowProc(reinterpret_cast<WNDPROC>(lpWndProc), hWnd, uiMsg, wParam, lParam);

  }

  return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

WNDPROC Window::_IntendedWndProc(HINSTANCE hInst, CTSTRING &tsClass) {

  WNDPROC r    = NULL;
  WNDCLASS wc  = {0};

  if (WND_TRUE(GetClassInfo(hInst, tsClass.c_str(), &wc))) {

    return wc.lpfnWndProc;

  }

  return r;
}
