/**
      @author  Richard GNU-Linux
      @studentNum 1302241
    */
#include <iostream>
#include "SillyString.h"
namespace SillyString {
		SillyString::SillyString(const char *data){
        	this-> _length = 0;

		    while(data[this-> _length]!='\0') this-> _length++;

    		this->data = new char[this->_length];

            for(int j=0; j<this->_length; j++){
    		     this->data[j] = data[j];
        	}
     	}

		//Lets you take only a portion of a C-style string
		SillyString::SillyString(const char *data, int length){
		   this-> _length = length;
           this->data = new char[this->_length];
           for(int a=0; a<this->_length; a++){
                  this->data[a] = data[a];
            }

		}
		//Copy constructor
		SillyString::SillyString(const SillyString &original){
			this->_length = original._length;
			this->data = new char[this->_length];
			for(int b=0; b<this->_length; b++){
				this->data[b] = original.data[b];
			}

		}

		//Destructor
		SillyString::~SillyString(){
		delete[] data;
		}

		//Concatenate
		SillyString SillyString::operator+(const SillyString &other) const{
			int len = this->_length+other._length;
			char *concatenated = new char[len+1];
			for(int c=0; c<this->_length; c++){
				concatenated[c] = this->data[c];
			}
			for(int d=0; d<other._length; d++){
				concatenated[this->_length+d] = other[d];
			}
			concatenated[len] = '\0';
			return SillyString(concatenated);

		}

		//Returns new ALL-UPPERCASE version
		SillyString SillyString::operator+() const{
			char *upper = new char[this->_length+1];
			for(int i=0; i<this->_length; i++){
				if(this->data[i] >= 97 && this->data[i]<=122){
					upper[i] = this->data[i]-32;
				}
			}
			upper[this->_length] = '\0';
			return SillyString(upper);
		}
		//Returns new all-lowercase version
		SillyString SillyString::operator-() const{
			char *lower = new char[this->_length+1];
             for(int i=0; i<this->_length; i++){
                  if(this->data[i] >= 65 && this->data[i]<=90){
                      lower[i] = this->data[i]+32;
                  }
              }
              lower[this->_length] = '\0';
              return SillyString(lower);
          }


		 //noisrev sdrawkcab a snruteR
		SillyString SillyString::operator~() const{
			char *backwards = new char[this->_length+1];
			int count = 0;
			for(int e=this->_length-1; e>=0; e--){
				backwards[count] = this->data[e];
				count++;
			}
			backwards[this->_length] = '\0';
			return SillyString(backwards);
		}

		//Does this have earlier or equal lexicographic priority to other?
		bool  SillyString::operator<=(const SillyString &other) const{
			return !((*this)>other);
		}

		//Does this has earlier lexicographic priority to other?
		bool  SillyString::operator<(const SillyString &other) const{
			 return (!((*this)>other)&&((*this)!=other));
		}

		//Does this is the same string, or comes after other?
		bool  SillyString::operator>=(const SillyString &other) const{
			return((*this)>other&&(*this)==other);
		}

		//Does this comes after other?
		bool  SillyString::operator>(const SillyString &other) const{
			int l,r = 0;
			for(int i=0; i<this->_length; i++){
					l+=this->data[i];
			}
			for(int j=0; j<other._length; j++){
					r+=other[j];
			}

			return l>r;
		}

		//Test for string equality
		bool  SillyString::operator==(const SillyString &other) const{
			return !((*this)!=other);
		}

		//Test for string inequality
		bool  SillyString::operator!=(const SillyString &other) const{
			bool inequal = false;
			for(int i=0; i<this->_length; i++){
				if(this->data[i] != other[i]){
					return true;
				}
			}
			return inequal;
		}

		//Test for empty SillyString
		bool  SillyString::operator!() const{
			return this->_length==0;
		}

 		//Returns a slice, from 'from' (inclusive) to 'to' (exclusive)
		SillyString SillyString::operator()(const int from, const int to) const{
			char *slice = new char[to-from];
			int count = 0;
			for(int f=from; f<to; f++){
				slice[count] = data[f];
				count++;
			}
			return SillyString(slice);
		}
 		//Returns character at that position (zero-based); '\0' if outside of bounds
		char  SillyString::operator[](const int &pos) const{
			if(pos>=0 && pos<this->_length){
				return this->data[pos];
			}
			else{
				return '\0';
			}
		}

 		//Returns position of first occurrence of c, or -1 if not found
		int  SillyString::indexOf(char c) const{
			for(int g=0; g<this->_length; g++){
                 if(this->data[g] == c){
                     return g;
            	}
			}
             return -1;

		}
		//Same as above, but starting from position pos (zero-based indexing)
		int SillyString::indexOf(char c, int pos) const{
			for(int h=pos; h<this->_length; h++){
				if(this->data[h] == c){
					return h;
				}
			}
			return -1;
		}
		//Returns the length of the string (the actual number of characters)
		int  SillyString::length() const{return this->_length;}

		//Note: though a peciuiarity, since this string class relies (initially) on C-strings, it's expected that you'll rely on them for any stream extraction
		std::ostream& operator<<(std::ostream &out, const SillyString &ss){
          out << "[" << ss._length << ":";
 	        for(int i=0;i<ss._length;i++){
 	            out << ss.data[i];
 	        }
 	        out << "]";
 	        return out;
 	    }
	};




