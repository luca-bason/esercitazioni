#ifndef _ELETTRONE
#define _ELETTRONE
#include "Particella.h"

class Elettrone: public Particella{
 public:
  using Particella::Particella;
  Elettrone():Particella(9.1093826e-31,-1.60217653e-19){}

};
#endif
