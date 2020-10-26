#include "Tree.hpp"
#include "../Queue/queue.hpp"


struct Tree::node {
    unsigned char key;
    int frq; 
    node *left;
    node *right;
    
    node() {
        this->key = '+';
        this->frq = 0;
        left = nullptr;
        right = nullptr;
    }
    node(unsigned char key, int frq) {
        this->key = key;
        this->frq = frq;
        left = nullptr;
        right = nullptr;
    }
    bool isLeaf(){
        return !left && !right;
    }
};

Tree::Tree(){
    root = nullptr;
}
Tree::Tree(node* root){
    this->root = root;
}
Tree::Tree(Tree& other){
    root = new node(other.root->key,other.root->frq);
    root->left = other.root->left;
    root->right = other.root->right;
}

Tree::Tree(unsigned char key, int frq){
    root = new node(key, frq);
}

Tree::Tree(Tree* left, Tree* right){
    root = new node();
    root->frq = left->getFrq() + right->getFrq();
    root->left = left->root;
    root->right = right->root;
}

bool Tree::operator<(Tree& x){
    return root->frq < x.getFrq();
}

bool Tree::operator<=(Tree& x){
    return root->frq <= x.getFrq();
}

bool Tree::operator==(Tree& x){
    return root->frq == x.getFrq();
}

int Tree::getFrq(){
    return root->frq;
}
unsigned char Tree::getKey(){
    return root->key;
}

void Tree::print(){
    ofstream outtree;
    outtree.open("../../Data/datatree.txt");
    node* no = root;
    Queue <node*> fila; // cria fila vazia
    fila << no; // enfileira o nó raiz na fila
    while ( ! fila.isEmpty () ) {
        fila >> no;
        if (no != nullptr) {
            if(no->left)
                fila << (no->left);
            if(no->right)
                fila << (no->right);
            outtree << no->key << '-' << no->frq << endl;
            cout << no->key << '-' << no->frq << endl; /* visita raiz */
        }
    }
}

void Tree::makeLeavesCode(node *ptnode, string* table, string bincode){
    if(ptnode->isLeaf()){
        code data;
        data.key = ptnode->key;
        data.byte = bincode;
        table[ptnode->key] = bincode;
        return;
    }
    makeLeavesCode(ptnode->left, table, bincode +'0');
    makeLeavesCode(ptnode->right, table, bincode +'1'); 
    
}

void Tree::make(string code, unsigned char character){

    if(root == nullptr)
        this->root = new node();
    int max = code.length();
    
    node* ptnode = root;

    for(int i = 0; i < max; i++){
        if(code[i] == '0'){
            if(ptnode->left == nullptr){
                ptnode->left = new node();
            }
            ptnode = ptnode->left;
            
        }else{
            if(ptnode->right == nullptr){
                ptnode->right =  new node();
            }
            ptnode = ptnode->right;
            
        }
    }
    ptnode->key = character;
    
}

string tobin(int dec){
    string data = "";
    while(dec){
        data = (to_string(dec%2) + data);
        dec /= 2; 
    }
    while(data.length() < 8)
        data = '0' + data;
    return data;   
}

void Tree::decode(ofstream& outfile, ifstream& infile,long int cbytes){
    node* ptnode = root;
    Queue<unsigned char> bytes;
    char c;
    infile.read(&c,1); 
    while(infile && !infile.eof()){
        string byte = tobin((unsigned char)c);
        int max = byte.length();
        for(int i = 0; i < max; i++){
            bytes << byte[i];
        }
        while(!bytes.isEmpty()){
            unsigned char bit = bytes.front();
            bytes.pop();
            if(ptnode)
                ptnode = (bit == '0') ? ptnode->left : ptnode->right;
            if(ptnode && ptnode->isLeaf()){
                cbytes--;
                cout << ptnode->key << ' ';
                outfile << ptnode->key;
                ptnode = root;
            }
            if(!cbytes)
                return;
                
        }
        infile.read(&c,1);
    }
}

void Tree::setKey(unsigned char key){
    this->root->key = key;
}

void Tree::search(Tree *ptnode, string* table){
    makeLeavesCode(ptnode->root, table, string());
}

Tree::~Tree(){  
    delete root; 
}

