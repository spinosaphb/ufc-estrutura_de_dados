// use para compilar:
// $ g++ -std=c++11 vec.cpp -o saida 
// execute:
// ./saida

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class vec {
   T* data;
   int size; 
   void _invert_(int i, int j) {
      if (i &lt; j) {
          int x = data[i];
          data[i] = data[j];
          data[j] = x;
          _invert_(i+1, j-1);
      }
   }
   int last;
public:
   vec(int size) {
       data = new T[size];
       vec::size = size;
       last = 0;
   } 
   string toStr() {
       string s;
       for(int k = 0; k &lt; size; k++) 
          s += to_string(data[k]) 
               + " ";
       s = "{" + s + "}";
       return s 	 	 ;
   }
                     
   T& operator[] (int k) {
       if (k >= 0 && k < size)
           return data[k];
       else
           throw "acesso invalido"; 
   } 
   vec<T>& operator<< (const int& x) {
      if (last < size) {
          data[last++] = x;
          for (int k = last; 
               k < size; 
               k++)
              data[k] = 0; 
      } 
      return *this; 
   }   
   void invert() {
       _invert_(0, size-1);
   }
   static vec <T> ones(int n) {
       vec u(n);
       for (int k=0; k<n; k++)  
           u[k] = 1;
       return u;
   }
   int sortByBubble() {

   }
   //quick sort
    int part(int begin, int final){  
        int pivo = data[final];   
        int i = (begin - 1);   
    
        for (int j = begin; j <= final - 1; j++){    
            if (data[j] < pivo){  
                i++;   
                std::swap(data[i], data[j]);  
            }  
        }  
        std::swap(data[i + 1], data[final]);  
        return (i + 1);  
    }



   int sorByInsertion(){
        int j;  
        for (int i = 1; i < size; i++){  
            T key = data[i];
            for(j = i-1;j>=0 && data[j]>key;j--)  
                data[j+1] = data[j];     
            data[j+1] = key;  
        }  
   }
   ~vec() {
       delete [] data;
   }
};