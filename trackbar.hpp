#ifndef _TRACKBAR_H
#define _TRACKBAR_H

#include "window.hpp"

class TrackBar : public Window {

public:
  TrackBar() {}
  virtual ~TrackBar() {}

  // Creates the trackbar
  HWND Create(DWORD_PTR dwStyleEx, DWORD_PTR dwStyle, INT_PTR x, INT_PTR y, 
              INT_PTR cx, INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst = NULL);

  // Clears the selection range for the trackbar
  void ClearSelection(bool bRedraw = true);

  // Removes tic-marks from the trackbar
  void ClearTics(bool bRedraw = true);

  // Retrieves the handle of the trackbar's buddy window
  // Set iLocation to 0 to retrieve the left/top buddy,
  // or 1 for right/bottom buddy
  HWND GetBuddy(INT_PTR iLocation);

  // Retreives the size and position of the bounding
  // rectangle for the trackbar's channel
  void GetChannelRect(RECT *pRect);

  // Retrieves the number of logical positions the 
  // trackbar's slider moves in response to keyboard input
  LONG_PTR GetLineSize(void);

  // Returns the number of tic marks on the trackbar
  LONG_PTR GetNumTics(void);

  // Retreives the number of logical positions the slider
  // moves in response to clicks on the channel area
  LONG_PTR GetPageSize(void);

  // Returns the location of the slider on the trackbar
  LONG_PTR GetPos(void);

  // Returns an array of tic-mark locations on the trackbar
  DWORD_PTR *GetPTics(void);

  // Retrieves the maximum position for the slider
  LONG_PTR GetRangeMax(void);

  // Retrieves the minimum position for the slider
  LONG_PTR GetRangeMin(void);

  // Retrieves the ending position of a selection on the trackbar
  LONG_PTR GetSelEnd(void);

  // Retrieves the starting position of a selection on the trackbar
  LONG_PTR GetSelStart(void);

  // Retrieves the length of the slider on the trackbar
  LONG_PTR GetThumbLength(void);

  // Retrieves the rectangle for the slider on the trackbar
  void GetThumbRect(RECT *pRect);

  // Returns the logical position of a tic mark, given the index.
  // returns the position or -1 if an error occurs
  LONG_PTR GetTic(INT_PTR iIndex);

  // Returns the physical position of a tic mark, given the index.
  // returns the position or -1 if an error occurs
  LONG_PTR GetTicPos(INT_PTR iIndex);

  // Returns the handle of the tooltip control associated
  // with the trackbar, if any. Returns NULL if no tooltip
  // is associated
  HWND GetToolTips(void);

  // Determines whether or not the trackbar is using unicode
  bool GetUnicodeFormat(void);

  // Sets a buddy window for the trackbar
  // Set iLocation to 0 for left/top buddy location,
  // or 1 for right/bottom
  bool SetBuddy(HWND hWndBuddy, INT_PTR iLocation);

  // Sets the number of logical positions the slider moves
  // as a result of keyboard input
  // Returns the old line size
  LONG_PTR SetLineSize(INT_PTR iLineSize);

  // Sets the number of logical positions the slider
  // moves in response to clicks on the channel area
  // Returns the old page size
  LONG_PTR SetPageSize(INT_PTR iPageSize);

  // Sets the logical position of the slider
  void SetPos(INT_PTR iPos, bool bRedraw = true);

  // Sets the range of minimum and maximum logical
  // positions for the slider
  void SetRange(WORD wMax, WORD wMin, bool bRedraw = true);

  // Sets the maximum logical position for the slider
  void SetRangeMax(LONG_PTR lMax, bool bRedraw = true);

  // Sets the minimum logical position for the slider
  void SetRangeMin(LONG_PTR lMin, bool bRedraw = true);

  // Sets the starting and ending positions for a selection
  // on the trackbar
  void SetSel(WORD wStart, WORD wEnd, bool bRedraw = true);

  // Sets the ending logical position of an existing selection
  // on the trackbar
  void SetSelEnd(LONG_PTR lEnd, bool bRedraw = true);

  // Sets the starting logical position of an existing selection
  // on the trackbar
  void SetSelStart(LONG_PTR lStart, bool bRedraw = true);

  // Sets the length of the slider on the trackbar
  void SetThumbLength(UINT_PTR uiLen);

  // Sets a tic mark on the trackbar at the specified
  // logical location
  bool SetTic(LONG_PTR lPos);

  // Sets the frequency interval for tic marks on the trackbar
  void SetTicFreq(WORD wFreq);

  // Positions a tooltip control used by the trackbar.
  // See PSDK for list of valid parameters
  // Returns the tooltip's previous location
  LONG_PTR SetTipSide(INT_PTR iLocation);

  // Sets the tooltip associated with the trackbar
  void SetToolTips(HWND hWndTooltip);

  // Sets the unicode character flag for the trackbar
  // Returns the previous flag
  LONG_PTR SetUnicodeFormat(bool bUnicode);

};

#endif // !_TRACKBAR_H
