from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *
import sys


gStyle.SetOptStat(0)
h      = TH1D("h","",40,0,40)

nbkg  = 22.35

nobs  = 0.0
for line in open("dati_lowstat.dat"):
    mass = float(line)
    
    h.Fill(mass)

h.Draw()
gApplication.Run(True)

nobs = h.GetBinContent(15)+h.GetBinContent(16)

#calcolare p-value Ns=0
pval = 0.0
for x in range (0,int(nobs)):
    pval = pval+TMath.PoissonI(x,nbkg)

prob = 1-pval
print (prob)

alpha = 0.01
if prob>=alpha:
    print("ipotesi non rigettabile")
else:
    print("ipotesi rigettabile")
