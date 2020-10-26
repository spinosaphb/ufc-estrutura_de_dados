#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define one 255
#define two 65535

class point {
   int _x, _y;
public:
   point(int x, int y);
   int x();
   int y();
   void operator=(const point& p);
   bool operator==(const point& p);
};

union atom {
   char    bytes[2];
   short   value;
};

typedef short grayScale; // 2 bytes

class pgm {
   grayScale *data;
   int ncols, nrows, maxval;
   int bytesPerPixel();
   void copyFrom(const pgm& p);
public:
   pgm(const char* filename);
   pgm(grayScale color, 
       int nc, int nr,  
       int maxval);
   // pgm(pgm& p);   
   pgm(const pgm& p);
   void operator= (pgm& p);

   grayScale& pixel (int col, int row);
   void saveAs(const char* filename); 
   int nCols();
   int nRows();
 
   // geometria
   void line(point &p, point &q);
   void rect(point& p, point& q);
   void circle(point &p, int radius);     
   // ***

   // operacoes algebricas
   pgm trans();
   pgm hflip();
   pgm vflip();
   // ***

   void info();
   ~pgm();
};


