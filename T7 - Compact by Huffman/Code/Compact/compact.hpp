
#ifndef _COMPACT_
#define _COMPACT_

#include <iostream>
#include <sstream>
#include "../WordCounter/listv.hpp"
#include "../SortedQueue/SQueue.hpp"
#include "../Queue/queue.hpp"
#include "../Tree/Tree.hpp"
#include "base.hpp"

class Compact : public Tree{
    /**
     * size file
     * */
    long long int size = 0;
    /**
     * const descompact
     * */
    int _Descompact = 0;
    /**
     * filename
     * */
    string filename;
    /**
     * input archive
     * */
    ifstream infile;
    /**
     * output archive
     * */
    ofstream outfile;
    /**
     * Frequency table
     * */
    string table[256];
    /**
     * Frequency Tree
     * */
    Tree* root;
    /**
     * Priority Queue
     * */
    SQueue<Tree> fQueue;
        /**
     * Make Priority Queue
     * */
    void makeQueue(List& ByteC);
    /**
     * Make Tree acess
     * */
    void makeTree();
    /**
     * Make Tree for descompact acess
     * */
    void makeTree(int);
    /**
     * Make Table
     * */
    void makeTable();
    /**
     * process Archive swapping key to code
     * */
    void processArchive();
    /**
     * save table
     * */
    string saveTable();
public:
    /**
     * Class constructor
     * */
    Compact(string filename);
    /**
     * print table code
     * */
    void printTable();
    /**
     * Compact file
     * */
    bool compactByHuffman();
    /**
     * Descompact file
     * */
    void descompact();
    /**
     * Class desctructor
     * */
    ~Compact();
};
#endif