#ifndef  BTree
#define  BTree

#include <iostream>
#include <sstream>
#include "../Queue/queue.hpp"
#include "../Compact/base.hpp"

using namespace std;

class Tree {
    struct node;
    node *root;
private:
    void makeLeavesCode(node* ptnode, string* table, string bincode);
public:
    Tree();
    Tree(Tree&);
    Tree(unsigned char, int);
    Tree(Tree*, Tree*);
    Tree(node*);
    bool operator<(Tree& x);
    bool operator<=(Tree& x);
    bool operator==(Tree& x);
    void print();
    int getFrq();
    unsigned char getKey();
    void setKey(unsigned char key);
    void make(string, unsigned char character);
    void search(Tree* root, string* table);
    void decode(ofstream&, ifstream&,long int);
    bool isEmpty();
    ~Tree();
};
#endif