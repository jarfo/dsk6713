#define PI		3.14159265358979
#define N 		256			/*Longitud tram de senyal*/
#define IO_N 	128 			/*Longitud bloc de dades*/
#define NFFT	N			/*Longitud FFT*/

typedef enum {rect,triang,hann,hamm} window;
typedef enum {ss2,non} nr_type; 
typedef struct {
	window win;	/*Tipus de finestra*/
	nr_type type; 	/*Tipus de processament per a la reducció de soroll*/
	int start_noise_estimation; /*1: Es fa estimació espectre soroll, 0: No es fa*/
	float stdev;	/*Desviació estàndar del soroll*/
	float alpha;	/*Paràmetre de la substracció espectral*/
	float betta;	/*Paràmetre de la substracció espectral*/
	int numT;	/*Nombre de trams que s’usen en el càlcul de l’estimació espectral del soroll*/
	float w[N];	/*Finestra*/
}NRstruct;

void analisi(float *io_data, float *blockIn, float *x, NRstruct *nr);
void sintesi(float *io_data, float *blockOut, float *x);
void fftr(float *, int, int);
void wait_buffer(void);   
void init_NR(NRstruct *nr, window win, nr_type type, int start_noise_estimation, float stdev, float alpha, float betta, int numT, float *io_data);    
void spec_est(float *x, float *spec);
void alpha_est(float *speechSpec, float *noiseSpec, NRstruct *nr);
void nr_ss2(float *x, float *speechSpec, float *noiseSpec, NRstruct *nr);
void add_noise(int nSamples, float stdev, float *x);
void process(float *, NRstruct *);

