#include "CircularBuffer.h"

CircularBuffer::CircularBuffer() {
    size_ = 0;
    write_index_ = 0;
    data = nullptr;
}

CircularBuffer::CircularBuffer(int size) {
    size_ = size;
    write_index_ = 0;
    data = new float[size_];
    for (int i = 0; i < size_; i++) {
        data[i] = 0.0f;
    }
}

CircularBuffer::CircularBuffer(const CircularBuffer& other) {
    size_ = other.size_;
    write_index_ = other.write_index_;
    data = new float[size_];
    for (int i = 0; i < size_; i++) {
        data[i] = other.data[i];
    }
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& other) {
    if (this != &other) {
        delete[] data;
        size_ = other.size_;
        write_index_ = other.write_index_;
        data = new float[size_];
        for (int i = 0; i < size_; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

float CircularBuffer::operator[](int delay) {
    return data[(write_index_ - 1 - delay + size_) % size_];
}

CircularBuffer::~CircularBuffer() {
    delete[] data;
    data = nullptr;
}

void CircularBuffer::write(float sample) {
    data[write_index_] = sample;
    write_index_ = (write_index_ + 1) % size_;
}

float CircularBuffer::read(int delay) {
    return data[(write_index_ - 1 - delay + size_) % size_];
}

void CircularBuffer::reset() {
    for (int i = 0; i < size_; i++) {
        data[i] = 0.0f;
    }
    write_index_ = 0;
}

int CircularBuffer::size() const {
    return size_;
}


