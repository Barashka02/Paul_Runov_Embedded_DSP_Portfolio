#ifndef FFT_H
#define FFT_H
#include <complex.h>
typedef struct array{
    size_t len;
    double _Complex  *data;
} array;

void dft(array *X_w, array *x_t);

void fft(array *x_t);

void ifft(array *x_t);

void fft_convolve(array *f, array *g);

void convolve(array *y, array *f,  array *g);
#endif
