#ifndef MYSTRING
#define MYSTRING
#include <iostream>

using namespace std;

class mystring : public std::string{
    
public:
    mystring();
    
    mystring(const char* x);

    bool operator==(const mystring &x);
};

#endif