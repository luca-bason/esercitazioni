#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE
#include "Vettore.h"
#include "Particella.h"

class PuntoMateriale: public Particella{
 public:
  using Particella::Particella;
  PuntoMateriale(double m, double c, const Vettore& p, const Vettore& v):Particella(m,c), m_r(p), m_v(v){};
  PuntoMateriale(Particella P,  const Vettore& p, const Vettore& v):Particella(P.Massa(), P.Carica()), m_r(p), m_v(v){};
  Vettore R() const;
  Vettore V() const;
  void R(Vettore);
  void V(Vettore);
  Vettore CampoGravitazionale(Vettore);
 private:
  Vettore m_r, m_v;
};
#endif
