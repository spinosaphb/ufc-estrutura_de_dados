#include <iostream>
#include "queue.hpp"
#include <cmath>
#include <ctime>
using namespace std;

typedef queue<long long unsigned int> fila;

void _toBin_(int n,long long unsigned int* bin){
    if (n/2)
        _toBin_(n/2,bin);
    *bin = ((*bin)*10) + (n%2);
}

long long unsigned int toBin(int n){
    long long unsigned int aux = 0;
    _toBin_(n,&aux);
    return aux;
}

void _toDec_(long long unsigned int n,int p,int* dec){
    if (n/10)
        _toDec_(n/10,p+1,dec);
    if(n%10)
        *dec+=pow(2,p);
}
int toDec(long long unsigned int n){
    int aux = 0;
    _toDec_(n,0,&aux);
    return aux;
}

int digb(int n){
    long long unsigned int max = toBin(n);
    int digb = 0;
    for( ; max ; max /=10, digb++);
    return digb;
}

int max(long long unsigned int *data,int n){
    int max = 0;
    for(int i=0;i<n;i++)
        if(data[i]>max)
            max = data[i];
    return max;
}

void radiixsort(long long unsigned int *data, int n) {
 
    
    int ndig = digb(max(data,n));
    

    for(int i=0;i<n;i++)
        data[i] = toBin(data[i]);


    fila* b[2];
    for (int k=0; k<2; k++)       
        b[k] = new fila(n);

    long long unsigned int d = 1;
    
    for (int i = 0; i < ndig; i++) {
        for (int j=0; j < n; j++) {
            int dig = ( data[j]/d ) % 10;
            b[dig]->enqueue(data[j]);
        }  
 
        int ivec = 0;    
        for(int j=0; j<2; j++) {
            while ( !(b[j]->isEmpty()) ) {
                data[ivec] = b[j]->get(outlet);
                b[j]->dequeue(); 
                ivec++;
            }
        }
    
        d *= 10;
    }
     
    for(int i=0;i<n;i++)
        data[i] = toDec(data[i]);
    
    for (int k=0; k<2; k++)       
        delete b[k];
}

int main(int argc,char** argv) {

    srand((unsigned int)std::clock());
    
    if(argc<2){
        printf("provide the vector size\n");
        return 0;
    }
    int maxn = atoi(argv[1]);
    long long unsigned int v[maxn];
    
    for(int i=0;i<maxn;i++)
        v[i] = rand()%std::clock();
    for(int i=0;i<15;i++)
        printf(">>>");
    printf("\n");

    for(int i=0;i<maxn;i++)
        cout << v[i] << " ";
    printf("\n");

    radiixsort(v,maxn);

    for(int i=0;i<15;i++)
        printf("<<<");
    printf("\n");

    for(int i=0;i<maxn;i++)
        cout << v[i] << " ";
    printf("\n");



    return 0;
}