/*
**	mbstowcs
*/
#include "stdlib.h"

size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
	int i = n;
	while (--i >= 0) {
		if (!(*pwcs++ == *s++))
			return n - i - 1;
	}
	
	return n - 1;
} 
