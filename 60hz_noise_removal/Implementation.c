#include "ece5210.h"
#include <stdio.h>
#include <math.h>

static int down_index = 0;

//static int first_count = 0;
float values[2] = {0};
static float buffer[3] = {0};



float interpolate(float x, float y1, float y2){
	float y = 0;

//	y = y1 + (x- x1) * ((y2-y1)/(x2 - x1));
	y = y1 + (x+1) * ((y2 - y1)/100);
	return y;
}

float fir(float sample_in, float *b, uint16_t len_b) {
	 // Buffer for past samples, initialized to 0
    float y = 0; // Output sample

    // Shift the buffer contents to make room for the new sample
    for (int i = len_b - 1; i > 0; i--) {
        buffer[i] = buffer[i - 1];
    }
    // Insert the new sample at the beginning of the buffer
    buffer[0] = sample_in;

    // Compute the output sample using the FIR filter equation
    for (int i = 0; i < len_b; ++i) {
        y += b[i] * buffer[i];
    }

    return y;
}


int16_t process_sample(int16_t sample_in)
{

	//initialize variables
	//int16_t sample_out = 0.0;
	float sample_out_f = 0.0;
	float sample_in_f = (float)sample_in;
	float coeff[3] = {1, (float)(-2 * cos(120 * M_PI / 480)), 1};



//check if value is 0 or 100 to discard

	if (down_index == 0) {



			values[1] = values[0];
//			y = interpolate(down_index, values[1], values[0]);
			values[0] = fir(sample_in_f, coeff, 3);

			sample_out_f = interpolate(down_index, values[1], values[0]);
			down_index++;
			return (int16_t)sample_out_f;

	    }
	else if (down_index < 99){
		sample_out_f = interpolate(down_index, values[1], values[0]);
		down_index++;
		return (int16_t)sample_out_f;

	}
	else{
//		sample_out_f = interpolate(down_index, values[1], values[0]);
		sample_out_f = interpolate(down_index, values[1], values[0]);
		down_index = 0;
		return (int16_t)sample_out_f;
	}
}

