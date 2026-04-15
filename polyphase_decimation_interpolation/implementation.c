#include "ece5210.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846264338327950288f

#define NUM_TAPS 900
#define DECIMATE 100
#define DEC_TAPS (NUM_TAPS / DECIMATE)
#define INTERPOLATE (DECIMATE)
#define INT_TAPS (NUM_TAPS / INTERPOLATE)

#define W_C (PI / DECIMATE)


# define BUFF_SIZE (128U)
# define BUFF_SIZE_MASK (BUFF_SIZE-1U)
typedef struct buffer {
    float data [BUFF_SIZE];
    uint16_t write_buff_index ;
} buffer ;



//-------------------------------------------------------------------
//Writing to circular buffer
//-------------------------------------------------------------------
/* *
Write to circular buffer .
* @param * buff pointer to the buffer
* @param value the value to be inserted
* @return void
*/


void write_buff_val ( buffer * buff , float value )
{
buff -> data [(++buff -> write_buff_index) & BUFF_SIZE_MASK] = value ;
}

//-------------------------------------------------------------------
//Reading from circular buffer
//-------------------------------------------------------------------
/* *
Read value from circular buffer .
* @param * buff pointer to the buffer
* @param idx_in index you want to read from ( as if it is a
linear buffer
* @return value from index of interest
*/
float read_buff_val ( buffer * buff , uint16_t idx_in )
{
return buff -> data [(buff -> write_buff_index - idx_in ) & BUFF_SIZE_MASK];
}

//-------------------------------------------------------------------
//FIR filter
//-------------------------------------------------------------------
static buffer int_poly_buffer[DECIMATE];
float h_aa[NUM_TAPS] = {0.f};
float h_poly[NUM_TAPS] = {0.f};

/* *
Implementation of an FIR filter system .
* @param sample_in the current sample x [ n ] to be processed
* @param * b array of filter coefficients b_0 , b_1 ,... , b_M
* @param len_b the length of b
* @return the output sample y [ n ]
*/
float fir(float sample_in, float *b, uint16_t len_b, int poly_start_index, int poly_index) {
	// Buffer for past samples, initialized to 0
    float y = 0; // Output sample

    // Insert the new sample at the beginning of the buffer
    write_buff_val(&int_poly_buffer[poly_index], sample_in);

    // Compute the output sample using the FIR filter equation
    for (int i = 0; i < len_b; i++) {
        y += b[i + poly_start_index] * read_buff_val(&int_poly_buffer[poly_index], (uint16_t)i);
    }

    return y;
}



//-------------------------------------------------------------------
//FIR filter (with new buffers for interpolation)
//-------------------------------------------------------------------
static buffer poly_buffer[DECIMATE];

/* *
Implementation of an FIR filter system .
* @param sample_in the current sample x [ n ] to be processed
* @param * b array of filter coefficients b_0 , b_1 ,... , b_M
* @param len_b the length of b
* @return the output sample y [ n ]
*/
float int_fir(float sample_in, float *b, uint16_t len_b, int poly_start_index, int poly_index) {
	// Buffer for past samples, initialized to 0
    float y = 0; // Output sample

    // Insert the new sample at the beginning of the buffer
    write_buff_val(&poly_buffer[poly_index], sample_in);

    // Compute the output sample using the FIR filter equation
    for (int i = 0; i < len_b; i++) {
        y += b[i + poly_start_index] * read_buff_val(&poly_buffer[poly_index], (uint16_t)i);
    }

    return y;
}

static float notch_buffer[3] = {0};
//-------------------------------------------------------------------
//FIR filter (with new buffers for notch filter)
//-------------------------------------------------------------------
float notch_fir(float sample_in, float *b, uint16_t len_b) {
	 // Buffer for past samples, initialized to 0
    float y = 0; // Output sample

    // Shift the buffer contents to make room for the new sample
    for (int i = len_b - 1; i > 0; i--) {
        notch_buffer[i] = notch_buffer[i - 1];
    }
    // Insert the new sample at the beginning of the buffer
    notch_buffer[0] = sample_in;

    // Compute the output sample using the FIR filter equation
    for (int i = 0; i < len_b; ++i) {
        y += b[i] * notch_buffer[i];
    }

    return y;
}


