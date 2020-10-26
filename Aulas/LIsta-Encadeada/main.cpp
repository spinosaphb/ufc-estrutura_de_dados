#include "linkedlist.h"
#include <iostream>

int main() {
   list<int> ls;
   ls << 2  << 5 << 11 << 3;
   for (list<int>::iter i = ls.begin();!i.end();i++)
        std::cout << i.key() << " ";
}
       
