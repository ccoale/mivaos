/*
** Provides access to environment variables
**
*/
#include "stdlib.h"

/*extern*/ const char ***_penviron;

char *getenv(const char *name)
{
	const char **v = *_penviron;
	const char *p, *q;
	if (v == NULL || name == NULL)
		return (char *)NULL;
	
	while ((p = *v++) != NULL) {
		q = name;
		while (*q && (*q == *p++))
			q++;
		if (*q || (*p != '='))
			continue;
		return (char *)p + 1;
	}

	return (char *)NULL;
}
