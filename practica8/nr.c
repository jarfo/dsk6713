/*****************************************************************************/
/*      NR.C: Funcions d'estimaci� espectral i modificaci� de l'espectre     */
/*****************************************************************************/

#include <math.h>
#include "block.h"

void spec_est(float *x, float *spec)  /* Calcula el periodograma */
{

	/*************************************************************************/
	/*** ESCRIURE CODI ***/
	/*************************************************************************/

}

void alpha_est(float *speechSpec, float *noiseSpec, NRstruct *nr) 
/* Decideix el valor de alpha d'acord amb la SNR estimada, segons Berouti et al. */
{
	float SNR=0, speechPower=0, noisePower=0;

	/* Estimaci� de la SNR */

	/*************************************************************************/
	/*** ESCRIURE CODI ***/
	/*************************************************************************/

	/* Estimaci� de alpha partir de la SNR estimada */
	if (SNR>-5 && SNR<20)
		nr->alpha = 4 - SNR*3/20;
	else if(SNR<-5)
		nr->alpha = 5;
	else
		nr->alpha = 1;
}

void nr_ss2(float *x, float *speechSpec, float *noiseSpec, NRstruct *nr) /* Substracci� espectral */
{

/*************************************************************************/
/*** ESCRIURE CODI ***/
/*************************************************************************/

}

