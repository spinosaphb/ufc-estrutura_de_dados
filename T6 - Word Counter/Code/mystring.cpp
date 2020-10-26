#include "mystring.hpp"


mystring::mystring() : string() {

}
mystring::mystring(const char* x) : string(x) {

}
bool mystring::operator==(const mystring &x){
    int max = this->length();
    if(x.length() != max)
        return false;
    for(int i = 0; i < max; i++)
        if( (*this)[i] != x[i] )
            return false;
    return true;
}