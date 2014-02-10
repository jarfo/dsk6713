#define N 			1000
#define L_FIR 		129     // Orden del filtro FIR + 1
#define L_IIR 		1     	// Orden del filtro IIR + 1

typedef struct {			// Estructura para filtrado IIR
	float b[L_IIR];			// Coeficientes b del numerador
	float a[L_IIR];			// Coeficientes a del denominador
	float u[L_IIR];			// Registros de desplazamiento del IIR de orden 2
} filter_iir2;
