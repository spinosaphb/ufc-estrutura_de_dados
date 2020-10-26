#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

#define one 255
#define two 65535



class point {
   int _x, _y;
public:
   point(int x, int y);
   point(const point& p);
   point& operator=(const point& p);
   bool isNull();
   int& x();
   int& y();
};
	
class pgm {
   char *data;
   int ncols, nrows, maxval;
   void copyFrom(pgm& p);
public:
   pgm(string filename);
   pgm(char, int, int, int);
   pgm(pgm& p);   
   void operator= (pgm& p);

   char& pixel (int col, int row);
   void saveAs(string filename); 
   int nCols()const;
   int nRows()const;
  
   // TRANPOSIÇAO 
   pgm trans();
   // ***

   string info();
   ~pgm();
};


