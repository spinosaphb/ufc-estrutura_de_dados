#ifndef _QUEUE_
#define _QUEUE_

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T>

class Queue {
    struct node {
        T key;
        node *next;
        node *prev;
        node(T key) {
            this->key = key;
            next = nullptr;
            prev = nullptr;
        }
    } *ptraiz,*ptend;
    int size;
public:
    Queue() {
        ptraiz = nullptr;
        ptend = nullptr;
        size = 0;
    }
    Queue& operator<<(T x) {
        if (size == 0) {
            ptraiz = new node(x);
            ptend = ptraiz;
            size++;
        }else{
            node *aux = new node(x);
            aux->next = ptraiz;
            ptraiz->prev = aux;
            ptraiz = aux;
            size++;
        }
        return *this;
    }
    void operator>>(T& x) {
        x = this->front();
        this->pop();
    }

    T front(){
        return ptend->key;
    }

    T operator[](int index){
        node* aux = ptraiz;
        while(index--)
            aux = aux->next;
        return aux->key;
    }

    int search(T& key){
        node* aux = ptraiz;
        for(int i = 0;aux != nullptr; i++){
            if(aux->key == key)
                return i;
            aux = aux->next;
        }
        return -1;
    }

    void pop(){
        if(size == 1){
            delete ptend;
            ptraiz = nullptr;
            ptend = nullptr;
        }else{
            ptend->prev->next = nullptr;
            delete ptend;
            ptend = ptend->prev;
        }
        --size;
    }
public:
    void print();

    bool isEmpty(){
        return !size;
    }
    int length(){
        return size;
    }
    ~Queue() {
        while (ptraiz != 0) {
            node *p = ptraiz;
            ptraiz = ptraiz->next;
            delete p;
        }
    }
};
#endif
