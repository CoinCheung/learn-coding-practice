
import numpy as np

mtr = np.arange(9).reshape(3,3)
print(mtr)

sqr1 = np.sum(np.square(mtr),axis = 1).reshape(3,1)
sqr2 = np.sum(np.square(mtr),axis = 1).reshape(1,3)
diff = np.dot(mtr,mtr.T) *(-2)

print('sqr1')
print(sqr1)
print('sqr2')
print(sqr2)
print('diff')
print(diff)

res = np.zeros((3,3)) + diff
print(res)
res = res + sqr1
print(res)
res = res + sqr2
print(res)

for i in range(3):
    res[i,:] = np.arange(3)
print(res)

print('start')
arr = np.array([1,2,3,4,5])
for i in range(5):
    #  print(arr[:i])
    #  print(arr[i+1:])
    print(np.hstack(tuple(arr[:i]) + tuple(arr[i+1:])))

ar = np.array([1,2,3,4,5,6,7,8,9]).reshape(3,3)
print(ar)
print(np.split(ar,3,axis = 0))
print(ar[:,1])

ar = np.array([1,2,3,4,5,6,7,8,9]).reshape(3,3)
print(ar[np.arange(2), np.array([1,2])])
#  print(ar[np.array([1,2]), np.array([0,1])])

print(ar - np.arange(3).reshape(3,1)+1)
#  ar[ar > 2] = 0
print(ar)
print(np.sum(ar))

print(ar * np.arange(3).reshape(3,1))
print( np.arange(3).reshape(3,1) * np.arange(3).reshape(1,3))

print(ar)
ar[np.arange(2), np.array([1,2])] = -np.arange(2)
print(ar)
indices = np.random.choice(np.arange(3), 2)
print(indices)
print(ar[indices])

print(ar)
ar[0,0] = 3
print(ar.max(axis = 1))
best = ar.max(axis = 1)
indices = ar[ar == best]
print(indices)
print('here')
print(np.argmax(ar, axis = 1))

ar = np.arange(9).reshape(3,3)
print(np.exp(ar))

print(ar[:,2])
print(np.zeros_like(ar))

ones = np.ones((3,3))
col = np.arange(3).reshape(3,1)
print(ar)
print(col.T + ar)

print(ar[:,2].shape)

print(np.maximum(3,ar))

print(np.ones((2,2)))

print(1.00000e+00)


print(ar)
sum = np.sum(ar,axis = 1,keepdims = True)
print(ar/sum)
print(np.all(ar == col.T))
