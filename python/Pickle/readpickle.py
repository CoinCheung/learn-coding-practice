#!/usr/bin/python
#filename:readpickle.py


import cPickle as pickle
import os

pth=os.path.expanduser('./')
target=os.path.abspath('%sdata.dat'%(pth))

f=file(target,'rb')
token=pickle.load(f)

print token

print'the data is read from the pickle!!'
