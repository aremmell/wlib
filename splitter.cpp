#include "stdafx.h"
#include "splitter.hpp"
#include "util.hpp"

//
// SplitDataList : Public
//
INT_PTR SplitDataList::LeftBorder(void) {

  return _Border(_LEFTPIXELS);
}

INT_PTR SplitDataList::TopBorder(void) {

  return _Border(_TOPPIXELS);
}

INT_PTR SplitDataList::RightBorder(void) {

  return _Border(_RIGHTPIXELS);
}

INT_PTR SplitDataList::BottomBorder(void) {

  return _Border(_BOTTOMPIXELS);
}

bool SplitDataList::EnumWindows(SplitDataList::EnumType Type, PSPLITTERDATA *ppData) {

  return _Enum(Type, ppData);
}

//
// SplitDataList : Private
//
bool SplitDataList::_Enum(SplitDataList::EnumType Type, PSPLITTERDATA *ppOut) {

  bool f            = false;
  PSPLITTERDATA pD  = NULL;

  while(!f) {

    if (m_Iter == m_List.end()) {

      Reset();
      return false;

    } else {

      pD = &(*m_Iter);

      switch(Type) {

        case _LEFTPIXELS:
          if (pD->Type == SDT_LWINDOW || pD->Type == SDT_LPIXEL) {

            f = true; break;

          }
        break;

        case _TOPPIXELS:
          if (pD->Type == SDT_TWINDOW || pD->Type == SDT_TPIXEL) {

            f = true; break;

          }
        break;

        case _RIGHTPIXELS:
          if (pD->Type == SDT_RWINDOW || pD->Type == SDT_RPIXEL) {

            f = true; break;

          }
        break;

        case _BOTTOMPIXELS:
          if (pD->Type == SDT_BWINDOW || pD->Type == SDT_BPIXEL) {

            f = true; break;

          }
        break;

        case _LOAWINDOWS:
          if (pD->Type == SDT_LOAWINDOW) {

            f = true; break;

          }
        break;

        case _ROBWINDOWS:
          if (pD->Type == SDT_ROBWINDOW) {

            f = true; break;

          }
        break;

      }

    }

    if (f) { *ppOut = &(*m_Iter); }

    m_Iter++;

  }

  return f;
}

INT_PTR SplitDataList::_Border(SplitDataList::EnumType Type) {

  PSPLITTERDATA pData = NULL;
  INT_PTR r           = 0;
  WINDOWING w;

  Reset();

  while(_Enum(Type, &pData)) {

    if (pData->Type == SDT_LWINDOW || pData->Type == SDT_RWINDOW) {

      GetWindowCoords(pData->hWnd, &w);
      r += w.iWidth;

    } else if (pData->Type == SDT_TWINDOW || pData->Type == SDT_BWINDOW) {

      GetWindowCoords(pData->hWnd, &w);
      r += w.iHeight;

    } else {

      r += pData->Val;

    }

  }

  return r;
}

//
// Splitter : Public
//
HWND Splitter::Create(PSPLITTERSTRUCT pss) {

  if (_IsValidSplitterStruct(pss)) {

    Window::Create(0L,
                   _T("STATIC"),
                   _T(""),
                   WS_CHILD | WS_VISIBLE | SS_NOTIFY | WS_CLIPSIBLINGS,
                   pss->x,
                   pss->y,
                   pss->cx,
                   pss->cy,
                   pss->hWndParent,
                   pss->iCtlID);

    if (NULL != m_hWnd) { m_State = *pss; }

  }

  return m_hWnd;
}

bool Splitter::AddWindow(HWND hWnd, SplitterDataType Type) {

  SPLITTERDATA data;

  data.hWnd  = hWnd;
  data.Type  = Type;

  return _Add(&data);
}

bool Splitter::AddWindow(PSPLITTERDATA psd) {

  return _Add(psd);
}

bool Splitter::AddBorderPixels(HWND hWnd, INT_PTR iPixels, SplitterDataType Type) {

  SPLITTERDATA data;

  data.hWnd = hWnd;
  data.Val  = iPixels;
  data.Type = Type;

  return _Add(&data);
}

bool Splitter::AddBorderPixels(PSPLITTERDATA psd) {

  return _Add(psd);
}

//
// Splitter : Private
//
LRESULT Splitter::OnSetCursor(WPARAM wParam, LPARAM lParam) {

  SetCursor(LoadCursor(NULL, (m_State.Orientation == SO_VERT) ? IDC_SIZEWE : IDC_SIZENS));

  return TRUE;
}

LRESULT Splitter::OnLButtonDown(WPARAM wParam, LPARAM lParam) {

  _Highlight(true);

  return Window::OnLButtonDown(wParam, lParam);
}

LRESULT Splitter::OnCaptureChanged(WPARAM wParam, LPARAM lParam) {

  if (reinterpret_cast<HWND>(lParam)!= m_hWnd) {

    _Highlight(false);

  }

  return Window::OnCaptureChanged(wParam, lParam);
}

LRESULT Splitter::OnLButtonUp(WPARAM wParam, LPARAM lParam) {

  _Highlight(false);

  return Window::OnLButtonUp(wParam, lParam);
}

