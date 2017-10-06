#!/usr/bin/python3
#filename: cmpr001.py

import os

def readSignals(filename):
    signals = []

    file = open(filename)
    all_lines = file.readlines()#.splitlines().encode('latin1')

    for line in all_lines: # if the line is a message descriptor
        linelist = line.split(' ')
        if linelist[0] == 'BO_':
            for i, message in enumerate(linelist):
                if i == 2:
                    sigmessage = message[0:-2]
                    break
                elif i == 1:
                    messageID = int(message)

        elif linelist[0] == ''  and len(linelist) != 1 and linelist[1] == 'SG_':  # if the line is a signal descriptor
            sdict = dict()
            linelist = line.split(' ')
            for i, value in enumerate(linelist):
                if i == 2:  # even though the first character is space, the split will return a list headed with none
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
                elif i ==6:
                    value = value.strip('[')
                    value = value.strip(']')
                    sublist = value.split('|')
                    sdict['min'] = sublist[0]
                    sdict['max'] = sublist[1]

            sdict['message'] = sigmessage
            sdict['messageID'] = messageID
            sdict['diffmode'] = 'noin'
            signals.append(sdict)

    file.close()

    return signals


def compareSignalLists(siglist1, siglist2):
    relist1 = []
    relist2 = []
    for i in range(len(siglist1)):
        for j in range(len(siglist2)):
            if siglist1[i]['signame'] == siglist2[j]['signame']:
                res = compareSignals(siglist1[i],siglist2[j])
                siglist1[i]['diffmode'] = res
                siglist2[j]['diffmode'] = res
                if res == 1: # exactly same
                    relist1.append(siglist1[i])
                    relist2.append(siglist2[j])

    for ele1 in relist1:
        siglist1.remove(ele1)

    for ele2 in relist2:
        siglist2.remove(ele2)

    return siglist1,siglist2


def compareSignals(sig1,sig2):
    ret = 1
    if sig1['messageID'] != sig2['messageID']:
        ret = 2
    elif sig1['startbit'] != sig2['startbit']:
        ret = 3
    elif sig1['length'] != sig2['length']:
        ret = 4
    elif sig1['factor'] != sig2['factor']:
        ret = 5
    elif sig1['offset'] != sig2['offset']:
        ret = 6

    if ret == 2:
        print('name %s is same, and messageID is different'%sig1['signame'])
    elif ret == 3:
        print('name %s is same, and startbit is different'%sig1['signame'])
    elif ret == 4:
        print('name %s is same, and length is different'%sig1['signame'])
    elif ret == 5:
        print('name %s is same, and factor is different'%sig1['signame'])
    elif ret == 6:
        print('name %s is same, and offset is different'%sig1['signame'])

    return ret   # if all the elemets are same, return 1


##
def writeResult(diff1y2n,diff1n2y,fname1,fname2):
    fhd = open('result.txt','w')
    fhd.close()

    fhd = open('result.txt','a')

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


if __name__ == '__main__':
    fname1 = 'AS26HYB.dbc'
    fname2 = 'AS24_HYB.dbc'

    signals1 = readSignals(fname1)
    signals2 = readSignals(fname2)

    diff1y2n, diff1n2y = compareSignalLists(signals1, signals2)

    writeResult(diff1y2n,diff1n2y,fname1,fname2)

    #  signals2 = readSignals('AS26HYB.dbc')
    #  signals1 = readSignals('AS24_HYB.dbc')

    print(len(diff1y2n))


