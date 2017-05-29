#!/usr/bin/python
#filename:usecpickle.py

'''use Cpickle to write data to file and then read the data back'''

import cPickle as pickle
import os


pth=os.path.expanduser('./')
target=os.path.abspath('%sdata.dat'%(pth))

token=raw_input('please enther the token-->')

if not os.path.exists(pth):
	os.system('mkdir %s'%(pth))

f=file('%s'%(target),'a')
pickle.dump(token,f,True)
f.close()

print'the token is writen'


