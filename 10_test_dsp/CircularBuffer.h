#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

class CircularBuffer{
    private:
        float* data;
        int size_;
        int write_index_;
    public:
        CircularBuffer();
        CircularBuffer(int size);
        CircularBuffer(const CircularBuffer& other);
        CircularBuffer& operator=(const CircularBuffer& other);
        float operator[](int delay);
        ~CircularBuffer();

        void write(float sample);
        float read(int delay);
        void reset();
        int size() const;
};

#endif
