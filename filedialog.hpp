#ifndef _FILEDIALOG_H
#define _FILEDIALOG_H

#include "stdafx.h"
#include <commdlg.h>

#define FD_ERROR      0
#define FD_SUCCESS    1
#define FD_CANCELLED  2

//
// FILEDIALOG Structure
//
// OPENFILENAME Wrapper
//
typedef struct tagFILEDIALOG {

  tagFILEDIALOG() {

    tsDlgTitle    = _T("");
    tsDefPath     = _T("");
    tsDefExt      = _T("");
    tszFilter     = NULL;
    tsFile        = _T("");
    tszCustFilter = NULL;
    iCustFilter   = 0;
    hWndParent    = NULL;
    hInst         = NULL;
    dwFlags       = 0UL;
    dwFlagsEx     = 0UL;

  }

  TSTRING tsDlgTitle;
  TSTRING tsDefPath;
  TSTRING tsDefExt;
  TCHAR *tszFilter;
  TSTRING tsFile;
  TCHAR *tszCustFilter;
  INT_PTR iCustFilter;
  HWND hWndParent;
  HINSTANCE hInst;
  DWORD_PTR dwFlags;
  DWORD_PTR dwFlagsEx;

} FILEDIALOG, *PFILEDIALOG;

//
// FileDialog Class
//
// GetOpen/SaveFileName() Wrapper
//
class FileDialog {

public:
  FileDialog() {}
  virtual ~FileDialog() {}

  // Return values:
  // 0 = Failure = FD_ERROR
  // 1 = Success = FD_SUCCESS
  // 2 = Cancelled = FD_CANCELLED
  INT_PTR GetOpenFileName(PFILEDIALOG pfd);
  INT_PTR GetSaveFileName(PFILEDIALOG pfd);

protected:
  void _FD2OFN(PFILEDIALOG pfd, LPOPENFILENAME pofn);

};

#endif // !_FILEDIALOG_H
