#ifndef  SQUEUE
#define  SQUEUE

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>

class SQueue {
    struct node {
        T* key;
        node *next;
        node(T& key){// nao to entendendo a necessidade desses : 
            this->key = &key;
            next = nullptr;
        }
    } *ptraiz;
    int size;
public:
    SQueue() {
        ptraiz = nullptr;
        size = 0;
    }
    SQueue& operator<<(T& x) {
        if (size == 0)
            ptraiz = new node(x);
        else if (x < *(ptraiz->key)) {
            node *aux = new node(x);
            aux->next = ptraiz;
            ptraiz = aux;
        }else{
            node *p = ptraiz;
            while (p->next != nullptr && *(p->next->key) <= x)
                p = p->next;
            node *q = new node(x);
            q->next = p->next;
            p->next = q;
        }
        size++;
        return *this;
    }
    void operator>>(T*& x){
        if(!ptraiz)
            return; 
        x = ptraiz->key;
        ptraiz = ptraiz->next;
        size--;
    }
    void print();
    bool isEmpty(){
        return ptraiz == nullptr;
    }
    int length(){
        return size;
    }
    ~SQueue() {

        while (ptraiz != nullptr) {
            node *p = ptraiz;
            ptraiz = ptraiz->next;
            delete p;
        }
    }
};
#endif


