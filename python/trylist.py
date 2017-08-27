#!/usr/bin/python3


#  #  lis = [1,2,3,4,5,6,7,8]
#  #  ll = (i for i in lis if i%2 == 0)
#  #  print(next(ll))
#  #  print(next(ll))
#  #  print(next(ll))
#  #  print(next(ll))
#
#  di = {'name':'Coin', 'Age':23, 'Gender':'Male'}
#  print('before conver',di)
#
#  print('after conver',tuple(di.items()))
#
#  print([(x,y) for x,y in di.items()])
#
#  print('conver back',list([di,di.values()]))
#
#  t = ((1, 'a'),(2, 'b'))
#
#  print([(y,x) for x,y in t])
#
#  #  print(hash(di))
#
#  t = [(x,y) for x,y in di.items()]
#  print(tuple(t))
#  print(type(set(t)))
#  print((x,y)) for (x,y) in di.items()
#  print(type(di.items()))

## ====================================
di = [ {'name':'Coin', 'Age':23, 'Gender':'Male'},{'name':'Cheung', 'Age':25, 'Gender':'Male1'} ]


ditp = [tuple(diel.items()) for diel in di ]
print(ditp)
diset = set(ditp)
print(diset)
print('conver back',list(diset))

print()
dic = (('name', 'Coin'), ('Age', 23), ('Gender', 'Male'))
print('compare')
print(dict(dic))

ditpback = [dict(dic) for dic in list(diset)]
print(ditpback)
print(di)

print(di == ditpback)
print(di[0])
print(ditpback[0])


print()
print()
di = {'name':'Coin', 'Age':23, 'Gender':'Male'}
print(di.keys())


print([x for x in di.keys()])


dic = (['name', 'Coin'], ['Age', 23], ['Gender', 'Male'])
print(dict(dic))
