#ifndef _IMAGELIST_H
#define  _IMAGELIST_H

#include "stdafx.h"
#include "image.hpp"
#include "wnd.hpp"

class ImageList {

public:
  ImageList() {

    m_hList   = NULL;
    m_hInst   = NULL;
    m_iImgCX  = 0;
    m_iImgCY  = 0;

  }
  virtual ~ImageList() {

    ImageList_Destroy(m_hList);

  }

  // Creates the ImageList object
  bool Create(INT_PTR cx, INT_PTR cy, UINT_PTR uiFlags = ILC_COLOR32, INT_PTR iInitial = 0, 
              INT_PTR iGrow = 1, HINSTANCE hInst = NULL);

  // Destroys the ImageList object
  bool Destroy(void);

  //
  // All methods that return INT_PTR return -1
  // for failure unless otherwise noted
  //

  // Adds an image as specified in an IMAGEDATA structure
  // Returns index of new image
  INT_PTR AddImage(PIMAGEDATA pid);

  // Adds a bitmap, and optionally, a mask bitmap
  // Returns the index of the new image
  INT_PTR AddBitmap(HBITMAP hBitmap, HBITMAP hMask = 0);
  INT_PTR AddBitmap(INT_PTR iBitmapID, INT_PTR iMaskID = 0);
  INT_PTR AddBitmap(CTSTRING &tsBitmap, CTSTRING &tsMask = _T(""));

  // Adds an icon
  // Returns the index of the new image
  INT_PTR AddIcon(HICON hIcon);
  INT_PTR AddIcon(INT_PTR iIconID);
  INT_PTR AddIcon(CTSTRING &tsIcon);

  // Adds a bitmap that contains a bitmap and a mask
  // and creates a masked bitmap
  // Returns the index of the new image
  INT_PTR AddMasked(HBITMAP hBitmap, COLORREF clrMask);

  // Removes the image at the index specified
  bool RemoveImg(INT_PTR iIndex);

  // Removes all the images in the list, but
  // does not destroy the image list
  bool RemoveAll(void);

  // Draws an image from the list on a device context
  bool Draw(INT_PTR iIndex, HDC hDC, INT_PTR x, INT_PTR y, UINT_PTR fStyle = ILD_NORMAL);

  // Draws an image from the list on a device context
  // using blending
  bool DrawEx(INT_PTR iIndex, HDC hDC, INT_PTR x, INT_PTR y, INT_PTR dx, INT_PTR dy,
              COLORREF clrBk = CLR_NONE, COLORREF clrFore = CLR_NONE, UINT_PTR fStyle = ILD_NORMAL);

  // Draws an image from the list on a device context
  // based on a IMAGELISTDRAWPARAMS structure
  bool DrawIndirect(IMAGELISTDRAWPARAMS *pildp);

  // Creates a duplicate of the image list
  HIMAGELIST Duplicate(void);

  // Creates an HICON of an image in the list
  // Returns NULL for failure
  HICON GetIcon(INT_PTR iIndex, UINT_PTR uiFlags = ILD_NORMAL);

  // Returns the current background color
  // of the images in the list
  COLORREF GetBkColor(void);

  // Sets the current background color
  // of the images in the list
  // Returns the previous color
  COLORREF SetBkColor(COLORREF clrBk);

  // Retrieves the size of the images in the list
  bool GetImgSize(PSIZE ps);

  // Resizes the image size used by the list, and
  // removes all images
  bool SetImgSize(INT_PTR cx, INT_PTR cy);

  // Retreives information about an image in the list
  bool GetImgInfo(INT_PTR iIndex, IMAGEINFO *pi);

  // Resizes the image list to contain uiCount images
  bool Resize(UINT_PTR uiCount);

  // Returns the HIMAGELIST associated with the list
  HIMAGELIST Handle(void) const { return m_hList; }

  // Returns the number of images contained by the list
  INT_PTR Count(void);

private:
  HINSTANCE   m_hInst;
  HIMAGELIST  m_hList;
  INT_PTR     m_iImgCX;
  INT_PTR     m_iImgCY;

  INT_PTR _LoadIcon(PCTSTR pIcon, DWORD_PTR dwFlags);
  INT_PTR _LoadBitmap(PCTSTR pBitmap, PCTSTR pMask, DWORD_PTR dwFlags);

};

#endif // !_IMAGELIST_H
