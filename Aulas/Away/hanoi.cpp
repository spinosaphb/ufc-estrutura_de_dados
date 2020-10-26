#include <iostream>

void hanoi(int n,char a, char b , char c){
    if(!n)
        return;
    else{
        hanoi (n-1,a,c,b);
        std::cout << a << "->" << c << std::endl;
        hanoi (n-1,b,a,c);
    }
    return;
}

int main(){

    hanoi(3,'A','B','C');
    



    return 0;
}