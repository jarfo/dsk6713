/****************************************************************************/
/*      ANALISINT.C: Funcions per a anàlisi i síntesi amb encavalcament        */
/****************************************************************************/

#include <math.h>
#include "fftr.h"
#include "block.h"

void analisi(float *io_data, float *blockIn, float *x, NRstruct *nr)
{

// Suposa que cada bloc de processament (tram) conté dos blocs de dades.
// Usa el vector auxiliar blockIn.
// Posa a x la transformada de Fourier del tram de senyal.

  int n;
  
  for(n=0;n<IO_N;n++)
  	blockIn[n+IO_N] = io_data[n]; // Posa el bloc actual al final de blockIn
  
  for(n=0;n<N;n++)
	x[n] = blockIn[n]*(nr->w[n]); // Multiplica el tram que s'analitza per la finestra

  fftr(x,N,1);		//  FFT directa
 
  for(n=0;n<IO_N;n++)
	blockIn[n] = blockIn[n+IO_N]; // Posa el bloc actual al principi de blockIn per a la iteració següent
}


void sintesi(float *io_data, float *blockOut, float *x)
{

// Suposa que cada bloc de processament (tram) conté dos blocs de dades. 
// Usa el vector auxiliar blockOut.
// Rep a través de x la transformada de Fourier del tram de senyal modificat.

  int n;

  fftr(x, N, -1);		//  FFT inversa

  for(n=0;n<N;n++)
  	blockOut[n]+=x[n]; // Acumula el tram actual amb la part solapada de l'anterior
  
  for (n=0;n<IO_N;n++) 
  	io_data[n] = blockOut[n]; // Passa a la sortida D/A el bloc resultant de l'acumulació

//Prepara blockOut per a la iteració següent

/*************************************************************************/
/*** ESCRIURE CODI ***/
/*************************************************************************/

}

