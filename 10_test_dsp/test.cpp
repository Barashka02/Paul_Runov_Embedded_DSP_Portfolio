#include <iostream>
using namespace std;

class CircularBuffer {
    private:
        float* data;
        int size_;
        int write_index_;
    public:
        CircularBuffer(){
            size_ = 0;
            write_index_ = 0;
            data = nullptr;
        }
        CircularBuffer(int size){
            size_ = size;
            write_index_ = 0;
            data = new float[size];
        }
        CircularBuffer(const CircularBuffer& other){
            size_ = other.size_;
            write_index_ = other.write_index_;
            data = new float[size_];
            for(int i = 0; i < size_; i++){
                data[i] = other.data[i];
            }
        }
        ~CircularBuffer(){
            delete[] data;
            data = nullptr;
        }
        CircularBuffer& operator = (const CircularBuffer& other){
            if(this != &other){
                delete[] data;
                size_ = other.size_;
                write_index_ = other.write_index_;
                for(int i = 0; i < size_; i++){
                    data[i] = other.data[i];
                }
            }
            return *this;
        }
        
        void write(float sample){
            data[write_index_] = sample;
            write_index_ = (write_index_ + 1) % size_;    
        }
        float read(int index){
            return data[(write_index_ - 1 - index + size_) % size_];    
        }
};
int main() {
    // create original buffer and write some samples
    CircularBuffer original(4);
    original.write(1.0f);
    original.write(2.0f);
    original.write(3.0f);

    cout << "--- Original ---" << endl;
    cout << original.read(0) << endl;  // should print 3
    cout << original.read(1) << endl;  // should print 2
    cout << original.read(2) << endl;  // should print 1

    // copy constructor
    CircularBuffer copy(original);

    cout << "--- Copy (should match original) ---" << endl;
    cout << copy.read(0) << endl;  // should print 3
    cout << copy.read(1) << endl;  // should print 2
    cout << copy.read(2) << endl;  // should print 1

    // prove it is a deep copy — modify original, copy should not change
    original.write(99.0f);

    cout << "--- After writing 99 to original ---" << endl;
    cout << "Original read(0): " << original.read(0) << endl;  // should print 99
    cout << "Copy read(0): " << copy.read(0) << endl;          // should still print 3

    return 0;
}
