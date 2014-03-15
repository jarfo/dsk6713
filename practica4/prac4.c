#include "C6713dskinit.h"
#include "block.h"
#include "process.h"

float io1[N], io2[N];        // IO Buffers
float *io_block = io1, *io_buffer = io2; // IO pointers
int index = 0;

interrupt void c_int11() {  // Interrupt Service Routine
     if (index < N) {
         output_sample((int)io_buffer[index]);
        io_buffer[index++]=(float)input_left_sample();
    }
}

void wait_buffer_block(void) {
    float *ptmp;            // Dummy pointer

    while (index < N);      // Waits buffer

    ptmp = io_buffer;       // Swap pointers
    io_buffer = io_block;
    io_block = ptmp;
    index = 0;              // Reset counter
}

void main() {
    Uint32 fs=DSK6713_AIC23_FREQ_16KHZ; // Ajuste de la frecuencia de muestreo
    float hFIR[L_FIR];              // Respuesta impulsional del filtro FIR
//    filter_iir2 hIIR;               // Coeficientes del filtro IIR

    init_processFIR1(hFIR);         // Filtro paso alto
//    init_processFIR2(hFIR);         // Filtro generado con MATLAB
//    init_processIIR(&hIIR);         // Filtro generado con MATLAB

    comm_intr(fs);                  // inicio DSK, codec, McBSP usando interrupciones

    while(1) {                      // bucle infinito
        wait_buffer_block();        // Espera a que se llene el buffer
        processFIR(io_block,hFIR);  // Procesa bloque
//        processIIR(io_block,&hIIR,L_IIR,N);        // Procesa bloque
    }
}

