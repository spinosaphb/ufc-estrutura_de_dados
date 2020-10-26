#include <iostream>
#include "stack.hpp"

using namespace std;

class calc{
public:
    // Constructor calc class
    calc();
private:
    // Variables vector
    bool variables[52] = {false};
    // Vector of values variables
    double variablesValue[52] = {false};
    // operands stack
    stack<string>* operands;
    // operators stack
    stack<char>* operators;
    // Return position of caractere in vetor
    int position(char c);
    // Return if character is a letter
    bool isLetter(char c);
    // Return if character is number
    bool isNumber(char c);
    // Return if character is Operator
    bool isOperator(char c);
    // Process the last state of the stack
    bool process();
    // Resolves *,/,+ the last state of the stack
    bool solver();
    // Assignment 
    bool ass();
public:
    // Solver Expression
    void calcExpression(string);
    // Destructor calc class
    ~calc();
};