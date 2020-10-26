#include <iostream>
#include <sstream>
#include "compact.hpp"


int main(int argc, char** argv){
    if(argc < 3){
        cout << "arguments not provided";
        return 0;
    }
    Compact archive(argv[2]);
    string opc = argv[1]; 
    if(opc == "compact")
        archive.compactByHuffman();
    else
        archive.descompact();
}