/*
**
*/
#include "stdlib.h"

int mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	if (s == (const char *)NULL) return 0;
	if (n <= 0) return 0;
	if (pwc) *pwc = *s;
	return (*s != 0);
}
