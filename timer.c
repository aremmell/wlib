#include "Timer.h"

int Timer_Begin(PTIMERSTRUCT pt) {

	if (NULL == pt) { return 0; }
	
	//
	// Grab current time information
	//
	ftime(&pt->s);
	
	return 1;
}

int Timer_Stop(PTIMERSTRUCT pt) {

	if (NULL == pt) { return 0; }

	//
	// Grab current time information
	//
	ftime(&pt->e);

	//
	// Perform calculations
	//
	if (1 == (pt->e.time - pt->s.time)) {

		if (pt->e.millitm == pt->s.millitm) {

			pt->dwSec   = 1UL;
			pt->usMsec  = 0U;

		}

		pt->dwSec  = 0UL;
		pt->usMsec = ((pt->e.millitm + 1000U)) - (pt->s.millitm);

	} else {

		if (pt->e.millitm < pt->s.millitm) {

			pt->e.time--;
			pt->dwSec      = pt->e.time - pt->s.time;
			pt->e.millitm += 1000U;
			pt->usMsec     = (pt->e.millitm - pt->s.millitm);

		} else {

			pt->dwSec   = pt->e.time - pt->s.time;
			pt->usMsec  = (pt->e.millitm - pt->s.millitm);

		}

	}

	return 1;
}
