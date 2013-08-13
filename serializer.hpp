#ifndef _SERIALIZER_H
#define _SERIALIZER_H

#include "stdafx.h"

/*
 * Serializer Class
 *
 * Provides templated file
 * serialization for datum
 *
 * Ryan Matthew Lederman, ryan@ript.net
 * November 24, 2003
 */
template <typename _Datum> class Serializer {

public:
  Serializer() {}
  virtual ~Serializer() {}

  enum IOType {

    IOT_READ,
    IOT_WRITE

  };

 /*
  * Write to file 
  */
  bool Write(const TCHAR *szFile, const _Datum *pDatum) {

    bool r        = false;
    HANDLE hFile  = _OpenFile(szFile, IOT_WRITE);

    if (INVALID_HANDLE_VALUE != hFile) {

      DWORD_PTR dwWritten = 0UL;

      if (TRUE == WriteFile(hFile, pDatum, sizeof(_Datum), &dwWritten, NULL)) {

        if (sizeof(_Datum) == dwWritten) {

          r = true;

        }

      }

      CloseHandle(hFile);
    }

    return r;
  }

 /*
  * Read from file 
  */
  bool Read(const TCHAR *szFile, _Datum *pDatum) {

    bool r        = false;
    HANDLE hFile  = _OpenFile(szFile, IOT_READ);

    if (INVALID_HANDLE_VALUE != hFile) {

      DWORD_PTR dwRead = 0UL;

      if (TRUE == ReadFile(hFile, pDatum, sizeof(_Datum), &dwRead, NULL)) {

        if (sizeof(_Datum) == dwRead) {

          r = true;

        }

      }

      CloseHandle(hFile);
    }

    return r;
  }

 /*
  * Write to registry
  */
  bool Write(HKEY hKeyRoot, const TCHAR *szPath, const TCHAR *szValName, const _Datum *pDatum) {

    bool r    = false;
    HKEY hKey = _OpenKey(hKeyRoot, szPath);

    if (NULL != hKey) {

      if (_SetRegValue(hKey, szValName, pDatum)) {

        r = true;

      }

      RegCloseKey(hKey);
    }

    return r;
  }

 /*
  * Read from registry
  */
  bool Read(HKEY hKeyRoot, const TCHAR *szPath, const TCHAR *szValName, _Datum *pDatum) {

    bool r    = false;
    HKEY hKey = _OpenKey(hKeyRoot, szPath);

    if (NULL != hKey) {

      if (_GetRegValue(hKey, szValName, pDatum)) {

        r = true;

      }

      RegCloseKey(hKey);
    }

    return r;
  }

protected:
  
  HANDLE _OpenFile(const TCHAR *szFile, IOType Type) {

    HANDLE hFile = INVALID_HANDLE_VALUE;

    if (NULL != szFile) {

      DWORD dwFlag;

      switch (Type) {

        case IOT_READ:  dwFlag  = OPEN_EXISTING; break;
        case IOT_WRITE: dwFlag  = OPEN_ALWAYS; break;

      }

      hFile = CreateFile(szFile,
                         FILE_ALL_ACCESS,
                         0UL,
                         NULL,
                         dwFlag,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL);

    }

    return hFile;
  }

  HKEY _OpenKey(HKEY hKeyRoot, const TCHAR *szPath) {

    HKEY hKey = NULL;

    if (NULL != szPath) {

      LONG_PTR lResult = RegCreateKeyEx(hKeyRoot,
                                        szPath,
                                        0UL,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_ALL_ACCESS,
                                        NULL,
                                        &hKey,
                                        NULL);

      if (ERROR_SUCCESS != lResult) {

        hKey = NULL;

      }

    }

    return hKey;
  }

  bool _SetRegValue(HKEY hKey, const TCHAR *szName, const _Datum *pDatum) {

    bool r = false;

    if ((NULL != szName) && (0 != *szName) && (NULL != pDatum)) {

      if (ERROR_SUCCESS == RegSetValueEx(hKey,
                                         szName,
                                         0UL,
                                         REG_BINARY,
                                         reinterpret_cast<const BYTE *>(pDatum),
                                         sizeof(_Datum)))
      {

        r = true;

      }

    }

    return r;
  }

  bool _GetRegValue(HKEY hKey, const TCHAR *szName, _Datum *pDatum) {

    bool r = false;

    if ((NULL != szName) && (0 != *szName) && (NULL != pDatum)) {

      DWORD_PTR dwType = REG_BINARY;
      DWORD_PTR dwSize = sizeof(_Datum);

      if (ERROR_SUCCESS == RegQueryValueEx(hKey,
                                           szName,
                                           NULL,
                                           &dwType,
                                           reinterpret_cast<BYTE *>(pDatum),
                                           &dwSize))
      {

        r = true;

      }

    }

    return r;
  }

};

#endif // !_SERIALIZER_H
