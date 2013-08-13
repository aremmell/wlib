#ifndef _WINDOW_H
#define _WINDOW_H

#include "wnd.hpp"

#define WND_VMSG virtual LRESULT

//
// WINDOWINIT Structure
//
// Defines the parameters needed
// to create a window
//
typedef struct tagWINDOWINIT {

  tagWINDOWINIT() {

    dwStyleEx   = 0UL;
    dwStyle     = 0UL;
    tsClass     = _T("");
    tsCaption   = _T("");
    x           = 0;
    y           = 0;
    cx          = 0;
    cy          = 0;
    hWndParent  = NULL;
    iID         = 0;
    hInst       = NULL;

  }

  tagWINDOWINIT &operator=(const tagWINDOWINIT &in) {

    dwStyleEx   = in.dwStyleEx;
    dwStyle     = in.dwStyle;
    tsClass     = in.tsClass;
    tsCaption   = in.tsCaption;
    x           = in.x;
    y           = in.y;
    cx          = in.cx;
    cy          = in.cy;
    hWndParent  = in.hWndParent;
    iID         = in.iID;
    hInst       = in.hInst;

    return (*this);
  }

  DWORD_PTR dwStyleEx;
  DWORD_PTR dwStyle;
  TSTRING tsClass;
  TSTRING tsCaption;
  INT_PTR x;
  INT_PTR y; 
  INT_PTR cx;
  INT_PTR cy;
  HWND hWndParent;
  INT_PTR iID;
  HINSTANCE hInst;

} WINDOWINIT, *PWINDOWINIT;

//
// Window Class
//
// Virtual message routing
// base class for all windows
//
class Window : public _Wnd {

public:
  Window() {}
  virtual ~Window() {}

  virtual HWND Create(DWORD_PTR dwStyleEx, CTSTRING &tsClass, CTSTRING &tsTitle, 
                      DWORD_PTR dwStyle, INT_PTR x, INT_PTR y, INT_PTR cx, 
                      INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst = NULL);

  virtual HWND Create(PWINDOWINIT pw);

  //
  // Message handlers
  //
  WND_VMSG OnCreate(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnCommand(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnPaint(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnNCPaint(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnSize(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnDestroy(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnClose(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnDrawItem(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnNotify(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnLButtonDown(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnLButtonUp(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnRButtonDown(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnRButtonUp(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnChar(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnSetCursor(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnCaptureChanged(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnMouseMove(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnMouseLeave(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnMouseHover(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnMeasureItem(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnKeyDown(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnKillFocus(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnSetFocus(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnSetFont(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnNCMouseLeave(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnNCHitTest(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnParentNotify(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnActivate(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnShowWindow(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnTimer(WPARAM wParam, LPARAM lParam);
  WND_VMSG OnCopyData(WPARAM wParam, LPARAM lParam);

  //
  // _Wnd Overrides
  //
  bool Attach(HWND hWnd);
  
  //
  // Window Procedure
  //
  static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
  static LRESULT _RouteMsg(Window *pThis, HWND hWnd, UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam);
  WNDPROC _IntendedWndProc(HINSTANCE hInst, CTSTRING &tsClass);

};

#endif // _WINDOW_H
