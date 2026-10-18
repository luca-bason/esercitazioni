from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *
import sys


gStyle.SetOptStat(0)
h      = TH1D("h","",40,0,40)

nbkg  = 44.7

nobs  = 0.0
for line in open("dati_highstat.dat"):
    mass = float(line)
    #calcolare nobs
    
    h.Fill(mass)

h.Draw()
gApplication.Run(True)

nobs = h.GetBinContent(15)+h.GetBinContent(16)

#calcolare UL @ 95%CL
alpha = 0.05
pval = 0.0
while (pval<alpha):
    prob = 0.0
    for x in range(0,int(nobs)):
        prob = prob+TMath.PoissonI(x,nbkg)
    pval = 1-prob
    nbkg = nbkg+1
print (nbkg)