//-------------------------------------------------------------------
//Initialization of the FIR filter
//-------------------------------------------------------------------
/**
Generates a windowed sinc lowpass filter with cutoff
frequency defined as a constant W_C with the number of
taps also defined as a constant (NUM_TAPS).  This filter
uses a Hamming window.

   * @param void
   * @return void
*/
void init_firwin(void)
{
    uint16_t M = NUM_TAPS - 1;
    float sum = 0.f;

    for (uint16_t n = 0; n < NUM_TAPS; n++)
    {
        if ((n == M/2) && (NUM_TAPS % 2))
        {
            h_aa[n] = W_C/PI;
        }
        else
        {
            h_aa[n] = sinf(W_C*(n - (float)M/2)) /
                (PI*(n - (float)M/2));
        }

        h_aa[n] *= 0.54f - 0.46f*cosf(2*PI*n/M);
        
        sum += h_aa[n];
    }

    for (int n = 0; n < NUM_TAPS; n++)
    {
        h_aa[n] /= sum;
    }
    /* add code to population h_poly here */
    int h_index = 0;
    for(int i = 0; i < DECIMATE; i++)
    {
        for(int j = 0; j < DEC_TAPS; j++)
        {
            h_poly[h_index] = h_aa[i + j*DECIMATE];
            h_index++;
        }    
    }   
}


//-------------------------------------------------------------------
//Polyphase decimation
//-------------------------------------------------------------------
/* *
Implementation of polyphase decimation with an efficient                            
FIR filter .
* @param x incoming sample x [ n ]
* @param * h coefficients of the entire FIR LPF
* @param M decimation factor ( must be integer )
* @return output is either the decimation value or a zero
*/
//global variables
//float prev_x[DECIMATE] = {0.f};
int decimate_index = 0;
buffer prev_x[DECIMATE];

float polyphase_decimation(float x, float *h, uint16_t M) {
    float dec_sum = 0.0;

    // Update the circular buffer with the new sample
    write_buff_val (prev_x, x);

    // Perform decimation only if the condition meets
    if (decimate_index % M == 0) {
        for (int i = 0; i < M; i++) {
            dec_sum += fir(read_buff_val(prev_x, (uint16_t)i), h, DEC_TAPS, i * DEC_TAPS, i);
        }
        //dec_sum = notch_fir(dec_sum, h, 3);
    }
    // Increment and wrap the decimate index properly
    decimate_index = (decimate_index + 1);  
    return dec_sum; // This returns the decimated value when appropriate, otherwise, it should be zero or handled accordingly.
}






//-------------------------------------------------------------------
//Polyphase interpolation
//-------------------------------------------------------------------
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
// Then call it like this for each poly_buffer entry
// Declare buffer and other necessary variables outside of the function
buffer int_buff[INTERPOLATE];
int y_count = 0;
float x_in = 0;

float polyphase_interpolation(float x, float *h, uint16_t L) {
    float y_out = 0.0;
    
    // Check if y_count has reached 0 which indicates a new cycle
    if (y_count == 0) {
        x_in = x; // Update x_in at the beginning of each new cycle
        y_out = L * int_fir(x_in, h, INT_TAPS, y_count * INT_TAPS, y_count);
    } else {
        // Use the previous x_in for interpolation in between
        y_out = L * int_fir(x_in, h, DEC_TAPS, y_count * DEC_TAPS, y_count);
    }
    
    // Increment y_count and reset if it equals L
    y_count++;
    if (y_count >= L) {
        y_count = 0; // Reset y_count to 0 when it reaches L
    }
    
    return y_out;
}

//-------------------------------------------------------------------
//Putting it all together
//-------------------------------------------------------------------
int notch_index = 0;
int16_t process_sample(int16_t sample_in)
{
    float coeff[3] = {1, (float)(-2 * cos(120 * M_PI / 480)), 1};

    int16_t sample_out = 0;
    float sample_in_f = (float)sample_in;
 
    //init_firwin();

    // This is just simple pass through, if you want to
    // do any signal processing, start editing here...  
    //float sample_out_f = 0.0;
    float sample_out_f = polyphase_decimation(sample_in_f, h_poly, DECIMATE);
    //sample_out_f = notch_fir(sample_out_f, coeff, 3);
    if(notch_index % DECIMATE == 0)
    {
        sample_out_f = notch_fir(sample_out_f, coeff, 3);
        sample_out_f = polyphase_interpolation(sample_out_f, h_poly, INTERPOLATE);
    }
    else
    {
        sample_out_f = polyphase_interpolation(sample_out_f, h_poly, INTERPOLATE);
    }
    notch_index = (notch_index + 1) % DECIMATE;
    //sample_out_f = polyphase_interpolation(sample_out_f, h_poly, INTERPOLATE);
    
    // Convert back to int16_t
    sample_out = (int16_t)sample_out_f;
    return sample_out;

}
