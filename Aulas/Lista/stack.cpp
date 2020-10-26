#include "stack.h"

template <typename T>
stack<T>::stack(int n) {
    len = 0;
    size = n;
    data = new T[size];
}

template <typename T>
void stack<T>::push(T& x) {
    if ( isFull() )
        throw string("STACK OVERFLOW!");
    else {
       data[len]=x; 
       len++;
    }
}

template <typename T>
void stack<T>::pop() {
   if ( isEmpty() )
       throw string("STACK UNDERFLOW");
   else 
       len--;
}

template <typename T>
T stack<T>::top() {
    if ( isEmpty() )
        throw string("STACK IS EMPTY");
    else
        return data[len-1]; 
}

template <typename T>
bool stack<T>::isEmpty() {
    return len==0;
}

template <typename T>
bool stack<T>::isFull() {
    return len==size;
}

template <typename T>
int stack<T>::height() {
    return len;
}

template <typename T>
stack<T>::~stack() {
   delete [] data;
}


