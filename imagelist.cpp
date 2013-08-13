#include "stdafx.h"
#include "imagelist.hpp"

//
// ImageList : Public
//
bool ImageList::Create(INT_PTR cx, INT_PTR cy, UINT_PTR uiFlags, INT_PTR iInitial, 
                       INT_PTR iGrow, HINSTANCE hInst)
{

  if ((NULL != (m_hList = ImageList_Create(cx, cy, uiFlags, iInitial, iGrow)))) {

    m_iImgCX = cx;
    m_iImgCY = cy;
    m_hInst  = (NULL != hInst) ? hInst : GetModuleHandle(NULL);

    return true;
  }

  return false;
}

bool ImageList::Destroy(void) {

  return WND_TRUE(ImageList_Destroy(m_hList));
}

INT_PTR ImageList::AddImage(PIMAGEDATA pid) {

  INT_PTR r = -1;

  if (NULL != pid) {

    if (pid->IsBitmap()) {

      r = AddBitmap(pid->Bitmap(), pid->Mask());

    } else if (pid->IsIcon()) {

      r = AddIcon(pid->Icon());

    }

  }

  return r;
}

INT_PTR ImageList::AddBitmap(HBITMAP hBitmap, HBITMAP hMask) {

  INT_PTR r =  ImageList_Add(m_hList, hBitmap, hMask);

  if (-1 != r) {

    DeleteObject(hBitmap);
    DeleteObject(hMask);

  }

  return r;
}

INT_PTR ImageList::AddBitmap(INT_PTR iBitmapID, INT_PTR iMaskID) {

  return _LoadBitmap(MAKEINTRESOURCE(iBitmapID), MAKEINTRESOURCE(iMaskID), 0UL);
}

INT_PTR ImageList::AddBitmap(CTSTRING &tsBitmap, CTSTRING &tsMask) {

  return _LoadBitmap(tsBitmap.c_str(), tsMask.c_str(), LR_LOADFROMFILE);
}

INT_PTR ImageList::AddIcon(HICON hIcon) {

  INT_PTR r = ImageList_AddIcon(m_hList, hIcon);

  if (-1 != r) { DestroyIcon(hIcon); }

  return r;
}

INT_PTR ImageList::AddIcon(INT_PTR iIconID) {

  return _LoadIcon(MAKEINTRESOURCE(iIconID), 0UL);
}

INT_PTR ImageList::AddIcon(CTSTRING &tsIcon) {

  return _LoadIcon(tsIcon.c_str(), LR_LOADFROMFILE);
}

INT_PTR ImageList::AddMasked(HBITMAP hBitmap, COLORREF clrMask) {

  INT_PTR r = ImageList_AddMasked(m_hList, hBitmap, clrMask);

  if (-1 != r) { DeleteObject(hBitmap); }

  return r;
}

bool ImageList::RemoveImg(INT_PTR iIndex) {

  return WND_TRUE(ImageList_Remove(m_hList, iIndex));
}

bool ImageList::RemoveAll(void) {

  return WND_TRUE(ImageList_RemoveAll(m_hList));
}

bool ImageList::Draw(INT_PTR iIndex, HDC hDC, INT_PTR x, INT_PTR y, UINT_PTR fStyle) {

  return WND_TRUE(ImageList_Draw(m_hList, iIndex, hDC, x, y, fStyle));
}

bool ImageList::DrawEx(INT_PTR iIndex, HDC hDC, INT_PTR x, INT_PTR y, INT_PTR dx, 
                       INT_PTR dy, COLORREF clrBk, COLORREF clrFore, UINT_PTR fStyle)
{
  return WND_TRUE(ImageList_DrawEx(m_hList, iIndex, hDC, x, y, dx, dy, clrBk, clrFore, fStyle));
}

bool ImageList::DrawIndirect(IMAGELISTDRAWPARAMS *pildp) {

  return WND_TRUE(ImageList_DrawIndirect(pildp));
}

HIMAGELIST ImageList::Duplicate(void) {

  return ImageList_Duplicate(m_hList);
}

HICON ImageList::GetIcon(INT_PTR iIndex, UINT_PTR uiFlags) {

  return ImageList_GetIcon(m_hList, iIndex, uiFlags);
}

COLORREF ImageList::GetBkColor(void) {

  return ImageList_GetBkColor(m_hList);
}

COLORREF ImageList::SetBkColor(COLORREF clrBk) {

  return ImageList_SetBkColor(m_hList, clrBk);
}

bool ImageList::GetImgSize(PSIZE ps) {

  bool r = false;

  if (NULL != ps) {

    if (WND_TRUE(ImageList_GetIconSize(m_hList, reinterpret_cast<int *>(&ps->cx),
                                       reinterpret_cast<int *>(&ps->cy)))) {

      r = true;

    }

  }

  return r;
}

bool ImageList::SetImgSize(INT_PTR cx, INT_PTR cy) {

  return WND_TRUE(ImageList_SetIconSize(m_hList, cx, cy));
}

bool ImageList::GetImgInfo(INT_PTR iIndex, IMAGEINFO *pi) {

  bool r = false;

  if (NULL != pi) {

    if (WND_TRUE(ImageList_GetImageInfo(m_hList, iIndex, pi))) {

      r = true;

    }

  }

  return r;
}

bool ImageList::Resize(UINT_PTR uiCount) {

  return WND_TRUE(ImageList_SetImageCount(m_hList, uiCount));
}

INT_PTR ImageList::Count(void) { 

  return ImageList_GetImageCount(m_hList); 
}

//
// ImageList : Private
//
INT_PTR ImageList::_LoadIcon(PCTSTR pIcon, DWORD_PTR dwFlags) {

  return AddIcon(static_cast<HICON>(LoadImage(m_hInst, pIcon, IMAGE_ICON, m_iImgCX, m_iImgCY, dwFlags)));
}

INT_PTR ImageList::_LoadBitmap(PCTSTR pBitmap, PCTSTR pMask, DWORD_PTR dwFlags) {

  INT_PTR r = -1;

  HBITMAP hBmp = static_cast<HBITMAP>(LoadImage(m_hInst, pBitmap, 
                                                IMAGE_BITMAP, m_iImgCX, m_iImgCY, dwFlags));

  if ((-1 != r) && (NULL != pMask) && (0 != *pMask)) {

    HBITMAP hMask = static_cast<HBITMAP>(LoadImage(m_hInst, pMask,
                                                   IMAGE_BITMAP, m_iImgCX, m_iImgCY, dwFlags));
    r = AddBitmap(hBmp, hMask);

  }

  return r;
}
