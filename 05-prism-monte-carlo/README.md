# Dispersione ottica e simulazione Monte Carlo

Esercizio in **Python con CERN ROOT (PyROOT)** per stimare i coefficienti della legge di Cauchy di un prisma a partire da misure angolari e studiarne le incertezze tramite simulazioni gaussiane e uniformi.

**Dipendenza:** CERN ROOT con PyROOT disponibile nell'ambiente Python.

**Esecuzione:** `python PrismScheme.py`

**Nota:** correggere la formula di `B` in `GetAB()` (differenza, non somma, al denominatore) e azzerare gli istogrammi tra le due simulazioni prima di interpretare i risultati.
