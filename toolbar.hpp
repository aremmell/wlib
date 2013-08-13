#ifndef _TOOLBAR__H
#define _TOOLBAR__H

#include "window.hpp"
#include "imagelist.hpp"

typedef struct tagTOOLBAR {

  tagTOOLBAR() {

    hWndParent    = NULL;
    hInstance     = NULL;
    iImgWidth     = 0;
    iImgHeight    = 0;
    iBtnWidth     = 0;
    iBtnHeight    = 0;
    fStyle        = 0U;
    iID           = 0;
    x             = 0;
    y             = 0;
    cx            = 0;
    cy            = 0;
    bUseHotImages = false;
    bExtendedVer  = true;

  }

  HWND hWndParent;
  HINSTANCE hInstance;
  INT_PTR iImgWidth;
  INT_PTR iImgHeight;
  INT_PTR iBtnWidth;
  INT_PTR iBtnHeight;
  UINT fStyle;
  INT_PTR iID;
  INT_PTR  x;
  INT_PTR  y;
  INT_PTR cx;
  INT_PTR cy;
  bool bUseHotImages;
  bool bExtendedVer;

} TOOLBAR, *PTOOLBAR;

typedef struct tagTOOLBARBTN {

  tagTOOLBARBTN() {

    iCmd        = -1;
    dwUser      = 0UL;
    tsText      = _T("");
    bAutoSize   = false;
    bCheck      = false;
    bCheckGrp   = false;
    bGroup      = false;
    bDropDown   = false;
    bWholeDrop  = false;
    bShowText   = false;
    bSeparator  = false;
    bHidden     = false;
    bEnabled    = true;

  }

  INT_PTR iCmd;
  IMAGEDATA id;
  IMAGEDATA idHot;
  DWORD_PTR dwUser;
  TSTRING tsText;
  bool bAutoSize;
  bool bCheck;
  bool bCheckGrp;
  bool bGroup;
  bool bDropDown;
  bool bWholeDrop;
  bool bShowText;
  bool bSeparator;
  bool bHidden;
  bool bEnabled;

} TOOLBARBTN, *PTOOLBARBTN;

class Toolbar : public Window {

public:
  Toolbar() { }
  virtual ~Toolbar() { }

  // Creates a toolbar control
  bool Create(PTOOLBAR pt);

  // Adds a button
  bool AddButton(PTOOLBARBTN ptb);
  // Removes a button
  bool RemButton(INT_PTR iID);
  // Enables/disables a button
  bool EnableButton(INT_PTR iID, bool bEnable);
  // Checks/unchecks a button
  bool CheckButton(INT_PTR iCmd, bool bCheck);
  // Hides/shows a button
  bool ShowButton(INT_PTR iCmd, bool bShow);
  // Presses/releases a button
  bool PressButton(INT_PTR iCmd, bool bPress);

  // Determines if a button is checked
  bool IsButtonChecked(INT_PTR iCmd);
  // Determines if a button is enabled
  bool IsButtonEnabled(INT_PTR iCmd);
  // Determines if a button is visible
  bool IsButtonVisible(INT_PTR iCmd);
  // Determines if a button is highlighted
  bool IsButtonHighlighted(INT_PTR iCmd);
  // Determines if a button is pressed
  bool IsButtonPressed(INT_PTR iCmd);

  // Adds a separator
  bool AddSeparator(INT_PTR iID);

  // Causes the toolbar to auto-size
  void AutoSize(void);

  // Returns number of buttons
  INT_PTR ButtonCount(void);

  // Translates a command ID to index
  INT_PTR CommandToIndex(INT_PTR iCmd);

  // Sets the command ID of a button
  bool SetCommandID(INT_PTR iBtn, INT_PTR iCmd);

  // Sets info for a button
  bool SetButtonInfo(INT_PTR iCmd, LPTBBUTTONINFO ptbbi);
  // Gets info for a button
  bool GetButtonInfo(INT_PTR iCmd, LPTBBUTTONINFO ptbbi);

  // Sets the size of the buttons
  bool SetButtonSize(INT_PTR iHeight, INT_PTR iWidth);
  // Gets the size of the buttons
  bool GetButtonSize(INT_PTR *piHeight, INT_PTR *piWidth);

  // Gets the rectangle of a button
  bool GetButtonRect(INT_PTR iBtn, LPRECT prc);

  // Sets the text of a button
  bool SetButtonText(INT_PTR iCmd, CTSTRING &tsText);
  // Gets the text of a button
  bool GetButtonText(INT_PTR iCmd, TSTRING &tsText);

  // Sets the extended styles in use
  DWORD_PTR SetExtendedStyles(DWORD_PTR dwStyles);
  // Gets the extended styles in use
  DWORD_PTR GetExtendedStyles(void);

  // Sets the hot item
  INT_PTR SetHotItem(INT_PTR iBtn);
  // Returns index of hot item
  INT_PTR GetHotItem(void);

  // Sets the image list
  HIMAGELIST SetImageList(HIMAGELIST hList);
  // Sets the hot image list
  HIMAGELIST SetHotImageList(HIMAGELIST hList);
  // Returns the image list
  HIMAGELIST GetImageList(void);
  // Returns the hot image list
  HIMAGELIST GetHotImageList(void);

  // Returns the rectangle of a button
  bool GetItemRect(INT_PTR iBtn, PRECT pRect);

  // Sets the state of a button
  bool SetButtonState(INT_PTR iCmd, DWORD_PTR fState);
  // Retreives the state of a button
  LONG_PTR GetButtonState(INT_PTR iCmd);

protected:
  ImageList  m_ImgList;
  ImageList  m_HotImgList;

};

#endif // _TOOLBAR__H
