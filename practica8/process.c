#include <math.h>
#include <stdlib.h>
#include "block.h"
#include "fftr.h"

float sp_spec[NFFT];
float no_spec[NFFT];
float blockIn[N], blockOut[N];
float x[NFFT];									
float w[N];

void init_NR(NRstruct *nr, window win, nr_type type, int start_noise_estimation, float stdev, float alpha, float betta, int numT, float *io_data) 
/* Inicialitza vectors i paràmetres */ 
{
    int n;
    int i; 
    float theta=(2*PI)/N;
    
    for(n=0;n<N;n++)
    {
    	blockIn[n] = 0;
	blockOut[n] = 0;
    }

    for(n=0;n<IO_N;n++)
    {
	io_data[n]=0;
    }

    nr->win =win;
    nr->type = type;
    nr->start_noise_estimation = start_noise_estimation;
    nr->stdev = stdev;
    nr->alpha = alpha;
    nr->betta = betta;
    nr->numT = numT;

    /*Crea finestra*/

	switch (win)
	{
    	case rect:						/* Rectangular */ 
			for(i=0;i<N;i++) nr->w[i] = 1; 
    		break;

    	case triang:					/* Barlett */
    		break;

    	case hann:						/* Hanning */
			for(i=0;i<N;i++) nr->w[i] = 0.5 - 0.5*cos(i*theta); 
			break;

    	case hamm:						/* Hamming */
    		for (i=0; i<N; i++) nr->w[i] = 0.54 - 0.46*cos(i*theta);
	    	break;
    }
}

void process(float *io_data, NRstruct *nr)
{
	static int compt;
	int n;
	float lambda=0.95;

/* Generació i suma de soroll blanc*/

//	add_noise(IO_N, nr->stdev, io_data); 	

/* Anàlisi del senyal: enfinestrament i DFT */

	analisi(io_data, blockIn, x, nr); 

/* Estimació espectral del soroll usant la funció spec_est i el paràmetre lambda. El resultat
es posa a no_spec */

	if (nr->start_noise_estimation)
	{
 		compt = 0;		// Comptador de segments-trams inclosos en l'estimació espectral del soroll
		for(n=0;n<NFFT;n++) no_spec[n] = 0; 
		nr->start_noise_estimation = 0;	
	}

	if(compt < nr->numT)
	{

/*************************************************************************/
/*** ESCRIURE CODI ***/
/*************************************************************************/

	}
	
	else
	{

/* Processament en freqüència: nr_ss2 fa substracció espectral usant el mòdul al quadrat */
//	spec_est(x, sp_spec);
//	alpha_est(sp_spec, no_spec, nr)
//	nr_ss2(x, sp_spec, no_spec, nr);  
 	}   

	sintesi(io_data, blockOut, x); 	/* Síntesi */
}

