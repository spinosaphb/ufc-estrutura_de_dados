#include<iostream>
#include<sstream>
#include<string>
 
using namespace std;
 
class array {
   int* data;
   int len;
   int size; 
public:
   array(int n) {
       len = n;
       data = new int[n];
       size = 0;
   } 
   string toStr() {
       stringstream ss;
       ss << "{ ";
       for(int k = 0; k < size; k++) 
          ss << data[k] << " ";
       ss << " }";
       return ss.str();
   }
   void add(int x) { 
       if (size < len) 
           data[size++] = x;
       else {
           cout << "vetor cheio!";
       }
   }                        
   array& operator <<
          (const int& x) 
   {
       this->add(x);
       return *this ;
   }
   int& operator[] (int k) {
       return data[k];
   } 
   //menor e maior valor
   void extremos(int& min, int& max) {
        min = data[0];
        max = data[0];
        for(int i=0;i<size-1;i++){
            if(data[i]<min)
                min = data[i];
            if(data[i]>max)
                max = data[i];
        }
   }
   //dois maiores valores
   void maximus(int& a, int& b) {
       a = b = data[0];
       for(int i=0;i<size-1;i++){
            if(data[i]>a)
                a = data[i];
            else
                if(data[i]>b && b<a)
                    b = data[i];
       }
   } 
   //soma de todos os elementos
    int soma() {
        int soma = 0;
        for(int i=0;i<size-1;i++)
            soma += data[i];
        return soma;
    }
   //inverte a lista 
    void invert() {
        for(int i=0,j=size-1;i<j;i++,j--){
            int x = data[i];
            data[i] = data[j];
            data[j] = x;
        }
    }
   ~array() {
       delete [] data;
       cout << "morri";
   }
//static
   static int red;  
   static void update(int c) {
       array::red = c;      
   }  
};
 
int array::red = 0;
 
int main() {
    array w(10);
    w.update(2);
 
    array::red = 22; 
    array::update(1);
 
    w << -2 << 4 << 6 << 8;
    w[0] = -5;
 
    cout << w.toStr();  
    cout << w[2];
 
    // CINCEITO DE REFERENCIA
 
    // teste(int& x) {      
    //    int b = 100;
    //    x = b;
    // }
    // int a;
    // teste(a) 
 
 
    return 0; 
}