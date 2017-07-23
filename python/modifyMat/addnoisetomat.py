#!/usr/bin/python
# -*- coding: utf-8 -*-


import scipy.io as scio
import numpy as np
import matplotlib.pyplot as pl
import os


def wgn(x, snr):
    snr = 10**(snr/10.0)
    xx = []
    for element in x:
        xx.append(element**2)
    #print(xx)
    xpower = np.sum(xx)/len(xx)
    print(xpower)
    npower = xpower / snr
    print(npower)
    d = np.random.randn(len(xx)) * np.sqrt(npower)
    #pl.figure(2)
    #pl.plot(d)
    #pl.show()
    print(max(d))
    return d


if __name__ == '__main__':
    indata = scio.loadmat(os.getcwd() + '/indata.mat')

    print(type(indata))
    print(indata.keys())

    print(indata['UI'][1][-1])

    soc = []
    for bl in indata['UI']:
        soc.append(bl[-1])


    print(type(soc[2]))
    #print(soc**2)

    n = wgn(soc,0.003)
    socn = soc + n/70

    socmat = []
    for d in socn:
        socmat.append([d])
    print(socmat)

    outdata = os.getcwd()+'/outdata.mat'
    scio.savemat(outdata,{'SOC':socmat})

    #pl.subplot(211)
    #pl.plot(soc)
    #pl.subplot(212)
    #pl.plot(socn)
    #pl.show()

    #pl.figure(2)
    #pl.plot(n)
    #pl.show()


