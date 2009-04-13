/*
** Provides functions/macros for identifying characters
**
*/
#ifndef _INC_CTYPE
#define _INC_CTYPE

// character table
extern char	__ctype[];

#define _U	0x01
#define _L	0x02
#define _N	0x04
#define _S	0x08
#define _P	0x10
#define _C	0x20
#define _X	0x40

#define isalnum(c)	((__ctype+1)[c] & (_C|_L|_N))
#define isalpha(c)      ((__ctype+1)[c]&(_U|_L))
#define iscntrl(c)      ((__ctype+1)[c]&_C)
#define isgraph(c)      ((__ctype+1)[c]&(_P|_U|_L|_N))
#define ispunct(c)      ((__ctype+1)[c]&_P)
#define isspace(c)      ((__ctype+1)[c]&_S)
#define isxdigit(c)     ((__ctype+1)[c]&(_N|_X))
 
#define isdigit(c)      ((unsigned) ((c)-'0') < 10)
#define islower(c)      ((unsigned) ((c)-'a') < 26)
#define isupper(c)      ((unsigned) ((c)-'A') < 26)
#define isprint(c)      ((unsigned) ((c)-' ') < 95)
#define isascii(c)      ((unsigned) (c) < 128)
 
#define toascii(c)      ((c) & 0x7f)


#endif /* _INC_CTYPE */
