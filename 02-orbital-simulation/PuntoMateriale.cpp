#include "PuntoMateriale.h"
#include "Particella.h"
#include "Vettore.h"
#include <cmath>

Vettore PuntoMateriale::R(){
  return m_r;
}

Vettore PuntoMateriale::V(){
  return m_v;
}

void PuntoMateriale::R(Vettore r){
  m_r = r;
}

void PuntoMateriale::V(Vettore v){
  m_v = v;
}

Vettore PuntoMateriale::CampoGravitazionale(Vettore r){
  double M=this->Massa();
  Vettore v_dist=(this->R())-r;
  double dist=pow(v_dist.Mod(),2);
  double K=M/dist;
  return (v_dist.Vers())*K;
}
