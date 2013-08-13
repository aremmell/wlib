#include "stdafx.h"
#include "combobox.hpp"

/*
 * ComboBox : Public
 */
HWND ComboBox::Create(DWORD_PTR dwStyleEx, CTSTRING &tsTitle, DWORD_PTR dwStyle,
                      INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy,
                      HWND hWndParent, INT_PTR iID, HINSTANCE hInst)
{
  return Window::Create(dwStyleEx, _T("COMBOBOX"), tsTitle, dwStyle, x, y, cx, cy, hWndParent, iID, hInst);
}

bool ComboBox::AddString(CTSTRING &tsStr) {

  bool r = false;

  if (0 < tsStr.size()) {

    LONG_PTR lResult = SendMsg(CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(tsStr.c_str()));

    if ((CB_ERR != lResult) && (CB_ERRSPACE != lResult)) {

      r = true;

    }

  }

  return r;
}

bool ComboBox::DelString(INT_PTR iIndex) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_DELETESTRING, iIndex, 0L)) {

    r = true;

  }

  return r;
}

INT_PTR ComboBox::FindString(CTSTRING &tsSearch) {
 
  return SendMsg(CB_FINDSTRING, -1L, reinterpret_cast<LPARAM>(tsSearch.c_str()));
}

INT_PTR ComboBox::FindStringExact(CTSTRING &tsSearch) {

  return SendMsg(CB_FINDSTRINGEXACT, -1L, reinterpret_cast<LPARAM>(tsSearch.c_str()));
}

#if (_WIN32_IE >= 0x560)

bool ComboBox::GetComboBoxInfo(PCOMBOBOXINFO pcbi) {

  bool r = false;

  if (NULL != pcbi) {

    if (0 != SendMsg(CB_GETCOMBOBOXINFO, 0L, reinterpret_cast<LPARAM>(pcbi))) {

      r = true;

    }

  }

  return r;
}
#endif

INT_PTR ComboBox::GetCount(void) {
  
  return SendMsg(CB_GETCOUNT, 0L, 0L);
}

INT_PTR ComboBox::GetCurSel(void) {

  return SendMsg(CB_GETCURSEL, 0L, 0L);
}

INT_PTR ComboBox::GetDroppedWidth(void) {

  return SendMsg(CB_GETDROPPEDWIDTH, 0L, 0L);
}

bool ComboBox::IsDroppedDown(void) {
  
  return WND_TRUE(SendMsg(CB_GETDROPPEDSTATE, 0L, 0L));
}

bool ComboBox::GetEditSel(DWORD_PTR *pStart, DWORD_PTR *pEnd) {

  bool r = false;

  if ((NULL != pStart) && (NULL != pEnd)) {

    SendMsg(CB_GETEDITSEL, reinterpret_cast<WPARAM>(pStart), reinterpret_cast<LPARAM>(pEnd));

    r = true;
  }

  return r;
}

LONG_PTR ComboBox::GetItemData(INT_PTR iItem) {

  return SendMsg(CB_GETITEMDATA, iItem, 0L);
}

INT_PTR ComboBox::GetItemHeight(INT_PTR iItem) {

  return SendMsg(CB_GETITEMHEIGHT, iItem, 0L);
}

bool ComboBox::GetItemText(INT_PTR iItem, TSTRING &tsText) {

  bool r = false;

  LONG_PTR lSize = GetItemTextLen(iItem);

  if (CB_ERR != lSize) {

    TCHAR *szBuf = new TCHAR[lSize + 1];

    if (NULL != szBuf) {

      ZeroMemory(szBuf, lSize + 1);

      if (CB_ERR != SendMsg(CB_GETLBTEXT, iItem, reinterpret_cast<LPARAM>(szBuf))) {

        tsText = szBuf;
        r      = true;

      }

      delete szBuf;
    }

  }


  return r;
}

