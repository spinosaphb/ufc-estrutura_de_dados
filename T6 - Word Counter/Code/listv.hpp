#ifndef  LIST
#define  LIST

#include "mystring.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>


class List {
    struct node;

public:
    int size;
    
    List(); 
    List& operator<<(mystring x);
private:
    node* operator[](int index);
    void swap(node* n1, node* n2);
public:
    void saveAs(string filename);
    void gnomeSort();
    void print();
    ~List();
};
#endif