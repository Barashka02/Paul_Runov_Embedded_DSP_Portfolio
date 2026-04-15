#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "fft.h"


// HELPER FUNCTIONS
// -----------------------------------------------------------------------------------
void print_complex_array(double complex *arr, int n){
    for(int i = 0; i < n; i++){
         printf("c[%d]: %.5f + j %.5f\n",i,  creal(arr[i]), cimag(arr[i]));
    }
}

void bitReverse(double complex * arr, int n) {
    // Calculate the logarithm base 2 of n. This gives the number of bits required to represent n.
    int log2n = (int)log2(n); // Assumes n is a power of 2
    
    // Iterate over each element in the array.
    for(int i = 0; i < n; i++) {
        // Initialize a variable to store the reversed value of 'i'
        int rev = 0;
        // Copy the value of 'i' to 'x' to manipulate it without changing 'i'.
        int x = i;

        // Loop for each bit in 'i' (from 0 to log2n-1).
        for(int j = 0; j < log2n; j++) {
            // Shift 'rev' left by one bit and OR it with the least significant bit of 'x'.
            // This step appends the least significant bit of 'x' to 'rev'.
            rev = (rev << 1) | (x & 1);
            // Right shift 'x' by one bit to process the next bit.
            x >>= 1;
        }

        // If the original index 'i' is less than its reversed index 'rev',
        // swap the elements at these indices. This ensures each swap is done only once.
        if(i < rev) {
            double complex temp = arr[i]; // Temporary variable to hold the value at index 'i'.
            arr[i] = arr[rev]; // Place the value from 'rev' index to 'i' index.
            arr[rev] = temp;  // Place the original value from 'i' index to 'rev' index.
        }
       
    }
}


// -----------------------------------------------------------------------------------
void dft(array *X_w, array *x_t) {
    size_t size_x = x_t->len;
    for(size_t r = 0; r < size_x; r++) {
        X_w->data[r] = 0;  // initialize to 0
        for(size_t k = 0; k < size_x; k++) {
            double theta = ((-2 * M_PI * (double)r * (double)k) / (double)size_x);
            double complex exp_value = cexp(I * theta);  // compute exp(i*theta)
            X_w->data[r] += x_t->data[k] * exp_value;  // accumulate result
        }
    }
}


/* FFT FUNCTION
 * ----------------------------------------------------------------------------------
 * Implementation of a radix-2 decimation-in-time FFT.
 * In a DITFFT, the input is bit-reversed before passing through the butterfly phase.
*/


void fft(array *x_t){
    
    //initializing size
    size_t size = x_t->len;
    
    //reversing bits
    bitReverse(x_t->data, (int)size);
        
    // loop for the depth (fft has log2(size) butterfly stages) 
    
    for(int i = 0; i <= log2((int)size); i++){
        // computing the block size (size of each butterfly section from left to right) 
        size_t block_size = (size_t)pow(2, i);
        //this block is used for iteration
        size_t half_size = block_size / 2;

        // initializing W = base, W_cur used to keep track of the W in the calculation
        double theta = (-2 * M_PI) /(double)block_size;
        double complex W = cexp(I * theta);
        double complex W_cur;
        
        // iterating over each butterfly section
        for(int j = 0; j < size; j += (int)block_size){
            W_cur = 1 + 0 * I;
            
            // loop for doign the actual calculations for the butterfly operations
           for(int k = 0; k < half_size; k++){
            // variable for even indexes
            size_t i_even = (size_t)j + (size_t)k;
            // varaible for odd indexes
            size_t i_odd = i_even + half_size;

            //data of the even
            double complex u = x_t->data[i_even];
            //data for the value to add or subtract.
            double complex t = W_cur * x_t->data[i_odd];
            
            //storing the values for the even and odd indexes
            x_t->data[i_even] = u + t;
           x_t->data[i_odd] = u - t;
            
            //updating the current index (W^2 is the same as W*W)
            W_cur = W_cur * W;
            }
    
        }       

    }
//    *X_w = *x_t;
//    for(int i = 0; i < size; i++){
//       X_w->data[i] = x_t->data[i];
//   }
}

void ifft(array *x_t) {
    for(int i = 0; i < x_t->len; i++){ 
        x_t->data[i] = conj(x_t->data[i]);
    }
    fft(x_t);
    for(int i = 0; i < x_t->len; i++){
        x_t->data[i] = x_t->data[i] / (double)x_t->len;
        x_t->data[i] = conj(x_t->data[i]);
    }
}

void convolve(array *y,  array *f, array *g){
    size_t len = f->len + g->len - 1;
    
    for(size_t i = 0; i < len; i++){
        y->data[i] = 0;
        for(size_t j = 0; j < f->len; j++){
            if(i >= j && (i-j) < g->len) {
                y->data[i] += f->data[j] * g->data[i - j];
            }
        }
    }
}

void fft_convolve(array *f, array *g){
    fft(f);
    fft(g);

    for(int i = 0; i < f->len; i++){
      f->data[i] *= g->data[i];
    }

    ifft(f);

}



