#include "Biquad.h"

Biquad::Biquad(float a1, float a2, float b0, float b1, float b2){
    a1_ = a1;
    a2_ = a2;
    b0_ = b0;
    b1_ = b1;
    b2_ = b2;
    w1_ = 0;
    w2_ = 0;
}
Biquad::Biquad(const Biquad& other){
    a1_ = other.a1_;
    a2_ = other.a2_;
    b0_ = other.b0_;
    b1_ = other.b1_;
    b2_ = other.b2_;
    w1_ = other.w1_;
    w2_ = other.w2_;

}
Biquad& Biquad::operator = (const Biquad& other){
    a1_ = other.a1_;
    a2_ = other.a2_;
    b0_ = other.b0_;
    b1_ = other.b1_;
    b2_ = other.b2_;
    w1_ = other.w1_;
    w2_ = other.w2_;
    return *this;
}

//methods
void Biquad::init(){
    w1_ = 0;
    w2_ = 0;
}
float Biquad::process(float in){
   float y_n = b0_ * in + w1_;
   w1_ = in * b1_ - a1_ * y_n + w2_;
   w2_ = in * b2_ - a2_ * y_n;

   return y_n;
}
 
