/*
** Converts a string to an integer
**
*/
#include "stdlib.h"

int atoi(const char *nptr)
{
	return strtol(nptr, (char **)NULL, 10);
}
