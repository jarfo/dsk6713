#include <math.h>
#include <stdlib.h>
#include "block.h"
#include "process.h"

#define PI 3.141592654
#define WC (PI/2)

float sinc(float s) {
    if (s==0)
        return(1);
    else
        return(sin(s)/s);
}

// Filtrado FIR paso alto obtenido mediante enventadado de Hamming
void init_processFIR1(float *h) {
	int n;
    for (n=0; n<L_FIR; n++) {
        h[n] = -(WC/PI)*sinc(WC*(n-(L_FIR-1)/2));      // Highpass filter
        if (n==(L_FIR-1)/2)
            h[n] = h[n] + 1;
        h[n] *= (0.54 - 0.46*cos((2*PI*n)/L_FIR));     // Hamming window
    }
}

// Filtrado FIR con coeficientes obtenidos en MATLAB
void init_processFIR2(float *h) {

// Pegue entre corchetes en la definición de hh la lista de los coeficientes 
// obtenidos con MATLAB

    float hh[]={0};
    int n;

    for (n=0; n<L_FIR; n++)
        h[n] = hh[n];

}

void fir(float *x, float *y, float *h, int k, int n) {
// Complete el código
}


void processFIR(float *block, float *h)
{
    int i;
    static float x[(L_FIR-1)+N];         // FIR Input buffer             

    for (i=0; i<N; i++) x[L_FIR-1+i] = block[i];
    fir(x, block, h, L_FIR, N);
    for (i=0; i<(L_FIR-1); i++) x[i] = x[i+N];
}

void init_processIIR(filter_iir2 *h) {
    int i;

// Pegue entre corchetes en la definición de a y de b la lista de los coeficientes 
// obtenidos con MATLAB

    float a[] = {0};
    float b[] = {0};

    for (i=0; i<L_IIR; i++) {
        h->a[i] = a[i];
        h->b[i] = b[i];
        h->u[i] = 0.0;
    }
}

void processIIR(float *x, filter_iir2 *h, int k, int n) {
// Complete el código
}

