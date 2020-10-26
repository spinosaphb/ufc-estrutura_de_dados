#include <iostream>
#include "calc.hpp"

using namespace std;

int main(){
    
    string express = "exit";
    calc p;   
    do{
        cout << ">>> ";
        getline(cin, express);
        if(express == "exit" || express == "<<<")
            break;
        p.calcExpression(express);
    }while(true);
    
    return 0;
}