#ifndef _MUTEX_H
#define _MUTEX_H

#include "stdafx.h"

/*
 * Mutex Class
 *
 * Provides a simple
 * wrapper for Win32 Mutex
 * objects.
 */
class Mutex {

public:
  Mutex() {

    m_tsName  = _T("");
    m_hMutex  = NULL;

  }
  virtual ~Mutex() {

    Detach();

  }

  Mutex &operator=(const Mutex &in) {

    m_tsName = in.m_tsName;
    m_hMutex = in.m_hMutex;

    return (*this);
  }

 /*
  * Creates a new Mutex object.
  */
  bool Create(LPSECURITY_ATTRIBUTES lpSA = NULL, BOOL bInitialOwn = TRUE,
              const TCHAR *szName = NULL)
  {

    bool r = false;

    Detach();

    if (NULL != (m_hMutex = CreateMutex(lpSA, bInitialOwn, szName))) {

      m_tsName  = szName;
      r         = true;

    }

    return r;
  }

 /*
  * Locks the Mutex.
  */
  DWORD Lock(DWORD dwMsec = INFINITE) {

    return WaitForSingleObject(m_hMutex, dwMsec);
  }

 /*
  * Releases control of the mutex
  */
  bool Unlock(void) {

    bool r = false;

    if (TRUE == ReleaseMutex(m_hMutex)) {

      r = true;

    }

    return r;
  }

 /*
  * Attaches this class instance
  * to an existing Mutex object.
  */
  void Attach(HANDLE hMutex, CTSTRING tsName = _T("")) {

    Detach();

    m_hMutex  = hMutex;
    m_tsName  = tsName;

  }

 /*
  * Resets the state of this
  * class instance, and detaches
  * any Mutex objects.
  */
  void Detach(void) {

    if (NULL != m_hMutex) {

      CloseHandle(m_hMutex);

    }

    m_tsName  = _T("");
    m_hMutex  = NULL;

  }

protected:
  TSTRING m_tsName;
  HANDLE  m_hMutex;

};

#endif // !_MUTEX_H
