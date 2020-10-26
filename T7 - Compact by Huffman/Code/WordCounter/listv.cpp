#include "listv.hpp"

struct List::node {
    unsigned char key;
    int frq;
    node *next;
    node *prev;
    node(char k) {
        key = k;
        frq = 1;
        next = 0;
        prev = 0;
    }
} *ptraiz;

    
List::List() {
    ptraiz = 0;
    size = 0;
}

List& List::operator<<(unsigned char x) {
    if (size == 0) {
        ptraiz = new node(x);
        size++;
    }else if (x == ptraiz->key) {
        ptraiz->frq++;
    }else{
        node *p = ptraiz;
        while (p->next != 0 && p->next->key != x)
            p = p->next;
        if(p->next != 0)
            p->next->frq++;
        else{
            node* q = new node(x);
            p->next = q;
            q->prev = p;
            size++;
        }
        
    }
    return *this;
}

void List::operator>>(node& x){
    if(!ptraiz)
        return;
    x = *ptraiz;
    ptraiz = ptraiz->next;
}

List::node* List::operator[](int index){
    node* aux = ptraiz;
    while(index--)
        aux = aux->next;
    return aux;
}

void List::swap(node* n1, node* n2){
    if(n1 == ptraiz)
      ptraiz = n2;

    n2->prev = n1->prev;
    n1->prev = n2;
    n1->next = n2->next;
    n2->next = n1;
    
    if(n2->prev != nullptr)
        n2->prev->next = n2;
    if(n1->next != nullptr)
        n1->next->prev = n1;
}

void List::gnomeSort(){
    int index = 0; 
    
    while (index < size) {   
        if ( index == 0 || (*this)[index]->frq >= (*this)[index - 1]->frq) 
            index++; 
        else { 
            swap((*this)[index - 1], (*this)[index]); 
            index--; 
        }
    }
    return; 
}

void List::print(){
    if( !ptraiz )
        return;
    node* aux = ptraiz;
    do{
        cout << aux->key << '\t' << aux->frq << endl;
        aux = aux->next;
    }while(aux != 0); 
}

bool List::isEmpty(){
    return ptraiz == nullptr;
}

int List::getFrq(){
    return ptraiz->frq;
}
void List::pop(){
    node* aux = ptraiz;
    ptraiz = ptraiz->next;
    delete aux;
}

unsigned char List::getKey(){
    return ptraiz->key;
}

List::~List() {
    while (ptraiz != 0) {
        node *p = ptraiz;
        ptraiz = ptraiz->next;
        delete p;
    }
}
