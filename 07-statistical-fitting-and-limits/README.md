# Fit statistici e limiti di confidenza

Esercitazione universitaria di analisi statistica con **Python e CERN ROOT**. Si studia una distribuzione composta da un segnale gaussiano e da un fondo esponenziale, confrontando fit *binned* e *unbinned*. Si calcolano inoltre un **p-value** per l’ipotesi di solo fondo e un **limite superiore al 95% di confidenza** utilizzando la distribuzione di Poisson.

## File

- `fit.py`: fit della distribuzione di massa (campione ad alta statistica).
- `limit.py`: test d’ipotesi sul campione a bassa statistica.
- `limit2.py`: stima del limite superiore al 95% CL.
- `dati_highstat.dat`, `dati_lowstat.dat`: dati utilizzati negli esercizi.

## Dipendenze ed esecuzione

Richiede **CERN ROOT con PyROOT**; gli import aggiuntivi degli script originali sono elencati in `requirements.txt`. Eseguire dalla cartella del progetto:

```bash
python fit.py
python limit.py
python limit2.py
```
