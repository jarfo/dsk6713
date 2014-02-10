#include <math.h>
#include <stdlib.h>
#include "block.h"

float x[IO_N];						// Generated sinusoid
float y[NFFT];						// Sum of generated sinusoid and signal from ADC
float w[NFFT];						// Window
float s[NFFT/2+1];					// Contains the estimated spectrum

void init_process(window win)		// Window initialisation
{
    int i; 
    float theta;
    
    theta = (2*PI)/IO_N;

    // Crear tipo de ventana
    switch (win){
    	case rect:
	// COMPLETAR CODIGO Rectangular window
	    break;
    	case barl:
	// COMPLETAR CODIGO Barlett window
	    break;
    	case hann:
	// COMPLETAR CODIGO  Hanning window
	    break;
    	case hamm:
    		for (i=0; i<IO_N; i++)  
				w[i] = 0.54 - 0.46*cos(i*theta);	// Hamming window
	    break;
    	case blac:
	// COMPLETAR CODIGO Blackman window
    	break;
    }

    for (; i<NFFT; i++) w[i] = 0;

}

void rsin(int ns, float *x, float a, float state[2])
{
	// COMPLETAR CODIGO
}

void spec(float *x, float *w, float *s, int ns)
{
	// COMPLETAR CODIGO
}

void process(float *block)
{
    int i;
    static float state[2] = {-10000,10000};
    static float a = -1.0;

    // Genera una sinusoide de forma recurrente
    rsin(IO_N, x, a, state);

    // Suma la señal generada a la recogida del conversor A/D
    for (i=0; i<IO_N; i++)
		y[i] = x[i] + block[i];
    for (; i<NFFT; i++)
		y[i] = 0.0;

    // Analisis espectral
    spec(y, w, s, NFFT);

	// Env¡a al conversor D/A la sinusoide generada
    for (i=0; i<IO_N; i++)
		block[i] = x[i];

}

