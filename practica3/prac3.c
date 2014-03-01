//************************************************************************
//                                 PRAC3.C                                
//                                                                        
//                       Modulaciones banda trasladada                     
//========================================================================
#include <stdlib.h>
#include <math.h>
#include "modulate.h"
#include "noise.h"
#include "C6713dskinit.h"

#define SIMB_BUFF       100    // simbolos a generar por bloque 
#define AMPLITUD        16384    
// amplitud maxima de componentes en fase y cuadratura 
#define MUESTRAS_SIMBOLO 12
#define LBUFFER         MUESTRAS_SIMBOLO*SIMB_BUFF

#define ILOG2(x)   ( (int) (0.5 + log((double) (x))/log(2.0)) )

typedef struct {
   int *bits;
   int nbits;
   int index;
} SEQUENCE;

#define ninput_bits 2 //Al empezar se tomara la secuencia 10101010... 
int input_bits[]={1,0,0,0,0,1,1,1};

int buffer1[LBUFFER];
int buffer2[LBUFFER];
int *iobuffer = buffer1;
int *oblock   = buffer2; 
int sample;

interrupt void c_int11()
{
   if (sample<LBUFFER)
      output_sample(iobuffer[sample++]);
   return;
}

void init_arrays() {
   int i;
   for (i=0;i<LBUFFER;i++)
      buffer1[i] = buffer2[i] = 0;
   sample=0;
}

void init_user(USER_BT *pUsr, Modulation M, int Levels, double snr) {
    
   double l_snr;
    
   // Definicion de los niveles de la modulacion 
   pUsr->modulation = M;
   if (Levels > MAXLEVELS)
      Levels = MAXLEVELS;
   pUsr->nLevels = Levels;
   pUsr->snr = snr;

   // Inicializacion 
   pUsr->lSymb = MUESTRAS_SIMBOLO;
   pUsr->lBuff = LBUFFER;
   pUsr->nbitsSymb = ILOG2(pUsr->nLevels);
   pUsr->nbits = SIMB_BUFF * pUsr->nbitsSymb; 
   if (pUsr->bits != NULL) {
      free (pUsr->bits);
      free (pUsr->cos_fd);
      free (pUsr->sen_fd);
      free (pUsr->outp);
      free (pUsr->outq);
   }
   pUsr->bits  = (int *) malloc(sizeof(int) * pUsr->nbits);
   pUsr->outp  = (double *) malloc(sizeof(double) * pUsr->lBuff);
   pUsr->outq  = (double *) malloc(sizeof(double) * pUsr->lBuff);
   
   // Las siguientes variables pueden utilizarse para FSK 
   // Dependiendo de la implementacion seran preferibles otras definiciones 
   pUsr->cos_fd = (double *) malloc(sizeof(double) * pUsr->lSymb);
   pUsr->sen_fd = (double *) malloc(sizeof(double) * pUsr->lSymb);
   
   // ASK y PSK: Inicializa pUsr->coefP[] y pUsr->coefQ[] 
   modulator_init(pUsr);

   pUsr->V = AMPLITUD;
   // Calcular sdev a partir de snr y del esquema de modulacion
   l_snr = pow(10,pUsr->snr/10);
   switch (pUsr->modulation) {
   case ASK:
// Completar codigo 
      break;
   case FSK:
      pUsr->sdev = pUsr->V / sqrt(2*l_snr);
      break;
   case PSK: 
      pUsr->sdev = pUsr->V / sqrt(2*l_snr);
      break;
   }

}

void wait_buffer (void) {
   int *pt;
   while (sample < LBUFFER);
   pt = oblock;
   oblock = iobuffer;
   iobuffer = pt;
   sample = 0;
}

void read_bits(SEQUENCE *pSeq, int nbits, int *bits) {
   int i;
   for (i=0; i<nbits; i++) {
      bits[i] = pSeq->bits[pSeq->index++];
      if (pSeq->index == pSeq->nbits) 
         pSeq->index = 0;
   }
}

void main (void){
   Uint32 fs=DSK6713_AIC23_FREQ_16KHZ; //ajuste de la frecuencia de muestreo
   SEQUENCE seq = {input_bits, ninput_bits, 0};
   USER_BT usr;
   usr.bits = NULL;
   Modulation Mod = PSK; // Modulacion tipo
   int Lev = 2;          // Numero de simbolos
   double snr = 100.0;
   init_arrays();                    // Inicio de los arrays
   init_user(&usr, Mod, Lev, snr);   // Configuracion modulador
   comm_intr(fs);                    //inicio del DSK, codec, MCBSP
   
   while (1) {
      wait_buffer();
      read_bits(&seq, usr.nbits, usr.bits);
      if (usr.modulation != FSK) {
         modulator_ask_psk(&usr);
         if (usr.snr < 90.0) 
            add_noise(usr.lBuff, usr.sdev, usr.outp, usr.outq);
         mpy_cos  (usr.lBuff, usr.outp, usr.outq, oblock);
      }
      else {
         modulator_fsk(&usr, oblock);
      }
   }
}
