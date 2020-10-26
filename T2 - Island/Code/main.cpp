#include <iostream>
#include <fstream>
#include <cstring>
#include "island.hpp"

using namespace std;

void processIsland(string file){
    island l(file);
    do{
        for(int i = 0; i < l.Rows; i++)
            for(int j = 0; j < l.Colls; j++){
                if(l.pixel(i,j) == 'o')
                    l.sum(i,j);
            }
    }while(!l.isStable());      
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Archive not providied\n");
        return 0;
    }
    processIsland(argv[1]);
}