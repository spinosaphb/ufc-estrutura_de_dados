#include <iostream>
#ifndef _BASE_
#define _BASE_
using namespace std;

struct code{
    unsigned char key = 0;
    string byte; 
    code(){
        
    }
    code(unsigned char key){
        this->key = key;
    }
    code(code& other){
        this->key = other.key;
        this->byte = other.byte;
    }
    bool exist(){
        return byte.length() != 0;
    }
    bool operator==(code& other){
        return this->key == other.key;
    }
};
#endif