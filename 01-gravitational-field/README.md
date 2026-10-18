# Campo gravitazionale di un punto materiale

Esercizio universitario in **C++11** sulla programmazione a oggetti: classi per vettori tridimensionali, particelle e punti materiali, con calcolo del campo gravitazionale generato da una massa puntiforme.

**File principali:** `Main.cpp`, `PuntoMateriale.*`, `Particella.h`, `Vettore.*`, `Elettrone.h`.

**Compilazione (dopo la correzione indicata sotto):** `g++ -std=c++11 Main.cpp PuntoMateriale.cpp Vettore.cpp -o Main && ./Main`

**Nota:** nella versione originale manca un costruttore usato da `Main.cpp`; va aggiunto o va passato esplicitamente il vettore velocità. Il `Makefile` richiede ROOT anche se questo esercizio non lo utilizza.
