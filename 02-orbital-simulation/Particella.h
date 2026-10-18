#ifndef _PARTICELLA
#define _PARTICELLA
class Particella{
 public:
  Particella(double massa=0, double carica=0):m_massa(massa),m_carica(carica){}
  double Massa() {return m_massa;}
  double Carica(){return m_carica;}
 private:
  double m_massa;
  double m_carica;
};
#endif
