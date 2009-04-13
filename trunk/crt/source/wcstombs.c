/*
**
*/
#include "stdlib.h"

size_t wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
	int i = n;
	while (--i >= 0) {
		if (!(*s++ = *pwcs++))
			break;
	}
	return n - i - 1;
}
