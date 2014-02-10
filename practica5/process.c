#include <math.h>
#include <stdlib.h>
#include "block.h"
#include "fftr.h"

float h[NFFT];
float x[NFFT];

void init_process()		// Filtrado FIR con coeficientes obtenidos en MATLAB
{

// Pegue entre corchetes en la definición de hh la lista de los coeficientes 
//obtenidos con MATLAB

	float hh[]={0};
    int n;

    for (n=0; n<L_FIR; n++)
		h[n] = hh[n];
	for (; n<NFFT; n++)
		h[n] = 0.0;
	fftr(h, NFFT, 1);

}

void cc(float *y,float *H)
{
    // Complete el código 

	fftr(y, NFFT, 1);		//  FFT directa
    // Complete el código 

    fftr(y, NFFT, -1);		//  FFT inversa

}


void process(float *block)
{
    // Complete el código 
	
    cc(x,h);
    // Complete el código 

}

