#include <iostream>
#include "queue.hpp"
#include "libpgm.h"
#define M 10

struct Fill{
    int x;
    int y;
};

bool isRange(int x,int y){
    return (x>=0 && y>=0 && x<M && y<M )?true:false;
}

void _floodfill_(char m[][M], Fill* d, char replace, char target){
    
    if(target==replace)
        return;
    if(m[d->x][d->y]!=target)
        return;
    m[d->x][d->y] = replace;
    queue<Fill>* q = new queue<Fill>(4*M);

    q->enqueue(*d);
    
    while(!q->isEmpty()){
        Fill n = q->get(outlet);
        q->dequeue();
        if(isRange(n.x-1,n.y) && m[n.x-1][n.y]==target){
            m[--n.x][n.y] = replace;
            q->enqueue(n);
        }
        if(isRange(n.x+1,n.y) && m[n.x+1][n.y]==target){
            m[++n.x][n.y] = replace;
            q->enqueue(n);
        }
        if(isRange(n.x,n.y-1) && m[n.x][n.y-1]==target){
            m[n.x][--n.y] = replace;
            q->enqueue(n);
        }
        if(isRange(n.x,n.y+1) && m[n.x][n.y+1]==target){
            m[n.x][++n.y] = replace;
            q->enqueue(n);
        }
    }

}
void floodfill(char m[][M], Fill* d, char color){
    int alvo = m[d->x][d->y];
    _floodfill_(m,d,color,alvo);
}
int main(){

    char m[M][M];
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++){
            if(!i || !j || i==M-1 || j==M-1)
                m[i][j] = '1';
            else
                m[i][j] = '2';
        }
            
    for(int i=0;i<M;i++,printf("\n"))
        for(int j=0;j<M;j++)
            printf("%c ",m[i][j]);
    
    printf("\n");
    Fill p;
    p.x = 4;
    p.y = 4;

    floodfill(m,&p,'4');
    printf("\n");
    
    for(int i=0;i<M;i++,printf("\n"))
        for(int j=0;j<M;j++)
            printf("%c ",m[i][j]);

}