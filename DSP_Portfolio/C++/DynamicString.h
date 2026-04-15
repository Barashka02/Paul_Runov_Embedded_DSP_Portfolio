#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H
#include <iostream>

/**
 * DynamicString class which stores strings
 * using dynamically sized char arrays.
 *
 * The char array should be null-terminated so
 * as to be compatible with c_string functions.
 * This means that the last character in the string
 * should always be the null character '\0'.  When
 * counting the length of the string the null character
 * does not count.  However, when allocating the array
 * you need to make sure to always include an extra position
 * for storing the null character.
 *
 * Certain methods assume an 8-bit ascii char representation.
 *
 * You are not allowed to remove or rename any of the
 * data memebers of methods from this class.  However
 * you can add additional data members and methods as
 * you see fit.  You can also change the method
 * implementations as needed.
 *
 */
class DynamicString{

   public:
      /** Default Constructor
       * Creates an empty DynamicString object
       * Initializes the cstr array to be an array of size 1
       * containing the null character
       */
      DynamicString();

      /**
       * c-string constructor. Creates a copy of
       * the provided c-string, allocating the
       * required amount of memory.
       * @param str the c-string to store.
       */
      DynamicString(const char* str);

      /* Copy Constructor.  This should initialize all your data members by
       * copying the values from other. You should also allocate a new array to
       * hold the string and then copy each value from the "other" argument
       */
      DynamicString(const DynamicString& other);

      /* Assignment operator.  This method is similar to the copy constructor
       * but now "this" object is already instantiated.  You should first
       * make sure the object being assigned is not the same as this object.
       * Then delete the existing allocated memory, set any class variables,
       * reallocate a new array and make a deep copy of the values.
       */

      // copy constructor

      ~DynamicString();
      DynamicString& operator=(const DynamicString& other);

      /* Get a pointer to the null-terminated char array */
      const char* c_str() const;

      /** Get the number of chars in the string
       */
      int len() const;

      /** Get a copy of the character at the specified position.
       * @param position the 0-based index to retreive.
       * @return the character at the specified position.
       */
      char char_at(int position) const;

      /** Get a reference to the character at the specified position.
       * @param position the 0-based index to retreive.
       * @return the character at the specified position.
       */
      char& operator[](int position);

      /** Returns true if other is a prefix of this string.
       * @param other the string to check as a prefix.
       * @return bool true if other is a prefix.
       */
      bool startsWith(const DynamicString& other) const;

      /** Returns true if other is a suffix of this string.
       * @param other the string to check as a suffix.
       * @return bool true if other is a suffix.
       */
      bool endsWith(const DynamicString& other) const;

       /** Compares this string to other using dictionary ordering with the ascii values.
        * @param other the string to compare.
        * @return -1 if this string is smaller (comes earlier in the dictionary), 0 if they are the same, and 1 if this string is larger (comes later in the dictionary).
        */
      int compare(const DynamicString& other) const;

      /** Converts all characters to lowercase.
       * Contents are modified "in-place"
       * @return self (the lowercased string)
       */
      DynamicString& toLower();

      /** Converts all characters to uppercase.
       * Contents are modified "in-place"
       * @return self (the uppercased string)
       */
      DynamicString& toUpper();

      /** Replaces all instances of char old with char newCh.
       * Contents are modified "in-place"
       * @return self (the string with the replaced characters)
       */
      DynamicString& replace(char old, char newCh);

      /** Finds the first index of the character in the string
       * @param start the position of the string to start at
       * @param c the char to look for
       * @return the index of the character or -1 if the character is not found.
       */
      int find(char c, int start=0) const;

   friend std::ostream& operator<<(std::ostream& out, const DynamicString& str);

protected:
      char* cstr; /** pointer to the underlying null-terminated dynamic array */
    int size = -1;
};

#endif
