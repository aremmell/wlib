#include "stdafx.h"
#include "filedialog.hpp"

//
// FileDialog : Public
//
INT_PTR FileDialog::GetOpenFileName(PFILEDIALOG pfd) {

  INT_PTR r = FD_ERROR;

  if (NULL != pfd) {

    OPENFILENAME ofn          = {0};
    TCHAR pFile[MAX_PATH + 1] = {0};

    _FD2OFN(pfd, &ofn);

    ofn.lpstrFile = pFile;

    if (0 == ::GetOpenFileName(&ofn)) {

      if (0 == CommDlgExtendedError()) {

        r = FD_CANCELLED;

      }

    } else {

      pfd->tsFile = pFile;
      r           = FD_SUCCESS;

    }

  }

  return r;
}

INT_PTR FileDialog::GetSaveFileName(PFILEDIALOG pfd) {

  INT_PTR r = FD_ERROR;

  if (NULL != pfd) {

    OPENFILENAME ofn          = {0};
    TCHAR pFile[MAX_PATH + 1] = {0};

    _FD2OFN(pfd, &ofn);

    ofn.lpstrFile = pFile;

    if (0 == ::GetSaveFileName(&ofn)) {

      if (0 == CommDlgExtendedError()) {

        r = FD_CANCELLED;

      }

    } else {

      pfd->tsFile  = pFile;
      r      = FD_SUCCESS;

    }

  }

  return r;
}

void FileDialog::_FD2OFN(PFILEDIALOG pfd, LPOPENFILENAME pofn) {

  pofn->lStructSize       = sizeof(OPENFILENAME);
  pofn->Flags             = pfd->dwFlags;
  pofn->hInstance         = pfd->hInst;
  pofn->hwndOwner         = pfd->hWndParent;
  pofn->lpstrCustomFilter = pfd->tszCustFilter;
  pofn->lpstrDefExt       = pfd->tsDefExt.c_str();
  pofn->lpstrFileTitle    = const_cast<PTSTR>(pfd->tsDlgTitle.c_str());
  pofn->lpstrFilter       = pfd->tszFilter;
  pofn->lpstrInitialDir   = pfd->tsDefPath.c_str();
  pofn->nMaxFile          = MAX_PATH + 1L;
  pofn->nMaxFileTitle     = pfd->tsDlgTitle.size();
  pofn->nMaxCustFilter    = pfd->iCustFilter;;
}
