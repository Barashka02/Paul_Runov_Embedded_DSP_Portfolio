
#include "FIRFilter.h"

FIRFilter::FIRFilter(float* coeffs_in, int num_taps) : buffer(num_taps) {
    num_taps_ = num_taps;
    coeffs = new float[num_taps_];
    for(int i = 0; i < num_taps_; i++){
        coeffs[i] = coeffs_in[i];
    }
}
FIRFilter::FIRFilter(const FIRFilter& other) : buffer(other.buffer){
        num_taps_ = other.num_taps_;
        coeffs = new float[num_taps_];
        for(int i = 0; i < num_taps_; i++){
            coeffs[i] = other.coeffs[i];
    }
}

FIRFilter::~FIRFilter(){
    delete[] coeffs;
    coeffs = nullptr;
}
FIRFilter& FIRFilter::operator = (const FIRFilter& other){
    if(this != &other){
        delete[] coeffs;
        num_taps_ = other.num_taps_;
        coeffs = new float[num_taps_];
        for(int i = 0; i < num_taps_; i++){
            coeffs[i] = other.coeffs[i];
        }
    }
    return *this;
}
float FIRFilter::process(float sample){
    buffer.write(sample);
    float y_n = 0;
    for(int i = 0; i<num_taps_; i++){
        y_n += coeffs[i] * buffer[i];
    }
    return y_n;
}
void FIRFilter::reset(){
    buffer.reset();

}


