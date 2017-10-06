#!/usr/bin/python3
#filename: test.py
#-*- coding = utf-8 -*-

import codecs

#  file1 = codecs.open('AS26_HYB.dbc','r',encoding = 'utf8')
#  file1 = open('AS26_HYB.dbc',encoding = 'latin1')
#  file2 = open('AS24_HYB.dbc')
#
#  for line in file.readline().decode('latin1'):
#      print(line)
#
#  data = file.read().encode('latin1')

#  lines1 = [file1.readline() for i in range(46)]
#  lines2 = [file2.readline() for i in range(46)]
#
#  lines1 = [lines1[i] for i in range(39,46)]

#  for l1 in lines1:
#      for l2 in lines2:
#          if l1 == l2:
#              print('true')

#  for l1 in lines1:
#      print(l1.split(' '))
    #  print(l1)

#  l2 = lines1[1].split(' ')
#  print(l2)
#  for i,el in enumerate(l2):
#      l2[i] = 'hahaha'
#  print(l2)
#
#  file1.close()
#  file2.close()

#  list1 = ['1', '2', '3','4','5']
#  list2 = ['1', '2', '3','4','5']
#
#  #  for ele1 in list1:
#  flag = 0
#  n = 5
#  for i in range(n):
#      #  if ele1 == list2[i]:
#          #  list1.remove(ele1)
#      if flag == 0:
#          n = 3
#          list2.remove(list2[2])
#          flag = 1
#      print(i)
#      print(len(list2))
#
#  print(list1)
#  print(list2)


#  a = {'a':1,'b':'c'}
#  b = {'b':2,'c':3}
#  e = (a,)+(b,)
#  print(e)
#  if a in e:
#      print('true')
#  print((a,))
#
#
#  c = (1,2)
#  d = (2,3)
#  print(c+d)
#  print(tuple(a.items()))
#
#  myt = tuple()
#  print(myt+(1,))
#  del myt
#
#  print(c[1])
#  print(list(c+d))
#
#  cdlist = list(c+d)
#  print('start')
#  print(cdlist)
#  del(cdlist[2])
#  print(list(c+d).remove(list(c+d)[2]))
#  print(del(list(c+d)))
#  print(cdlist.remove(cdlist[2]))
#
#  print(cdlist)
#  print('end')
#
#  l = [1,2,4,5,6]
#  print(l)
#  #  del l[1]
#  l.remove(l[2])
#  print(l)
#
#  print(c+d)
#  cdlist = list(c+d)
#  del cdlist[1]
#  print(tuple(cdlist))

#  l = [1,2,3,4,5]
#  print(l)
#  def changel(l):
#      for i in range(len(l)):
#          l[i] = 3
#  changel(l)
#  print(l)
#
#  d = {1:'a',2:'b'}
#  print(d)
#  def changed(d):
#      d[1] = 3
#  changed(d)
#  print(d)
#
#  ll = [{1:'a',2:'b'}, d]
#  def changed(ll):
#      d[1] = 3
#  print(d)
#
#  l = 'nameddde'
#  print(l[-3:len(l)])



####
## function: writeResult(diff1y2n,diff1n2y,fname1,fname2,resname)
##
## write the name of uncommon signals and conflict signals to a result file
def writeResult(diff1y2n,diff1n2y,fname1,fname2,resname):
    fhd = open(resname,'a')

    # write signals dbc1 has while dbc2 not
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('the signals that %s have but %s do not'%(fname1,fname2))
    fhd.write(os.linesep)
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)

    for sig in diff1y2n:
        if sig['diffmode'] == 'noin':
            fhd.write(os.linesep)
            fhd.write(sig['signame'])
    fhd.write(os.linesep)
    fhd.write(os.linesep)

    # write signals dbc2 has while dbc1 not
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('the signals that %s have but %s do not'%(fname2,fname1))
    fhd.write(os.linesep)
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)

    for sig in diff1n2y:
        if sig['diffmode'] == 'noin':
            fhd.write(os.linesep)
            fhd.write(sig['signame'])
    fhd.write(os.linesep)
    fhd.write(os.linesep)

    # write signals of conflicts
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('the conflict signals of %s and %s'%(fname1,fname2))
    fhd.write(os.linesep)
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)

    for sig in diff1n2y:
        if sig['diffmode'] == 2:
            fhd.write('signal %s has message ID conflicts in the two files'%sig['signame'])
            fhd.write(os.linesep)
        elif sig['diffmode'] == 3:
            fhd.write('signal %s has startbit conflicts in the two files'%sig['signame'])
            fhd.write(os.linesep)
        elif sig['diffmode'] == 4:
            fhd.write('signal %s has length conflicts in the two files'%sig['signame'])
            fhd.write(os.linesep)
        elif sig['diffmode'] == 5:
            fhd.write('signal %s has factor conflicts in the two files'%sig['signame'])
            fhd.write(os.linesep)
        elif sig['diffmode'] == 6:
            fhd.write('signal %s has offset conflicts in the two files'%sig['signame'])
            fhd.write(os.linesep)
    fhd.write(os.linesep)
    fhd.write(os.linesep)

    fhd.close()


