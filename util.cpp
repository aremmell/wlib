#include "stdafx.h"
#include "util.hpp"

bool GetAppPath(TSTRING &tsPath) {

  bool r                = false;
  TCHAR szBuf[MAX_PATH] = {0};

  if (0UL != GetModuleFileName(GetModuleHandle(NULL), szBuf, MAX_PATH)) {

    for (int n = _tcslen(szBuf); n > 0; n--) {
      
      if (szBuf[n] == _T('\\')) {

        szBuf[n + 1] = _T('\0');
        break;

      }

    }

    tsPath = szBuf;
    r      = true;
  
  }

  return r;
}

void GetShortFileName(CTSTRING &tsFile, TSTRING &tsOut) {

  if (_T("") != tsFile) {

    tsOut = _T("<invalid>");

    TSTRING::size_type n = tsFile.rfind(_T('\\'));

    if (TSTRING::npos != n) {

      tsOut = tsFile.substr(n + 1);

    }

  }

}

bool GetFileExtension(CTSTRING &tsFile, TSTRING &tsOut) {

bool r = false;

  if (_T("") != tsFile) {

    TSTRING::size_type n = tsFile.rfind(_T('.'));

    if (TSTRING::npos != n) {

      tsOut = tsFile.substr(n + 1);
      r     = true;

    }

  }


  return r;
}

void odsf(PCTSTR format, ...) {

  TCHAR szBuf[MAX_AGMSGLEN] = {0};

  va_list l;
  va_start(l, format);

  _vsntprintf(szBuf, MAX_AGMSGLEN, format, l);
  OutputDebugString(szBuf);

  va_end(l);

}

void sprintf(TSTRING& s, PCTSTR sFormat, ...) {

  va_list argptr;
  TCHAR szBuf[MAX_AGMSGLEN] = {0};

  va_start(argptr, sFormat);
  _vsntprintf(szBuf, MAX_AGMSGLEN, sFormat, argptr);
  va_end(argptr);

  s = szBuf;

}

INT_PTR MsgBox(HWND hWnd, CTSTRING &tsMsg, CTSTRING &tsCap, UINT_PTR uiFlags) {

  return MessageBox(hWnd, tsMsg.c_str(), tsCap.c_str(), uiFlags);
}

INT_PTR PrintMsgBox(HWND hWnd, CTSTRING &tsCap, UINT_PTR uiFlags, PCTSTR szFormat, ...) {

  va_list l;
  va_start(l, szFormat);

  TCHAR pBuf[MAX_PRINTSIZE] = {0};
  _vsntprintf(pBuf, MAX_PRINTSIZE, szFormat, l);

  va_end(l);  

  return MsgBox(hWnd, pBuf, tsCap, uiFlags);
}

void StrToUpper(TSTRING &s) {

	TSTRING::iterator it = s.begin();

	for(; it != s.end(); it++) { (*it) = toupper((*it)); }

}

void StrToLower(TSTRING &s) {

	TSTRING::iterator it = s.begin();

	for(; it != s.end(); it++) { (*it) = tolower((*it)); }

}

HINSTANCE _HLInst(HINSTANCE hInst) { 

  return hInst ? hInst : GetModuleHandle(NULL); 
}

