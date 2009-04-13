/*
** Returns the length of a multibyte string
*/
#include "stdlib.h"


int mblen(const char *s, size_t n)
{
	if (s == (const char *)NULL) return 0;
	if (n <= 0) return 0;
	return (*s != 0);
}
