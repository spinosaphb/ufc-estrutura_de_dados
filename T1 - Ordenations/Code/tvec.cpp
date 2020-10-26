#ifndef TVEC_H
#define TVEC_H
#include "queue.hpp"
template <typename T>
class vec{
private:
    #define MILLISECOND log(std::clock()-start);
    /**
     * lista de elementos
     * */
    T* data;
    T* aux;
    /**
     * tamanho da lista
     * */
    int size;
    /**
     * objeto de clock_t
     * */
    clock_t start;
    /**
     * tempo em segundos
     * */
    double clock;
    /**
     * inverte a lista
     * */
    void _invert_(int i, int j){
        if (i < j) {
            T x = data[i];
            data[i] = data[j];
            data[j] = x;
            _invert_(i+1, j-1);
        }
    }
    /**
     * retorna uma lista com elementos menores que o pivo
     * a esquerda e maiores a direita (quicksort) 
     * */
    int part(int begin, int final){
        T pivo = data[final];
        int j = begin-1;
        for(int i = begin;i < final;i++) {
            if (data[i]<pivo) {
                j++;
                swap(i, j);
            }
            
        }
        swap(j+1, final); 
        return j+1;
    }
    /**
     * retorna dada duas partes, um vetor ordenado
     * (esort)
     * */
    void fundir(int ini, int mid, int fim){
        int i, j, k; 
        int n1 = mid - ini + 1; 
        int n2 = fim - mid;  
        int left[n1], right[n2];                              

        for (i = 0; i < n1; i++) 
            left[i] = data[ini + i]; 
        for (j = 0; j < n2; j++) 
            right[j] = data[mid + 1 + j];
        i=j=0;
        k=ini;
        for (;i < n1 && j < n2;k++) 
            data[k] = (left[i] <= right[j])?left[i++]:right[j++];
        for (;i < n1;k++) 
            data[k] = left[i++];   
        for (;j < n2;k++)
            data[k] = right[j++];  
    }
    /**
     * retorna o maxmimo elemento de modo que todos a esquerda sao menores
     * e os da direita sao maiores
     * */
    void heapmax(int n, int i){
        int max = i;
        int left = 2*i + 1; 
        int right = 2*i + 2;  
        if (left < n && data[left] > data[max]) 
            max = left; 
        if (right < n && data[right] > data[max]) 
            max = right; 
        if (max != i){
            swap(i, max); 
            heapmax(n, max); 
        }
    }
    /**
     * utimo elemento da lista
     * */
    int last;

public:
    /**
     * construtor, recebe o tamanho da lista
     * */
    vec(int size){
        data = new T[size];
        aux = new T[size];
        this->size = size;
        last = 0;
    }
    /**
     * retorna uma String com todos os elementos da lista
     * */
    std::string toStr(){
        string s;
        for(int k = 0; k < size; k++) 
            s += to_string(data[k]) + " ";
        s = "{" + s + "}";
        return s;
    }
    /**
     * sobrecarga do operador []
     * */
    T& operator[] (int k){
        if (k >= 0 && k < size)
            return data[k];
        else
            throw "acesso invalido"; 
    }

    /**
     * sobrecarga do operador <<
     * */ 
    vec<T>& operator<< (const int& x){
        if (last < size) {
            data[last++] = x;
            for (int k = last;k < size;k++)
                data[k] = 0; 
        } 
        return *this; 
    }

