#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLine.h>

#include "OdeSolver.h"
#include "Vettore.h"
#include "PuntoMateriale.h"
#include "Elettrone.h"

using namespace std;

//Definizione della forza interna
Vettore fInterna(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p){
  Vettore Forza_i=(p[i].Massa()) * (p[j].CampoGravitazionale(p[i].R()));
  return Forza_i;
}

//Definizione della forza esterna
Vettore fEsterna(unsigned int i, double t, vector<PuntoMateriale> p){
  Vettore Forza_e;
  return Forza_e;
}

//Definizione del momento angolare totale
double L(OdeSolver ode){
  Vettore L_totale;
  for(unsigned int i=0; i<ode.N(); i++){
    Vettore L = ode.Punto(i).Massa()*((ode.Punto(i).R() - ode.Punto(0).R()).Cross(ode.Punto(i).V() - ode.Punto(0).V()));
    L_totale = L_totale + L;
  }
  return L_totale.Mod();
}

int main(){ 
  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  //Lettura dei dati dal file
  ifstream f("fileInput");
  double mass;
  double x,y,z,vx,vy,vz;
  vector<PuntoMateriale> v_pm;
  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){
    Vettore pos(x, y, z);
    Vettore vel(vx, vy, vz);
    PuntoMateriale pm(mass, 0, pos, vel);
    v_pm.push_back(pm);
  }

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  OdeSolver Verlet("Verlet", v_pm);
  OdeSolver Rk2("Rk2", v_pm);
  
  Verlet.fInterna = fInterna;
  Verlet.fEsterna = fEsterna;
  Verlet.Passo(0.5);

  Rk2.fInterna = fInterna;
  Rk2.fEsterna = fEsterna;
  Rk2.Passo(0.5);
  
  //Creazione dei grafici dei pianeti (uno per pianeta)
  vector<TGraph> gr(Verlet.N());
  TCanvas c1("c1","pianeti",10,10,500,500);

  //Preparazione del grafico delle coordinate dei pianeti
  double size=5; // 5 unita' astronimiche
  c1.DrawFrame(-size,-size,size,size);
  
  //Creazione e preparazione del grafico dei momenti angolari
  TGraph l1;
  TGraph l2;
  TCanvas c2("c2","momenti angolari",10,10,500,500);
  c2.DrawFrame(0, 0.99999, 400, 1.00001);


  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};

  //Inizializzazione del grafico dei pianeti
  for (unsigned int i=0; i<Verlet.N(); i++){
    gr[i].SetPoint(0, Verlet.Punto(i).R().X(), Verlet.Punto(i).R().Y());
    gr[i].SetMarkerColor(color[i]);
    gr[i].SetMarkerStyle(20);
    gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    c1.cd();
    gr[i].Draw("P");
  }

  //Aggiornamento del grafico
  c1.Modified(); c1.Update();
  app.Run(true);


  //Momenti angolari iniziali
  double lVerlet_iniziale=L(Verlet);
  double lRk2_iniziale=L(Rk2);
  int j=0;

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  while (Verlet.T()<365){
    Verlet.Cinematica();
    Rk2.Cinematica();

    //Rapporto dei momenti angolari al tempo considetato su i momenti angolari iniziali
    double rapporto_lVerlet=L(Verlet)/lVerlet_iniziale;
    double rapporto_lRk2=L(Rk2)/lRk2_iniziale;

    //Creazione di punti su grafico dei pianeti
    for (unsigned int i=0; i<Verlet.N(); i++){
      gr[i].SetPoint(gr[i].GetN(), Verlet.Punto(i).R().X(), Verlet.Punto(i).R().Y());
      gr[i].SetMarkerColor(color[i]);
      gr[i].SetMarkerStyle(20);
      gr[i].SetMarkerSize(0.1);
      if (i==0) gr[i].SetMarkerSize(1);
      c1.cd();
      gr[i].Draw("P");
    }
    
    //Creazione di punti sul grafico dei momenti angolari
    l1.SetPoint(j, Verlet.T(), rapporto_lVerlet);
    l1.SetMarkerColor(color[5]);
    l1.SetMarkerStyle(20);
    l1.SetMarkerSize(0.1);

    l2.SetPoint(j, Verlet.T(), rapporto_lRk2);
    l2.SetMarkerColor(color[7]);
    l2.SetMarkerStyle(20);
    l2.SetMarkerSize(0.1);

    c2.cd();
    l1.Draw("P"); l2.Draw("P");

    //Aggiornamento dei grafici
    c1.Modified(); c1.Update();
    c2.Modified(); c2.Update();

    j++;
  }
  
  app.Run(true);
  
  return 0;
  
}
