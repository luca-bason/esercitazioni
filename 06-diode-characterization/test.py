#!/usr/bin/python
    
import sys,serial
from dmm import *
from ps import *
import numpy as np
import time

ser1 = serial.Serial("COM7", 9600)
file2 = open("out2.dat","w")

gen = psinit()
pssel(gen,1)

# Misurazione
xV = np.array([0.1,0.2,0.25,0.3,0.35,0.4,0.45,0.5])
for i in range (0,len(xV)):
    cmd = f'APPLY {xV[i]}, 0.1'
    gen.write(cmd)
    time.sleep(1)
    I,eI = dmmread(ser1)
    print(xV[i],I,eI)
    file2.write(str(xV[i])+"\t")
    file2.write(str(I)+"\t")
    file2.write(str(eI)+"\t")
    file2.write("\n")

file2.close()
    




