#ifndef __STACK__
#define __STACK__
#include <sstream>
using namespace std;

template <typename T>
class stack {
   T *data;
   int size, len;
public:
   stack(int n) {
      len = 0;
      size = n;
      data = new T[size];
   }
   void push(const T& x) {
      if ( isFull() )
         throw string("STACK OVERFLOW!");
      else {
         data[len]=x; 
         len++;
      }
   }
   void pop() {
      if ( isEmpty() )
         throw string("STACK UNDERFLOW");
      else 
         len--;
   }
   T top() {
      if ( isEmpty() )
         throw string("STACK IS EMPTY");
      else
         return data[len-1]; 
   }
   bool isEmpty() {
      return len==0;
   }
   bool isFull() {
      return len==size;
   }
   int height() {
      return len;  
   }
   ~stack() {
      delete [] data;
   }
};

#endif