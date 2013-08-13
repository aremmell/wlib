#ifndef _WLIB_UTIL_H
#define _WLIB_UTIL_H

/*
 * Application path retrieval
 */
bool GetAppPath(TSTRING &tsPath);

/*
 * Misc file
 */
void GetShortFileName(CTSTRING &tsFile, TSTRING &tsOut);
bool GetFileExtension(CTSTRING &tsFile, TSTRING &tsOut);

/*
 * Debug output
 */
#define MAX_AGMSGLEN  4096

void odsf(PCTSTR format, ...);
void sprintf(TSTRING& s, PCTSTR sFormat, ...);

/*
 * Message Box utility and misc
 */
#define MAX_PRINTSIZE 4096

INT_PTR MsgBox(HWND hWnd, CTSTRING &tsMsg, CTSTRING &tsCap, UINT_PTR uiFlags = MB_OK);
INT_PTR PrintMsgBox(HWND hWnd, CTSTRING &tsCap, UINT_PTR uiFlags, PCTSTR szFormat, ...);

void StrToUpper(TSTRING &s);
void StrToLower(TSTRING &s);

HINSTANCE _HLInst(HINSTANCE hInst);

/*
 * File utility
 */
#define FS_BYTES  0x00000001UL
#define FS_KBYTES 0x00000002UL
#define FS_MBYTES 0x00000003UL
#define FS_GBYTES 0x00000004UL
#define FS_TBYTES 0x00000005UL

typedef struct tagFILESIZE {

  tagFILESIZE() {

    ui64Bytes     = 0U;
    dKiloBytes    = 0.0f;
    dMegaBytes    = 0.0f;
    dGigaBytes    = 0.0f;
    dTeraBytes    = 0.0f;
    DWORD dwMatch = 0UL;
    tsStrFmt      = _T("");

  }

  UINT64 ui64Bytes;
  double dKiloBytes;
  double dMegaBytes;
  double dGigaBytes;
  double dTeraBytes;
  DWORD dwMatch;
  TSTRING tsStrFmt;

} FILESIZE, *PFILESIZE;

typedef struct tagFILETIMES {

  tagFILETIMES() {

    RtlFillMemory(&stCreated, sizeof(stCreated), 0x00);
    RtlFillMemory(&stModified, sizeof(stModified), 0x00);
    tsShortCreated  = _T("");
    tsShortModified = _T("");
    tsLongCreated   = _T("");
    tsLongModified  = _T("");

  }

  SYSTEMTIME stCreated;     /* Structure for creation time */
  SYSTEMTIME stModified;    /* Structure for modification time */
  TSTRING tsShortCreated;   /* Formatted creation date (MM/DD/YYYY + time) */
  TSTRING tsShortModified;  /* Formatted modification date (MM/DD/YYYY + time) */
  TSTRING tsLongCreated;    /* Formatted creation date (DayOfWeek, Month Day, Year + time) */
  TSTRING tsLongModified;   /* Formatted modification date (DayOfWeek, Month Day, Year + time) */

} FILETIMES, *PFILETIMES;

bool FileGetSize(CTSTRING &tsFile, FILESIZE &fsOut);
bool FileGetTime(CTSTRING &tsFile, FILETIMES &ftOut);

TSTRING NumericDayToString(WORD wDay);
TSTRING NumericMonthToString(WORD wMonth);

TSTRING GetPathFromFile(CTSTRING &tsFile);
TSTRING GetFileFromPath(CTSTRING &tsPath);
TSTRING PathConcatFile(CTSTRING &tsPath, CTSTRING &tsFile);

#endif // !_WLIB_UTIL_H