INT_PTR ComboBox::GetItemTextLen(INT_PTR iItem) {

  return SendMsg(CB_GETLBTEXTLEN, iItem, 0L);
}

DWORD_PTR ComboBox::GetLocale(void) {

  return static_cast<DWORD_PTR>(SendMsg(CB_GETLOCALE, 0L, 0L));
}

#if (_WIN32_IE >= 0x560)

INT_PTR ComboBox::GetMinVisible(void) {

  return SendMsg(CB_GETMINVISIBLE, 0L, 0L);
}

#endif

INT_PTR ComboBox::GetTopIndex(void) {

  return SendMsg(CB_GETTOPINDEX, 0L, 0L);
}

bool ComboBox::InitStorage(DWORD_PTR dwItems, DWORD_PTR dwBytes) {

  bool r = false;

  if (CB_ERRSPACE != SendMsg(CB_INITSTORAGE, static_cast<WPARAM>(dwItems),
                             static_cast<LPARAM>(dwBytes)))
  {

    r = true;

  }

  return r;
}

bool ComboBox::InsertString(CTSTRING &tsItem, INT_PTR iIndex) {

  bool r = false;

  LONG_PTR lResult = SendMsg(CB_INSERTSTRING, iIndex,
                             reinterpret_cast<LPARAM>(tsItem.c_str()));

  if ((CB_ERR != lResult) && (CB_ERRSPACE != lResult)) {

    r = true;

  }

  return r;
}

void ComboBox::LimitText(INT_PTR iChars) {

  SendMsg(CB_LIMITTEXT, iChars, 0L);
}

void ComboBox::ResetContent(void) {

  SendMsg(CB_RESETCONTENT, 0L, 0L);
}

bool ComboBox::SelectString(CTSTRING &tsSearch) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SELECTSTRING, -1L, reinterpret_cast<LPARAM>(tsSearch.c_str()))) {

    r = true;

  }

  return r;
}

bool ComboBox::SetCurSel(INT_PTR iItem) {

  bool r = false;

  LONG_PTR lResult = SendMsg(CB_SETCURSEL, iItem, 0L);

  if ((-1 == iItem) || (GetCount() < iItem)) {

    r = true;

  } else {

    if (CB_ERR != lResult) {

      r = true;

    }

  }

  return r;
}

bool ComboBox::SetDroppedWidth(DWORD_PTR dwWidth) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETDROPPEDWIDTH, static_cast<WPARAM>(dwWidth), 0L)) {

    r = true;

  }

  return r;
}

bool ComboBox::SetEditSel(WORD wStart, WORD wEnd) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETEDITSEL, MAKEWPARAM(wStart, wEnd), 0L)) {

    r = true;

  }

  return r;
}

bool ComboBox::SetItemData(INT_PTR iItem, DWORD_PTR dwData) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETITEMDATA, iItem, static_cast<LPARAM>(dwData))) {

    r = true;

  }

  return r;
}

bool ComboBox::SetItemHeight(INT_PTR iHeight, INT_PTR iItem) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETITEMHEIGHT, iItem, iHeight)) {

    r = true;

  }

  return r;
}

bool ComboBox::SetLocale(DWORD_PTR dwLocale) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETLOCALE, static_cast<WPARAM>(dwLocale), 0)) {

    r = true;

  }

  return r;
}

#if (_WIN32_IE >= 0x560)

bool ComboBox::SetMinVisible(DWORD_PTR dwItems) {

  return WND_TRUE(SendMsg(CB_SETMINVISIBLE, static_cast<WPARAM>(dwItems), 0));
}

#endif

bool ComboBox::SetTopIndex(INT_PTR iItem) {

  bool r = false;

  if (CB_ERR != SendMsg(CB_SETTOPINDEX, iItem, 0L)) {

    r = true;

  }

  return r;
}

void ComboBox::ShowDropdown(bool bShow) {

  SendMsg(CB_SHOWDROPDOWN, bShow ? TRUE : FALSE, 0L);
}
