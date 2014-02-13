#include "C6713dskinit.h"
#include "process.h"

float io1[IO_N], io2[IO_N];	    	// Reserva espacio para los buffers
float *io_block=io1,*io_buffer=io2;	// Puntero del bloque a procesar
int index=0;

interrupt void c_int11()         	// Rutina de servicio de interrupcion
{  	
 	if (index < IO_N)
	{
 		output_sample((int)io_buffer[index]);
		io_buffer[index++]=(float)input_left_sample();
	}
	return;
}

void wait_buffer(void)
{
    float *ptmp;			// Puntero auxiliar			

    while(index < IO_N);	// Espera a que se llene el buffer	
    ptmp = io_buffer;		// Intercambia punteros: 		
    io_buffer = io_block;	// nuevo buffer de entrada/salida	
    io_block = ptmp;		// nuevo bloque de datos		
    index = 0;				// Inicializa index			
}

void main()
{
	Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; // Ajuste de la frecuencia de muestreo
	comm_intr(fs);				// inicio DSK, codec, McBSP usando interrupciones

	init_process();				// inicializa los codificadores
	while(1)               	  	// bucle infinito
	{
		wait_buffer();			// Espera a que se llene el buffer
		process(io_block);	    // Procesa bloque
	}	 
}

