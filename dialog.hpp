#ifndef _DIALOG_H
#define _DIALOG_H

#include "wnd.hpp"

#define DLG_VMSG virtual BOOL

class Dialog : public _Wnd {

public:
  Dialog() {}
  virtual ~Dialog() {}

  virtual bool DoModal(HINSTANCE hInstance, PCTSTR pszTemplate, HWND hWndParent);
  virtual HWND Create(HINSTANCE hInstance, PCTSTR pszTemplate, HWND hWndParent);

  //
  // Message Handlers
  //
  DLG_VMSG OnCreate(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnCommand(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnPaint(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnNCPaint(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnSize(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnDestroy(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnClose(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnDrawItem(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnNotify(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnLButtonDown(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnLButtonUp(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnLButtonDblClk(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnRButtonDown(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnRButtonUp(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnChar(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnSetCursor(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnCaptureChanged(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnMouseMove(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnMouseLeave(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnMouseHover(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnMeasureItem(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnKeyDown(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnKillFocus(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnSetFocus(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnSetFont(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnNCMouseLeave(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnNCHitTest(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnShowWindow(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnTimer(WPARAM wParam, LPARAM lParam) { return FALSE; }
  DLG_VMSG OnCopyData(WPARAM wParam, LPARAM lParam) { return FALSE; }

  //
  // _Wnd Overrides
  //
  bool Attach(HWND hWnd);

  //
  // Dialog-specific
  //
  bool EndDialog(INT_PTR nResult);

//
// Protected Functions
//
protected:
  static BOOL CALLBACK WindowProc(HWND hWnd, UINT_PTR msg, WPARAM wParam, LPARAM lParam);

};

#endif // _DIALOG_H
