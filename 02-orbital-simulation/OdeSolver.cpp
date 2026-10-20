#include "Vettore.h"
#include "OdeSolver.h"

void OdeSolver::Punto(PuntoMateriale tmp){
  m_p.push_back(tmp);
}

vector<PuntoMateriale> OdeSolver::Punti(){
  return m_p;
}

PuntoMateriale OdeSolver::Punto(unsigned int i){
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t = t0;
}

double OdeSolver::T(){
  return m_t;
}

void OdeSolver::Passo(double h){
  m_h = h;
}

double OdeSolver::Passo(){
  return m_h;
}


Vettore OdeSolver::m_eqDiff(unsigned int i, double t, vector<PuntoMateriale> p){
  Vettore F_int;
  for(unsigned j=0; j<p.size(); j++){
    if (j!=i){
      F_int = F_int+fInterna(i, j, t, p);
    }
  }
  Vettore Risultante = F_int+fEsterna(i, t, p);
  Vettore Accelerazione = Risultante*(1/(p[i].Massa())); 
  return Accelerazione;
}

//Da implementare a cura dello studente
void OdeSolver::Cinematica(){

  if (m_method=="Eulero"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());

    for (unsigned int i=0; i<m_p.size(); i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i, m_t, m_p);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }
  }

  else if (m_method=="Rk2"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
    vector<Vettore>  k2(m_p.size());
    vector<Vettore>  w2(m_p.size());

    for (unsigned int i=0; i<m_p.size(); i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i, m_t, m_p);
    }

    auto p_mid(m_p);
    for(unsigned int i=0; i<m_p.size(); i++){
      p_mid[i].R(m_p[i].R() + (0.5*k1[i]));
      p_mid[i].V(m_p[i].V() + (0.5*w1[i]));
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      k2[i] = m_h*p_mid[i].V();
      w2[i] = m_h*m_eqDiff(i, m_t, p_mid);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }
  }

  else if (m_method=="Rk4"){
    vector<Vettore> k1(m_p.size()), k2(m_p.size()), k3(m_p.size()), k4(m_p.size());
    vector<Vettore> w1(m_p.size()), w2(m_p.size()), w3(m_p.size()), w4(m_p.size());

    for (unsigned int i=0; i<m_p.size(); i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i, m_t, m_p);
    }

    auto mid1(m_p);
    for (unsigned int i=0; i<m_p.size(); i++){
      mid1[i].R(m_p[i].R()+0.5*k1[i]);
      mid1[i].V(m_p[i].V()+0.5*w1[i]);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      k2[i] = m_h*mid1[i].V();
      w2[i] = m_h*m_eqDiff(i, m_t+m_h/2, mid1);
    }

    auto mid2(m_p);
    for (unsigned int i=0; i<m_p.size(); i++){
      mid2[i].R(m_p[i].R()+0.5*k2[i]);
      mid2[i].V(m_p[i].V()+0.5*w2[i]);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      k3[i] = m_h*mid2[i].V();
      w3[i] = m_h*m_eqDiff(i, m_t+m_h/2, mid2);
    }

    auto mid3(m_p);
    for (unsigned int i=0; i<m_p.size(); i++){
      mid3[i].R(m_p[i].R()+k3[i]);
      mid3[i].V(m_p[i].V()+w3[i]);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      k4[i] = m_h*mid3[i].V();
      w4[i] = m_h*m_eqDiff(i, m_t+m_h, mid3);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(m_p[i].R()+k1[i]/6+k2[i]/3+k3[i]/3+k4[i]/6);
      m_p[i].V(m_p[i].V()+w1[i]/6+w2[i]/3+w3[i]/3+w4[i]/6);
    }
    
  }

  else if (m_method=="Verlet"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());

    auto p_successivo(m_p);

    for (unsigned int i=0; i<m_p.size(); i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i, m_t, m_p);
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      p_successivo[i].R(m_p[i].R() + k1[i] + (0.5*m_h*w1[i]));
    }

    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(p_successivo[i].R());
      m_p[i].V(m_p[i].V() + (0.5*w1[i]) + (0.5*m_h*m_eqDiff(i, m_t+m_h, p_successivo)));
    }
  }

  m_t += m_h;

}

