/*
** Converts a string to a long integer
**
*/
#include "stdlib.h"
#include "ctype.h"

long int atol(const char *nptr)
{
	long int total = 0;
	int minus = 0;
	while (isspace(*nptr)) nptr++;
	if (*nptr == '+') nptr++;
	else if (*nptr == '-') {
		minus = 1;
		nptr++;
	}
	while (isdigit(*nptr)) {
		total *= 10;
		total += (*nptr++ - '0');
	}

	return minus ? -total : total;
}
