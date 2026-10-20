# Simulazione gravitazionale e metodi numerici

Esercizio in **C++11 e CERN ROOT** per simulare il moto di più corpi soggetti a gravità, confrontando metodi di integrazione (Eulero, RK2, RK4 e Verlet) e l'evoluzione del momento angolare.

**File principali:** `Main.cpp`, `OdeSolver.*`, `PuntoMateriale.*`, `Particella.h`, `Vettore.*` e `fileInput` (condizioni iniziali).

**Esecuzione:** installare CERN ROOT con `root-config` disponibile, quindi eseguire `make && ./Main` dalla cartella del progetto.