    /**
     * interface do metodo _invert_
     * */   
    void invert(){
        _invert_(0, size-1);
    }
    /**
     * preenche a lista com 1
     * */
    static vec<T> ones(int n){
        vec u(n);
        for (int k=0; k<n; k++) 
            u[k] = 1;
        return u;
    }
    /**
     * swap por indice
     * */
    void swap(int a, int b){
        T x = data[a];
        data[a] = data[b];
        data[b] = x;  
    }
    /**
     * embaralha o vetor
     * */
    void suffle(){
        for(int i=size-1;i>0;i--){  
            int j = rand()%i;
            swap(i,j);
        }
    }
    /**
     * copia o vetor data para o vetor aux
     * */
    void tobuffer(){
        for(int i=0;i<size;i++)
            aux[i] = data[i];
    }
    /**
     * restaura para data o conteudo de aux
     * */
    void torestore(){
        for(int i=0;i<size;i++)
            data[i] = aux[i];
    }    
    /**
     * retorna o tamanho da lista
     * */
    int length(){
        return size;
    }
    /**
     * deleta o vetor data
     * */
    ~vec(){
         delete [] data;
    }
private:
    /**
     * quicksort recursivo
     * */
    void _quicksort_(int begin, int final){
        if (begin<final){
            int pivo = part(begin, final);
            _quicksort_(begin, pivo-1);
            _quicksort_(pivo+1, final);
        }
    }
    /**
     * mergesort recursivo
     * */
    void _mergesort_(int left, int right){
        if (left < right){ 
            int mid = left + (right-left)/2; 
            _mergesort_(left, mid); 
            _mergesort_(mid+1, right);
            fundir(left,mid,right); 
        }
    }
    /**
     * heapsort
     * */
    void _heapsort_(int n){
        for (int i = n/2 - 1; i >= 0; i--) 
            heapmax(n, i);  
        for (int i=n-1; i>=0; i--){ 
            swap(0, i);  
            heapmax(i, 0); 
        } 
    }
    /**
     * radixsort
     * */
    void _radixsort_(T *data, int n, int ndig) {
        typedef queue<int> fila;
        fila* b[10];
        for (int k=0; k<10; k++)       
            b[k] = new fila(n);

        int d = 1;
        for (int i = 0; i < ndig; i++) {
             for (int j=0; j < n; j++) {
                 int dig = ( data[j]/d ) % 10;
                 b[dig]->enqueue(data[j]);
             }  
    
             int ivec = 0;    
             for(int j=0; j<10; j++) {
                 while ( !(b[j]->isEmpty()) ) {
                     int x = b[j]->get(outlet);
                     data[ivec] = x;
                     b[j]->dequeue(); 
                     ivec++;
                 }
             }
             d *= 10;
        }
        for (int k=0; k<10; k++)       
            delete b[k];
    }
    /**
     * conta o numero de digitos do vetor
     * */
    int contdig(){
        T aux = size;
        int i = 0;
        for(;aux>0;aux/=10,i++);
        return i;
    }
public:
    /**
     * selection
     * */
    void selectsort(){ 
        start = std::clock();
        for(int i = 0;i<size-1;i++){
            int menor = i;
            for(int j= i+1;j<size;j++){
                if(data[j] < data[menor])
                    menor = j;
            }
            swap(menor,i);
        }
        this->clock = MILLISECOND;
    }
    /**
     * insertion
     * */
    void insertsort(){
        start = std::clock();
        int j;  
        for (int i = 1; i < size; i++){  
            int key = data[i];
            for(j = i-1;j>=0 && data[j]>key;j--){
                data[j+1] = data[j];
            }  
            data[j+1] = key;  
        }
        this->clock = MILLISECOND;
    }
    /**
     * bubblesort
     * */
    void bubblesort(){
        start = std::clock();
        for(int i=1;i<size;i++)
            for(int j=0;j<i;j++){
                if(data[j] > data[i])
                    swap(j,i);
            }
        this->clock = MILLISECOND;
    }
    /**
     * interface do quicksort recursivo
     * */
    void quicksort(){
        start = std::clock();
        _quicksort_(0, size-1);
        this->clock = MILLISECOND;
    }
    /**
     * intereface do mergesort recursivo
     * */
    void mergesort(){
        start = std::clock();
        _mergesort_(0, size-1);
        this->clock = MILLISECOND; 
    }
    /**
     * interface do heapsort
     * */
    void heapsort(){
        start = std::clock();
        _heapsort_(size);
        this->clock = MILLISECOND;
    }
    /**
     * interface do radixsort
     * */
    void radixsort(){
        int nrsize = contdig();
        start = std::clock();
        _radixsort_(data,size,nrsize);
        this->clock = MILLISECOND;
    }
    void orderby(char c){
        switch(c){
            case 'b':
                this->bubblesort();
            break;
            case 'i':
                this->insertsort();
            break;
            case 's':
                this->selectsort();
            break;
            case 'm':
                this->mergesort();
            break;
            case 'q':
                this->quicksort();
            break;
            case 'h':
                this->heapsort();
            break;
            case 'r':
                this->radixsort();
            break;
            default:
                printf("INVALIDO");
            return;
        } 
    }
    /**
     * retorna o valor de clock
     * */
    double getclock(){
        return clock;
    }
    /**
     * insere em clock o valor
     * */
    void setclock(double clock){
        this->clock = clock;
    }
    /**
     * retorna o tamanho da lista
     * */
    int getsize(){
        return size;
    }
    
    
};
#endif