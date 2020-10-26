#include <iostream>

int fat(int n){
    return (!n) ?1:n * fat(n-1);
}
int euc(int a,int b){
    return (!b)?a:euc(b,a%b);
}

int main (){
    int x = euc(4,12);
    std::cout << x; 
}