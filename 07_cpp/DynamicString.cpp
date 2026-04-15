#include "DynamicString.h"
#include <cctype>
#include <stdexcept>
//#include <cstring>


using std::out_of_range;
using std::tolower;
using std::toupper;
using std::ostream;

// Default Constructor
DynamicString::DynamicString(){
      cstr = new char[1];
      *cstr = '\0';
      size = 0;
//    char temp[] = "";
//    cstr = temp;

//    index_ = 0;
}

// Constructor to copy a provided string
DynamicString::DynamicString(const char* str) {
    int count = 0;
    while (str[count] != '\0'){
        count++;
    }
    size = count;
//    size = strlen(str);
    cstr = new char[size];
    for (int i = 0; i <= size; ++i) {
        cstr[i]=str[i];
    }
//    strcpy(cstr, str);

}

// Constructor to copy another DynamicString
DynamicString::DynamicString(const DynamicString& other){
    size = other.size;
    cstr = new char[size + 1];
    for (int i = 0; i <= size; ++i){
        cstr[i]=other.cstr[i];
    }
//    strcpy(cstr, other.cstr);
}

// destructor to clean up memory space
DynamicString::~DynamicString(){
    delete[] cstr;
    cstr = NULL;
}

// Operator to assign on c-string to another c-string
DynamicString& DynamicString::operator=(const DynamicString& other){
    if (this != &other) {
        if (cstr) {
            delete[] cstr;
            cstr = NULL;
        }
        size = other.size;
        cstr = new char[size + 1];
        for (int i = 0; i <= size; ++i){
            cstr[i] = other.cstr[i];
        }
//        strcpy(cstr, other.cstr);
    }
   return *this;
}

// method to find length
int DynamicString::len() const{
    return size;
}

// method to get pointer to null-terminated char array
const char* DynamicString::c_str() const{
   return cstr;
}

// method to get the character at a specified position.
char DynamicString::char_at(int position) const{
    if (position > size || position < 0)
    {
        throw out_of_range("out of range");
    }
    else {
   return cstr[position];
    }
}

// method to overload the [] operator with the pointerl
char& DynamicString::operator[](int position){
    if (position > size || position < 0)
    {
        throw out_of_range("out of range");
    }
    else {
        return cstr[position];
    }

//   return *(new char('z'));
}

// method to check if this starts with the string other.
bool DynamicString::startsWith(const DynamicString& other) const{
    bool starts = true;
    for (int i = 0; i < other.len(); ++i) {
        if (other.char_at(i) == cstr[i]){
            starts = true;
        }
        else {starts = false;}
    }
    return starts;
}

// method to check if this ends with the string other.
bool DynamicString::endsWith(const DynamicString& other) const{
    bool ends = true;
    // i equals end of other
    // j equals end of cstr
    for (int i = this->len() - 1, j = other.len() - 1; j >= 0; j--, i--)  {
        if (other.char_at(j) == cstr[i]){
            ends = true;
        }
        else {ends = false;}
    }
   return ends;
}

// method to alphabetically compare two strings.
int DynamicString::compare(const DynamicString& other) const{

        int count = 0;
        // checks the two strings until one is found to be greater/less than the other.
        while (cstr[count] != '\0' || other.cstr[count] != '\0'){
        if (this->char_at(count) == other.char_at(count)){
            count = count;
        }

        else if (this->char_at(count) < other.char_at(count)){
            return -1;
        }
        else if (this->char_at(count) > other.char_at(count)){
            return 1;

        }
        count++;
    }
    return 0;
}

// method to convert all letters in a string to lowercase.
DynamicString& DynamicString::toLower(){
    int count = 0;
    while(cstr[count] != '\0'){
        if (std::isdigit(cstr[count])){
            count++;
        }
        else {
          cstr[count] = tolower(cstr[count]);
          count++;
        }
    }
   return *this;
}

// method to convert all strings in a string to uppercase
DynamicString& DynamicString::toUpper() {
    int count = 0;
    while(cstr[count] != '\0'){
        if (std::isdigit(cstr[count])){
            count++;
        }
        else {
            cstr[count] = toupper(cstr[count]);
            count++;
        }
    }
    return *this;
}

// method to replace a specific character with a character of choice.
DynamicString& DynamicString::replace(char old, char newCh){
    for (int i = 0; i < this->len(); ++i) {
        if (cstr[i] == old){
            cstr[i] = newCh;
        }
    }
   return *this;
}

// method to find the index of a certain character from a specified start point.
int DynamicString::find(char c, int start) const{
    if (start < 0){
        start = 0;
    }
    for (int i = start; i < this->len(); ++i) {
        if (cstr[i] == c){
            return i;
        }
    }

    return -1;

}

// overloading the << operator to print out the string.
ostream& operator<<(ostream& out, const DynamicString& str){
    for (int i = 0; i < str.size; ++i) {
        out << str.char_at(i);
    }
   return out;
}
