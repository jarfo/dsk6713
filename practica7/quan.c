#include <math.h>
#include "quan.h"

int quan_init(QUAN *reg, float vmax, int nbits)
{
	reg->nlevels=1<<nbits;    /* nlevels = 2^nbits */
	return 0;
}

int quan(QUAN *reg, float x)
{
	return 0;
}

float iquan(QUAN *reg,int n)
{
	return 0;
}
