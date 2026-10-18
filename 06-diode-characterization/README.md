# Acquisizione e caratteristica I–V di un diodo

Esercizio in **Python** per acquisire automaticamente misure di corrente e tensione tramite alimentatore e multimetro, stimare le incertezze strumentali e adattare la caratteristica I–V con un modello esponenziale usando ROOT/Minuit.

**File principali:** `test.py` (acquisizione), `ps.py` e `dmm.py` (strumenti), `fitlin.py` (fit), `out2.dat` (dati d'esempio).

**Dipendenze:** `numpy`, `pyserial`, `pyvisa` (`pip install -r requirements.txt`) e CERN ROOT con PyROOT per il fit.

**Esecuzione:** `python fitlin.py` sui dati inclusi; `python test.py` **solo con strumenti compatibili collegati e configurati**.

**Nota:** porta seriale, identificativo dell'alimentatore e parametri iniziali del fit sono specifici dell'esperimento e vanno adattati.
