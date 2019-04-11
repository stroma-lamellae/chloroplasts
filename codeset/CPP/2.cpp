#include "SillyString.h"
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>

namespace SillyString {
//This is the constructor which copies the data into a new char array.
SillyString::SillyString(const char *data) {
  this->_length = 0;
  while (data[_length]!='\0'){
    this-> _length++;
  }
  this->data = new char[this->_length];
  for(int i = 0; i < this->_length; i++){
    this->data[i] = data[i];
  }
}

SillyString::SillyString(const char *data, int length) {
  this->_length = length;
  if (data[length]=='\0'){
    std::cout<<"This doesn't have enough letters to do that."<<std::endl;
    return;
  }
  this->data = new char[this->_length];
  for(int i = 0; i < this->_length; i++){
    this->data[i] = data[i];
  }
}

SillyString::SillyString(const SillyString &original) {
  this->_length = original._length;
  this->data = new char[this->_length];
  for(int i = 0; i < this->_length; i++){
    this->data[i] = original.data[i];
  }
}

//Concatenate operator
SillyString SillyString::operator+(const SillyString &other) const{
  SillyString result;
  int count;
  result._length = this->_length + other._length;
  result.data = new char[result._length];
  for (int i = 0; i < this->_length; i++){
    result.data[i] = this->data[i];
  }
  for (int i = this->_length; i < this->_length + other._length; i++){
    result.data[i] = other.data[count];
    count = count + 1 ;
  }
  return result;
}

//to Uppercase operator
SillyString SillyString::operator+() const{
  SillyString result;
  result._length = this->_length;
  result.data = new char[result._length];
  for (int i = 0; i < this->_length; i++){
    result.data[i] = toupper(this->data[i]);
  }
  return result;
}

//to Lowercase operator
SillyString SillyString::operator-() const{
  SillyString result;
  result._length = this->_length;
  result.data = new char[result._length];
  for (int i = 0; i < this->_length; i++){
    result.data[i] = tolower(this->data[i]);
  }
  return result;
}

//Backwards operator
SillyString SillyString::operator~() const{
  SillyString result;
  result._length = this->_length;
  result.data = new char[result._length];
  for (int i = 0; i < this->_length; i++){
    result.data[i] = this->data[(this->_length - 1) -i];
  }
  return result;
} //Backwards

//lexicographic priority check
bool SillyString::operator<=(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] <= other.data[i]){
      return true;
    }
  }
  return false;
}

//lexicographic < check
bool SillyString::operator<(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] < other.data[i]){
      return true;
    }
  }
  return false;
}

//lexicographic >= check
bool SillyString::operator>=(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] >= other.data[i]){
      return true;
    }
  }
  return false;
}

//lexicographic < check
bool SillyString::operator>(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] > other.data[i]){
      return true;
    }
  }
  return false;
}

//equality check
bool SillyString::operator==(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] != other.data[i])
      return false;
  }
  return true;
}

//inequality check
bool SillyString::operator!=(const SillyString &other) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] != other.data[i]){
      return true;
    }
  }
  return false;
}

//splice operator
SillyString SillyString::operator()(const int from, const int to) const{
  SillyString result;
  int a = 0;
  result._length = (to - from);
  result.data = new char[result._length];
  for (int i = from; i < to; i++){
    result.data[a] = this->data[i];
    a++;
  }
  return result;
}

//returns char at given position
char SillyString::operator[](const int &pos) const{
  if (this->data[pos]!='\0'){
    return this->data[pos];
  }
  else
  return '\0';
}

//returns position of given char
int SillyString::indexOf(char c) const{
  for (int i = 0; i<this->_length; i++){
    if (this->data[i] == c){
      return i;
    }
  }
  return -1;
}

//returns length
int SillyString::length() const{
  return this->_length;
}

//returns position at char from given position
int SillyString::indexOf(char c, int pos) const{
  for(int i = 0; i<(this->_length - pos); i++){
    if(this->data[pos + i] == c)
    return (int)i;
  }
 return -1;
}

//stream operator
std::ostream& operator<<(std::ostream &out, const SillyString &ss){
  return out << ss.data;
}

//destructor
SillyString::~SillyString(){
  //std::cout<<"The string "<<data;
  delete this->data;
  //std::cout<<" has been DESTROYED."<<std::endl;
}


}
