#!/usr/bin/python
# -*- coding: utf-8 -*-


from ctypes import *
import os
import numpy as np


test = cdll.LoadLibrary(os.getcwd()+'/libtest.so')
print(test.var)
test.print()

for i in range(1000):
    print(test.getVar())

test.setVar(44)
print(test.getVar())

test.printMyClassStr(test.dd)

arr = []
arr = [[0 for i in range(4)] for j in range(4)]
print(arr[2][3])
print("start")

arrnumpy = np.zeros((4,4),dtype = np.double)
pin = c_void_p(arrnumpy.ctypes.data)
rest = np.zeros((4,4),dtype = np.double)
pout = c_void_p(rest.ctypes.data)
test.calMix(pin,4,4,pout)

print(rest[2][2])
