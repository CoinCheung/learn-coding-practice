#!/usr/bin/python


import numpy as np


def fun(a,b,c):
    return a+b+c


if __name__ == '__main__':
    pa = range(10000000)
    pb = [i for i in range(10000000)]
    pc = np.arange(10000000)

    re = [x for x in map(fun, pa, pb, pc)]
    #  mapre = map(fun, pa, pb, pc)
    #  maplist = list(mapre)

    #  print(re[1])
