#!/usr/bin/python
# -*- coding: utf-8 -*-


from distutils.core import setup,Extension

mymodule = Extension('_so2048',sources = ['so2048.i','so2048.c'])

setup(
    name = 'so2048',
    version = '0.0',
    author = 'Coin',
    description = 'C methods called by python',
    ext_modules = [mymodule],
    py_modules = ['so2048'],
    )
