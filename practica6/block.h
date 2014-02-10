#define IO_N	256
#define INTERP	4					// Interpolation factor in frequency. Must be >=1
#define NFFT	IO_N*INTERP			// Must be a power of 2
#define PI		3.14159265358979

typedef enum {rect,barl,hann,hamm,blac} window;
void fftr(float *, int, int);
  
