/********************************************************************/
/*      NOISE.C: Módulos que suman ruido blanco gaussiano a la      */
/*               señal de entrada                                   */
/********************************************************************/

#include <stdlib.h>
#include <math.h>
#include "noise.h"

inline void tsgs2 (double *g1, double *g2) {
   double u, v, x, env, ph;

   u = (double) rand() /RAND_MAX;
   v = (double) rand() /RAND_MAX;
   x = log(u);
   env = sqrt(-2*x);
   ph = 2*PI*v;
   *g1 = env*cos(ph);
   *g2 = env*sin(ph);
}

void add_noise(int nSamples, double stdev, double *xf, double *xq) {
   int i;
   double g1,g2;

   for (i=0; i<nSamples; i++) {
      tsgs2(&g1,&g2);
      xf[i] += stdev*g2;
      xq[i] += stdev*g1;
   }
}
