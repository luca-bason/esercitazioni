#include "Vettore.h"
#include <cmath>
#include <iostream>


double Vettore::X() const{
  return m_v[0];
}

double Vettore::Y() const{
  return m_v[1];
}

double Vettore::Z() const{
  return m_v[2];
}

void Vettore::X(double x){
  m_v[0] = x;
}

void Vettore::Y(double y){
  m_v[1] = y;
}

void Vettore::Z(double z){
  m_v[2] = z;
}

Vettore Vettore::operator-(){
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = -m_v[i];
  }
  return res;
}


Vettore Vettore::operator-(const Vettore& b) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] - b.m_v[i];
  }
  return res;
}

Vettore Vettore::operator+(const Vettore& b) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] + b.m_v[i];
  }
  return res;
}

double Vettore::operator*(const Vettore& b) const{
  double prod=0;
  for (int i=0;i<3;i++){
    prod += m_v[i]*b.m_v[i];
  }
  return prod;
}

Vettore Vettore::Cross(const Vettore& b) const{
  Vettore res;
  res.X(m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1]);
  res.Y(m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2]);
  res.Z(m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0]);
  return res;
}

Vettore Vettore::operator*(double f) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i]*f;
  }
  return res;
}

Vettore Vettore::operator/(double f) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i]/f;
  }
  return res;
}

double Vettore::Mod() const {
  return sqrt((*this)*(*this));
}

Vettore Vettore::Vers() const {
  return (*this)*(1/Mod());
}

Vettore operator*(double f,  const Vettore& b){
  return b*f;
}

std::ostream& operator<<(std::ostream& os,  const Vettore& b){
  os << "(";
  os << b.X() << ",";
  os << b.Y() << ",";
  os << b.Z() << ")";
  return os;
}

std::istream& operator>>(std:: istream& is, Vettore& b){
  double x,y,z;
  is >> x >> y >> z;
  b  = Vettore(x,y,z);
  return is;
}
