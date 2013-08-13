#ifndef _SPLITTER_H
#define _SPLITTER_H

#include "window.hpp"
#include "collection.hpp"

enum SplitterOrientation {

  SO_HORZ = 0,
  SO_VERT

};

typedef struct tagSPLITTERSTRUCT {

  tagSPLITTERSTRUCT() {
    hWndParent  = NULL;
    x           = 0;
    y           = 0;
    cx          = 0;
    cy          = 0;
    Orientation = SO_VERT;
    iCtlID      = 0;
    iMaxExtent  = 0;
  }

  tagSPLITTERSTRUCT &operator=(const tagSPLITTERSTRUCT &in) {

    hWndParent  = in.hWndParent;
    x           = in.x;
    y           = in.y;
    cx          = in.cx;
    cy          = in.cy;
    Orientation = in.Orientation;
    iCtlID      = in.iCtlID;
    iMaxExtent  = in.iMaxExtent;

    return (*this);
  }

  HWND hWndParent;
  INT_PTR x;
  INT_PTR y;
  INT_PTR cx;
  INT_PTR cy;
  SplitterOrientation Orientation;
  INT_PTR iCtlID;
  INT_PTR iMaxExtent;

} SPLITTERSTRUCT, *PSPLITTERSTRUCT;

enum SplitterDataType {

  SDT_LOAWINDOW = 0,
  SDT_ROBWINDOW,
  SDT_LPIXEL,
  SDT_TPIXEL,
  SDT_RPIXEL,
  SDT_BPIXEL,
  SDT_LWINDOW,
  SDT_TWINDOW,
  SDT_RWINDOW,
  SDT_BWINDOW,
  SDT_INVALIDTYPE

};

typedef struct tagSPLITTERDATA {

  tagSPLITTERDATA() {

    Type  = SDT_INVALIDTYPE;
    Val   = 0;
    hWnd  = NULL;

  }

  tagSPLITTERDATA &operator=(const tagSPLITTERDATA &in) {

    Type  = in.Type;
    Val   = in.Val;
    hWnd  = in.hWnd;

    return (*this);
  }

  SplitterDataType Type;
  INT_PTR Val;
  HWND hWnd;

} SPLITTERDATA, *PSPLITTERDATA;

//
// Data collection class
//
class SplitDataList : public Collection<SPLITTERDATA> {

public:
  INT_PTR LeftBorder(void);
  INT_PTR TopBorder(void);
  INT_PTR RightBorder(void);
  INT_PTR BottomBorder(void);

  enum EnumType {

    _LEFTPIXELS = 0,
    _TOPPIXELS,
    _RIGHTPIXELS,
    _BOTTOMPIXELS,
    _LOAWINDOWS,
    _ROBWINDOWS

  };

  bool EnumWindows(EnumType Type, PSPLITTERDATA *ppData);

private:
  bool _Enum(EnumType Type, PSPLITTERDATA *ppOut);
  INT_PTR _Border(EnumType Type);

};

//
// Splitter Class
//
class Splitter : public Window {

public:
  Splitter() {

    m_bHighlight = false;

  }
  virtual ~Splitter() { }

  HWND Create(PSPLITTERSTRUCT pss);

  bool AddWindow(HWND hWnd, SplitterDataType Type);
  bool AddWindow(PSPLITTERDATA psd);
  bool AddBorderPixels(HWND hWnd, INT_PTR iPixels, SplitterDataType Type);
  bool AddBorderPixels(PSPLITTERDATA psd);

private:
  SplitDataList  m_List;
  SPLITTERSTRUCT  m_State;
  bool m_bHighlight;
  
  //
  // Message Handlers
  //
  LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
  LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
  LRESULT OnCaptureChanged(WPARAM wParam, LPARAM lParam);
  LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
  LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
  LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
  LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);

  bool _IsValidSplitterStruct(PSPLITTERSTRUCT pss);
  bool _IsValidSplitterData(PSPLITTERDATA psd);

  void _Highlight(bool bHighlight);
  bool _Highlighted(void) { return m_bHighlight; }

  bool _Add(PSPLITTERDATA psd);

};

#endif // _SPLITTER_H
