import matplotlib.pyplot as plt
import numpy as np
import math

'''
Definizione del potenziale V(xi), della funzione d'onda con il metodo di Numerov, del metodo per il calcolo della differenza delle derivate nel punto di matching e del metodo di bisezione per trovare l'energia per cui la derivata destra e sinistra coincidono
'''

def V(xi):
    return xi**2

def b(eps,xi):
    return (h**2*(2*eps-V(xi)))/12

def numerov(n1,n2,eps):
    psi = np.array(xi)*0
    j = np.sign(n2-n1)
    psi[n1] = 0
    psi[n1+j] = 0.01
    for i in range(n1+2*j,n2+j,j):
      psi[i] = (2*psi[i-j]*(1-5*b(eps,xi[i-j]))-psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i]))
    return psi

def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    a = psil[nmatch]/psir[nmatch]
    psir = a*psir
    dpsil = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
    dpsir = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    diff = dpsil-dpsir
    return diff

def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;

#Main code

n       = 14000
nmatch  = 8000
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]


#Trovo gli intervalli di cambio di segno della differenza di derivate nel punto di matching per E tra 0 e en_max e stampo le energie corrispondenti agli zeri

en_max=5
ntot = 101
ei=np.linspace(0,en_max,ntot)
der_diff=np.array(ei)
for i in range(0,ntot):
    der_diff[i]=evalDerivative(ei[i])

for i in range(0,ntot-1):
    if(der_diff[i]*der_diff[i+1]<0):
        print ("Energy is: ", findE(ei[i],ei[i+1],0.0001))

#Trovo il numero di zeri di psi a energia fissata eps

eps=5
e=findE(eps-0.0001,eps+0.0001,0.00005)

for i in range(nmatch+1,n,1):
  psil[i]=psir[i]

plt.plot(xi,psil)
plt.show()

n_zeri=0
for i in range(0,n-1,1):
    if(psil[i]*psil[i+1]<0):
        n_zeri+=1

print("Il numero di zeri di psi è :", n_zeri)
