#ifndef _IMAGE_H
#define _IMAGE_H

#include "stdafx.h"

//
// Image data for controls
//
enum ImageDataType {

  IDT_ICON = 0,
  IDT_BITMAP,
  IDT_CURSOR,
  IDT_NOTSET

};

enum ImageDataSrc {

  IDS_FILE = 0,
  IDS_RESOURCE,
  IDS_MEMORY,
  IDS_NOTSET

};

typedef struct _IMAGEDATA {

  _IMAGEDATA() {
    Reset();
  }

  _IMAGEDATA &operator=(const _IMAGEDATA &in) {

    bUseImg   = in.bUseImg;
    bUseMask  = in.bUseMask;
    cx        = in.cx;
    cy        = in.cy;
    Type      = in.Type;
    Src       = in.Src;
    hBmp      = in.hBmp;
    hMask     = in.hMask;
    hIcon     = in.hIcon;
    hCur      = in.hCur;
    tsBmp     = in.tsBmp;
    tsMask    = in.tsMask;
    tsIcon    = in.tsIcon;
    tsCur     = in.tsCur;
    iBmp      = in.iBmp;
    iMask     = in.iMask;
    iIcon     = in.iIcon;
    iCur      = in.iCur;
    hMod      = in.hMod;

    return (*this);
  }

  bool bUseImg;         // Defines whether or not image is used
  bool bUseMask;        // Defines whether or not a mask is used

  INT_PTR cx;           // Width of image, in pixels
  INT_PTR cy;           // Height of image, in pixels

  ImageDataType Type;   // Type of image
  ImageDataSrc  Src;    // Source of image

  HBITMAP hBmp;         // Handle of bitmap in memory
  HBITMAP hMask;        // Handle of mask bitmap in memory
  HICON  hIcon;         // Handle of icon in memory
  HCURSOR hCur;         // Handle of cursor in memory

  TSTRING tsBmp;        // Path of bitmap file on disk
  TSTRING tsMask;       // Path of mask bitmap file on disk
  TSTRING tsIcon;       // Path of icon on disk
  TSTRING tsCur;        // Path of cursor on disk

  INT_PTR iBmp;         // Resource identifier of bitmap
  INT_PTR iMask;        // Resource identifier of mask bitmap
  INT_PTR iIcon;        // Resource identifier of icon
  INT_PTR iCur;         // Resource identifier of cursor
  HINSTANCE hMod;       // Handle of module that contains resources

  HBITMAP Bitmap(void); // Loads bitmap and returns handle
  HBITMAP Mask(void);   // Loads mask bitmap and returns handle
  HICON Icon(void);     // Loads icon and returns handle
  HCURSOR Cursor(void); // Loads cursor and returns handle
  void Reset(void);     // Resets the state of this object

  bool IsBitmap(void);  // Determines if this object is of bitmap type
  bool HasMask(void);   // Determines if this object has a mask associated
  bool IsIcon(void);    // Determines if this object is of icon type
  bool IsCursor(void);  // Determines if this object is of cursor type

protected:
  enum _GIP {

    _GIP_BMP = 0,
    _GIP_ICO,
    _GIP_CUR,
    _GIP_MASK

  };

  typedef struct {

    PCTSTR pImg;
    UINT_PTR uiFlag;

  } _ID;

  HANDLE _LoadImg(PCTSTR pImg, UINT_PTR uiType, UINT_PTR uiFlag);
  void _Gip(_GIP Type, _ID *p);

} IMAGEDATA, *PIMAGEDATA;

#endif // !_IMAGE_H
