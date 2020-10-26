#ifndef  LIST
#define  LIST

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class List {
    struct node;
public:
    int size;
    List(); 
    List& operator<<(unsigned char x);
    void operator>>(node& x);
    void pop();
private:
    node* operator[](int index);
    void swap(node* n1, node* n2);
public:
    void gnomeSort();
    void print();
    int getFrq();
    unsigned char getKey();
    bool isEmpty();
    ~List();
};
#endif