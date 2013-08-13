#ifndef _REGISTRY_H
#define _REGISTRY_H

#include "stdafx.h"

class RegistryKey {

public:
  RegistryKey() { m_hKey = NULL; }
  virtual ~RegistryKey() { if (NULL != m_hKey) { _CloseKey(); } }

  enum ValueType {

    VT_DWORD = 0,
    VT_STRING,
    VT_BINARY

  };

 /*
  * Creates a registry key
  */
  bool Create(HKEY hKey, CTSTRING &tsPath) {

    return _OpenKey(hKey, tsPath, true);
  }

 /*
  * Opens a registry key
  */
  bool Open(HKEY hKey, CTSTRING &tsPath) { 

    return _OpenKey(hKey, tsPath, false);
  }

 /*
  * Determines whether or not this class
  * represents an open key handle
  */
  bool IsOpen(void) { return (NULL != m_hKey); }

 /*
  *  Closes an open key
  */
  void Close(void) { _CloseKey(); }

 /*
  * Deletes an open key
  */
  bool DeleteKey(HKEY hKey, CTSTRING &tsPath) {

    return (ERROR_SUCCESS == SHDeleteKey(hKey, tsPath.c_str()));  
  }

 /*
  * Deletes an existing value
  */
  bool DeleteValue(CTSTRING &tsValue) {

    return (ERROR_SUCCESS == RegDeleteValue(m_hKey, tsValue.c_str()));
  }

 /*
  * Write methods
  */
  bool WriteDWORD(CTSTRING &tsValName, DWORD_PTR dwVal) {

    return _WriteValue(tsValName, VT_DWORD, &dwVal, sizeof(DWORD_PTR));
  }

  bool WriteString(CTSTRING &tsValName, CTSTRING &tsVal) {

    return _WriteValue(tsValName, VT_STRING, tsVal.c_str(),
                       static_cast<DWORD>(tsVal.size() * sizeof(TCHAR)));
  }

  bool WriteBinary(CTSTRING &tsValName, void *pVal, DWORD dwBytes) {

    return _WriteValue(tsValName, VT_BINARY, pVal, dwBytes);
  }

  bool SetDefaultValue(CTSTRING &tsVal) {

    return _WriteValue(_T(""), VT_STRING, tsVal.c_str(), 
                       static_cast<DWORD>(tsVal.size() * sizeof (TCHAR)));
  }

 /*
  * Read methods
  */
  bool ReadDWORD(CTSTRING &tsValName, DWORD_PTR *pdwVal) {

    DWORD_PTR dwSize = sizeof(DWORD_PTR);

    return _ReadValue(tsValName, VT_DWORD, pdwVal, &dwSize);
  }

  bool ReadString(CTSTRING &tsValName, TSTRING &tsVal) {

    bool r            = false;
    DWORD_PTR dwSize  = 0UL;

    if (_ReadValue(tsValName, VT_STRING, NULL, &dwSize)) {

      if (0 < dwSize) {

        TCHAR *pBuf = new TCHAR[dwSize];

        if (NULL != pBuf) {

          RtlFillMemory(pBuf, dwSize, 0x00);

          if (_ReadValue(tsValName, VT_STRING, pBuf, &dwSize)) {

            tsVal = pBuf;
            r     = true;

          }

          delete pBuf;
        }

      }

    }

    return r;
  }

  bool ReadBinary(CTSTRING &tsValName, void *pVal, DWORD_PTR dwBytes) {

    return _ReadValue(tsValName, VT_BINARY, pVal, &dwBytes);
  }

  bool GetDefaultValue(TSTRING &tsVal) {

    return ReadString(_T(""), tsVal);
  }

 /*
  * Enumeration
  */
  bool EnumValues(TSTRING &tsNameOut, BYTE *pValueData, DWORD_PTR dwDataSize, 
                  DWORD_PTR dwType = REG_SZ)
  {

    bool r                = false;
    static DWORD dwIndex  = 0UL;
    LONG lRet             = ERROR_SUCCESS;
    TCHAR szBuf[16383]    = {0};
    DWORD dwNameSize      = 16383;

    lRet = RegEnumValue(m_hKey,
                        dwIndex++,
                        szBuf,
                        &dwNameSize,
                        NULL,
                        &dwType,
                        pValueData,
                        &dwDataSize);

    if (ERROR_SUCCESS == lRet) {

      tsNameOut = szBuf;
      r         = true;

    } else if (ERROR_NO_MORE_ITEMS == lRet) {

      tsNameOut = _T("");
      dwIndex   = 0UL;
      ZeroMemory(pValueData, dwDataSize);
      
    }

    return r;
  }

  bool EnumKeys(TSTRING &tsNameOut) {

    bool r                = false;
    static DWORD dwIndex  = 0UL;
    LONG lRet             = ERROR_SUCCESS;
    TCHAR szBuf[256]      = {0};

    lRet = RegEnumKey(m_hKey, dwIndex++, szBuf, 256);

    if (ERROR_SUCCESS == lRet) {

      tsNameOut = szBuf;
      r         = true;

    } else if (ERROR_NO_MORE_ITEMS == lRet) {

      tsNameOut = _T("");
      dwIndex   = 0UL;

    }

    return r;
  }
  
private:
  bool _OpenKey(HKEY hKey, CTSTRING &tsPath, bool bCreate) {

    bool r        = false;
    DWORD dwDisp  = 0UL;

    if (bCreate) {

      if (ERROR_SUCCESS == RegCreateKeyEx(hKey,
                                          tsPath.c_str(),
                                          0UL,
                                          NULL,
                                          REG_OPTION_NON_VOLATILE,
                                          KEY_ALL_ACCESS,
                                          NULL,
                                          &m_hKey,
                                          &dwDisp))
      {

        r = true;

      } else {

        m_hKey = NULL;

      }

    } else {

      if (ERROR_SUCCESS == RegOpenKeyEx(hKey,
                                        tsPath.c_str(),
                                        0UL,
                                        KEY_ALL_ACCESS,
                                        &m_hKey))
      {

        r = true;

      } else {

        m_hKey = NULL;

      }


    }

    return r;
  }

  void _CloseKey(void) { RegCloseKey(m_hKey); m_hKey = NULL; }

  bool _WriteValue(CTSTRING &tsValName, ValueType Type, const void *pVal, DWORD dwBytes) {

    bool r       = false;
    DWORD dwType = 0UL;

    switch (Type) {

      case VT_DWORD:  dwType = REG_DWORD; break;
      case VT_STRING: dwType = REG_SZ; break;
      case VT_BINARY: dwType = REG_BINARY; break;

    }

    if (ERROR_SUCCESS == RegSetValueEx(m_hKey, 
                                       (0 < tsValName.size()) ? tsValName.c_str() : NULL,
                                       0UL,
                                       dwType,
                                       static_cast<const BYTE *>(pVal),
                                       dwBytes))
    {

      r = true;

    }

    return r;
  }

  bool _ReadValue(CTSTRING &tsValName, ValueType Type, void *pVal, DWORD_PTR *pdwBytes) {

    bool r = false;

    if (ERROR_SUCCESS == RegQueryValueEx(m_hKey,
                                         (0 < tsValName.size()) ? tsValName.c_str() : NULL,
                                         0UL,
                                         NULL,
                                         static_cast<BYTE *>(pVal),
                                         pdwBytes))
    {

      r = true;

    }

    return r;
  }

protected:
  HKEY m_hKey;

};

#endif // !_REGISTRY_H
