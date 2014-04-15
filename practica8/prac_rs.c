#include "C6713dskinit.h"		// Suport codec-DSK
#include "block.h"

float io1[IO_N], io2[IO_N];	    	// Reserva espai buffers
float *io_block,*io_buffer;		// Punters del blocs d'adquisició i processament 
int index=0;

interrupt void c_int11()         	// Rutina de servei d'interrupció
{  	
    if (index < IO_N)
    {
 	output_sample((int)io_buffer[index]);
	io_buffer[index++]=(float)input_left_sample();
    }
    return;
}

void init_buffer(void)
{
    io_buffer = io1;
    io_block  = io2;
}

void wait_buffer(void)
{
    float *ptmp;			// Punter auxiliar			
    while(index < IO_N);	// Espera que s'ompli el buffer
    ptmp = io_buffer;		// Intercanvia punters: 		
    io_buffer = io_block;	// Nou buffer entrada/sortida
    io_block = ptmp;		// Nou bloc de dades		
    index = 0;				// Inicialitza index
}

void main()
{
	Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 	// Freqüència de mostreig
    int start_noise_estimation=1;
    int numT = 100;	
    float alpha = 1.0;
    float betta = 0.0;
    window win=hamm;
    nr_type type=ss2;
    NRstruct nrParams;
    float stdev = 300;
		
	init_buffer();
	init_NR(&nrParams, win, type, start_noise_estimation, stdev, alpha, betta, numT, io_block);
	comm_intr(fs);              // inici DSK, codec, McBSP usant interrupcions
	while(1)               	  	// bucle infinit
	{
		wait_buffer();		// Espera que s'ompli el buffer
		process(io_block, &nrParams);   // Processa bloc      
	}	 
}
