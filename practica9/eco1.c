#include "C6713dskinit.h"
#include <math.h>
#include <stdlib.h>
#include "eco1.h"

float io1[N], io2[N];	    // Reserva espacio para los buffers
float *io_block,*io_buffer;	// Puntero del bloque a procesar
int index=0;

float y_gen[M];                 /* Buffer de memoria interna del generador de eco */
float a[La];			

interrupt void c_int11()        /* Rutina de servicio de interrupcion */
{  	
    if (index < N) {
        output_sample((int) io_buffer[index]);
        io_buffer[index++] = (float) input_left_sample();
    }
    return;
}

void init_buffer_block(void)
{
    io_buffer = io1;
    io_block  = io2;
}

void wait_buffer_block(void)
{
    float *ptmp;			// Puntero auxiliar			

    while(index < N);		// Espera a que se llene el buffer	
    ptmp = io_buffer;		// Intercambia punteros: 		
    io_buffer = io_block;	// nuevo buffer de entrada/salida	
    io_block = ptmp;		// nuevo bloque de datos		
    index = 0;				// Inicializa index			
}

void init_proc_eco(void)
{
    int n;
    /* Inicialitzacio coeficients a */
    for (n=0; n<La; n++)
        a[n] = 0;
    a[9] = 0.5;

    /* Inicialitzacio y_gen */
    for (n=0; n<M; n++)
        y_gen[n] = 0;
}

void eco_gen(float * io_block, float * y_gen, float * a)
{
	int i, j, k, n;
	float G = 0.1;
	float sum;

	for (i=0; i<M-N; i++)
	    y_gen[i] = y_gen[i+N];

    for (i=M-N, j=0; i<M; i++, j++)
		y_gen[i] = io_block[j];

	for (n=0; n<N; n++)
	{
	    sum = 0;
		for(k=0; k<La; k++)
			sum += a[k]*y_gen[La-1+n-k];
		y_gen[M-N+n] = G*y_gen[M-N+n]+sum;
		io_block[n] = y_gen[M-N+n];
	}

}

void main()
{
	Uint32 fs=DSK6713_AIC23_FREQ_16KHZ; // Sampling frequency selection
	init_proc_eco();
	init_buffer_block();
	comm_intr(fs);                   	// DSK & codec initialization

	while(1)                            // Infinite loop
	{
        wait_buffer_block();            // Wait buffer to be filled
        eco_gen(io_block, y_gen, a);
	}	 
}

