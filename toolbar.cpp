#include "stdafx.h"
#include "toolbar.hpp"

bool Toolbar::Create(PTOOLBAR pt) {

  bool r = false;

  if ((NULL != pt) && WND_TRUE(::IsWindow(pt->hWndParent))) {

    Window::Create(0UL, 
                   pt->bExtendedVer ? _T("UNSUPPORTED") : TOOLBARCLASSNAME, 
                   _T(""), 
                   pt->fStyle,
                   pt->x,  
                   pt->y, 
                   pt->cx, 
                   pt->cy,
                   pt->hWndParent, 
                   pt->iID,
                   pt->hInstance);


    if (NULL != m_hWnd) {

      if (m_ImgList.Create(pt->iImgWidth, pt->iImgHeight, ILC_COLOR32 | ILC_MASK, 1, 1, pt->hInstance)) {

        SetImageList(m_ImgList.Handle());

        if (pt->bUseHotImages) {

          if (m_HotImgList.Create(pt->iImgWidth, pt->iImgHeight, ILC_COLOR32 | ILC_MASK, 1, 1, pt->hInstance)) {

            SetHotImageList(m_HotImgList.Handle());

          }

        } else {

          SetHotImageList(m_ImgList.Handle());

        }

        SendMsg(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0L);
        
        if ((0 != pt->iBtnHeight) && (0 != pt->iBtnWidth)) {

          SetButtonSize(pt->iBtnHeight, pt->iBtnWidth);

        }

        r = true;

      }

    }

  }

  return r;
}

bool Toolbar::AddButton(PTOOLBARBTN ptb) {
  
  bool r = false;

  if (NULL != ptb) {

    TBBUTTON tbb    = {0};
    BYTE fStyle     = 0U;
    BYTE fState     = 0U;
    
    if (ptb->id.bUseImg) {

      if (-1 == (tbb.iBitmap = m_ImgList.AddBitmap(ptb->id.Bitmap(), ptb->id.Mask()))) {

        return false;

      }

      if (ptb->idHot.bUseImg) {

        if (-1 == m_HotImgList.AddBitmap(ptb->idHot.Bitmap(), ptb->idHot.Mask())) {

          return false;

        }

      }

    } else {

      tbb.iBitmap = I_IMAGENONE;

    }

    if (ptb->bAutoSize) { fStyle |= BTNS_AUTOSIZE; }

    if (ptb->bCheck) { fStyle |= BTNS_CHECK; }

    if (ptb->bCheckGrp) { fStyle |= BTNS_CHECKGROUP; }

    if (ptb->bDropDown) { fStyle |= BTNS_DROPDOWN; }

    if (ptb->bGroup) { fStyle |= BTNS_GROUP; }

    if (ptb->bShowText) {fStyle |= BTNS_SHOWTEXT; }

    if (ptb->bWholeDrop) { fStyle |= BTNS_WHOLEDROPDOWN; }

    if (ptb->bSeparator) {
      
      fStyle |= BTNS_SEP;

    } else {
      
      fStyle |= BTNS_BUTTON;
    
    }

    if (ptb->bHidden) { fState |= TBSTATE_HIDDEN; }

    if (ptb->bEnabled) { fState |= TBSTATE_ENABLED; }

    tbb.dwData    = ptb->dwUser;
    tbb.fsState   = fState;
    tbb.fsStyle   = fStyle;
    tbb.idCommand = ptb->iCmd;
    tbb.iString   = ((_T("") != ptb->tsText) ? reinterpret_cast<INT_PTR>(ptb->tsText.c_str()) : 0);    

    r =  WND_TRUE(SendMsg(TB_ADDBUTTONS, 1L, reinterpret_cast<LPARAM>(&tbb)));

  }

  return r;
}

bool Toolbar::RemButton(INT_PTR iID) {
  
  bool r          = false;
  LONG_PTR lIndex = -1L;
  
  if (-1L != (lIndex = SendMsg(TB_COMMANDTOINDEX, iID, 0L))) {

    if (SendMsg(TB_DELETEBUTTON, lIndex, 0)) {

      r = true;

    }

  }

  return r;
}

