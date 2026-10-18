#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE

#include "Particella.h"
#include "Vettore.h"

namespace consts{
  const double c = 299792458;
  const double G = 1;
};

class PuntoMateriale: public Particella{
 public:
  PuntoMateriale(Particella p=Particella(), Vettore r=Vettore(), Vettore v=Vettore()):Particella(p),m_r(r),m_v(v){}
  PuntoMateriale(double massa, double carica, Vettore r, Vettore v):PuntoMateriale(Particella(massa,carica),r,v){}

  Vettore R();    
  Vettore V();
  void    R(Vettore);
  void    V(Vettore);

  Vettore CampoGravitazionale(Vettore);
  
 private:
  Vettore m_r;
  Vettore m_v;
};

#endif
