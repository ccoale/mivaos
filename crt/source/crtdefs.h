/*
** Provides compiler specifics for the rest of the CRT
**
*/
#ifndef _INC_CRTDEFS
#define _INC_CRTDEFS

// find out what compiler we are using..
#if defined(__GNUC__) || defined(__GNUG)
	#define __GNU 1
#elif defined(_MSC_VER)
	#define __MSC 1
#endif

// declare common macros based on this compiler
#ifdef __GNU
	#ifdef __LP64
		#define __M64	1
	#endif /* __LP64 */
#elif defined(__MSC)
	#ifdef __WIN64
		#define __M64	1
	#endif /* __WIN64 */
#endif /* __GNU */

// declare size_t
#ifndef _SIZE_T_DECLARED
	#ifdef __M64
		typedef unsigned long long int size_t;
	#else
		typedef unsigned int size_t;
	#endif /* __M64 */

	#define _SIZE_T_DECLARED
#endif /* _SIZE_T_DECLARED */

#ifndef _RSIZE_T_DEFINED
	#ifdef __M64
		typedef unsigned long long int rsize_t;
	#else
		typedef unsigned int rsize_t;
	#endif /* __M64 */

	#define _RSIZE_T_DEFINED
#endif /* _RSIZE_T_DEFINED */

#ifndef _INTPTR_T_DEFINED
	#ifdef __M64
		typedef long long int intptr_t;
	#else
		typedef int intptr_t;
	#endif /* __M64 */

	#define _INTPTR_T_DEFINED
#endif /* _INTPTR_T_DEFINED */

#ifndef _UINTPTR_T_DEFINED
	#ifdef __M64
		typedef unsigned long long int uintptr_t;
	#else
		typedef unsigned int uintptr_t;
	#endif /* __M64 */

	#define _UINTPTR_T_DEFINED
#endif /* _UINTPTR_T_DEFINED */

#ifndef _PTRDIFF_T_DEFINED
	#ifdef __M64
		typedef long long int ptrdiff_t;
	#else
		typedef int ptrdiff_t;
	#endif /* __M64 */

	#define _PTRDIFF_T_DEFINED
#endif /* _PTRDIFF_T_DEFINED */

#ifndef _WCHAR_T_DEFINED
	typedef unsigned short wchar_t;
	typedef unsigned short wctype_t;
	
	#define _WCHAR_T_DEFINED
#endif /* _WCHAR_T_DEFINED */

#ifndef _VA_LIST_DEFINED
	typedef char *va_list;

	#define _VA_LIST_DEFINED
#endif /* _VA_LIST_DEFINED */

#ifndef _ERRCODE_DEFINED
	typedef int errcode;
	typedef int errno_t;
	#define _ERRCODE_DEFINED
#endif /* _ERRCODE_DEFINED */

#ifndef _TIME32_T_DEFINED
	typedef long int __time32_t;
	#define _TIME32_T_DEFINED
#endif /* _TIME32_T_DEFINED */

#ifndef _TIME64_T_DEFINED
	typedef long long int __time64_t;
	#define _TIME64_T_DEFINED
#endif /* _TIME64_T_DEFINED */

#ifndef _TIME_T_DEFINED
	#ifdef _USE_32BIT_TIME_T
		typedef __time32_t time_t;
	#else
		typedef __time64_t time_t;
	#endif /* _USE_32BIT_TIME_T */

	#define _TIME_T_DEFINED
#endif /* _TIME_T_DEFINED */

#endif /* _INC_CRTDEFS */

