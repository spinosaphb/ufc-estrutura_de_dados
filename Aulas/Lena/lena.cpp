#include "libpgm.h"

int main() {
   try {
      pgm lena("lena.pgm");

      pgm lena_cp(lena);
      lena_cp.saveAs("lena_copia.pgm");

      pgm lenat = lena.trans();
      lenat.saveAs("lena_t.pgm");

      pgm lenah = lena.hflip();
      lenah.saveAs("lena_h.pgm");

      pgm lenav = lena.vflip();
      lenav.saveAs("lena_v.pgm");
       
   } catch(string s) {
      cout << s << endl;
   }
   return 0;
}
