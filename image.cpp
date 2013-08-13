#include "stdafx.h"
#include "image.hpp"

//
// IMAGEDATA : Public Functions
//
HBITMAP IMAGEDATA::Bitmap(void) {

  if (bUseImg && (Type == IDT_BITMAP)) {

    _ID id;
    _Gip(_GIP_BMP, &id);

    if ((0 != id.pImg)) {

      return static_cast<HBITMAP>(_LoadImg(id.pImg, IMAGE_BITMAP, id.uiFlag));

    } else {

      return hBmp;

    }

  }

  return static_cast<HBITMAP>(NULL);
}

HBITMAP IMAGEDATA::Mask(void) {

  if ((bUseImg && bUseMask) && (Type == IDT_BITMAP)) {

    _ID id;
    _Gip(_GIP_MASK, &id);

    if ((0 != id.pImg)) {

      return static_cast<HBITMAP>(_LoadImg(id.pImg, IMAGE_BITMAP, id.uiFlag));

    } else {

      return hMask;

    }

  }

  return static_cast<HBITMAP>(NULL);
}

HICON IMAGEDATA::Icon(void) {

  if (bUseImg && (Type == IDT_ICON)) {

    _ID id;
    _Gip(_GIP_ICO, &id);

    if ((0 != id.pImg)) {

      return static_cast<HICON>(_LoadImg(id.pImg, IMAGE_ICON, id.uiFlag));

    } else {

      return hIcon;

    }

  }

  return static_cast<HICON>(NULL);
}

HCURSOR IMAGEDATA::Cursor(void) {

  if (bUseImg && (Type == IDT_CURSOR)) {

    _ID id;
    _Gip(_GIP_CUR, &id);

    if ((0 != id.pImg)) {

      return static_cast<HCURSOR>(_LoadImg(id.pImg, IMAGE_CURSOR, id.uiFlag));

    } else {

      return hCur;

    }

  }
  
  return static_cast<HCURSOR>(NULL);
}

void IMAGEDATA::Reset(void) {

  bUseImg   = false;
  bUseMask  = false;
  cx        = 0L;
  cy        = 0L;
  Type      = IDT_NOTSET;
  Src       = IDS_NOTSET;
  hBmp      = NULL;
  hMask     = NULL;
  hIcon     = NULL;
  hCur      = NULL;
  tsBmp     = _T("");
  tsMask    = _T("");
  tsIcon    = _T("");
  tsCur     = _T("");
  iBmp      = 0L;
  iMask     = 0L;
  iIcon     = 0L;
  iCur      = 0L;
  hMod      = NULL;

}

bool IMAGEDATA::IsBitmap(void) {

  return (Type == IDT_BITMAP);
}

bool IMAGEDATA::HasMask(void) {

  return bUseMask;
}

bool IMAGEDATA::IsIcon(void) {

  return (Type == IDT_ICON);
}

bool IMAGEDATA::IsCursor(void) {

  return (Type == IDT_CURSOR);
}

//
// IMAGEDATA : Private
//
HANDLE IMAGEDATA::_LoadImg(PCTSTR pImg, UINT_PTR uiType, UINT_PTR uiFlag) {

  return LoadImage(hMod, pImg, uiType, cx, cy, uiFlag);
}

void IMAGEDATA::_Gip(_GIP Type, _ID *p) {

  PTSTRING ptsImg = NULL;
  INT_PTR *piImg  = NULL;

  switch (Type) {

    case _GIP_BMP:
      ptsImg = &tsBmp;
      piImg  = &iBmp;
    break;

    case _GIP_ICO:
      ptsImg = &tsIcon;
      piImg  = &iIcon;
    break;

    case _GIP_CUR:
      ptsImg = &tsCur;
      piImg  = &iCur;
    break;

    case _GIP_MASK:
      ptsImg = &tsMask;
      piImg  = &iMask;
    break;

  }

  switch (Src) {

    case IDS_FILE:
      p->pImg    = ptsImg->c_str();
      p->uiFlag  = LR_LOADFROMFILE;
    break;

    case IDS_RESOURCE:
      p->pImg    = MAKEINTRESOURCE(*piImg);
      p->uiFlag  = 0L;
    break;

    case IDS_NOTSET:
    case IDS_MEMORY:
    default:
      p->pImg    = NULL;
      p->uiFlag  = 0UL;
    break;

  }

}
