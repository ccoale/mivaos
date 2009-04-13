/*
** Converts a string to a long integer
*/

#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "stdlib.h" 

 static unsigned long int string2long( const char *nptr, char **endptr,
                         int base, int is_signed);
 
 long int strtol( const char *nptr, char **endptr, int base)
 {
         return (signed long)string2long(nptr, endptr, base, 1);
 }
 
 unsigned long int strtoul( const char *nptr, char **endptr, int base)
 {
         return (unsigned long)string2long(nptr, endptr, base, 0);
 }
 
 #define between(a, c, z)  ((unsigned) ((c) - (a)) <= (unsigned) ((z) - (a)))
 
 static unsigned long int string2long( const char *nptr, char ** const endptr,
                         int base, int is_signed)
 {
          unsigned int v;
          unsigned long int val = 0;
          int c;
         int ovfl = 0, sign = 1;
         const char *startnptr = nptr, *nrstart;
 
         if (endptr) *endptr = (char *)nptr;
         while (isspace(*nptr)) nptr++;
         c = *nptr;
 
         if (c == '-' || c == '+') {
                 if (c == '-') sign = -1;
                 nptr++;
         }
         nrstart = nptr;                 /* start of the number */
 
         /* When base is 0, the syntax determines the actual base */
         if (base == 0)
                 if (*nptr == '0')
                         if (*++nptr == 'x' || *nptr == 'X') {
                                 base = 16;
                                 nptr++;
                         }
                         else    base = 8;
                 else    base = 10;
         else if (base==16 && *nptr=='0' && (*++nptr =='x' || *nptr =='X'))
                 nptr++;
 
         for (;;) {
                 c = *nptr;
                 if (between('0', c, '9')) {
                         v = c - '0';
                 } else
                 if (between('a', c, 'z')) {
                         v = c - 'a' + 0xa;
                 } else
                 if (between('A', c, 'Z')) {
                         v = c - 'A' + 0xA;
                 } else {
                         break;
                 }
                 if (v >= base) break;
                 if (val > (ULONG_MAX - v) / base) ovfl++;
                 val = (val * base) + v;
                 nptr++;
         }
         if (endptr) {
                 if (nrstart == nptr) *endptr = (char *)startnptr;
                 else *endptr = (char *)nptr;
         }
 
         if (!ovfl) {
                 /* Overflow is only possible when converting a signed long. */
                 if (is_signed
                     && (   (sign < 0 && val > -(unsigned long)LONG_MIN)
                         || (sign > 0 && val > LONG_MAX)))
                     ovfl++;
         }
 
         if (ovfl) {
                 errno = ERANGE;
                 if (is_signed)
                         if (sign < 0) return LONG_MIN;
                         else return LONG_MAX;
                 else return ULONG_MAX;
         }
         return (long) sign * val;
 }

