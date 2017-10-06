#!/usr/bin/python3
# filename: cmp003.py

'''
 * collect more information from DBC files
 * fix the function readSignals(), and add "; automatically if they are left to the next line
 * add function createDBC(), which writes the information to a .dbc file
 * add function readSignals(), that writes the differenc information of the two dbcs to a file
'''


#============================================================#
# function definitions
#
#============================================================#

import os
import codecs


#============================================================#
# function definitions
#
#============================================================#

####
## function: signals,messagesDict, headerlines,badefs = readSignals(filename)
##
## read the signals information from DCB file, return the common information such as the headlines, the fixed lines in the middle(BA_DEF = badefs), the list of signal dicts(sdict) and the list of message dicts(mdicts)
def readSignals(filename):
    signals = []
    messagesDict = dict()
    badefs = []

    file = codecs.open(filename,encoding = 'utf8')

    headlines = [file.readline() for i in range(35)]

    all_lines = file.readlines()

    for line in all_lines: # if the line is a message descriptor
        linelist = line.split(' ')
        if linelist[0] == 'BO_':  # line of message, create messageDictc
            mdict = dict()
            mdict['message_line'] = line
            mdict['signal_index'] = []
            messageID = linelist[1]
            messagesDict[linelist[1]] = mdict

        elif linelist[0] == '' and len(linelist) != 1 and linelist[1] == 'SG_':  # if the line is a signal descriptor, create signals
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

        elif linelist[0] == 'CM_':  # line of comment, added to signals
            name = linelist[3]
            if not line[-4:-2] == '";':
                line = list(line)
                line.insert(-2,'"')
                line.insert(-2,';')
                line = ''.join(line)
            for i,el in enumerate(signals):
                if el['signame'] == name:
                    signals[i]['comment'] = line

        elif linelist[0] == 'BA_' and linelist[2] == 'SG_': # line of signal parameters, added to signals
            name = linelist[4]
            for i, el in enumerate(signals):
                if el['signame'] == name:
                    signals[i][linelist[1]] = line

        elif linelist[0] == 'BA_' and linelist[2] == 'BO_': # line of Message information, added to MessageDict
            messagesDict[linelist[3]][linelist[1]] = line

        elif linelist[0] == 'VAL_': # line of signal emulation values, added to signals
            for i in range(len(signals)):
                if signals[i]['signame'] == linelist[2]:
                    signals[i]['values'] = line

        elif linelist[0] == 'BA_DEF_DEF_' or linelist[0] == 'BA_DEF_' or (linelist[0] == 'BA_' and linelist[1] == '"BaudRate"'): # line of other common flag lines
            badefs.append(line)

    file.close()

    return signals, messagesDict, headlines, badefs


####
## function: createDBC(signals, messagesDict, headlines, badefs)
##
##
def createDBC(signals, messagesDict, headlines, badefs):
    SignalMaptoMessage(signals, messagesDict)

    fhd = codecs.open('test_output1.dbc','w','utf8')

    for el in headlines:
        fhd.write(el)

    fhd.writelines(['BU_: Merged DBC\r\n','\r\n','\r\n'])

    for msg in messagesDict.values():
        fhd.write(msg['message_line'])
        for ind in msg['signal_index']:
            line = signals[ind]['signal_line']#.encode('utf8','ignore')
            fhd.writelines(line)
        fhd.write('\r\n')

    fhd.write('\r\n')
    fhd.write('\r\n')

    for sig in signals:
        if 'comment' in sig.keys():
            fhd.writelines(sig['comment'])

    for el in badefs:
        fhd.writelines(el)

    for el in messagesDict.values():
        if '"GenMsgSendType"' in el.keys():
            fhd.writelines(el['"GenMsgSendType"'])
        if '"GenMsgCycleTime"' in el.keys():
            fhd.writelines(el['"GenMsgCycleTime"'])
        if '"GenMsgDelayTime"' in el.keys():
            fhd.writelines(el['"GenMsgDelayTime"'])

    for el in signals:
        if '"GenSigPubLatency"' in el.keys():
            fhd.writelines(el['"GenSigPubLatency"'])
        if '"GenSigWriteInterval"' in el.keys():
            fhd.writelines(el['"GenSigWriteInterval"'])
        if '"GenSigStartValue"' in el.keys():
            fhd.writelines(el['"GenSigStartValue"'])

    for el in signals:
        if 'values' in el.keys():
            fhd.writelines(el['values'])

    fhd.close()



####
## function: SignalMaptoMessage(signals, messagesDict)
##
##
def SignalMaptoMessage(signals, messagesDict):
    for i,val in enumerate(signals):
        if messagesDict[val['messageID']]:
            messagesDict[val['messageID']]['signal_index'].append(i)



####
## function: sigals1 ,signals2 = compareSignalLists(siglist1, siglist2)
##
## compare two signal collections and return the different part that the other does not have
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


####
## function: compareSignals(sig1,sig2):
##
## compare two signals and return the difference index
## difference: 1-exactly same, 2-messageID different, 3-startbit different, 4-length different, 5-factor different, 6-offset different
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
## function: signalAll, messagesDictAll = merge(signals1, signals2, messagesDict1, messagesDict2)
##
## merge the two signal lists and message lists to one each
def merge(sigs1, sigs2, msg1, msg2):
    pass

#============================================================#
# entrance of the script
#
#============================================================#
if __name__ == '__main__':
    dbc1 = 'AS26HYB.dbc'
    dbc2 = 'AS24_HYB.dbc'

    signals1,messagesDict1, headerlines1,badefs1 = readSignals(dbc1)
    signals2,messagesDict2, headerlines2,badefs2 = readSignals(dbc2)

    #  signalAll, messagesDictAll = merge(signals1, signals2, messagesDict1, messagesDict2)

    #  print(badefs1)
    print(signals1[1])
    createDBC(signals1,messagesDict1, headerlines1,badefs1)

    #  for el in signals1:
    #      print(el['signame'])
    #  mergesignals = merge(signals1,signals2)

    print(len(signals1))
    diff1y2n, diff1n2y = compareSignalLists(signals1, signals2)
    print(len(signals1))

    diff_info_name = 'test_diff_out003.log'
    writeResult(diff1y2n,diff1n2y,dbc1, dbc2,diff_info_name)
    #  print(len(diff1y2n))

    #  for el in diff1y2n:
    #      print(el['signame'])
    #  mergesignals = merge(signals1,signals2)
