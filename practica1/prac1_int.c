#include "C6713dskinit.h"

#define IDLE  asm("	idle")                 // Assembler idle instruction
static int output_data;
static int input_data;

interrupt void c_int11()                   // rutina de servicio de interrupcion
{
	input_data = input_left_sample();      // señal del canal izquierdo de line in
	output_sample(output_data);
	return;
}

void main()
{
	Uint32 fs = DSK6713_AIC23_FREQ_16KHZ;  // ajuste de la frecuencia de muestreo
	comm_intr(fs);                         // inicio DSK, codec, McBSP usando interrupciones
	while(1)               	  	           // bucle infinito
	{
		IDLE;
		output_data = input_data;
	}
}
