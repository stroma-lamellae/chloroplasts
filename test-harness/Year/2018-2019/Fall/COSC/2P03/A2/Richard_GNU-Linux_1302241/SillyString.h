/**
      @author  Richard GNU-Linux
      @studentNum 1302241
    */
#include <iostream>

namespace SillyString {
	class SillyString {
	private:
		char *data; //Character data
		int _length; //Number of characters in 'data' used as string
	public:
		SillyString(const char *data="");//Default constructor: takes C-style string until terminator ('\0'); defaults to empty string
		SillyString(const char *data, int length);//Lets you take only a portion of a C-style string
		SillyString(const SillyString &original);//Copy constructor

		~SillyString();//Destructor

		SillyString operator+(const SillyString &other) const;//Concatenate

		SillyString operator+() const; //Returns new ALL-UPPERCASE version
		SillyString operator-() const; //Returns new all-lowercase version

		SillyString operator~() const; //noisrev sdrawkcab a snruteR

		bool operator<=(const SillyString &other) const; //Does this have earlier or equal lexicographic priority to other?
		bool operator<(const SillyString &other) const; //Does this has earlier lexicographic priority to other?
		bool operator>=(const SillyString &other) const; //Does this is the same string, or comes after other?
		bool operator>(const SillyString &other) const; //Does this comes after other?
		bool operator==(const SillyString &other) const; //Test for string equality
		bool operator!=(const SillyString &other) const; //Test for string inequality
		bool operator!() const; //Test for empty SillyString

		SillyString operator()(const int from, const int to) const; //Returns a slice, from 'from' (inclusive) to 'to' (exclusive)
		char operator[](const int &pos) const; //Returns character at that position (zero-based); '\0' if outside of bounds

		int indexOf(char c) const; //Returns position of first occurrence of c, or -1 if not found
		int indexOf(char c, int pos) const; //Same as above, but starting from position pos (zero-based indexing)
		int length() const; //Returns the length of the string (the actual number of characters)

		//Assignment breaks strict immutability, but is *so* much easier that we may wish to cheat and provide it:
		SillyString& operator=(const SillyString &original){
			if (this==&original) //First, check for 'self-assignment'
				return *this;

			if (this->_length>0)
				delete[] this->data;
			this->_length=original._length;
			this->data=new char[this->_length];
			for (int i=0;i<this->_length;i++)
				this->data[i]=original.data[i];

			return *this; //Assignments typically return a reference to the object, for the sake of cascading/chaining
		};

		friend std::ostream& operator<<(std::ostream &out, const SillyString &ss);//Stream insertion
		//Note: though a peculiarity, since this string class relies (initially) on C-strings, it's expected that you'll rely on them for any stream extraction
	};
}
