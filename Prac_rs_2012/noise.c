/*********************************************************************************/
/*  NOISE.C: Funcions que sumen al senyal d'entrada soroll blanc gaussià         */
/*********************************************************************************/

#include <stdlib.h>
#include <math.h>
#include "block.h"

inline void norm(float *g1, float *g2) 
{
     	float u,v,rsq,fac;
     	do{	
		u = (float) 2*rand()/RAND_MAX -1;	
		v = (float) 2*rand()/RAND_MAX -1;	
		rsq = u*u + v*v;
     	} while(rsq==0||rsq>=1);
     	fac = sqrt((float)-2*log(rsq)/rsq);
     	*g1 = u*fac;	
     	*g2 = v*fac;
}

void add_noise(int nSamples, float stdev, float *s) 
{
   	int i;
   	float g1, g2;
   	for (i=0; i<nSamples; i=i+2)
   	{
      		norm(&g1, &g2);
      		s[i] += stdev*g1;
      		s[i+1] += stdev*g2;
   	} 
}

