#include "calc.hpp"
#include <cstring>

calc::calc(){

}
calc::~calc(){

}

int calc::position(char c){ 
    if(c >= 'A' && c <= 'z'){
        int p = c - 'A';
        p += (c >= 'a') ? -6 : 0;
        return p;
    }
    return 0; 
}
bool calc::isLetter(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool calc::isNumber(char c){
    return c >= '0' && c <= '9';
}
bool calc::isOperator(char c){
    return c == '+' || c == '*' || c == '/' || c == '=' || c == '(';
}

bool calc::process(){
    //cout << "aqui" << endl;
    
    while(!operators->isEmpty()){
        if(operators->top() == '('){
            operators->pop();
            break;
        }
        if(operators->top() == '='){
            return ass();
        }  
        if(! solver() )
            return false;
    }
    return true;
  
}

void calc::calcExpression(string s){

    int max = s.length();
    this->operands = new stack<string>(max);
    this->operators = new stack<char>(max);
    
    for(int i = 0; i < max; i++){
        if(s[i]==' ')
            continue;
        if(isLetter(s[i])){
            string ss;
            ss += s[i];
            operands->push(ss);
            //cout << '\t' << operands->top() << endl;
        }else if( isNumber(s[i]) ){
            stringstream stream;
            stream << s[i];
            while(isNumber(s[i+1]) || s[i+1] == '.')
                stream << s[++i];
            operands->push(stream.str());
        }else if(isOperator(s[i])){
            if(s[i] != '+')
                this->operators->push(s[i]);
            else{
                if(!operators->isEmpty() && operators->top() == '(')
                    operators->push(s[i]);
                else{
                    process();
                    operators->push(s[i]);
                }
            }
        }else if(s[i] == '-'){
            if(i == 0 || s[i-1]== '('){
                this->operators->push('*');
                this->operands->push("-1");
            }else{
                this->operators->push('+');
                this->operators->push('*');
                this->operands->push("-1");
            }
        }else if(s[i] == ')')
            process();
        else{
            cout << "Comando invalido" << endl;
            return;
        }
    }
    while(!operators->isEmpty())
        if(!process())
            return;
    string op = operands->top();
    if(isLetter(op[0])){
        int p = position(op[0]); 
        cout << ( (variables[p]) ? variablesValue[p] : op[0] ) << endl; 
    }else
        cout << stod(op) << endl;

    delete operators;
    delete operands;
}

bool calc::solver(){
    double v[2];
    for(int i = 0; i < 2; i++){
        string op = operands->top();
        if( isLetter(op[0]) ){
            int p = position(op[0]);
            if( variables[p] )
                v[i] = variablesValue[p];
            else{
                cout << "Variable not defined" << endl;
                return false;
            }
        }else
            v[i] = stod(op);
        operands->pop();
    }
    stringstream ss;
    switch(operators->top()){
        case '+':
            ss << v[0] + v[1];
        break;
        case '*':
            ss << v[0] * v[1];
        break;
        case '/':
            ss << v[1] / v[0];
        break;
    }
    operands->push(ss.str());  
    operators->pop();
    return true;
}
bool calc::ass(){
    double value = stod(operands->top());
    operands->pop();
    int p = position(operands->top()[0]);
    variables[p] = true;
    variablesValue[p] = value;
    operands->pop();
    operators->pop();
    return false;
}