LRESULT Splitter::OnMouseMove(WPARAM wParam, LPARAM lParam) {

  RECT rc               = {0};
  RECT rcClient         = {0};
  POINT pt              = {0};
  INT_PTR iLeftBorder   = m_List.LeftBorder();
  INT_PTR iTopBorder    = m_List.TopBorder();
  INT_PTR iRightBorder  = m_List.RightBorder();
  INT_PTR iBottomBorder = m_List.BottomBorder();
  INT_PTR iMax          = m_State.iMaxExtent;
  PSPLITTERDATA pD      = NULL;
  WINDOWING wcWnd;
  WINDOWING wcSplit;
  WINDOWING wcClient;

  GetCursorPos(&pt);
  ScreenToClient(GetParent(), &pt);

  GetCoords(&wcSplit);
  ::GetClientRect(GetParent(), &rcClient);

  if (_Highlighted()) {

    switch(m_State.Orientation) {

      case SO_VERT:
        if (pt.x >= rcClient.right - wcSplit.iWidth ||
            pt.x <= wcSplit.iWidth)
        {
          break;
        }

        if (pt.x >= rcClient.right - (iRightBorder + iMax) ||
            pt.x <= (iLeftBorder + iMax))
        {
          break;
        }

        MoveWindow(pt.x, wcSplit.rcClient.top, wcSplit.iWidth, wcSplit.iHeight, TRUE);
        GetCoords(&wcSplit);

        m_List.Reset();

        while(m_List.EnumWindows(m_List._LOAWINDOWS, &pD)) {

          GetWindowCoords(pD->hWnd, &wcWnd);
          ::MoveWindow(pD->hWnd, wcWnd.rcClient.left, wcWnd.rcClient.top, 
                wcSplit.rcClient.left - iLeftBorder, wcWnd.iHeight, TRUE);

        }

        m_List.Reset();

        while(m_List.EnumWindows(m_List._ROBWINDOWS, &pD)) {

          GetWindowCoords(pD->hWnd, &wcWnd);
          ::MoveWindow(pD->hWnd, wcSplit.rcClient.right, wcWnd.rcClient.top, 
                (rcClient.right - rcClient.left - wcSplit.rcClient.right) - iRightBorder, 
                wcWnd.iHeight, TRUE );

        }
 
      break;

      case SO_HORZ:

        if (pt.y <= rcClient.top + wcSplit.iHeight 
            || pt.y >= rcClient.bottom - wcSplit.iHeight)
        {
          break;
        }

        if (pt.y <= rcClient.top + (iTopBorder + iMax) ||
            pt.y >= rcClient.bottom - (iBottomBorder + iMax))
        {
          break;
        }

        MoveWindow(0, pt.y, wcSplit.iWidth, wcSplit.iHeight, TRUE);
        GetCoords(&wcSplit);

        m_List.Reset();

        while(m_List.EnumWindows(m_List._LOAWINDOWS, &pD)) {

          GetWindowCoords(pD->hWnd, &wcWnd);
          ::MoveWindow(pD->hWnd, wcWnd.rcClient.left, wcSplit.rcClient.bottom, wcWnd.iWidth, 
                 rcClient.bottom - rcClient.top - iBottomBorder - wcSplit.rcClient.bottom, TRUE);

        }

        m_List.Reset();

        while(m_List.EnumWindows(m_List._ROBWINDOWS, &pD)) {

          GetWindowCoords(pD->hWnd, &wcWnd);
          ::MoveWindow(pD->hWnd, wcWnd.rcClient.left, wcWnd.rcClient.top, wcWnd.iWidth, 
                wcSplit.rcClient.top - iTopBorder, TRUE);

        }

      break;
    }

  }

  return 0L;
}

LRESULT Splitter::OnPaint(WPARAM wParam, LPARAM lParam) {

  PAINTSTRUCT ps   = {0};
  HDC dc           = NULL;
  HBRUSH hBrush    = NULL;
  RECT rc          = {0};

  dc = BeginPaint(m_hWnd, &ps);
  GetClientRect(&rc);

  hBrush = GetSysColorBrush(_Highlighted() ? COLOR_HIGHLIGHT : COLOR_3DFACE);

  FillRect(dc, &rc, hBrush);
  EndPaint(m_hWnd, &ps);

  return 0L;
}

LRESULT Splitter::OnDestroy(WPARAM wParam, LPARAM lParam) {

  m_List.Clear();

  return Window::OnDestroy(wParam, lParam);
}

bool Splitter::_IsValidSplitterStruct(PSPLITTERSTRUCT pss) {

  return (FALSE == ::IsWindow(pss->hWndParent)) ? false : true;
}

bool Splitter::_IsValidSplitterData(PSPLITTERDATA psd) {

  return (psd->Type == SDT_INVALIDTYPE) ? false : true;
}

void Splitter::_Highlight(bool bHighlight) {

  switch(bHighlight) {

    case true:
      if (!_Highlighted()) {

        SetCapture(m_hWnd);
        m_bHighlight = true;
        Refresh();

      }
    break;

    case false:
      if (_Highlighted()) {

        ReleaseCapture();
        m_bHighlight = false;
        Refresh();

      }
    break;

  }

}

bool Splitter::_Add(PSPLITTERDATA psd) {

  bool r = false;

  if (_IsValidSplitterData(psd)) {

    m_List.AddItem(*psd);
    r = true;

  }

  return r;
}
