/*
** Implementation Dependent Values
**
*/
#ifndef _INC_LIMITS
#define _INC_LIMITS

//! The number of bits in a char.
#define CHAR_BIT		8

//! Minimum value of a signed char.
#define SCHAR_MIN		(-128)

//! Maximum value of a signed char.
#define SCHAR_MAX		127

//! Maximum value of an unsigned char.
#define UCHAR_MAX		0xFF

//! Maximum number of bytes in a multibyte character
#define MB_LEN_MAX		5

//! The minimum value of a signed short.
#define SHRT_MIN    		(-32768)

//! Maximum value of a signed short.
#define SHRT_MAX      		32767

//! Maximum value of an unsigned short.
#define USHRT_MAX     		0xFFFF

//! The minimum value of a signed int.
#define INT_MIN     		(-2147483648)

//! Maximum value of a signed int.
#define INT_MAX       		2147483647

//! Maximum value of an unsigned int.
#define UINT_MAX      		0xFFFFFFFF

//! Minimum value of a signed long.
#define LONG_MIN    		(-2147483648)

//! Maximum value of a signed long.
#define LONG_MAX      		2147483647

//! Maximum value of an unsigned long.
#define ULONG_MAX     		0xFFFFFFFFU

//! Minimum value of a signed long long (64-bit int)
#define LLONG_MAX     		9223372036854775807

//! Maximum value of a signed long long (64-bit int)
#define LLONG_MIN   		(-9223372036854775807)

//! Maximum value of an unsigned long long (64-bit uint)
#define ULLONG_MAX    		0xFFFFFFFFFFFFFFFFui64

//! The maximum value usable all-together
#define RSIZE_MAX		ULONG_MAX

#endif /* _INC_LIMITS */
