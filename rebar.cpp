#include "stdafx.h"
#include "rebar.hpp"

bool Rebar::Create(HWND hWndParent, INT_PTR iCtlID, UINT_PTR fStyle) {

  REBARINFO re = {0};

  Window::Create(WS_EX_TOOLWINDOW,
           REBARCLASSNAME,
           _T(""),
           fStyle,
           0, 0, 0, 0,
           hWndParent,
           iCtlID);

  if (NULL == m_hWnd) { return false; }

  re.cbSize = sizeof(REBARINFO);
  re.fMask  = 0U;
  re.himl   = (HIMAGELIST)NULL;

  if (0 == SendMsg(RB_SETBARINFO, 0, (LPARAM)&re)) {

    return false;

  }

  return true;
}

bool Rebar::AddBand(PREBARBAND prb) {

  bool r            = false;
  REBARBANDINFO rbi = {0};

  if (NULL != prb) {

    rbi.cbSize     = sizeof(REBARBANDINFO);
    rbi.cch        = prb->tsText.size() * sizeof(TCHAR);
    rbi.clrBack    = prb->rgbBack;
    rbi.clrFore    = prb->rgbFore;
    rbi.cx         = prb->cx;
    rbi.cxIdeal    = prb->mincx;
    rbi.cxMinChild = prb->mincx;
    rbi.cyChild    = prb->mincy;
    rbi.cyIntegral = 0U;
    rbi.cyMaxChild = prb->maxcy;
    rbi.cyMinChild = prb->mincy;
    rbi.fMask      = prb->fMask;
    rbi.fStyle     = prb->fStyle;
    rbi.hbmBack    = NULL;
    rbi.hwndChild  = prb->hChild;
    rbi.iImage     = 0;
    rbi.lParam     = 0L;
    rbi.lpText     = const_cast<PTSTR>(prb->tsText.c_str());
    rbi.wID        = prb->iID;
    rbi.cxHeader   = prb->headercx;

    if (0L != SendMsg(RB_INSERTBAND, prb->index, reinterpret_cast<LPARAM>(&rbi))) {

      r = true;

    }

  }

  return r;
}

bool Rebar::RemBand(INT_PTR iBand) {

  return (0L != SendMsg(RB_DELETEBAND, iBand, 0L) ? true : false);
}

bool Rebar::AddBandWithControl(HWND hControl, INT_PTR iHeader, bool bNewLine) {

  REBARBAND rb;
  bool r = false;

  if (::IsWindow(hControl)) {

    WINDOWING w;

    GetWindowCoords(hControl, &w);

    rb.cx       = w.iWidth;
    rb.fMask    = RBBIM_CHILD | RBBIM_STYLE | RBBIM_SIZE | 
                  RBBIM_CHILDSIZE | RBBIM_HEADERSIZE;
    rb.fStyle   = RBBS_GRIPPERALWAYS | RBBS_CHILDEDGE;
    bNewLine    ? rb.fStyle |= RBBS_BREAK : 0;
    rb.hChild   = hControl;
    rb.index    = -1;
    rb.mincx    = w.iWidth;
    rb.mincy    = w.iHeight;
    rb.maxcy    = rb.mincy;
    rb.headercx = iHeader;

    if (AddBand(&rb)) {

      r = true;

    }

  }
  
  return r;
}

bool Rebar::GetBarInfo(LPREBARINFO pri) {
  
  bool r = false;

  if (NULL != pri) {

    if (0L != SendMsg(RB_GETBARINFO, 0L, reinterpret_cast<LPARAM>(pri))) {

      r = true;

    }

  }

  return r;
}

UINT_PTR Rebar::BandCount(void) {

  return (UINT_PTR)SendMsg(RB_GETBANDCOUNT, 0L, 0L);
}

bool Rebar::SetBandInfo(INT_PTR iBand, LPREBARBANDINFO prbi) {
  
  bool r = false;

  if (NULL != prbi) {

    if (0L != SendMsg(RB_SETBANDINFO, iBand, (LPARAM)prbi)) {

      r = true;

    }

  }

  return r;
}

bool Rebar::GetBandInfo(INT_PTR iBand, LPREBARBANDINFO prbi) {
  
  bool r = false;

  if (NULL != prbi) {

    if (0L != SendMsg(RB_GETBANDINFO, iBand, reinterpret_cast<LPARAM>(prbi))) {

      r = true;

    }

  }

  return r;
}

INT_PTR Rebar::IndexFromID(INT_PTR iID) {

  return SendMsg(RB_IDTOINDEX, iID, 0L);
}

bool Rebar::ShowBand(INT_PTR iBand, bool bShow) {

  BOOL bArg = bShow ? TRUE : FALSE;

  return (0L != SendMsg(RB_SHOWBAND, iBand, bArg ? true : false));
}
