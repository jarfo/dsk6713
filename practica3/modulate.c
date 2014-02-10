//************************************************************************
//             MODULATE.C: Moduladores ASK, PSK y FSK                      
//************************************************************************
#include "modulate.h"
#include "math.h"
#define SQRT2s2 0.70710678118655 // sin(pi/4) 
#ifndef PI
#define PI 3.141592653
#endif

void mpy_cos(int nSamples, double * phase, double *quad, int *x) 
{
   static const double Cos[4]= {1.0, 0.0, -1.0,  0.0};
   static const double Sin[4]= {0.0, 1.0,  0.0, -1.0};
   static int j=0;
   int i;
   for (i=0; i<nSamples; i++) {
      x[i]= (int) (phase[i]*Cos[j] - quad[i]*Sin[j]);
      j = (j == 3 ? 0 : j+1);
   }
}

int modulator_init(USER_BT *pUsr) 
{ 
   // GRAY CODE 
   int i, error = 0;
   double x;
   switch (pUsr->modulation) {
  case ASK:
      for (i=0;i<pUsr->nLevels;i++)
	 pUsr->coefP[i] = pUsr->coefQ[i] = 0.0;

      switch (pUsr->nLevels) {
      case 2:
	 pUsr->coefP[0] = 0.0;
	 pUsr->coefP[1] = 1.0;
	 break;
      case 4:
	 x = 1.0/3.0;
	 pUsr->coefP[0] = 0.0;
	 pUsr->coefP[1] =   x;
	 pUsr->coefP[3] = 2*x;
	 pUsr->coefP[2] = 1.0;
	 break;
      case 8:
	 x = 1.0/7.0;
	 pUsr->coefP[0] = 0.0;
	 pUsr->coefP[1] =   x;
	 pUsr->coefP[3] = 2*x;
	 pUsr->coefP[2] = 3*x;
	 pUsr->coefP[6] = 4*x;
	 pUsr->coefP[7] = 5*x;
	 pUsr->coefP[5] = 6*x;
	 pUsr->coefP[4] = 1.0;
	 break;
      default:
	// Error: el modulador no esta preparado
	//   para cualquier numero de niveles 
	   error = 1;
      }
      break;
   case PSK:
      for (i=0; i< pUsr->nLevels;i++)
	 pUsr->coefP[i] = pUsr->coefQ[i] = 0.0;
      switch (pUsr->nLevels) {
      case 2:
	 pUsr->coefP[0] =  1.0;
	 pUsr->coefP[1] = -1.0;
	 break;
      case 4:
	 pUsr->coefP[0] =  SQRT2s2; pUsr->coefQ[0] =  SQRT2s2;
	 pUsr->coefP[2] = -SQRT2s2; pUsr->coefQ[2] =  SQRT2s2;
	 pUsr->coefP[3] = -SQRT2s2; pUsr->coefQ[3] = -SQRT2s2;
	 pUsr->coefP[1] =  SQRT2s2; pUsr->coefQ[1] = -SQRT2s2;
	 break;
      case 8:
	 pUsr->coefP[0] =      1.0; pUsr->coefQ[0] =      0.0;
	 pUsr->coefP[1] =  SQRT2s2; pUsr->coefQ[1] =  SQRT2s2;
	 pUsr->coefP[3] =      0.0; pUsr->coefQ[3] =      1.0;
	 pUsr->coefP[2] = -SQRT2s2; pUsr->coefQ[2] =  SQRT2s2;
	 pUsr->coefP[6] =     -1.0; pUsr->coefQ[6] =      0.0;
	 pUsr->coefP[7] = -SQRT2s2; pUsr->coefQ[7] = -SQRT2s2;
	 pUsr->coefP[5] =      0.0; pUsr->coefQ[5] =     -1.0;
	 pUsr->coefP[4] =  SQRT2s2; pUsr->coefQ[4] = -SQRT2s2;
	 break;
      default:
	// Error: el modulador no esta preparado
	//   para cualquier numero de niveles 
	   error = 1;
      }
      break;
   case FSK:
   // Completar codigo. Pueden utilizarse las variables 
      //pUsr->cos_fd y pUsr->sen_fd 

     break;
   }
   return error;
}


void modulator_ask_psk(USER_BT *pUsr) {

   double ampP, ampQ, *outp = pUsr->outp, *outq = pUsr->outq;
   int i, j, k, symb;
   
   for (i=k=0; i< pUsr->nbits;) {

      symb = pUsr->bits[i++];
      for (j=1; j<pUsr->nbitsSymb;j++)
	  symb = 2*symb + pUsr->bits[i++];
      ampP= pUsr->V * pUsr->coefP[symb];
      ampQ= pUsr->V * pUsr->coefQ[symb];
     
      for (j=0; j < pUsr->lSymb; j++) {
	 	outp[k] = ampP;
	 	outq[k++] = ampQ;
      }
   }
}

void modulator_fsk(USER_BT *pUsr) {
//   double *outp = pUsr->outp, *outq = pUsr->outq;
//	Completar el código
}
