#!/usr/bin/python
# -*- coding: utf-8 -*-


from ctypes import *
import os


test = cdll.LoadLibrary(os.getcwd()+'/libtest.so')
print(test.var)
test.print()


