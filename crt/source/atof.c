/*
** Converts a string to a double
**
*/
#include "stdlib.h"

double atof(const char *str)
{
	double d;
	return strtod(str, (char **)NULL);
}
