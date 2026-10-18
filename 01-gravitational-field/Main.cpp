#include "Elettrone.h"
#include "PuntoMateriale.h"
#include <iostream>

using namespace std;

int main(){
  
  //Costruzione da particella "nota"
  PuntoMateriale p(Elettrone(),Vettore(1,0,0));
  cout << p.Massa() << " " << p.Carica() << endl;
  cout << p.R() << endl;
  cout << p.V() << endl;
  
  //Costruzione punto materiale generico
  PuntoMateriale pm(1,0,Vettore(1,0,0),Vettore(1,1,1));
  cout << pm.Massa() << " " << pm.Carica() << endl;
  cout << pm.R() << endl;
  cout << pm.V() << endl;


  // Calcolo Campo Gravitazionale
  Vettore v = pm.CampoGravitazionale(Vettore(1.5,0,0));
  if (v.X()!=-4){
    cout << "Errore campo vettoriale:" << endl;
    cout << " valore aspettato -4, ottenuto " << v.X() << endl;
  }
  
  
}
