from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *
import sys


gStyle.SetOptStat(0)
h      = TH1D("h","",40,0,40)

#implementare fitfun
f = TF1("f","[0]*[1]*([2]*TMath::Gaus(x,[3],[4],true)+(1-[2])*(exp(-x/[5])/[5]))",0,50)

for line in open("dati_highstat.dat"):
    mass = float(line)
    h.Fill(mass)
h.Draw()
gApplication.Run(True)

mu = h.GetMean()
std = h.GetStdDev()

# implementare fit binned con metodo Fit
c1 = TCanvas()

f.SetParameter(3,15)
f.SetParLimits(3,14,16)
f.SetParameter(4,0.5)
f.SetParLimits(4,0.1,0.9)
f.FixParameter(0,1)
f.FixParameter(1,1)
f.SetParameter(2,0.2)
f.SetParLimits(2,0,1)
f.SetParameter(5,mu)

h.Draw()
h.Fit("f","0MULTI")
f.SetParameter(0, h.GetBinWidth(1))
f.SetParameter(1, h.Integral())
f.Draw("SAME")


gApplication.Run(True)

#implementare fit binned estesa

f.SetParameter(3,15)
f.SetParLimits(3,14,16)
f.SetParameter(4,0.5)
f.SetParLimits(4,0.1,0.9)
f.FixParameter(0,h.GetBinWidth(1))
f.FixParameter(1,h.GetEntries())
f.SetParameter(2,0.2)
f.SetParLimits(2,0,1)
f.SetParameter(5,mu)

h.Draw()
h.Fit("f","L")

gApplication.Run(True)

# implementare fit unbinned con TTree
c2 = TCanvas()
t = TTree()
t.ReadFile("dati_highstat.dat","t")
for i in range(0,t.GetEntries()):
    t.GetEntry(i)
f.SetParameter(3,15)
f.SetParLimits(3,14,16)
f.SetParameter(4,0.5)
f.SetParLimits(4,0.1,0.9)
f.FixParameter(0,1)
f.FixParameter(1,1)
f.SetParameter(2,0.2)
f.SetParLimits(2,0,1)
f.SetParameter(5,mu)

t.UnbinnedFit("f","t")
h.Draw()
f.SetParameter(0, h.GetBinWidth(1))
f.SetParameter(1, h.Integral())
f.Draw("SAME")

gApplication.Run(True)
