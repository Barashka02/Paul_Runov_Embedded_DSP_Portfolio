#include "ece5210.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846264338327950288f

#define NUM_TAPS 19// need to adjust
#define W_C (PI / 2)

float h_lp[NUM_TAPS] = {0.f};
float h_hp[NUM_TAPS] = {0.f};

/**
float h_coeffs[] = {
    1.23062815e-03, -3.27573192e-05, 1.21414656e-03, 3.04555326e-04,
    4.66066622e-04, 5.00948044e-04, -6.26578492e-05, -2.79249348e-04,
    3.77338247e-04, 4.99984872e-01, 3.77338247e-04, -2.79249348e-04,
    -6.26578492e-05, 5.00948044e-04, 4.66066622e-04, 3.04555326e-04,
    1.21414656e-03, -3.27573192e-05, 1.23062815e-03
    };


float l_coeffs[] = {
	-4.06564791e-03, -5.00707296e-04, 9.09128739e-04, -3.17356190e-04,
	-8.18620827e-04, -3.43560811e-05, -9.89734092e-04, -6.76504285e-04,
	-4.70717594e-04, 4.99939347e-01, -4.70717594e-04, -6.76504285e-04,
	-9.89734092e-04, -3.43560811e-05, -8.18620827e-04, -3.17356190e-04,
	9.09128739e-04, -5.00707296e-04, -4.06564791e-03
	};
**/
/**
float h_coeffs[] = {
    7.54313046e-04, -1.74560897e-05, 3.31523680e-03, 5.78786901e-04,
    2.56854003e-04, -4.99659024e-04, 1.12955169e-04, -2.34626137e-04,
    8.45071930e-04, 5.00010812e-01, 8.45071930e-04, -2.34626137e-04,
    1.12955169e-04, -4.99659024e-04, 2.56854003e-04, 5.78786901e-04,
    3.31523680e-03, -1.74560897e-05, 7.54313046e-04
    };
float l_coeffs[] = {
    -9.58387969e-05, -7.00332764e-03, 7.06778806e-04, -7.96770290e-04,
    -6.79474213e-05, -4.00826694e-05, -1.19038088e-03, 6.94089236e-05,
    2.59703800e-04, 4.99827679e-01, 2.59703800e-04, 6.94089236e-05,
    -1.19038088e-03, -4.00826694e-05, -6.79474213e-05, -7.96770290e-04,
    7.06778806e-04, -7.00332764e-03, -9.58387969e-05
	};
**/

float l_coeffs[] = {
    0.001456f, -0.02666342f, -0.0431693f, -0.03926709f, -0.01154633f, 0.03689976f,
    0.09646407f, 0.15380424f, 0.19505105f, 0.21009135f, 0.19505105f, 0.15380424f,
    0.09646407f, 0.03689976f, -0.01154633f, -0.03926709f, -0.0431693f, -0.02666342f,
    0.001456f
};

float h_coeffs[] = {
    0.02055109f, 0.03641191f, 0.03820462f, 0.022702f, -0.00959248f, -0.05405346f,
    -0.103017f, -0.14716693f, -0.17784654f, 0.81120165f, -0.17784654f, -0.14716693f,
    -0.103017f, -0.05405346f, -0.00959248f, 0.022702f, 0.03820462f, 0.03641191f,
    0.02055109f
};



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
            h_lp[n] = W_C/PI;
        }
        else
        {
            h_lp[n] = sinf(W_C*(n - (float)M/2)) /
                (PI*(n - (float)M/2));
        }

        h_lp[n] *= 0.54f - 0.46f*cosf(2*PI*n/M);
        
        sum += h_lp[n];
    }

    for (int n = 0; n < NUM_TAPS; n++)
    {
        h_lp[n] /= sum;
        if (n % 2 == 1)
        {
            h_hp[n] = -h_lp[n];
        }
        else
        {
            h_hp[n] = h_lp[n];
        }
    }
}

float delay_line_lp[NUM_TAPS] = {0.f};

// Low-pass filter using an optimized structure for Type I FIR filters
float lpf(float x, float *h, uint8_t M) {
    // Shift the delay line contents
    for (int i = M; i > 0; i--) {
        delay_line_lp[i] = delay_line_lp[i - 1];
    }
    // Add the new sample to the delay line
    delay_line_lp[0] = x;

    // Compute the FIR filtering using the symmetric property
    float y = h[M/2] * delay_line_lp[M/2];  // Central coefficient
    for (int k = 0; k < M/2; k++) {
        y += h[k] * (delay_line_lp[k] + delay_line_lp[M - k]);
    }
    return y;
}

float delay_line_hp[NUM_TAPS] = {0.f};

// Low-pass filter using an optimized structure for Type I FIR filters
float hpf(float x, float *h, uint8_t M) {
    // Shift the delay line contents
    for (int i = M; i > 0; i--) {
        delay_line_hp[i] = delay_line_hp[i - 1];
    }
    // Add the new sample to the delay line
    delay_line_hp[0] = x;

    // Compute the FIR filtering using the symmetric property
    float y = h[M/2] * delay_line_hp[M/2];  // Central coefficient
    for (int k = 0; k < M/2; k++) {
        y += h[k] * (delay_line_hp[k] + delay_line_hp[M - k]);
    }
    return y;
}



int16_t process_sample_left(int16_t sample_in)
{
    int16_t sample_out = 0;
    float sample_in_f = (float)sample_in;

    float sample_out_f = lpf(sample_in_f, l_coeffs, NUM_TAPS-1);
    //float sample_out_f = hpf(sample_in_f, h_coeffs, NUM_TAPS-1);

    // Convert back to int16_t
    sample_out = (int16_t)sample_out_f;
    return sample_out;
}

int16_t process_sample_right(int16_t sample_in)
{
    int16_t sample_out = 0;
    float sample_in_f = (float)sample_in;

    float sample_out_f = hpf(sample_in_f, h_coeffs, NUM_TAPS-1);

    // Convert back to int16_t
    sample_out = (int16_t)sample_out_f;
    return sample_out;
}
