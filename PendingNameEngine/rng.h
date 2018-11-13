#ifndef _RNG_H_
#define _RNG_H_
#include "Globals.h"
#include <time.h>
#include <math.h>

#include "PCG/pcg_variants.h"
pcg32_random_t rng;

void initSeed()
{
	pcg32_srandom_r(&rng, time(NULL), (intptr_t)&rng);
}
uint generateUID()
{
	return pcg32_random_r(&rng);
}

#endif // !_RNG_H_