bool Toolbar::EnableButton(INT_PTR iID, bool bEnable) {

  return WND_TRUE(SendMsg(TB_ENABLEBUTTON, iID, bEnable ? TRUE : FALSE));
}

bool Toolbar::AddSeparator(INT_PTR iID) {

  TBBUTTON tb = {0};

  tb.fsState    = TBSTATE_ENABLED;
  tb.fsStyle    = (BYTE)TBSTYLE_SEP;
  tb.idCommand  = iID;

  return WND_TRUE(SendMsg(TB_ADDBUTTONS, 1L, reinterpret_cast<LPARAM>(&tb)));
}

void Toolbar::AutoSize(void) {

  SendMsg(TB_AUTOSIZE, 0L, 0L);
}

INT_PTR Toolbar::ButtonCount(void) {

  return SendMsg(TB_BUTTONCOUNT, 0L, 0L);
}

bool Toolbar::CheckButton(INT_PTR iCmd, bool bCheck) {

  BOOL bArg = bCheck ? TRUE : FALSE;

  return WND_TRUE(SendMsg(TB_CHECKBUTTON, iCmd, bArg));
}

bool Toolbar::ShowButton(INT_PTR iCmd, bool bShow) {

  BOOL bArg = bShow ? FALSE : TRUE;

  return WND_TRUE(SendMsg(TB_HIDEBUTTON, iCmd, bArg));
}

bool Toolbar::IsButtonChecked(INT_PTR iCmd) {

  return (0L != SendMsg(TB_ISBUTTONCHECKED, iCmd, 0L) ? true : false);
}

bool Toolbar::IsButtonEnabled(INT_PTR iCmd) {

  return (0L != SendMsg(TB_ISBUTTONENABLED, iCmd, 0L) ? true : false);
}

bool Toolbar::IsButtonVisible(INT_PTR iCmd) {

  return (0L == SendMsg(TB_ISBUTTONHIDDEN, iCmd, 0L) ? true : false);
}

bool Toolbar::IsButtonHighlighted(INT_PTR iCmd) {

  return (0L != SendMsg(TB_ISBUTTONHIGHLIGHTED, iCmd, 0L) ? true : false);
}

bool Toolbar::IsButtonPressed(INT_PTR iCmd) {

  return (0L != SendMsg(TB_ISBUTTONPRESSED, iCmd, 0L) ? true : false);
}

bool Toolbar::PressButton(INT_PTR iCmd, bool bPress) {
  
  BOOL bArg = bPress ? true : false;

  return WND_TRUE(SendMsg(TB_PRESSBUTTON, iCmd, bArg));
}

INT_PTR Toolbar::CommandToIndex(INT_PTR iCmd) {

  return SendMsg(TB_COMMANDTOINDEX, iCmd, 0L);
}

bool Toolbar::SetCommandID(INT_PTR iBtn, INT_PTR iCmd) {

  return WND_TRUE(SendMsg(TB_SETCMDID, iBtn, iCmd));
}

bool Toolbar::SetButtonInfo(INT_PTR iCmd, LPTBBUTTONINFO ptbbi) {

  bool r = false;

  if (NULL != ptbbi) {

    if (0L != SendMsg(TB_SETBUTTONINFO, iCmd, reinterpret_cast<LPARAM>(ptbbi))) {

      r = true;

    }

  }

  return r;
}

bool Toolbar::GetButtonInfo(INT_PTR iCmd, LPTBBUTTONINFO ptbbi) {

  bool r = false;

  if (NULL != ptbbi) {

    if (-1L != SendMsg(TB_GETBUTTONINFO, iCmd, reinterpret_cast<LPARAM>(ptbbi))) {

      r = true;

    }

  }

  return r;
}

bool Toolbar::SetButtonSize(INT_PTR iHeight, INT_PTR iWidth) {

  return WND_TRUE(SendMsg(TB_SETBUTTONSIZE, 0L, MAKELONG(iWidth, iHeight)));
}

