/*
** Performs division
*/
#include "stdlib.h"

static long int tmp = -1;

struct div_t div(int numer, int denom)
{
	struct div_t r;
	if (tmp == -1) {
		tmp = (tmp / 2 == 0);
	}
	if (numer == 0) {
		r.quot = numer/denom;
		r.rem = numer % denom;
	} else if (! tmp && ((numer < 0) != (denom < 0))) {
		r.quot = (numer / denom) + 1;
		r.rem = numer - (numer / denom + 1) * denom;
	} else {
		r.quot = numer/denom;
		r.rem = numer % denom;
	}

	return r;
}

struct ldiv_t ldiv(long int numer, long int denom)
{
	struct ldiv_t r;
	if (tmp == -1) {
		tmp = (tmp / 2 == 0);
	}
	if (numer == 0) {
		r.quot = numer/denom;
		r.rem = numer % denom;
	} else if (! tmp && ((numer < 0) != (denom < 0))) {
		r.quot = (numer / denom) + 1;
		r.rem = numer - (numer / denom + 1) * denom;
	} else {
		r.quot = numer/denom;
		r.rem = numer % denom;
	}

	return r;
}
