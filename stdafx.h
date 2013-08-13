#ifndef _WLIB_STDAFX_H
#define _WLIB_STDAFX_H

#include <Windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <string>
#include <list>
#include <stdarg.h>
#include <shlwapi.h>

typedef std::basic_string<TCHAR> TSTRING, *PTSTRING;
typedef const TSTRING CTSTRING, *PCTSTRING;

typedef std::list<TSTRING> TSTRINGLIST, *PTSTRINGLIST;
typedef TSTRINGLIST::iterator TSTRINGLISTIT, *PTSTRINGLISTIT;

#endif // _WLIB_STDAFX_H
