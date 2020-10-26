#ifndef island_hpp
#define island_hpp
#include <iostream>
#include <fstream>
using namespace std;
class island{
public:
    //indentifier char Matrix
    #define _CHAR 1
    //indentifier double Matrix
    #define _DOUBLE 0
    //number of Colls
    int Colls = 0;
    //number of Rows
    int Rows = 0;
    //Bollean variable image creator
    bool ImageContinue = true;
    //Count number outputs
    int CountOut = 0;
private:
    //sum number of each matrix element
    double Sum_Before = 0;
    //Char Matrix
    char* Matrixc;
    //Double Matrix
    double* Matrixd;
    //Save matrix archive
    void write();
public:
    //Class Constructor 
    island(string filename);
    //Class Destructor
    ~island();
    //Return reference of Pixel Matrix
    char& pixel(int i,int j);
    //Print island
    void printIsland(int);
    //Return if island is stable
    bool isStable();
    //Define element valor of matrixf
    void sum(int i,int j);
    //Convert matrix file to image
    void save(); 
};

#endif