#!/usr/bin/python

from   pyvisa import ResourceManager

def psinit():
    rm = ResourceManager()
    instr = rm.open_resource("USB0::0x0AAD::0x0135::035375054::INSTR")
    return instr

def pssel(instr,ch):
    instsel = f"INST: NSEL {ch}"
    instout = f"INST OUT{ch}"
    instr.write(instsel)
    instr.write(instout)
    instr.write("OUTP ON")
