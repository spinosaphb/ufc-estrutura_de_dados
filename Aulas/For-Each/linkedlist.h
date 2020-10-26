#define forList(T,a,L) T varlist; for(list<T>::iter j=L.begin(); !j.end(); varlist=j.key(),j++)

template <typename T>
class list {
   struct node{
      T key;
      node* next;   
      node(T k) {
          key = k;
          next = 0;
      }
   } *ptraiz;

public:

    class iter {
       typedef void func(T);
       node* p;
    public:
       iter(node* q) {
           p = q;
       }
       iter operator=(const iter& j) {
           p = j;
       }
       void operator++(int){
           if (p!=0)
               p = p->next; 
           else
               throw "erro!";
       }
       T key() {
           return p->key;
       }
       bool end() {
           return p==0;
       }
    };

   int count;
public:
   list() {
      ptraiz = 0;
      count = 0;
   }
   // sem repeticao
   // ordenada
   list& operator<<(T x) {
      if (count==0) {
           ptraiz = new node(x);
           count++;
           // return true;
      } else

      if (x < ptraiz->key) {
          node* p = new node(x);
          p->next = ptraiz;
          ptraiz = p;
          count++;
          // return true;
      } else

      if (x!=ptraiz->key) {         
         node* p = ptraiz;
         while (p->next != 0 &&
             p->next->key < x)
             p = p->next;

             if (p->next == 0 || p->next->key != x) {
                node* q = new node(x);
                q->next = p->next;
                p->next = q;
         } 
      }

      // return false;
      return *this;  
   }

bool del(T x) {
    if (ptraiz==0)
        return false;
    if (ptraiz->key == x) {
        node* p = ptraiz;
        ptraiz = ptraiz->next;
        delete p;
        count--;
        return true;  
    }

    node* p = ptraiz; 
    while (p->next->key < x)         
        p = p->next;
    if (p->next = 0)
        return false; 
    if (p->next->key==x) {
        node* q = p->next;
        p = q->next;
        delete q;
        count--;
        return true;    
    }
    return false;

}
   
   iter begin() {
       return iter(ptraiz);
   }

   ~list() {
      while (ptraiz!=0) {
          node* p = ptraiz;
          ptraiz = ptraiz->next;
          delete p;
      }                
   }
};