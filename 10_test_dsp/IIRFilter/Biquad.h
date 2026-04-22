#ifndef BIQUAD_H
#define BIQUAD_H

class Biquad{

    private:
        float a1_, a2_, b0_, b1_, b2_, w1_, w2_;
    public:
        
        //constructors/overloading/destructors
        Biquad(float a1, float a2, float b0, float b1, float b2);
        Biquad(const Biquad& other);
        Biquad& operator = (const Biquad& other);

        //methods
        void init();
        float process(float in);
        
};

#endif
