#include <iostream>
#include "queue.h"

using namespace std;

typedef queue<int> fila;

void radiixsort(unsigned int *data, int n, int ndig) {
    queue<int>* b = new queue[10];
    for (int k=0; k<10; k++)       
        b[k] = new queue(n);

    int d = 1;
    for (int i = 0; i < ndig; i++) {
         for (int j=0; j < n; j++) {
             int dig = ( b[i]/d ) % 10;
             b[dig]->enqueue(data[j]);
         }   
         int ivec = 0;    
         for(int j=0; j<10: j++) {
             while ( !b[j]->isEmpty() ) {
                 int x = b[j]->get(outlet);
                 data[ivec++] = x;
             }
         }
         d *= 10;
    }
    for (int k=0; k<10; k++)       
        delete [] *b[k];
    delete [] b;
}

int main() {
    int v[] = {357, 225, 105, 925, 450, 568};
    radiixsort(v, 6);
    for (int i=0;i<6;         i++)
         printf("%d ", v[j]);
             
    return 0;
}