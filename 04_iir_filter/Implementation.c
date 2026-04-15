#include "ece5210.h"
#include <stdio.h>
#include <string.h>
//#define NS_TOT 4
#define NS_TOT 4
#define NUM_BQ_TAPS 3


typedef struct {
    float H[NUM_BQ_TAPS]; // History of outputs
    float w[NUM_BQ_TAPS]; // History of inputs
} BiquadState;
float a[12] = {
		1.00000000e+00f, -9.10906181e-01f, 0.00000000e+00f,
		1.00000000e+00f, -1.83780839e+00f,  8.72423683e-01f,
		1.00000000e+00f, -1.86469357e+00f, 9.40538624e-01f,
		1.00000000e+00f, -1.88711126e+00f,  9.84312541e-01f
	};


float b[12] = {
		9.97562846e-04f,  9.97562846e-04f,  0.00000000e+00f,
		1.00000000e+00f, -1.56290161e+00f,  1.00000000e+00f,
		1.00000000e+00f, -1.81628975e+00f, 1.00000000e+00f,
		1.00000000e+00f, -1.85808382e+00f,  1.00000000e+00f
    };


float b_len_test[NS_TOT*NUM_BQ_TAPS] = {0.9f,0.8f,0.7f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.3f,0.2f,0.1f,
	0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.3f,0.2f,0.1f,
    0.6f,0.5f,0.4f,
    0.3f,0.2f,0.1f
};

float a_len_test[NS_TOT*NUM_BQ_TAPS] = {1.f,0.6f,0.5f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.4f,0.3f,
    1.f,0.2f,0.1f,
	0.6f,0.5f,0.4f,
    0.6f,0.5f,0.4f,
    0.3f,0.2f,0.1f,
    0.6f,0.5f,0.4f,
    0.3f,0.2f,0.1f
};

float H_ap(float x, float *b, float *a, BiquadState *state) {
    // Direct calculation using array indexes
    float y = b[0] * x + b[1] * state->w[1] + b[2] * state->w[2] - a[1] * state->H[1] - a[2] * state->H[2];

    // Update history
    state->w[2] = state->w[1];
    state->w[1] = x;

    state->H[2] = state->H[1];
    state->H[1] = y;

    return y;
}
/* *
* @brief IIR filtering using cascaded biquad stages
*
* @param x input sample
* @param b array of b coefficients as 1 D array in groups of 3
* @param a array of a coefficients as 1 D array in groups of 3
* @param num_stages number of biquad stages
* @return float processed sample
*/

float iir_sos(float x, float *b, float *a, int num_stages) {
    static BiquadState biquadStates[NS_TOT]; // Keep state across function calls
    float y = x;

    for (int stage = 0; stage < num_stages; stage++) {
        int idx = stage * NUM_BQ_TAPS;
        y = H_ap(y, &b[idx], &a[idx], &biquadStates[stage]);
    }

    return y;
}


int16_t process_sample(int16_t sample_in)
{
    int16_t sample_out = 0;
    float sample_in_f = (float)sample_in;
//    float sample_in_f = (float)sample_in;
    float sample_out_f = iir_sos(sample_in_f, b, a, NS_TOT);

//    float sample_out_f = iir_sos(sample_in_f, b_len_test, a_len_test, NS_TOT);
//    float sample_out_f = iir_sos(sample_in_f, b, a, NS_TOT);

    sample_out = (int16_t)sample_out_f;
    return sample_out;
}

