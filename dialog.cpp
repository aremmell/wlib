#include "stdafx.h"
#include "dialog.hpp"

bool Dialog::DoModal(HINSTANCE hInstance, PCTSTR pszTemplate, HWND hWndParent) {

  bool r = false;

  if (((NULL != hWndParent) && (FALSE == ::IsWindow(hWndParent)))) { return false; }

  if (NULL != pszTemplate) {

    if (-1 != ::DialogBoxParam(hInstance, pszTemplate, hWndParent,
                               WindowProc, reinterpret_cast<LPARAM>(this))) {

      r = true;

    }

  }

  return r;
}

HWND Dialog::Create(HINSTANCE hInstance, PCTSTR pszTemplate, HWND hWndParent) {

  if (((NULL != hWndParent) && (FALSE == ::IsWindow(hWndParent)))) { return false; }

  if (NULL != pszTemplate) {

    m_hWnd = ::CreateDialogParam(hInstance, pszTemplate, hWndParent,
                                 WindowProc, reinterpret_cast<LPARAM>(this));

  }

  return m_hWnd;
} 

BOOL CALLBACK Dialog::WindowProc(HWND hWnd, UINT_PTR msg, WPARAM wParam, LPARAM lParam) {

  Dialog *pThis = reinterpret_cast<Dialog *>(_GetClass(hWnd));

  if (pThis || msg == WM_INITDIALOG) {

    switch(msg) {

      case WM_INITDIALOG:
      {
        if (0L != lParam) {

          pThis = reinterpret_cast<Dialog *>(lParam);

          if (_OnCreate(hWnd, pThis)) {

            pThis->OnCreate(wParam, lParam);

          }

        }
        break;

      }
      case WM_COMMAND:         return pThis->OnCommand(wParam, lParam);
      case WM_PAINT:           return pThis->OnPaint(wParam, lParam);
      case WM_NCPAINT:         return pThis->OnNCPaint(wParam, lParam);
      case WM_SIZE:            return pThis->OnSize(wParam, lParam);
      case WM_DESTROY:         return pThis->OnDestroy(wParam, lParam);
      case WM_CLOSE:           return pThis->OnClose(wParam, lParam);
      case WM_DRAWITEM:        return pThis->OnDrawItem(wParam, lParam);
      case WM_NOTIFY:          return pThis->OnNotify(wParam, lParam);
      case WM_LBUTTONDOWN:     return pThis->OnLButtonDown(wParam, lParam);
      case WM_LBUTTONUP:       return pThis->OnLButtonUp(wParam, lParam);
      case WM_LBUTTONDBLCLK:   return pThis->OnLButtonDblClk(wParam, lParam);
      case WM_RBUTTONDOWN:     return pThis->OnRButtonDown(wParam, lParam);
      case WM_RBUTTONUP:       return pThis->OnRButtonUp(wParam, lParam);
      case WM_CHAR:            return pThis->OnChar(wParam, lParam);
      case WM_SETCURSOR:       return pThis->OnSetCursor(wParam, lParam);
      case WM_CAPTURECHANGED:  return pThis->OnCaptureChanged(wParam, lParam);
      case WM_MOUSEMOVE:       return pThis->OnMouseMove(wParam, lParam);
      case WM_MOUSEHOVER:      return pThis->OnMouseHover(wParam, lParam);
      case WM_MOUSELEAVE:      return pThis->OnMouseLeave(wParam, lParam);
      case WM_MEASUREITEM:     return pThis->OnMeasureItem(wParam, lParam);
      case WM_KEYDOWN:         return pThis->OnKeyDown(wParam, lParam);
      case WM_KILLFOCUS:       return pThis->OnKillFocus(wParam, lParam);
      case WM_SETFOCUS:        return pThis->OnSetFocus(wParam, lParam);
      case WM_SETFONT:         return pThis->OnSetFont(wParam, lParam);
      case WM_NCMOUSELEAVE:    return pThis->OnNCMouseLeave(wParam, lParam);
      case WM_NCHITTEST:       return pThis->OnNCHitTest(wParam, lParam);
      case WM_SHOWWINDOW:      return pThis->OnShowWindow(wParam, lParam);
      case WM_TIMER:           return pThis->OnTimer(wParam, lParam);
      case WM_COPYDATA:        return pThis->OnCopyData(wParam, lParam);
    }
  }
  
  return FALSE;
}

bool Dialog::Attach(HWND hWnd) {

  Detach();
  return (_SubclassWindow(hWnd, reinterpret_cast<LONG_PTR>(WindowProc)));
}

bool Dialog::EndDialog(INT_PTR nResult) {

  return WND_TRUE(::EndDialog(m_hWnd, nResult));
}
