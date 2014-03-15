#ifndef PROCESS_INCLUDED_
#define PROCESS_INCLUDED_

typedef struct {			// Estructura para filtrado IIR
	float b[L_IIR];			// Coeficientes b del numerador
	float a[L_IIR];			// Coeficientes a del denominador
	float u[L_IIR];			// Registros de desplazamiento del filtro IIR
} filter_iir2;

void init_processFIR1(float *);
void init_processFIR2(float *);
void init_processIIR(filter_iir2 *);
void processFIR(float *, float *);
void processIIR(float *, filter_iir2 *, int, int);

#endif
