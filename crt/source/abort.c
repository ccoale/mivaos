/*
** Aborts the current program
**
*/
#include "stdlib.h"

//extern void (*_clean)(void);

void abort(void)
{
	//if (_clean) _clean();
	// raise(SIGABRT);
}
