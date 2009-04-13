/*
** Finds the absolute value of an integer
**
*/
#include "stdlib.h"

int abs(int x) { return ( x < 0 ? -x : x ); }
long int labs(long int x) { return ( x < 0 ? -x : x ); }
long long int abs64(long long int x) { return ( x < 0 ? -x : x ); }
