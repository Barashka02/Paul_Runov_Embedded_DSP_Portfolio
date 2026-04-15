#ifndef ECE5210_H
#define ECE5210_H

#include <stdint.h>

#define PASSTHROUGH_RIGHT

void init_firwin(void);
float polyphase_decimation(float x, float *h, uint16_t M);
float polyphase_interpolation(float x, float *h, uint16_t L);
int16_t process_sample(int16_t sample_in);
/* *
Implementation of polyphase decimation with an efficient
FIR filter .
* @param x incoming sample x [ n ]
* @param * h coefficients of the entire FIR LPF
* @param M decimation factor ( must be integer )
* @return output is either the decimation value or a zero
*/
float polyphase_decimation ( float x , float *h , uint16_t M );

/* *
Implementation of polyphase decimation with an efficient
FIR filter .
* @param x incoming sample x [ n ] , if no sample is needed
this should be taken as a zero
* @param * h coefficients of the entire FIR LPF ( with
unity gain at DC )
* @param L interpolation factor ( must be integer )
* @return interpolated sample y [ n ]
*/
float polyphase_interpolation ( float x , float *h ,
uint16_t L );

#endif
