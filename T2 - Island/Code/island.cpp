#include "island.hpp"
#include <cstring>

island::island(string filename){
    ifstream infile;
    int l = filename.length();
    infile.open("../Archives/Input/"+filename+((filename[l-3]=='.')?"":".md"));
    string date,aux;
    getline(infile, aux);
    
    if(!aux.length()){
        cout << "Error: Empety file\n";
        this->~island();
    }
        
    this->Colls = aux.length();

    while(!infile.fail()){
        date += aux + "\n"; 
        getline(infile, aux);
        this->Rows++;
    }

    infile.close();
    infile.open("../Archives/Input/"+filename+((filename[l-3]=='.')?"":".md"));
    
    Matrixc = new char[Rows*Colls];
    Matrixd = new double[Rows*Colls];
    //Loading Matrixc 
    for(int i = 0; i < Rows; i++){
        //i*Colls+j 
        string line;
        getline(infile,line);
        for(int j = 0; j < Colls; j++)
            Matrixc[i*Colls+j] = line[j];    
    }
    infile.close();
    //Loading Matrixd from Matrixc
    for(int i = 0; i < Rows; i++)
        for(int j = 0; j < Colls; j++)
            Matrixd[i*Colls+j] = (Matrixc[i*Colls+j]=='x')?1:0; 
    
    //Initialize data
    ofstream outfile;
    outfile.open("../Archives/date.md");
    string data;
    data += "# Rows: "+to_string(Rows)+"\tColls: "+to_string(Colls)+'\n';
    outfile << data;
    outfile.close();
}

void island::sum(int i,int j){
    double left, right, down, up, current;
    left = (Matrixc[i * Colls + (j-1)] != '.') ? Matrixd[i * Colls + (j-1)] : 0;
    right = (Matrixc[i * Colls + (j+1)] != '.') ? Matrixd[i * Colls + (j+1)] : 0;
    down = (Matrixc[(i+1) * Colls + j] != '.') ? Matrixd[ (i+1) * Colls + j] : 0;
    up = (Matrixc[(i-1) * Colls + j] != '.') ? Matrixd[(i-1) * Colls + j]:0;
    current = Matrixd[i * Colls + j]; 
    Matrixd[i * Colls + j] = (current+left+right+down+up)/5;
}

bool island::isStable(){
    double soma = 0;
    for(int i = 0; i < Rows;i++)
        for(int j = 0; j < Colls; j++)
            soma += (Matrixc[i * Colls + j] == 'o') ? Matrixd[i * Colls + j]:0;

    if((soma-Sum_Before)<1E-2)
        ImageContinue = false;
    if((soma-Sum_Before)<1E-10)    
        return true;
    Sum_Before = soma;
    this->write();
    return false;
}

void island::write(){
    if(!ImageContinue)
        return;
    string data = "";
    ofstream file;
    file.open("../Archives/Output/output"+to_string(CountOut++)+".md");
    for(int i = 0; i < Rows; i++){
        for(int j = 0; j < Colls; j++){
            data += "# "+to_string(i)+'\t'+to_string(j)+'\t';
            data += to_string(1 - Matrixd[i * Colls + j])+'\n';
        }
    }
    file << data;
    file.close();
}

char& island::pixel(int i,int j){
    return Matrixc[i * Colls + j];
}

void island::printIsland(int m){    
    if(m == _CHAR){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Colls; j++)
                cout << Matrixc[i*Colls+j];
            cout << endl; 
        }
    }else{
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Colls; j++)
                printf("%.2f ",Matrixd[i*Colls+j]);
            cout << endl;
        }
    }

}

void island::save(){
    this->ImageContinue = true;
    write();
    char prompt[50];
    string arg = "python3 code.py "+to_string(CountOut); 
    strcpy(prompt,arg.c_str());
    system(prompt);
    string date = "cd ../Images;convert -delay 150 -loop 0 ";
    for(int i = 0; i < CountOut; i++)
        date += "img"+to_string(i)+".png ";
    date += "anim.gif";
    char v[date.length()];
    strcpy(v, date.c_str());
    system(v);
    system("cd ../Images;rm *.png");
    system("cd ../Archives/Output;rm *.md");
    
}
island::~island(){
    save();
    delete [] Matrixc;
    delete [] Matrixd;
}