#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
setup.py file for Swig
'''

from distutils.core import setup,Extension

mymodule = Extension('_mymod',sources = ['mymod_wrap.c','test.c'])

setup(
        name = 'mymod', #the name of the module to be imported in python
        version = '0.1',
        author = 'Coin',
        description = 'just a try of this extension',
        ext_modules = [mymodule], # the module object created above
        py_modules = ['mymod'], # the python file created by swig (if any)
        )
