#include <iostream>
struct vector{
    int chave;
    int* data;
    vector(int x){}
};

int main(){
    vector* p[10];
    for(int i=0;i<10;i++)
        p[i] = new vector(i);

}