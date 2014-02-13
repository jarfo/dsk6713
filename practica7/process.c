#include "process.h"
#include "ulaw.h"
#include "quan.h"
#include "dpcm.h"
#include "adpcm.h"

typedef enum {CT_MULAW, CT_QUAN, CT_DPCM, CT_ADPCM} CODER;

static CODER coder = CT_MULAW;
static float vmax  =    24000;
static int   nbits =        3;

static QUAN cqdat, dqdat;

void init_process(void)
{
    quan_init(&cqdat, vmax, nbits);
    quan_init(&dqdat, vmax, nbits);
}

void process(float *io_data)
{
    int i, code;

    for (i=0; i<BLOCK_SIZE; i++)
    {
	switch (coder) {
	case CT_MULAW:
	    code = ulaw_compress(io_data[i]);
	    io_data[i] = ulaw_expand(code);
	    break;

	case CT_QUAN:
	    code = quan(&cqdat, io_data[i]);
	    io_data[i] = iquan(&dqdat, code);
	    break;

	case CT_DPCM:
	    io_data[i] = 0;
		break;

	case CT_ADPCM:
	    io_data[i] = 0;
		break;

	default:
	    io_data[i] = 0;
	    break;

	}
    }
}

