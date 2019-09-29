import sys
sys.path.append('../build')

from liboutput import ffi, lib
import numpy as np

lib.voidprint()

p = ffi.new('double []', [1,2,3,4,5,6])

l = list([1,2,3,4,5])
pa = np.array(p)
print(pa)

num = 3
#  typ = exec()
pc = ffi.cast('double (*)[{}]'.format(num),p)
print(pc[1][2])


marr = np.array([1,2,3,4,5,6,7,8])
print(np.max(marr))
print(marr.max())
print(np.argmax(marr))
print('here')
marr = np.delete(marr, 0, axis = 0)
print(marr)

#  myd = dict()
myd = {}
myd[3] = 1
myd[3] += 1
myd['1'] = 4

if 3 in myd:
    print(myd[3])


a = [1,2,3,4,5]

print(type(myd.keys()))
print(max(myd,key = myd.get))

arr = np.array(range(9)).reshape(3,3)
print(arr)
newarr = np.delete(arr, [1,2], axis = 1)
print(newarr)

print()
arrp = np.array([[1],[2],[3]])
resarr = arrp + arr
print('here')
print(resarr)
print(resarr.shape)
print(arrp.shape)
row = np.arange(3)
print(np.vstack((arr,row)))

arrn = np.arange(6).reshape(2,3)
#  print(arrn - arr)
print(np.arange(3).T.reshape(3,1))
