#include "libpgm.h"

point::point(int x, int y) {
  _x = x;
  _y = y;
}

void point::operator=(const point& p) {
   _x = p._x;
   _y = p._y; 
}

bool point::operator==(const point& p) {
   return _x==p._x &&
          _y==p._y;
}

int point::x() {
   return _x;
}

int point::y() {
   return _y;
}

int pgm::bytesPerPixel() {
    if (maxval < 256)
       return 1;
    else if (maxval < 65536)
       return 2;
    else
       throw string("quantidade de bytes invalida!"); 
}

void pgm::info() {
   //cout << "\nimagem pgm:\n"
   //     << ncols << "x"
   //     << nrows << "\n 0.." 
   //     << maxval << " tons \n"
   //     << bytesPerPixel() << " bytes p/ pixel\n";
}

pgm::pgm(const char* filename) {
    ifstream file;
    file.open(filename, 
              ifstream::in |
              ifstream::binary);
    if ( file.fail() )   
        throw string("arquivo invalido!");
    string m;
    getline(file, m);
    if (m != "P5") {
        throw string("imagem invalida");
    }
    file >> ncols >> nrows >> maxval;
    int len = ncols * nrows;
    data = new grayScale[len];
    atom a;
    for (int k = 0; k < len; k++) {
        
        if (bytesPerPixel()==1) {
           a.bytes[0] = file.get();
        } else 
          if (bytesPerPixel()==2) {
           a.bytes[0] = file.get();
           a.bytes[1] = file.get();
        } else 
           throw string("wecala cinza invalida");
        data[k] = a.value;
    }
    file.close();

    info();
}

pgm::pgm(grayScale color, 
         int nc, int nr, 
         int maxval) {
   ncols = nc;
   nrows = nr;
   this->maxval = maxval;
   int len = nc*nr;   
   data = new grayScale[len];
   for (int k=0; k<len; k++)
      data[k] = color;
   info();
}

void pgm::copyFrom(const pgm& p) {
   ncols = p.ncols;
   nrows = p.nrows;
   maxval = p.maxval;
   int len = ncols * nrows;
   data = new grayScale[len];
   //for (int col=0; col<ncols; col++)
   //   for(int row=0; row<nrows; row++) {
   //      pixel(col, row) = p.pixel(col, row);
   //   }

   for (int k=0; k<len; k++) {
      data[k] = p.data[k];
   }
}

pgm::pgm(const pgm& p) {
   copyFrom(p);
   info();
}

void pgm::operator= (pgm& p) {
   if (data != 0)
     delete [] data;
   copyFrom(p);   
}

grayScale& pgm::pixel(int col, int row) {
   if (data==0)
       throw string("imagem vazia!");
   if (col<0 || col>=ncols ||
       row<0 || row>=nrows)
       throw string("pixel invalido!");
   int p = row * ncols + col;
   if (p >= ncols*nrows)
      throw string("inconsistemcis");
   return data[p]; 
}

void pgm::saveAs(const char* filename) {
   ofstream file(filename, ofstream::out);
   file << "P5\n" 
        << ncols << " "
        << nrows << " "
        << maxval << "\n";
   int len = ncols * nrows;
   atom a;
   for (int k = 0; k<len; k++) {
      a.value = data[k];
      if (bytesPerPixel() ==1) {
         file.put( a.bytes[0] );
      } else if (bytesPerPixel()==2) {
         file.put( a.bytes[0] );
         file.put( a.bytes[1] );
      } else {
         throw string("erro ao salvar");}
      }
   file.close();  
   info();  
}

int pgm::nCols() {
   return ncols;
}

int pgm::nRows() {
   return nrows;
}

/*void pgm::line(point &p, point &q) {
   float w = p._x>=q.x ? p._x-q._x : 
                         q._x-p._x;
   float h = p._y>=q.y ? p._y-q._y : 
                         q._y-p._y;
   if (w==h && w==0) {

   } else if () 
}*/

void pgm::rect(point& p, point& q) {

}

void pgm::circle(point &p, int radius) {

}     


pgm pgm::trans() {
   grayScale color;
   pgm out(color, nrows, ncols, maxval);   
   for (int col=0; col<ncols; col++)
      for (int row=0; row<nrows; row++)
         out.pixel(row, col)=pixel(col,row);
   return out;
}

pgm pgm::hflip() {
   pgm p(0, ncols, nrows, maxval);
   for (int col=0; col < ncols; col++) 
      for(int row=0; row<nrows; row++) {
         p.pixel(col, row)=pixel(ncols-col-1, row);
      }
   return p;
}

pgm pgm::vflip(){
   pgm p(0, ncols, nrows, maxval);
   for (int col=0; col < ncols; col++) 
      for(int row=0; row<nrows; row++) {
         p.pixel(col, row)=pixel(col, nrows-row-1);
      }
   return p;
}

pgm::~pgm() {
   if (data != 0)
       delete [] data;
}



