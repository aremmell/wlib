#ifndef _REBAR_H
#define _REBAR_H

#include "window.hpp"

typedef struct tagREBARBAND {

  tagREBARBAND() {

    fMask     = 0U;
    fStyle    = 0U;
    tsText    = _T("");
    hChild    = NULL;
    rgbBack   = 0UL;
    rgbFore   = 0UL;
    iID       = 0;
    cx        = 0;
    mincy     = 0;
    mincx     = 0;
    maxcy     = 0;
    headercx  = 0;
    index     = 0;

  }

  UINT_PTR fMask;   // Bitmask
  UINT_PTR fStyle;  // Style bitmask
  TSTRING tsText;   // Text
  HWND hChild;      // Handle of child control
  COLORREF rgbBack; // Background colour
  COLORREF rgbFore; // Foreground colour
  INT_PTR iID;      // ID for customdraw notifications.
  INT_PTR cx;       // Width of band
  INT_PTR mincy;    // Minimum height of band
  INT_PTR mincx;    // Minimum width of band
  INT_PTR maxcy;    // Maximum height of band
  INT_PTR headercx; // Width of header area
  INT_PTR  index;   // -1 for last item

} REBARBAND, *PREBARBAND;

class Rebar : public Window {

public:
  Rebar() { }
  virtual ~Rebar() { }

  // Creates the control
  bool Create(HWND hWndParent, INT_PTR iCtlID, UINT_PTR fStyle);

  // Adds a band
  bool AddBand(PREBARBAND prb);
  // Removes a band
  bool RemBand(INT_PTR iBand);

  // Adds a band with a control on it
  bool AddBandWithControl(HWND hControl,  INT_PTR iHeader, bool bNewLine);

  // Gets info about the rebar
  bool GetBarInfo(LPREBARINFO pri);

  // Returns the count of bands
  UINT_PTR BandCount(void);

  // Sets info for a band
  bool SetBandInfo(INT_PTR iBand, LPREBARBANDINFO prbi);
  // Retrieves info of a band
  bool GetBandInfo(INT_PTR iBand, LPREBARBANDINFO prbi);

  // Translates an identifier to an index
  INT_PTR IndexFromID(INT_PTR iID);

  // Shows/Hides a band
  bool ShowBand(INT_PTR iBand, bool bShow);

};

#endif // _REBAR_H
