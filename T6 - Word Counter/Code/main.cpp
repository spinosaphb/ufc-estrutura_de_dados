#include <iostream>
#include "listv.hpp"
#include <sstream>
#include <fstream>


bool isAlphabet(char c){
    return (c >= 'A' && c <= 'z') || c == '-' || c == '\'';
}

bool isUpper(char c){
    return c >= 'A' && c <= 'Z';
}

mystring& toLower(mystring& s){
    int max = s.length();
    while(--max >= 0)
        if(isUpper( s[max] ))
            s[max] += 32;
    return s;
}

bool formatstring(stringstream& ss){
    if(ss.str().length() < 4)
        return false;
    string s( ss.str() );
    int max = s.length();
    while(--max >= 0)
        if(!isAlphabet( s[max] ))
            s[max] = ' ';
    ss.str( string() );
    ss << s;
    return true;
}

void load(ifstream& infile, string filename){
    stringstream ss;
    mystring s;
    List word;
    cout << "processing file..." << endl;
    infile >> s;
    while(!infile.eof()){
        ss << s << ' ';
        infile >> s;
    }
    cout << "formatting file..." << endl;
    formatstring(ss);
    ss >> s;
    cout << "passing file to the list..." << endl;
    while(!ss.eof()){
        if(s.length() > 3)
            word << toLower(s);
        ss >> s;
    }
    infile.close();
    cout << "sorting list..." << endl;
    word.gnomeSort();
    cout << "saving file..." << endl;
    word.saveAs(filename);
}

int main(int argc, char** argv){
    
    if(argc < 2){
        cout << "file not provided" << endl;
        return 0;
    }
    ifstream infile;
    string s = argv[1];
    infile.open("Input/"+s);
    
    if(!infile.is_open()){
        cout << "file does not exist" << endl;
        return 0;
    }

    load(infile, argv[1]);
    
}