####
## function: signals,messagesDict, headerlines,badefs = readSignals(filename)
##
## read the signals information from DCB file
def readSignals(filename):
    signals = []
    messagesDict = dict()
    badefs = []

    file = codecs.open(filename,encoding = 'utf8')

    headlines = [file.readline() for i in range(35)]

    all_lines = file.readlines()

    for line in all_lines: # if the line is a message descriptor
        linelist = line.split(' ')
        if linelist[0] == 'BO_':  # line of message
            mdict = dict()
            mdict['message_line'] = line
            mdict['signal_index'] = []
            messageID = linelist[1]
            messagesDict[linelist[1]] = mdict

        elif linelist[0] == '' and len(linelist) != 1 and linelist[1] == 'SG_':  # if the line is a signal descriptor
            sdict = dict()
            linelist = line.split(' ')
            for i, value in enumerate(linelist):
                if i == 2:
                    sdict['signame'] = value
                elif i == 4:
                    sublist = value.split('|')
                    sdict['startbit'] = sublist[0]
                    sdict['length'] = sublist[1].split('@')[0]
                elif i == 5:
                    value = value.strip('(')
                    value = value.strip(')')
                    sublist = value.split(',')
                    sdict['factor'] = sublist[0]
                    sdict['offset'] = sublist[1]

            sdict['messageID'] = messageID
            sdict['diffmode'] = 'noin'
            sdict['signal_line'] = line

            signals.append(sdict)

        elif linelist[0] == 'CM_':  # line of comment
            name = linelist[3]
            for i,el in enumerate(signals):
                if el['signame'] == name:
                    signals[i]['comment'] = line

        elif linelist[0] == 'BA_' and linelist[2] == 'SG_':
            name = linelist[4]
            for i, el in enumerate(signals):
                if el['signame'] == name:
                    signals[i][linelist[1]] = line

        elif linelist[0] == 'BA_' and linelist[2] == 'BO_':
            messagesDict[linelist[3]][linelist[1]] = line

        elif linelist[0] == 'VAL_':
            for i in range(len(signals)):
                if signals[i]['signame'] == linelist[2]:
                    signals[i]['values'] = line

        elif linelist[0] == 'BA_DEF_DEF_' or linelist[0] == 'BA_DEF_' or (linelist[0] == 'BA_' and linelist[1] == '"BaudRate"'):
            badefs.append(line)

    file.close()

    return signals, messagesDict, headlines, badefs




if __name__ == '__main__':
    sigals, messageDict, headlines, badefs = readSignals('AS26HYB.dbc')
    #  writeResult()
    #  pass
    #  import chardet
    #
    #  lo = 'abcdefg\n'
    #  l = list(lo)
    #  print(chardet.detect(lo))
    #  print(type(lo))
    #  l.insert(2,'22')
    #  print(''.join(l).encode('utf8'))
    #  print(type(l))
    #  print(list(l))

    l = [1,2,3,4,5]
    #  print(l)
    #
    #  ll = l[2:3]
    #  ll[0] = 444
    #  print(ll)
    #  print(l)
    #
    #  import copy
    #
    #  tp = (1,2)
    #  lstp = list(tp)
    #  tpcp = copy.deepcopy(tp)
    #  print(id(tp))
    #  print(id(tpcp))
    #  print(id(lstp))


mdi = {1:'1',2:'2',3:'3'}
print(mdi.items())

print(type(str(int('3'))))

def wrap_fun(var1, var2):
    def inner_fun():
        print(var1)
        print(var3)

    var3 = var1
    inner_fun()

wrap_fun(2,3)


a = ['coin','is','a','good','citizen']
b = ['who','is','colin']

for token in a:
    print(token)
    if token in b:
        print(token)


str = 'abc def ghi jkl'
print(str[-3:].upper())
print(str[-3:-1].upper())

a = 'abcdefghijk'
b = a[:3]
print(a)
print(b)
print(a is b)
c = 'abcdefghijk'
#  print(a.equal(b))
print(a == b)
#  c = a
a = 'abcd'
c = 'abcd'
print(a is c)
print(a == c)

a = 'abcd'
c = a
print(a is c)
print(a == c)

a = [1,2,3,4]
c = [1,2,3,4]
#  c = a[:]
print(a == c)
print(a is c)

a = [1,2,3,4]
c = a
#  c = a[:]
print(a == c)
print(a is c)

a = 'abc2c_de'
print(a.upper())


import re
pattern = re.compile(r'H\dHSC')
match = pattern.match('H6HSC6')
print(match.group())
