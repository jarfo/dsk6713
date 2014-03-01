#define MAXLEVELS 8
typedef enum {ASK,PSK,FSK} Modulation;

typedef struct {
	int *bits;                /* Bits a transmitir */
	int nbits;
	int lSymb;                /* Muestras por simbolo */
	int nbitsSymb;            /* Bits por simbolo    */
	int V;                    /* Amplitud de la senyal modulada */
	Modulation modulation;
	unsigned short nLevels;
	double coefP[MAXLEVELS],  /* coefP[i]|coefQ[i]: niveles de las componentes*/ 
	       coefQ[MAXLEVELS];  /* en fase y en cuadratura del simbolo i*/
	double *cos_fd, *sen_fd;  /* Pueden utilizarse para implementar FSK */
	double snr;
	double sdev;
	double *outp, *outq;      /* Componentes en fase y cuadratura de la senyal modulada */
	unsigned int lBuff;       /* Dimension de outp y outq */
} USER_BT;

void mpy_cos(int nSamples, double *phase, double *quad, int *out);
int  modulator_init(USER_BT *);
void modulator_ask_psk(USER_BT *);
void modulator_fsk(USER_BT *pUsr, int *out);
