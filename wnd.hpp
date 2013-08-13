#ifndef _WND_H
#define _WND_H

#include "stdafx.h"
#include "windowing.hpp"

#define WND_WNDPROC_PROP  _T("WNDPROC")
#define WND_TRUE(x)      (((x != FALSE) ? true : false))
#define WND_MAXCLASS      256

//
// _Wnd Class
// Contains low-level
// functionality for
// Window and Dialog
//
class _Wnd {

//
// Public Functions
//
public:
  _Wnd() {

    m_hWnd  = NULL;

  }
  virtual ~_Wnd() {

    Detach();

  }

  //
  // Message sending
  //
  LONG_PTR SendMsg(UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam);
  BOOL PostMsg(UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam);
  LONG_PTR SendDlgItemMsg(INT_PTR iDlgItem, UINT_PTR uiMsg, WPARAM wParam, LPARAM lParam);

  //
  // State set/get
  //
  void Show(void);
  void Hide(void);
  void Minimize(void);
  void Maximize(void);
  void Restore(void);
  void Enable(void);
  void Disable(void);

  bool SetWindowPos(HWND hWndInsert, INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy, UINT_PTR uiFlags);
  bool MoveWindow(INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy, bool bRepaint);
  bool StayOnTop(void);
  bool NotOnTop(void);
  HWND SetFocus(void);

  bool Center(HWND hWndContainer);

  bool GetCoords(PWINDOWING pw);
  bool GetWindowRect(LPRECT pr);
  bool GetClientRect(LPRECT pr);

  bool GetPlacement(WINDOWPLACEMENT *pwp);
  bool SetPlacement(WINDOWPLACEMENT *pwp);

  bool Slide(DWORD_PTR dwMsec = 200UL, DWORD_PTR dwFlags = AW_VER_NEGATIVE);
  bool Blend(DWORD_PTR dwMsec = 200UL, DWORD_PTR dwFlags = 0UL);
  bool BringToTop(void);

  LONG_PTR GetLongPtr(INT_PTR iIndex);
  LONG_PTR SetLongPtr(INT_PTR iIndex, LONG_PTR lNewVal);

  DWORD_PTR GetStyles(void);
  DWORD_PTR SetStyles(DWORD_PTR dwStyles);
  DWORD_PTR GetExStyles(void);
  DWORD_PTR SetExStyles(DWORD_PTR dwExStyles);

  bool SetParent(HWND hWnd);
  HWND GetParent(void);

  HWND GetDlgItem(INT_PTR iID);
  HWND GetOwner(void);

  bool SetProp(CTSTRING &tsProp, void *pData);
  void *GetProp(CTSTRING &tsProp);

  bool SetInstance(HINSTANCE hInst);
  HINSTANCE GetInstance(void);

  void SetFont(HFONT hFont, bool bRepaint);
  HFONT GetFont(void);

  void SetSmIcon(HICON hIcon);
  HICON GetSmIcon(void);
  void SetLgIcon(HICON hIcon);
  HICON GetLgIcon(void);

  bool SetMenu(HMENU hMenu);
  HMENU GetMenu(void);

  bool SetWindowText(CTSTRING &tsText);
  bool GetWindowText(TSTRING &tsOut);
  bool GetWindowText(HWND hWnd, TSTRING &tsOut);

  INT_PTR GetTextLength(void);

  bool SetDlgItemText(INT_PTR iDlgItem, CTSTRING &tsText);
  bool GetDlgItemText(INT_PTR iDlgItem, TSTRING &tsOut);

  bool GetClass(TSTRING &tsClass);
  INT_PTR GetID(void);

  HDC GetDC(void);
  HDC GetWinDC(void);

  bool GetInfo(PWINDOWINFO pwi);

  //
  // State query
  //
  bool IsChild(HWND hWnd);
  bool IsChild(_Wnd *pWnd);
  bool IsMinimized(void);
  bool IsMaximized(void);
  bool IsWindow(void);
  bool IsUnicode(void);
  bool IsVisible(void);
  bool IsEnabled(void);
  bool IsStayOnTop(void);

  //
  // Drawing-related
  //
  bool InvalidateRect(LPRECT pRect = NULL, bool bErase = false);
  bool UpdateWindow(void);
  bool Refresh(LPRECT pRect = NULL);
  bool SetLayeredAttributes(COLORREF clrKey, BYTE bAlpha, DWORD_PTR dwFlags);

  //
  // Attaching/Detaching
  //
  bool Detach(void);
  virtual bool Attach(HWND hWnd) = 0;

  //
  // Destruction
  //
  bool Destroy(void);

//
// Public Members
//
public:
  HWND m_hWnd;

//
// Private Functions
//
private:
  bool _AnimateWindow(DWORD_PTR dwMsec, DWORD_PTR dwFlags);
  void _ShowWindow(INT_PTR iCmdShow);
  HWND _GetWindow(UINT_PTR uType);
  HICON _GetIcon(DWORD_PTR dwFlag);
  void _SetIcon(HICON hIcon, DWORD_PTR dwFlag);

//
// Protected Functions
//
protected:
  bool _SubclassWindow(HWND hWnd, LONG_PTR lpWndProc);
  static bool _OnCreate(HWND hWnd, _Wnd *pWnd);
  static bool _SetClass(HWND hWnd, _Wnd *pWnd);
  static _Wnd *_GetClass(HWND hWnd);
  static bool _SetWndProc(HWND hWnd, LONG_PTR lpWndProc);
  static LONG_PTR _GetWndProc(HWND hWnd);

};

#endif // !_WND_H
