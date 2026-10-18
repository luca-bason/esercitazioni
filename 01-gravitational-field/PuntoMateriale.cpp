#include "Vettore.h"
#include "Particella.h"
#include "PuntoMateriale.h"
#include <cmath>

Vettore PuntoMateriale::R() const{
return m_r;
}

Vettore PuntoMateriale::V() const{
return m_v;
}

void PuntoMateriale::R(Vettore r){
m_r=r;
}

void PuntoMateriale::V(Vettore v){
m_v=v;
}

Vettore PuntoMateriale::CampoGravitazionale(Vettore r){
double M=this->Massa();
Vettore v_dist=(this->R())-r;
double dist=pow(v_dist.Mod(),2);
double K=M/dist;
return (v_dist.Vers())*K;
}
