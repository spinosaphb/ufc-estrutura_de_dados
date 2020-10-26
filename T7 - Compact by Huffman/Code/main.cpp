#include <iostream>
#include <sstream>
#include "Compact/compact.hpp"


int main(int argc, char** argv){
    if(argc < 3){
        cout << "arguments not provided";
        return 0;
    }
    string filename = argv[2];
    Compact archive(filename);
    string opc = argv[1]; 
    if(opc == "compact")
        archive.compactByHuffman();
    else
        archive.descompact();
}