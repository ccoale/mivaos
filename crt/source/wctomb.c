/*
**
*/

#include "stdlib.h"
int wctomb(char *s, wchar_t wchar)
{
	if (!s) return 0;
	*s = wchar;
	return 1;
}
