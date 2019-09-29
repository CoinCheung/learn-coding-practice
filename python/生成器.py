#!/bin/python3
# -*- coding: utf-8 -*-

def fun():
    print('start...')
    m = yield '4'
    print(m)
    print('middle ...')
    d = yield m #'23'
    print(d)
    print('end...')


if __name__ == '__main__':
    g = fun()
    print(next(g))
    print(g.send('message'))
    #  g.send('message')
    print(next(g))
