#ifndef QUAN_H__
#define QUAN_H__

typedef struct {
        int nlevels;
        float delta;
        int nmax;
        int nmin;
}
QUAN;

int quan_init(QUAN *qdat, float vmax, int nbits);
int quan(QUAN *qdat, float x);
float iquan(QUAN *iqdat, int q);

#endif

