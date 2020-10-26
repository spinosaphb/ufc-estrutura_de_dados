#include "compact.hpp"
#include <cmath>

Compact::Compact(string filename){
    this->filename = filename;
}

void Compact::makeQueue(List& ByteC){
    while(!ByteC.isEmpty()){
        unsigned char key = ByteC.getKey();
        int frq = ByteC.getFrq();
        Tree *temp = new Tree(key,frq);
        fQueue << *temp;
        ByteC.pop();
    }
}

void Compact::makeTree(){
    if(fQueue.isEmpty())
        return;
    Tree *n1,*n2;
    while(fQueue.length() > 1){
        fQueue >> n1;
        fQueue >> n2;
        Tree *father = new Tree(n1,n2);
        fQueue << *father;
    }
    fQueue >> root;
    root->print();
}

void Compact::makeTree(int _Descompact){
    root = new Tree();
    for(int i = 0; i < 256; i++){
        if( !table[i].empty() )
            this->root->make(table[i], i);
    }
    this->root->print();
}

void Compact::makeTable(){
    root->search(root, table);
    printTable();
}

string Compact::saveTable(){
    string cod;
    cod += to_string( this->size ) + '\n';
    cod += this->filename + '\n';
    for(int i = 0; i < 256; i++){
        if(table[i].empty())
            continue;
        cod += i;
        cod += '\t';
        cod += table[i] + "\n"; 
    }
    cod += ";\t;;\n";
    cout << cod;
    return cod;
}

string refat(string& name){
    int max = name.length();
    string aux;
    for(int i = 0; i < max && name[i] != '.'; i++)
        aux += name[i];
    aux += ".sp";
    return aux;
}

int tobyte(string sb){ 
    while(sb.length() < 8)
        sb = (sb + '0');
    int dec = 0;
    for(int i = 7; i >= 0 ; i--)
        dec += (sb[7 - i] == '0') ? 0 : pow(2,i);
    return dec;   
}

void Compact::processArchive(){
    infile.open("../Data/"+filename,ios::binary);
    outfile.open("../Data/"+refat(filename),ios::binary);
    outfile << saveTable();
    Queue<char> bytes;
    char c;
    infile.read(&c,1);
    while(infile && !infile.eof()){
        if( table[ (unsigned char)c ].empty()){
            infile.read(&c,1);
            continue;
        }
        int max = table[ (unsigned char)c ].length();
        for(int k = 0; k < max; k++)
            bytes << table[ (unsigned char) c][k];
        while(bytes.length() >= 8){
            string byte;
            for(int j = 0; j < 8; j++){
                byte += bytes.front();
                bytes.pop();
            }
            outfile << (unsigned char) tobyte(byte);
        }
        infile.read(&c,1);
    }
    string byte;
    while(!bytes.isEmpty()){
        byte += bytes.front();
        bytes.pop(); 
    }
    if(!byte.empty())
        outfile << (unsigned char) tobyte(byte);
    outfile.close();
}

bool Compact::compactByHuffman(){
    infile.open("../Data/"+filename,ios::binary);
    if( !infile ){
        cout << "file not found" << endl;
        return false;
    }
    char c;
    infile.read(&c,1);
    List wc;
    while(infile && !infile.eof()){
        this->size++;
        wc << (unsigned char) c;
        infile.read(&c,1);
    }
    wc.gnomeSort();
    wc.print();
    makeQueue(wc);
    makeTree();
    makeTable();
    infile.close();
    processArchive();
    return true;
}

void Compact::descompact(){
    infile.open("../Data/"+filename);
    if( !infile ){
        cout << "file not found" << endl;
        return;
    }
    char c;
    string data;
    infile >> data;
    size = stol(data);
    infile >> data;
    filename = data;
    
    infile.read(&c,1);
    infile.read(&c,1);
    infile >> data;
    while(infile && !infile.eof()){
        if(c == ';' && data == ";;")
            break;
        table[(unsigned char)c] = data;
        infile.read(&c,1);
        infile.read(&c,1);
        infile >> data;
    }
    infile.read(&c,1);
    cout << size << endl;
    cout << filename << endl;
    printTable();
    makeTree(_Descompact);
    outfile.open("../Data/"+filename);
    this->root->decode(outfile, infile, size);
    outfile.close();
}

void Compact::printTable(){
    for(int i = 0; i < 256; i++)
        if(!table[i].empty())
            cout << (unsigned char)i << '\t' << table[i] << endl;
            
}

Compact::~Compact(){

}