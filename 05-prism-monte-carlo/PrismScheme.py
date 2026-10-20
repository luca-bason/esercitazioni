from   ROOT import *
from   math import *
import time
import random as rnd

#Parametri e misure
lambda1 = 579.1
lambda2 = 404.7
alpha   = pi/3
th0     = 1.5701
th1     = 2.6958
th2     = 2.7904
eth     = 0.0005
sth     = eth/sqrt(3)

#Funzione 
def GetAB(th0,th1,th2):
    del1  = th1-th0
    del2  = th2-th0
    n1    = (sin((del1+alpha)/2))/(sin(alpha/2))
    n2    = (sin((del2+alpha)/2))/(sin(alpha/2))
    lamq1 = lambda1**2
    lamq2 = lambda2**2
    B     = (n2-n1)*lamq1*lamq2/(lamq1-lamq2)
    A     = n1-(B/lamq1)
    return A,B

def GetABError(th0,th1,th2):
    A,B   = GetAB(th0,th1,th2)
    A0,B0 = GetAB(th0+sth,th1,th2)
    A1,B1 = GetAB(th0,th1+sth,th2)
    A2,B2 = GetAB(th0,th1,th2+sth)
    
    eA0 = A0-A
    eB0 = B0-B
    eA1 = A1-A
    eB1 = B1-B
    eA2 = A2-A
    eB2 = B2-B
    
    eA = sqrt(eA0**2+eA1**2+eA2**2)
    eB = sqrt(eB0**2+eB1**2+eB2**2)
    return eA,eB

#Main
A,B   = GetAB(th0,th1,th2)
eA,eB = GetABError(th0,th1,th2)

print ("A = ",A,"+-",eA)
print ("B = ",B,"+-",eB)

rnd = TRandom3()
rnd.SetSeed(123456789)

A  = TH1D("A","A",100,0,0)
B  = TH1D("B","B",100,0,0)
AB = TH2D("AB","AB",100,0,0,100,0,0)

for i in range (0,10000):
    TH0 = rnd.Gaus(th0,sth)
    TH1 = rnd.Gaus(th1,sth)
    TH2 = rnd.Gaus(th2,sth)

    Apt,Bpt = GetAB(TH0,TH1,TH2)

    A.Fill(Apt)
    B.Fill(Bpt)
    AB.Fill(Apt,Bpt)

c0 = TCanvas()
c0.cd()
A.Draw()
c1 = TCanvas()
c1.cd()
B.Draw()
c2 = TCanvas()
c2.cd()
AB.Draw()

A_1  = A.GetMean()
eA_1 = A.GetRMS()

B_1  = B.GetMean()
eB_1 = B.GetRMS()

CF1  = AB.GetCorrelationFactor()

print("A = ",A_1,"+-",eA_1)
print("B = ",B_1,"+-",eB_1)
print("Fattore di correlazione: ",CF1)

A.Reset()
B.Reset()
AB.Reset()

for i in range (0,10000):
    TH0 = rnd.Uniform(th0-eth,th0+eth)
    TH1 = rnd.Uniform(th1-eth,th1+eth)
    TH2 = rnd.Uniform(th2-eth,th2+eth)

    Apt,Bpt = GetAB(TH0,TH1,TH2)

    A.Fill(Apt)
    B.Fill(Bpt)
    AB.Fill(Apt,Bpt)

c0 = TCanvas()
c0.cd()
A.Draw()
c1 = TCanvas()
c1.cd()
B.Draw()
c2 = TCanvas()
c2.cd()
AB.Draw()

A_2  = A.GetMean()
eA_2 = A.GetRMS()

B_2  = B.GetMean()
eB_2 = B.GetRMS()

CF2  = AB.GetCorrelationFactor()

print("A = ",A_2,"+-",eA_2)
print("B = ",B_2,"+-",eB_2)
print("Fattore di correlazione: ",CF2)

gApplication.Run(True)
