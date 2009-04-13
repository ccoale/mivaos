/*
** Declarations and definitions of commonly used library functions
**
*/
#ifndef _INC_STDLIB
#define _INC_STDLIB
#include "crtdefs.h"
#include "limits.h"

// Define our NULL value. If we are in c++ it can be 0, otherwise it needs to be ((void *)0).
#ifndef NULL
	#ifdef __cplusplus
		//! NULL value
		#define NULL 0
	#else /* __cplusplus */
		#define NULL ( (void *)0 )
	#endif /* __cplusplus */
#endif

// exit() function arguments

//! A successful exit was made.
#define EXIT_SUCCESS		0

//! A non-successful exit was made.
#define EXIT_FAILURE		1

//! Maximum length of a path name
#define _MAX_PATH   		260

//! Maximum length of a directory name
#define _MAX_DIR    		256

//! Maximum length of a file name (without extension)
#define _MAX_FNAME  		256

//! Maximum length of a file extension
#define _MAX_EXT    		256

//! Sizes for buffers used by the getenv/putenv family of functions.
#define _MAX_ENV 		32767

struct div_t
{
	int quot;
	int rem;
};

struct ldiv_t
{
	long int quot;
	long int rem;
};

// Function prototypes..
#ifndef _CRT_TERMINATE_DEFINED
	#define _CRT_TERMINATE_DEFINED
	void exit(int code);
#endif /* _TERMINATE_DEFINED */

#ifndef _CRT_ABS_DEFINED
	#define _CRT_ABS_DEFINED
	int abs(int x);
	long int labs(long int x);
	long long int abs64(long long int x);
#endif /* _CRT_ABS_DEFINED */

#ifndef _CRT_ATOF_DEFINED
	#define _CRT_ATOF_DEFINED
	double atof(const char *str);
#endif /* _CRT_ATOF_DEFINED */

#ifndef _CRT_BSEARCH_DEFINED
	#define _CRT_BSEARCH_DEFINED
	void *bsearch(const void *key, const void *base, size_t num, size_t size, int (* comparator)(const void *, const void *));
#endif /* _CRT_BSEARCH_DEFINED */

#ifndef _CRT_QSEARCH_DEFINED
	#define _CRT_QSEARCH_DEFINED
	void qsort(void *base, size_t num, size_t size, int (* comparator)(const void *, const void *));
#endif /* _CRT_QSEARCH_DEFINED */

#ifndef _CRT_GETENV_DEFINED
	#define _CRT_GETENV_DEFINED
	char *getenv(const char *name);
#endif /* _CRT_GETENV_DEFINED */

#ifndef _CRT_ASTRFUNCTIONS_DEFINED
	#define _CRT_ASTRFUNCTIONS_DEFINED
	int atoi(const char *str);
	long int atol(const char *str);
	double strtod(const char *str, char **endptr);
	long int strtol(const char *str, char **endptr, int base);
	unsigned long int stroul(const char *str, char **endptr, int base);
	int mblen(const char *pmb, size_t max);
	int mbtowc(wchar_t *pwc, const char *pmb, size_t max);
	int wctomb(char *pmb, wchar_t character);
	size_t mbstowcs(wchar_t *wcstr, const char *mbstr, size_t max);
	size_t wcstombs(char *mbstr, const wchar_t *wcstr, size_t max);
#endif /* _CRT_STRFUNCTIONS_DEFINED */

#ifndef _CRT_MISCFUNCTIONS_DEFINED
	#define _CRT_MISCFUNCTIONS_DEFINED
	int rand();
	void srand(unsigned int seed);
	struct div_t div(int num, int den);
	struct ldiv_t ldiv(long int num, long int den);
#endif /* _CRT_MISCUNCTIONS_DEFINED */

#ifndef _CRT_MALLOCFUNCTIONS_DEFINED
	#define _CRT_MALLOCFUNCTIONS_DEFINED
	void *calloc(size_t num, size_t size);
	void free(void *ptr);
	void *malloc(size_t size);
	void *realloc(void *ptr, size_t size);
#endif /* _CRT_MALLOCFUNCTIONS_DEFINED */

#ifndef _CRT_SYSFUNCTIONS_DEFINED
	#define _CRT_SYSFUNCTIONS_DEFINED
	void abort();
	int atexit(void (*func)());
	int system(const char *command);
#endif /* _CRT_SYSFUNCTIONS_DEFINED */

#ifndef _RAND_MAX_DEFINED
	#define _RAND_MAX_DEFINED
	#define RAND_MAX	(0xFFFF)
#endif /* _RAND_MAX_DEFINED */


#endif /* _INC_STDLIB */
