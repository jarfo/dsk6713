#ifndef C6713DSKINIT_INCLUDED_
#define C6713DSKINIT_INCLUDED_

#include "dsk6713_aic23.h"

void c6713_dsk_init(Uint32 fs);
void comm_poll(Uint32 fs);
void comm_intr(Uint32 fs);
void output_sample(int);
void output_left_sample(short);
void output_right_sample(short);
Uint32 input_sample();
short input_left_sample();
short input_right_sample();

#endif
