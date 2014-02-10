#include <math.h>
#include <stdlib.h>
#include "quan.h"


int quan_init(QUAN *reg, float vmax, int nbits)
{
	reg->nlevels = 1<<nbits;
// Completar el código

	return 0;
}

int quan(QUAN *reg, float x)
{
// Completar el código
}

float iquan(QUAN *reg, int n)
{
// Completar el código
}


void process(QUAN *reg, float *block)
{
// Completar el código
}