bool Toolbar::GetButtonSize(INT_PTR *piHeight, INT_PTR *piWidth) {

  bool r = false;
  
  if (NULL != piHeight && NULL != piWidth) {

    DWORD_PTR dwRet = SendMsg(TB_GETBUTTONSIZE, 0L, 0L);

    *piHeight = HIWORD(dwRet);
    *piWidth  = LOWORD(dwRet);
    r         = true;

  }

  return r;
}

bool Toolbar::GetButtonRect(INT_PTR iBtn, LPRECT prc) {

  return WND_TRUE(SendMsg(TB_GETITEMRECT, iBtn, reinterpret_cast<LPARAM>(prc)));
}

bool Toolbar::SetButtonText(INT_PTR iCmd, CTSTRING &tsText) {

  TBBUTTONINFO bi = {0};

  bi.cbSize   = sizeof(TBBUTTONINFO);
  bi.dwMask   = TBIF_TEXT;
  bi.pszText  = const_cast<PTSTR>(tsText.c_str());

  return SetButtonInfo(iCmd, &bi);
}

bool Toolbar::GetButtonText(INT_PTR iCmd, TSTRING &tsText) {

  bool r          = false;
  LONG_PTR lSize  = SendMsg(TB_GETBUTTONTEXT, iCmd, NULL);

  if (-1L != lSize) {

    TCHAR *pBuf = new TCHAR[lSize];

    if (NULL != pBuf) {

      LONG_PTR lRet = SendMsg(TB_GETBUTTONTEXT, iCmd, (LPARAM)pBuf);

      if (-1L != lRet) {

        tsText  = pBuf;
        r       = true;

      }

      delete[] pBuf;
    }

  }

  return r;
}

DWORD_PTR Toolbar::SetExtendedStyles(DWORD_PTR dwStyles) {

  return (DWORD_PTR)SendMsg(TB_SETEXTENDEDSTYLE, 0L, static_cast<LPARAM>(dwStyles));
}

DWORD_PTR Toolbar::GetExtendedStyles(void) {

  return (DWORD_PTR)SendMsg(TB_GETEXTENDEDSTYLE, 0L, 0L);
}

INT_PTR Toolbar::SetHotItem(INT_PTR iBtn) {

  return SendMsg(TB_SETHOTITEM, iBtn, 0L);
}

INT_PTR Toolbar::GetHotItem(void) {

  return SendMsg(TB_GETHOTITEM, 0L, 0L);
}

HIMAGELIST Toolbar::SetImageList(HIMAGELIST hList) {

  return reinterpret_cast<HIMAGELIST>(SendMsg(TB_SETIMAGELIST, 0, reinterpret_cast<LPARAM>(hList)));
}

HIMAGELIST Toolbar::SetHotImageList(HIMAGELIST hList) {
  return reinterpret_cast<HIMAGELIST>(SendMsg(TB_SETHOTIMAGELIST, 0, reinterpret_cast<LPARAM>(hList)));
}

HIMAGELIST Toolbar::GetImageList(void) {

  return reinterpret_cast<HIMAGELIST>(SendMsg(TB_GETIMAGELIST, 0L, 0L));
}

HIMAGELIST Toolbar::GetHotImageList(void) {

  return reinterpret_cast<HIMAGELIST>(SendMsg(TB_GETHOTIMAGELIST, 0L, 0L));
}

bool Toolbar::GetItemRect(INT_PTR iBtn, PRECT pRect) {

  bool r = false;

  if (NULL != pRect) {

    if (TRUE == SendMsg(TB_GETITEMRECT, iBtn, reinterpret_cast<LPARAM>(pRect))) {

      r = true;

    }

  }

  return r;
}

bool Toolbar::SetButtonState(INT_PTR iCmd, DWORD_PTR fState) {

  return WND_TRUE(SendMsg(TB_SETSTATE, iCmd, MAKELONG(fState, 0L)));
}

LONG_PTR Toolbar::GetButtonState(INT_PTR iCmd) {

  return SendMsg(TB_GETSTATE, iCmd, 0L);
}
