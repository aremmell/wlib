#include "stdafx.h"
#include "listbox.hpp"

//
// ListBox : Public
//
bool ListBox::Create(DWORD_PTR dwStyleEx, DWORD_PTR dwStyle, HWND hWndParent, INT_PTR x, INT_PTR y,
                     INT_PTR cx, INT_PTR cy, INT_PTR iID)
{

  HWND hWnd = Window::Create(dwStyleEx,
                             _T("LISTBOX"),
                             _T(""),
                             dwStyle,
                             x,
                             y,
                             cx,
                             cy,
                             hWndParent,
                             iID);

  return ::IsWindow(hWnd) ? true : false;
}

LONG_PTR ListBox::AddString(CTSTRING &tsString) {

  return AddString(tsString.c_str());
}

LONG_PTR ListBox::AddString(const void *pVoid) {

  LONG_PTR r = SendMsg(LB_ADDSTRING, 0L, reinterpret_cast<LPARAM>(pVoid));

  return ((r != LB_ERRSPACE) && (r != LB_ERR)) ? r : LB_ERR;
}

LONG_PTR ListBox::InsertString(INT_PTR iIndex, CTSTRING &tsString) {

  return InsertString(iIndex, tsString.c_str());
}

LONG_PTR ListBox::InsertString(INT_PTR iIndex, const void *pVoid) {

  LONG_PTR r = SendMsg(LB_INSERTSTRING, iIndex, reinterpret_cast<LPARAM>(pVoid));

  return ((r != LB_ERRSPACE) && (r != LB_ERR)) ? r : LB_ERR;
}

LONG_PTR ListBox::DeleteString(INT_PTR iIndex) {

  return SendMsg(LB_DELETESTRING, iIndex, 0L);
}

LONG_PTR ListBox::FindString(CTSTRING &tsFind, INT_PTR iStart) {

  return SendMsg(LB_FINDSTRING, (WPARAM)iStart, (LPARAM)tsFind.c_str());
}

LONG_PTR ListBox::FindStringExact(CTSTRING &tsFind, INT_PTR iStart) {

  return SendMsg(LB_FINDSTRINGEXACT, iStart, reinterpret_cast<LPARAM>(tsFind.c_str()));
}

bool ListBox::SetAnchor(INT_PTR iIndex) {

  return (LB_ERR != SendMsg(LB_SETANCHORINDEX, iIndex, 0L));
}

LONG_PTR ListBox::GetAnchor(void) {

  return SendMsg(LB_GETANCHORINDEX, 0L, 0L);
}

bool ListBox::SetCaret(INT_PTR iIndex) {

  return (LB_ERR != SendMsg(LB_SETCARETINDEX, iIndex, static_cast<LPARAM>(FALSE)));
}

LONG_PTR ListBox::GetCaret(void) {

  return SendMsg(LB_GETCARETINDEX, 0L, 0L);
}

bool ListBox::SetCount(INT_PTR iCount) {

  LONG_PTR r = SendMsg(LB_SETCOUNT, iCount, 0L);

  return ((LB_ERRSPACE != r) && (LB_ERR != r));
}

LONG_PTR ListBox::GetCount(void) {

  return SendMsg(LB_GETCOUNT, 0L, 0L);
}

bool ListBox::SetSelItem(INT_PTR iIndex) {

  bool r        = false;
  LONG_PTR lRet = LB_ERR;

  if (LB_ERR == (lRet = SendMsg(LB_SETCURSEL, iIndex, 0L))) {

    if (-1L == iIndex) {

      r = true;

    }

  } else {

    r = true;

  }

  return r;
}

LONG_PTR ListBox::GetSelItem(void) {

  return SendMsg(LB_GETCURSEL, 0L, 0L);
}

bool ListBox::SetItemData(INT_PTR iIndex, const void *pData) {

  return (LB_ERR != SendMsg(LB_SETITEMDATA, iIndex, reinterpret_cast<LPARAM>(pData)));
}

void *ListBox::GetItemData(INT_PTR iIndex) {
  
  void *p       = NULL;
  LONG_PTR lRet = LB_ERR;

  lRet = SendMsg(LB_GETITEMDATA, iIndex, 0L);

  if (LB_ERR != lRet) {

    p = reinterpret_cast<void *>(lRet);

  }

  return p;
}

bool ListBox::SetItemHeight(INT_PTR iIndex, INT_PTR iHeight) {

  return (LB_ERR != SendMsg(LB_SETITEMHEIGHT, iIndex, iHeight));
}

LONG_PTR ListBox::GetItemHeight(INT_PTR iIndex) {

  return SendMsg(LB_GETITEMHEIGHT, iIndex, 0L);
}