bool FileGetSize(CTSTRING &tsFile, FILESIZE &fsOut) {

  bool r = false;

 /*
  * Make sure the file exists
  */
  if (-1 != GetFileAttributes(tsFile.c_str())) {

    HANDLE hFile = NULL;

   /*
    * Open the file for query access
    */
    hFile = CreateFile(tsFile.c_str(),                      /* File Name */
                       FILE_READ_ATTRIBUTES,                /* Open for query access */
                       FILE_SHARE_READ | FILE_SHARE_WRITE,  /* Don't want to hog the file */
                       NULL,                                /* Default security attributes */
                       OPEN_EXISTING,                       /* Don't actually create a file */
                       FILE_ATTRIBUTE_NORMAL,               /* Normal attributes */
                       NULL);                               /* Not using a template */
 
    if (INVALID_HANDLE_VALUE != hFile) {

     /*
      * File successfully opened;
      * query size and calculate (b/KB/MB/GB/TB)
      */
      DWORD dwFileHigh  = 0UL;
      DWORD dwFileLow   = GetFileSize(hFile, &dwFileHigh);

      UINT64 ui64Bytes = static_cast<UINT64>(((static_cast<UINT64>(dwFileHigh) << 32) & 0xFFFFFFFF00000000) |
                                             (static_cast<UINT64>(dwFileLow) & 0x00000000FFFFFFFF));

     /*
      * Fill out the structure
      */
      fsOut.ui64Bytes = ui64Bytes;
      fsOut.dKiloBytes = static_cast<double>(ui64Bytes / 1024.0f);
      fsOut.dMegaBytes = static_cast<double>(fsOut.dKiloBytes / 1024.0f);
      fsOut.dGigaBytes = static_cast<double>(fsOut.dMegaBytes / 1024.0f);
      fsOut.dTeraBytes = static_cast<double>(fsOut.dGigaBytes / 1024.0f);

     /*
      * Figure out which format is the 'most likely' match
      * to be displayed to the user.
      */
      TCHAR *szSuffix = NULL;
      double *pdMatch = NULL;

      if (fsOut.ui64Bytes < 1024U) {
        fsOut.dwMatch = FS_BYTES;
        szSuffix      = _T("Bytes");
      } else if (fsOut.dKiloBytes < 1024.0f) {
        fsOut.dwMatch = FS_KBYTES;
        szSuffix      = _T("KB");
        pdMatch       = &fsOut.dKiloBytes;
      } else if (fsOut.dMegaBytes < 1024.0f) {
        fsOut.dwMatch = FS_MBYTES;
        szSuffix      = _T("MB");
        pdMatch       = &fsOut.dMegaBytes;
      } else if (fsOut.dGigaBytes < 1024.0f) {
        fsOut.dwMatch = FS_GBYTES;
        szSuffix      = _T("GB");
        pdMatch       = &fsOut.dGigaBytes;
      } else if (fsOut.dTeraBytes < 1024.0f) {
        fsOut.dwMatch = FS_TBYTES;
        szSuffix      = _T("TB");
        pdMatch       = &fsOut.dTeraBytes;
      }

      if (FS_BYTES == fsOut.dwMatch) {
        sprintf(fsOut.tsStrFmt, _T("%I64u %s"), fsOut.ui64Bytes, szSuffix);
      } else {
        sprintf(fsOut.tsStrFmt, _T("%.02f %s"), *pdMatch, szSuffix);
      }

      CloseHandle(hFile);
      r = true;
    }

  }

  return r;
}

bool FileGetTime(CTSTRING &tsFile, FILETIMES &ftOut) {

  bool r = false;

 /*
  * Make sure the file exists
  */
  if (-1 != GetFileAttributes(tsFile.c_str())) {

    HANDLE hFile = NULL;

   /*
    * Open the file for query access
    */
    hFile = CreateFile(tsFile.c_str(),                      /* File Name */
                       GENERIC_READ,                        /* Open for read access */
                       FILE_SHARE_READ | FILE_SHARE_WRITE,  /* Don't want to hog the file */
                       NULL,                                /* Default security attributes */
                       OPEN_EXISTING,                       /* Don't actually create a file */
                       FILE_ATTRIBUTE_NORMAL,               /* Normal attributes */
                       NULL);                               /* Not using a template */
 
    if (INVALID_HANDLE_VALUE != hFile) {

     /*
      * Acquire the FILETIMEs for the file,
      * and convert to SYTEMTIME.
      */
      FILETIME ftCreatedTmp  = {0};
      FILETIME ftModifiedTmp = {0};

      if (0 != GetFileTime(hFile, &ftCreatedTmp, NULL, &ftModifiedTmp)) {
      
        FILETIME ftCreated = {0};

        if (0 != FileTimeToLocalFileTime(&ftCreatedTmp, &ftCreated)) {

          FILETIME ftModified = {0};

          if (0 != FileTimeToLocalFileTime(&ftModifiedTmp, &ftModified)) {

            if (0 != FileTimeToSystemTime(&ftCreated, &ftOut.stCreated)) {

              if (0 != FileTimeToSystemTime(&ftModified, &ftOut.stModified)) {

              /*
                * SYSTEMTIMEs acquired successfully,
                * format string outputs.
                *
                * Short = MM/DD/YYYY + time
                * Long  = DayOfWeek, Month Day, Year + time
                */
                TCHAR *szSuffix = NULL;
                WORD w12Hour    = ftOut.stCreated.wHour;

                if (w12Hour > 12) {
                  w12Hour -= 12;
                  szSuffix = _T("PM");
                } else {
                  szSuffix = _T("AM");
                }
                  
              /*
                * Created
                */
                sprintf(ftOut.tsShortCreated, _T("%02d/%02d/%02d %02d:%02d:%02d %s"), ftOut.stCreated.wMonth,
                        ftOut.stCreated.wDay, ftOut.stCreated.wYear, w12Hour, ftOut.stCreated.wMinute,
                        ftOut.stCreated.wSecond, szSuffix);

                sprintf(ftOut.tsLongCreated, _T("%s, %s %d, %d %02d:%02d:%02d %s"),
                        NumericDayToString(ftOut.stCreated.wDayOfWeek).c_str(),
                        NumericMonthToString(ftOut.stCreated.wMonth).c_str(), ftOut.stCreated.wDay,
                        ftOut.stCreated.wYear, w12Hour, ftOut.stCreated.wMinute, ftOut.stCreated.wSecond, szSuffix);

                w12Hour = ftOut.stModified.wHour;

                if (w12Hour > 12) {
                  w12Hour -= 12;
                  szSuffix = _T("PM");
                } else {
                  szSuffix = _T("AM");
                }

              /*
                * Modified
                */
                sprintf(ftOut.tsShortModified, _T("%02d/%02d/%02d %02d:%02d:%02d %s"), ftOut.stModified.wMonth,
                        ftOut.stModified.wDay, ftOut.stModified.wYear, w12Hour, ftOut.stModified.wMinute,
                        ftOut.stModified.wSecond, szSuffix);

                sprintf(ftOut.tsLongModified, _T("%s, %s %d, %d %02d:%02d:%02d %s"),
                        NumericDayToString(ftOut.stModified.wDayOfWeek).c_str(),
                        NumericMonthToString(ftOut.stModified.wMonth).c_str(), ftOut.stModified.wDay,
                        ftOut.stModified.wYear, w12Hour, ftOut.stModified.wMinute, ftOut.stModified.wSecond, szSuffix);

                r = true;

              }

            }

          }

        }

      }

      CloseHandle(hFile);
    }

  }

  return r;
}

