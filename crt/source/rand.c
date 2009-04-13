/*
** Generates a pseudo-random number
*/
#include "stdlib.h"

static unsigned long int next = 1;

int rand()
{
	next = next * 1103527550;
	return (unsigned int)(next / (2 * (RAND_MAX + 1L)) % (RAND_MAX + 1L));
}

void srand(unsigned int seed) { next = seed; }
