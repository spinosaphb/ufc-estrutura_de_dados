#IFNDEF __STACK__
#DEFINE __STACK__

using namespace std;

template <typename T>
class stack {
   T *data;
   int size, len;
public:
   stack(int n);
   void push(T& x);
   void pop();
   T top();
   bool isEmpty();
   bool isFull(); 
   int height();
   ~stack();
};

#ENDIF

