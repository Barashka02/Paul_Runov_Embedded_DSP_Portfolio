#ifndef FIRFILTER_H
#define FIRFILTER_H

#include "CircularBuffer.h"

class FIRFilter{
    private:
        float* coeffs;
        int num_taps_;
        CircularBuffer buffer
            ;
    public:
        FIRFilter(float* coeffs_in, int num_taps);
        FIRFilter(const FIRFilter& other);
        ~FIRFilter();
        FIRFilter& operator = (const FIRFilter& other);
        float process(float sample);
        void reset();


};

#endif
