#ifndef _ODESOLVER
#define _ODESOLVER

#include <vector>
#include "Vettore.h"
#include "PuntoMateriale.h"
#include <functional>

using namespace std;

class OdeSolver{
 public:
  OdeSolver(string method="Eulero", vector<PuntoMateriale> p=vector<PuntoMateriale>(0)):m_method(method),m_p(p),m_t(0),m_h(0.1){}
  void                   Punto(PuntoMateriale tmp);
  PuntoMateriale         Punto(unsigned int i);
  vector<PuntoMateriale> Punti();
  unsigned int   N();
  void           T(double t0);
  double         T();
  void           Passo(double h);
  double         Passo();
  void           Cinematica();
  std::function <Vettore(unsigned int i, unsigned int j, double t, vector<PuntoMateriale> p)> fInterna;
  std::function <Vettore(unsigned int i, double t, vector<PuntoMateriale> p)> fEsterna;
 private:
  string   m_method;
  vector<PuntoMateriale> m_p;
  double   m_t,m_h; 
  Vettore  m_eqDiff(unsigned int i, double t, vector<PuntoMateriale>);
};


#endif
