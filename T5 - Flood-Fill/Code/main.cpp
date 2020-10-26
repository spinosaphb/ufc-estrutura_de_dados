#include <iostream>
#include "queue.hpp"
#include "libpgm.h"
#include "cstring"


using namespace std;

struct Fill{
    int x;
    int y;
};

bool isRange(pgm* matriz,int x,int y){
    return (x>=0 && y>=0 && x<matriz->nCols() && y<matriz->nRows() )?true:false;
}

void _floodfill_(pgm* matriz,Fill* d,char replace, char target){

    if(target==replace)
        return;
    if(matriz->pixel(d->x,d->y)!=target)
        return;
    matriz->pixel(d->x,d->y) = replace;

    queue<Fill>* q = new queue<Fill>((matriz->nRows()+matriz->nCols())*2);

    q->enqueue(*d);
    
    while(!q->isEmpty()){
        
        Fill n = q->get(outlet);
        q->dequeue();

        if(isRange(matriz,n.x-1,n.y) && matriz->pixel(n.x-1,n.y)==target){
            matriz->pixel(--n.x,n.y) = replace;
            q->enqueue(n);
        }
        if(isRange(matriz,n.x+1,n.y) && matriz->pixel(n.x+1,n.y)==target){
            matriz->pixel(++n.x,n.y) = replace;
            q->enqueue(n);
        }
        if(isRange(matriz,n.x,n.y-1) && matriz->pixel(n.x,n.y-1)==target){
            matriz->pixel(n.x,--n.y) = replace;
            q->enqueue(n);
        }
        if(isRange(matriz,n.x,n.y+1) && matriz->pixel(n.x,n.y+1)==target){
            matriz->pixel(n.x,++n.y) = replace;
            q->enqueue(n);
        }

    }

}
void floodfill(char* filename,char color,int i,int j){
    string x = "Input/";
    pgm matriz(x + filename);
    i = matriz.nCols()/2;
    j = matriz.nRows()/2;
    int alvo = matriz.pixel(i,j);
    Fill d;
    d.x = i;
    d.y = j;
    _floodfill_(&matriz,&d,color,alvo);
    filename[strlen(filename)-4] = '\0';
    string saida = filename;
    saida+="_out.pgm";
    matriz.saveAs("Output/"+saida);
}
int main(int argc, char** argv){

    if(argc < 5){
        printf("envie imagem,cor,linha(i) e coluna(j) de entrada nos argumentos nesta ordem:\n");
        return 0;
    }
    floodfill(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));  

}