bool ListBox::GetItemRect(INT_PTR iIndex, PRECT pRect) {

  bool r = false;

  if (NULL != pRect) {

    if (LB_ERR != SendMsg(LB_GETITEMRECT, iIndex, reinterpret_cast<LPARAM>(pRect))) {

      r = true;

    }

  }

  return r;
}

bool ListBox::SetSel(INT_PTR iIndex, bool bSel) {

  BOOL bArg = bSel ? TRUE : FALSE;

  return (LB_ERR != SendMsg(LB_SETSEL, bArg, iIndex));
}

bool ListBox::IsItemSelected(INT_PTR iIndex) {

  LONG_PTR lRet = LB_ERR;

  lRet = SendMsg(LB_GETSEL, iIndex, 0L);

  return ((LB_ERR != lRet) && (0L != lRet));
}

LONG_PTR ListBox::GetSelCount(void) {

  return SendMsg(LB_GETSELCOUNT, 0L, 0L);
}

bool ListBox::GetSelItems(std::list<INT_PTR> *pList) {

  bool r = false;

  if (NULL != pList) {

    LONG_PTR lCount = GetSelCount();
    
    if (LB_ERR != lCount) {

      INT_PTR *piItems = new INT_PTR[lCount];

      if (NULL != piItems) {

        LONG_PTR lRet = LB_ERR;
        
        lRet = SendMsg(LB_GETSELITEMS, lCount, 
                       reinterpret_cast<LPARAM>(piItems));

        if (LB_ERR != lRet) {

          pList->clear();

          for (INT_PTR n = 0; n < lRet; n++) {

            pList->push_back(piItems[n]);

          }

          r = true;
        }

        delete[] piItems;
      }

    }

  }

  return r;
}

LONG_PTR ListBox::GetItemTextLen(INT_PTR iIndex) {

  return SendMsg(LB_GETTEXTLEN, iIndex, 0L);
}

bool ListBox::GetItemText(INT_PTR iIndex, TSTRING &tsOut) {

  bool r          = false;
  LONG_PTR lSize  = LB_ERR;

  if (LB_ERR != (lSize = GetItemTextLen(iIndex))) {

    TCHAR *pBuf = new TCHAR[lSize + 1];
    
    if (NULL != pBuf) {

      if (LB_ERR != SendMsg(LB_GETTEXT, iIndex,
                            reinterpret_cast<LPARAM>(pBuf)))
      {

        tsOut = pBuf;
        r     = true;

      }

      delete[] pBuf;
    }

  }

  return r;
}

bool ListBox::SetTopIndex(INT_PTR iIndex) {

  return (LB_ERR != SendMsg(LB_SETTOPINDEX, iIndex, 0L));
}

LONG_PTR ListBox::GetTopIndex(void) {

  return SendMsg(LB_GETTOPINDEX, 0L, 0L);
}

bool ListBox::AllocateMem(DWORD_PTR dwItems, DWORD_PTR dwBytes) {

  return (LB_ERRSPACE != SendMsg(LB_INITSTORAGE, static_cast<WPARAM>(dwItems),
                                 static_cast<LPARAM>(dwBytes)));
}

LONG_PTR ListBox::HitTest(INT_PTR x, INT_PTR y) {

  LONG_PTR r          = LB_ERR;
  DWORD_PTR dwCoords  = MAKEWORD(x, y);
  LONG_PTR lRet       = LB_ERR;
  
  lRet = SendMsg(LB_ITEMFROMPOINT, 0L, static_cast<LPARAM>(dwCoords));

  if (0 == HIWORD(lRet)) {

    r = LOWORD(lRet);

  }

  return r;
}

void ListBox::Clear(void) {

  SendMsg(LB_RESETCONTENT, 0L, 0L);
}

LONG_PTR ListBox::SelectString(CTSTRING &tsFind, INT_PTR iStart) {

  return SelectString(tsFind.c_str(), iStart);
}

LONG_PTR ListBox::SelectString(const void *pFind, INT_PTR iStart) {

  return SendMsg(LB_SELECTSTRING, iStart, reinterpret_cast<LPARAM>(pFind));
}

bool ListBox::SelectRange(INT_PTR iStart, INT_PTR iEnd, bool bSelect) {

  BOOL bArg = bSelect ? TRUE : FALSE;

  DWORD_PTR dwRange = MAKEWORD(iStart, iEnd);

  return (LB_ERR != SendMsg(LB_SELITEMRANGE, bArg, static_cast<LPARAM>(dwRange)));
}
