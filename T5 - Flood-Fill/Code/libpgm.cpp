#include "libpgm.h"

point::point(int x, int y) {
  _x = x;
  _y = y;
}

int& point::x(){
   return _x;
}

int& point::y(){
   return _y;
}
 
/*point::point(const point& p) {
   this->_x = p.x();
   this->_y = p.y();
}

point& point::operator=(const point& p) {
    this->_x = p.x();
    this->_y = p.y();
    return *this;
}
*/
string pgm::info() {
   string msg;
   stringstream s(msg);
   s << ncols << "x"
     << nrows << ": 0.."
     << maxval << endl;
   return msg;
}

pgm::pgm(char color, 
         int nc, int nr, 
         int maxval) 
{
   ncols = nc;
   nrows = nr;
   this->maxval = maxval;
   int len = nc*nr;   
   data = new char[len];
   for (int k=0; k<len; k++)
      data[k] = color;
}

pgm::pgm(string filename) 
{
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
    data = new char[len];
    for (int k = 0; k < len; k++)
        if (maxval==one) {
           data[k] = file.get(); ;
        } else 
           throw string("wecala cinza invalida");
    file.close();
}

void pgm::copyFrom(pgm& p) {
   ncols = p.ncols;
   nrows = p.nrows;
   maxval = p.maxval;

   int len = ncols * nrows;
   if (data!=0)  {
       delete [] data;
       data = 0;  
   } 
   data = new char[len];
   //for (int col=0; col<ncols; col++)
   //   for(int row=0; row < nrows;  row++) 
   //   {
   //      pixel(col, row) = p.pixel(col, row);
   //   }

   for (int k=0; k<len; k++)
      data[k] = p.data[k];
}

pgm::pgm( pgm& p) {
   copyFrom(p);
}

void pgm::operator= (pgm& p) {
   if (data != 0)
     delete [] data;
   copyFrom(p);   
}

char& pgm::pixel(int col, int row) {
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

void pgm::saveAs(string filename) {
   ofstream file(filename, ofstream::out);
   file << "P5\n" 
        << ncols << " "
        << nrows << "\n"
        << maxval << "\n";
   int len = ncols * nrows;
   for (int k = 0; k<len; k++)
      if (maxval==one) {
         file.put( data[k] );
      } else if (maxval==two) {
         file.put(data[k]);
         file.put(data[k]);
      } else
         throw string("erro ao salvar");
   file.close();     
}

int pgm::nCols()const {
   return ncols;
}

int pgm::nRows()const {
   return nrows;
}

pgm pgm::trans() {
   char color = 0;
   pgm out(color, nrows, ncols, maxval);   
   for (int col=0; col<ncols; col++)
      for (int row=0; row<nrows; row++)
         out.pixel(row, col)=pixel(col,row);
   return out;
}

pgm::~pgm() {
   if (data != 0)
       delete [] data;
}