TSTRING NumericDayToString(WORD wDay) {

  TSTRING r = _T("<invalid>");

  switch (wDay) {
    
    case 0:
      r = _T("Sunday");
    break;
    case 1:
      r = _T("Monday");
    break;
    case 2:
      r = _T("Tuesday");
    break;
    case 3:
      r = _T("Wednesday");
    break;
    case 4:
      r = _T("Thursday");
    break;
    case 5:
      r = _T("Friday");
    break;
    case 6:
      r = _T("Saturday");
    break;
 
  }

  return r;
}

TSTRING NumericMonthToString(WORD wMonth) {

  TSTRING r = _T("<invalid>");

  switch (wMonth) {

    case 1:
      r = _T("January");
    break;
    case 2:
      r = _T("February");
    break;
    case 3:
      r = _T("March");
    break;
    case 4:
      r = _T("April");
    break;
    case 5:
      r = _T("May");
    break;
    case 6:
      r = _T("June");
    break;
    case 7:
      r = _T("July");
    break;
    case 8:
      r = _T("August");
    break;
    case 9:
      r = _T("September");
    break;
    case 10:
      r = _T("October");
    break;
    case 11:
      r = _T("November");
    break;
    case 12:
      r = _T("December");
    break;

  }

  return r;
}

TSTRING GetPathFromFile(CTSTRING &tsFile) {

  TSTRING::size_type r = tsFile.rfind(_T('\\'));

  if (TSTRING::npos != r) {

    return tsFile.substr(0, r + 1);

  } else if (TSTRING::npos != (r = tsFile.rfind(_T('/')))) {

    return tsFile.substr(0, r + 1);

  }

  return _T("");
}

TSTRING GetFileFromPath(CTSTRING &tsPath) {

  TSTRING::size_type r = tsPath.rfind(_T('\\'));

  if (TSTRING::npos != r) {

    return tsPath.substr(r + 1);
    
  } else if (TSTRING::npos != (r = tsPath.rfind(_T('/')))) {

    return tsPath.substr(r + 1);

  }

  return _T("");
}

TSTRING PathConcatFile(CTSTRING &tsPath, CTSTRING &tsFile) {

  TSTRING r = tsPath;
  TSTRING::iterator it = r.end();

  it--;

  if ((*it) != _T('\\') && (*it) != _T('/')) {

    r += _T("\\");

  }

  return r + tsFile;
}
