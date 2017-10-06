#!/usr/bin/python3
#filename: cmpr002.py
# use set to compute the signal collections difference


#============================================================#
# function definitions
#
#============================================================#

## function: readSignals(filename)
## read the signals information from DCB file
def readSignals(filename):
    signals = []

    file = open(filename)

    headlines = [file.readline() for i in range(33)]

    all_lines = file.readlines()

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
                elif i ==6:
                    value = value.strip('[')
                    value = value.strip(']')
                    sublist = value.split('|')
                    sdict['min'] = sublist[0]
                    sdict['max'] = sublist[1]

            sdict['message'] = sigmessage
            sdict['messageID'] = messageID
            signals.append(sdict)

    file.close()

    return signals, headlines



## function: compareSignalLists(siglist1, siglist2)
## compare two signal collections and return the common part and siglist1 - common
def compareSignalLists(siglist1, siglist2):
    sigset1 = set([tuple(ele.items()) for ele in siglist1])
    sigset2 = set([tuple(ele.items()) for ele in siglist2])

    commontuple = sigset1 & sigset2
    diff1y2n = sigset1 - commontuple

    siglistcommon = [dict(ele) for ele in list(commontuple)]
    siglistdiff1y2n = [dict(ele) for ele in list(diff1y2n)]

    return siglistcommon,siglistdiff1y2n


## function: compareSignals(sig1,sig2):
## compare two signals and return the difference index
## difference: 1-all same, 2-messageID different, 3-startbit different, 4-length different, 5-factor different, 6-offset different
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


## function: compareSignalLists(siglist1, siglist2)
## compare two signal collections and return the difference
def merge(sigs1, sigs2):
    pass

#============================================================#
# entrance of the script
#
#============================================================#
if __name__ == '__main__':
    signals1,headerlines1 = readSignals('AS26HYB.dbc')
    signals2,headerlines2 = readSignals('AS24_HYB.dbc')

    #  mergesignals = merge(signals1,signals2)

    print(signals1[1])
    commonlist, diff1y2n = compareSignalLists(signals1, signals2)
    print(commonlist)
    print(len(signals1))
    print(len(commonlist))
    print(len(diff1y2n))
