
// use para compilar:
// $ g++ -std=c++11 vec.cpp -o saida 
// execute:
// ./saida
 
#include<iostream>
#include<sstream>
#include<string>
 
using namespace std;
 
class vec {
   int* data;
   int size; 
   struct two {
       int fst;
       int snd; 
       two(int i, int j) {
           two::fst = i;
           two::snd = j;
       }
   };
   int _soma_(int n) {
       if (n==0)
           return 0;
       return data[n-1] +
              _soma_(n-1);      
   } 
   void _invert_(int i, int j) {
      if (i < j) {
          int x = data[i];
          data[i] = data[j];
          data[j] = x;
          _invert_(i+1, j-1);
      }
   }
   int last;
public:
   vec(int size) {
       data = new int[size];
       vec::size = size;
       last = 0;
   } 
   string toStr() {
       string s;
       for(int k = 0; k < size; k++) 
          s += to_string(data[k]) 
               + " ";
       s = "{" + s + "}";
       return s          ;
   }
                      
   int& operator[] (int k) {
       return data[k];
   } 
   vec& operator<< (const int& x) {
      if (last < size) {
          data[last++] = x;
          for (int k = last; 
               k < size; 
               k++)
              data[k] = 0; 
      } 
      return *this; 
   }
   two extremos() {
       int a, b;
       a = b = (*this)[0];
       for (int k = 1; k<size; k++) {
          if (data[k] < a) a = data[k];
           if (data[k] > b) b = data[k];
       }
       return two(a, b); 
   }
   two maximus() {
       int a, b;
       a = b = (*this)[0];
       for (int k = 1; k<size; k++) {
          if (data[k] > a) {
              b = a;   
              a = data[k];
           }
       }
       return two(a, b);  
   } 
   int soma() {
        return _soma_(size);
   } 
   void invert() {
       _invert_(0, size-1);
   }
   ~vec() {
       delete [] data;
   }
};
 
int main() {
    vec u(5);
    u << 1 << 6 << 5 << 11 << -7;
    u.invert(); 
    cout << u.toStr() << "\n";
    return 0; 
}