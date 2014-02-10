//========================================================================
//         CODEC.C: Codificadores para transmision en banda base          
//========================================================================

#include "codec.h"

void cod_rz (USER *pUsr, int *out, int rz) {
   int *b, i, j, k;
   for (b=pUsr->bits, i=k=0; i < pUsr->nbits; i++) {
      if (b[i] == 0)
	 for (j=0; j < pUsr->lSymb; j++,k++)
	    out[k] = 0;
      else {
	 for (j=0; j< rz; j++,k++)
	    out[k] = b[i] * pUsr->V;
	 for (;j< pUsr->lSymb;j++, k++)
	    out[k] = 0;
      }
   }

}

void cod_polar (USER *pUsr, int *out) {
   int *b, i, j, k, x;
   for (b = pUsr->bits, i=k=0; i < pUsr->nbits; i++) {
      x = ( b[i]==1 ? pUsr->V : -pUsr->V);

      for (j=0; j< pUsr->lSymb; j++, k++)
	 out[k] = x;
   }
}

void cod_bipolar (USER *pUsr, int *out) {
   int *b, i, j, k, x;
   for (b=pUsr->bits, i=k=0; i<pUsr->nbits; i++) {
      if (b[i]==1) {
	 x = pUsr->V * pUsr->state.sgnOne;
	 pUsr->state.sgnOne = -pUsr->state.sgnOne;
      } else
	 x = 0;
      for (j=0; j<pUsr->lSymb; j++,k++)
	 out[k] = x;
   }
}

void cod_ami (USER *pUsr, int *out) {
}

void cod_cmi (USER *pUsr, int *out) {
}

void cod_hdb3 (USER *pUsr, int *out) {
//                                                                             
// PRECONDICION:  en pUsr->bits[-3], pUsr->bits[-2], pUsr->bits[-1],          
//                están almacenados los 3 simbolos {+1,0,-1} previos       
// POSTCONDICION: los bits en pUsr->bits son cambiados a simbolos {+1,0,-1} 
//                El usuario deberia copiarlos si los quiere preservar

   int *b, i, j;
   b=pUsr->bits;
   for (i=0; i<pUsr->nbits; i++) {
      if (b[i]==1) {
	 b[i] = pUsr->state.sgnOne;
	 pUsr->state.sgnOne = -pUsr->state.sgnOne;
	 pUsr->state.dc += b[i];
	 pUsr->state.zeroes = 0;
      }
      else {
	 pUsr->state.zeroes++;
	 if (pUsr->state.zeroes == 4) {
	    if (pUsr->state.dc) {
	       b[i] = b[i-3] = pUsr->state.sgnOne;

	       // Completar codigo para actualizar 
		  //pUsr->state.sgnOne y pUsr->state.dc 

	    } else {
	       b[i] = -pUsr->state.sgnOne;

	      // Completar codigo para actualizar 
		 //pUsr->state.sgnOne y pUsr->state.dc 

	    }
	    pUsr->state.zeroes = 0;
	 } 
      }
   }
   //Conformacion de pulso de los 3 bits del tramo anterior y
   //los nuevos (nbits-3) 
   // Modificacion de pUsr->bits para poder aprovechar cod_rz 
   pUsr->bits = &(pUsr->bits[-3]);
   cod_rz(pUsr, out, pUsr->lSymb);
   // Recuperación de pUsr->bits 
   pUsr->bits = b;

   // Guardar los 3 ultimos simbolos 
   for (i= -3, j = pUsr->nbits-3; i<0; i++, j++)
       b[i] = b[j];
}

void cod_manchester (USER *pUsr, int *out) {
}

void cod_dif (USER *pUsr) {
}
