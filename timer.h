#ifndef _TIMER_H_INCLUDED
#define _TIMER_H_INCLUDED

#include <Windows.h>
#include <sys/timeb.h>

typedef struct {

	DWORD dwSec;
	USHORT usMsec;
	struct timeb s;
	struct timeb e;

} TIMERSTRUCT, *PTIMERSTRUCT;

#ifdef __cplusplus
extern "C" {
#endif

int Timer_Begin(PTIMERSTRUCT pt);
int Timer_Stop(PTIMERSTRUCT pt);

#ifdef __cplusplus
}
#endif

#endif // !_TIMER_H_INCLUDED
