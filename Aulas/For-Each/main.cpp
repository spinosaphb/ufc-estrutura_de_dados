#include "linkedlist.h"
#include <iostream>

int main() {
    list<int> ls;
    ls << 2  << 5 << 11 << 3;
    int k;
    //for (list<int>::iter i = ls.begin();
    //     !i.end();
    //     ++i)
    forList(int, x, ls)
        std::cout << varlist << '\n'; //i.key() << " ";
}