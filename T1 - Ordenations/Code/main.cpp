#include <iostream>
using namespace std;
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include "tvec.cpp"
/**
 * escreve em um arquivo os algoritmos e seus cicles
 * */

void write(string c,vec<int>* u){

        string date,aux;
        ifstream infile;
        infile.open(c+".md");
        
        getline(infile, aux);
        while(!infile.fail()){
            date += aux + "\n"; 
            getline(infile, aux);
        }
       
        infile.close();
        

        ofstream outfile;
        outfile.open(c+".md");
        if(!outfile.is_open() || !outfile.good()){
            printf("ERRO!");
            outfile.close();
            return;
        }
       
        //date+="algorithm: "+c+"\n";
        date+="# size: "+to_string(u->getsize())+"\n";
        date+=("# clock: ")+to_string(u->getclock())+"\n\n";
    
        outfile << date;
        outfile.close();      
}
void toarrey(char* array,string s){
    strcpy(array, s.c_str());
}
void clearArchives(){
    string folders[] = {"Elementares/","O(n)-vs-O(nlog(n))/","Select-Quick/"};
    string archives[] = {"bubblesort","insertionsort","selectionsort","mergesort",
    "quicksort","heapsort","radixsort"};
    
    
    string aux;
    ifstream infile;
    infile.open("data.md");
    getline(infile, aux);
    char arrey[aux.length()+1];
    toarrey(arrey,aux);
    int ns = atoi(arrey);

    for(int i = 0;i<ns;i++){
        for(int j=0;j<3;j++){
            string s = "../"+folders[0]+archives[j]+'/'+archives[j]+to_string(i)+".md";
            char array[s.length()+1]; 
            toarrey(array,s);
            remove(array);
        }
        for(int j=3;j<7;j++){
            string s = "../"+folders[1]+archives[j]+'/'+archives[j]+to_string(i)+".md";
            char array[s.length()+1]; 
            toarrey(array,s);
            remove(array);
        }
        for(int j=2;j<5;j+=2){
            string s = "../"+folders[2]+archives[j]+'/'+archives[j]+to_string(i)+".md";
            char array[s.length()+1]; 
            toarrey(array,s);
            remove(array);
        }
        string s = "../Elementares/0 - Graphs/fig"+to_string(i)+".png";
        string s1 = "../O(n)-vs-O(nlog(n))/0 - Graphs/fig"+to_string(i)+".png";
        string s2 = "../Select-Quick/0 - Graphs/fig"+to_string(i)+".png";
        char arrey1[s.length()+1];
        char arrey2[s1.length()+1];
        char arrey3[s2.length()+1];
        toarrey(arrey1,s);toarrey(arrey2,s1);toarrey(arrey3,s2);
        remove(arrey1);remove(arrey2);remove(arrey3);
    }
    remove("data.md");   
}

void plotar(){
    system("cd ../Elementares;python3 a-code.py");
    system("cd '../O(n)-vs-O(nlog(n))';python3 a-code.py");
    system("cd ../Select-Quick;python3 a-code.py");
}
void writedata(string date){
    ofstream outfile;
    outfile.open("data.md");
    outfile << date;
    outfile.close(); 
}

int main(int argc,char* argv[]) {

    if(argc<4){
        cout << "(nmin),(nmax),(s) not provided\n";
        cout << "(nmin): inferior limit iterations algorithm\n";
        cout << "(nmax): inferior limit iterations algorithm\n";
        cout << "(s) Graph numbers to be plotted\n";
        return 0;
    }
    if(atoi(argv[1])>atoi(argv[2])){
        cout << "(lowe limit(nmin) is lower than the upper limit(nmax))";
        return 0;
    }


    clearArchives();
    int maxn = atoi(argv[2]);
    int minn = atoi(argv[1]);
    int maxs = atoi(argv[3]);
    writedata(argv[3]);

    srand((unsigned int)std::clock());
    char a[] = "bismqhr"; 
    string folders[] = {"Elementares/","O(n)-vs-O(nlog(n))/","Select-Quick/"};
    string archives[] = {"bubblesort","insertionsort","selectionsort","mergesort",
    "quicksort","heapsort","radixsort"};
    cout << "#Elementares Iniciado...\n";
    for(int s = 0;s<maxs;s++){
        // ALGORITMOS ELEMENTARES  
        for(int n=minn;n<=maxn;n++){
            vec<int> u(n);
            for(int i = n;i>0;i--)
                u << i;
            u.suffle();
            u.tobuffer(); 
            for(int f=0;f<3;f++){
                u.orderby(a[f]); 
                write("../"+folders[0]+archives[f]+'/'+archives[f]+to_string(s),&u);
                u.torestore();  
            }     
        }
    }
    cout << "#Elementares Finalizado...\n\n";
    cout << "#Quick vs Select Iniciado...\n";
    for(int s = 0;s<maxs;s++){
        //QUICK VS SELCT
        for(int n=minn;n<=maxn;n++){
            vec<int> u(n);
            for(int i = n;i>0;i--)
                u << i;
            u.suffle();
            u.tobuffer();
            for(int f=2;;f+=2){
                u.orderby(a[f]); 
                write("../"+folders[2]+archives[f]+'/'+archives[f]+to_string(s),&u);
                if(f==4)
                    break;
                u.torestore(); 
            }
        }
    }
    cout << "#Quick vs Select Finalizado...\n\n";
    cout << "#O(n) vs O(nlog(n)) Iniciado...\n";
    for(int s = 0; s<maxs;s++){
        // ALGORITMOS O(nlog(n))   
        for(int n=minn;n<=maxn;n++){
            vec<int> u(n);
            for(int i = n;i>0;i--)
                u << i;
            u.suffle();
            u.tobuffer();
            for(int f=0;;f++){
                u.orderby(a[f+3]); 
                write("../"+folders[1]+archives[f+3]+'/'+archives[f+3]+to_string(s),&u);
                if(f==3)
                    break;
                u.torestore();
            }
        }
    }
    cout << "#O(n) vs O(nlog(n)) Finalizado...\n\n";
    cout << "Plotando Graficos...\n\n";
    plotar();
    cout << "Graficos Plotados...\n";
    return 0; 
}