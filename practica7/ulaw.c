/* ULAW.C	UGST/CCITT G711 (ulaw) MODULE				*/
#include "ulaw.h"

int ulaw_compress(float input)
{
    int i;		/* aux.var. */
    int absno;		/* absolute value of linear (input) sample */
    int segno;		/* segment (Table 2/G711, column 1) */
    int low_nibble;	/* low  nibble of log companded sample */
    int high_nibble;	/* high nibble of log companded sample */
    int output;		/* log companded sample */

    absno = (int) input;
	absno = absno >> 3;  /* from 16 bits to 13 bits */
    absno = absno < 0 ? (~absno) + 33 : absno + 33;
    if (absno > (0x1FFF)) absno = (0x1FFF);

    /* Determination of sample's segment */
    i = absno >> 6;
    segno = 1;
    while (i != 0) { segno++; i >>= 1; }

    /* Mounting the high-nibble of the log-PCM sample */
    high_nibble = (0x0008) - segno;

    /* Mounting the low-nibble of the log-PCM sample */
    low_nibble = (absno >> segno) & (0x000F);
    low_nibble = (0x000F) - low_nibble;

    /* Joining the high-nibble and the low-nibble of the log-PCM sample */
    output = (high_nibble << 4) | low_nibble;

    /* Add sign bit */
    if (input >= 0) output = output | (0x0080);

    return(output);
}

float ulaw_expand(int input)
{
    int segment;	/* segment (Table 2/G711, column 1) */
    int mantissa;	/* low  nibble of log companded sample */
    int exponent;	/* high nibble of log companded sample */
    int sign;		/* sign of output sample */
    int step;
    float output;

    sign = input < (0x0080) ? -1 : 1;
    mantissa = ~input;
    exponent = (mantissa >> 4) & (0x0007);
    segment = exponent + 1;
    mantissa = mantissa & (0x000F);

    /* Compute Quantized Sample (14 bit left justified) */
    step = 1 << segment;
    output = (float)
	(sign*((0x20 << exponent) + step * mantissa + (step >> 1) - 33));

	output = output*8;  /* from 13 bits to 16 bits */
    return(output);
}
