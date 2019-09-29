#!/usr/bin/python
# -*- encoding: utf8 -*-
# filename: refer.py


import numpy as np


def fun(x):
    out = x
    out[0] = 9999
    return out


if __name__ == '__main__':
    inpt = np.arange(9).reshape(3, 3)
    print(inpt)
    outpt = fun(inpt)
    print(inpt)
    print(outpt)
    inpt[0] = 3333
    print(inpt)
    print(outpt)
