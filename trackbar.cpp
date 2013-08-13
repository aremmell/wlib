#include "stdafx.h"
#include "trackbar.hpp"

/*
 * TrackBar : public
 */

HWND TrackBar::Create(DWORD_PTR dwStyleEx, DWORD_PTR dwStyle, INT_PTR x, INT_PTR y, INT_PTR cx,
                      INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst)
{
  return Window::Create(dwStyleEx, TRACKBAR_CLASS, _T(""), dwStyle, x, y, cx, cy, hWndParent, iID, hInst);
}

void TrackBar::ClearSelection(bool bRedraw) {

  SendMsg(TBM_CLEARSEL, bRedraw ? TRUE : FALSE, 0L);

}

void TrackBar::ClearTics(bool bRedraw) {

  SendMsg(TBM_CLEARTICS, bRedraw ? TRUE : FALSE, 0L);

}

HWND TrackBar::GetBuddy(INT_PTR iLocation) {

  BOOL fLocation;

  if (0 == iLocation) { fLocation = TRUE; }
  if (1 == iLocation) { fLocation = FALSE; }

  return reinterpret_cast<HWND>(SendMsg(TBM_GETBUDDY, fLocation, 0L));

}

void TrackBar::GetChannelRect(RECT *pRect) {

  if (NULL != pRect) {

    SendMsg(TBM_GETCHANNELRECT, 0L, reinterpret_cast<LPARAM>(pRect));

  }

}

LONG_PTR TrackBar::GetLineSize(void) {

  return SendMsg(TBM_GETLINESIZE, 0L, 0L);
}

LONG_PTR TrackBar::GetNumTics(void) {

  return SendMsg(TBM_GETNUMTICS, 0L, 0L);
}

LONG_PTR TrackBar::GetPageSize(void) {

  return SendMsg(TBM_GETPAGESIZE, 0L, 0L);
}

LONG_PTR TrackBar::GetPos(void) {

  return SendMsg(TBM_GETPOS, 0L, 0L);
}

DWORD_PTR *TrackBar::GetPTics(void) {

  return reinterpret_cast<DWORD_PTR *>(SendMsg(TBM_GETPTICS, 0L, 0L));
}

LONG_PTR TrackBar::GetRangeMax(void) {

  return SendMsg(TBM_GETRANGEMAX, 0L, 0L);
}

LONG_PTR TrackBar::GetRangeMin(void) {

  return SendMsg(TBM_GETRANGEMIN, 0L, 0L);
}

LONG_PTR TrackBar::GetSelEnd(void) {

  return SendMsg(TBM_GETSELEND, 0L, 0L);
}

LONG_PTR TrackBar::GetSelStart(void) {

  return SendMsg(TBM_GETSELSTART, 0L, 0L);
}

LONG_PTR TrackBar::GetThumbLength(void) {

  return SendMsg(TBM_GETTHUMBLENGTH, 0L, 0L);

}

void TrackBar::GetThumbRect(RECT *pRect) {

  if (NULL != pRect) {

    SendMsg(TBM_GETTHUMBRECT, 0L, reinterpret_cast<LPARAM>(pRect));

  }

}

LONG_PTR TrackBar::GetTic(INT_PTR iIndex) {

  return SendMsg(TBM_GETTIC, iIndex, 0L);
}

LONG_PTR TrackBar::GetTicPos(INT_PTR iIndex) {

  return SendMsg(TBM_GETTICPOS, iIndex, 0L);
}

HWND TrackBar::GetToolTips(void) {

  return reinterpret_cast<HWND>(SendMsg(TBM_GETTOOLTIPS, 0L, 0L));
}

bool TrackBar::GetUnicodeFormat(void) {

  return (SendMsg(TBM_GETUNICODEFORMAT, 0L, 0L) != 0L ? true : false);
}

bool TrackBar::SetBuddy(HWND hWndBuddy, INT_PTR iLocation) {

  bool r = false;

  if (::IsWindow(hWndBuddy)) {

    BOOL fLocation;

    if (0 == iLocation) { fLocation = TRUE; }
    if (1 == iLocation) { fLocation = FALSE; }

    SendMsg(TBM_SETBUDDY, fLocation, reinterpret_cast<LPARAM>(hWndBuddy));

    r = true;

  }

  return r;
}

LONG_PTR TrackBar::SetLineSize(INT_PTR iLineSize) {

  return SendMsg(TBM_SETLINESIZE, 0L, iLineSize);
}

LONG_PTR TrackBar::SetPageSize(INT_PTR iPageSize) {

  return SendMsg(TBM_SETPAGESIZE, 0L, iPageSize);
}

void TrackBar::SetPos(INT_PTR iPos, bool bRedraw) {

  SendMsg(TBM_SETPOS, bRedraw ? TRUE : FALSE, iPos);

}

void TrackBar::SetRange(WORD wMax, WORD wMin, bool bRedraw) {

  SendMsg(TBM_SETRANGE, bRedraw ? TRUE : FALSE, MAKELPARAM(wMin, wMax));

}

void TrackBar::SetRangeMax(LONG_PTR lMax, bool bRedraw) {

  SendMsg(TBM_SETRANGEMAX, bRedraw ? TRUE : FALSE, lMax);

}

void TrackBar::SetRangeMin(LONG_PTR lMin, bool bRedraw) {

  SendMsg(TBM_SETRANGEMIN, bRedraw ? TRUE : FALSE, lMin);

}

void TrackBar::SetSel(WORD wStart, WORD wEnd, bool bRedraw) {

  SendMsg(TBM_SETSEL, bRedraw ? TRUE : FALSE, MAKELPARAM(wStart, wEnd));

}

void TrackBar::SetSelEnd(LONG_PTR lEnd, bool bRedraw) {

  SendMsg(TBM_SETSELEND, bRedraw ? TRUE : FALSE, lEnd);

}

void TrackBar::SetSelStart(LONG_PTR lStart, bool bRedraw) {

  SendMsg(TBM_SETSELSTART, bRedraw ? TRUE : FALSE, lStart);

}

void TrackBar::SetThumbLength(UINT_PTR uiLen) {

  SendMsg(TBM_SETTHUMBLENGTH, static_cast<WPARAM>(uiLen), 0L);

}

bool TrackBar::SetTic(LONG_PTR lPos) {

  return WND_TRUE(SendMsg(TBM_SETTIC, 0L, lPos));
}

void TrackBar::SetTicFreq(WORD wFreq) {

  SendMsg(TBM_SETTICFREQ, static_cast<WPARAM>(wFreq), 0L);
}

LONG_PTR TrackBar::SetTipSide(INT_PTR iLocation) {

  return SendMsg(TBM_SETTIPSIDE, iLocation, 0L);
}

void TrackBar::SetToolTips(HWND hWndTooltip) {

  if (::IsWindow(hWndTooltip)) {

    SendMsg(TBM_SETTOOLTIPS, reinterpret_cast<WPARAM>(hWndTooltip), 0L);

  }

}

LONG_PTR TrackBar::SetUnicodeFormat(bool bUnicode) {

  return SendMsg(TBM_SETUNICODEFORMAT, bUnicode ? TRUE : FALSE, 0L);
}
