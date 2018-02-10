#!/usr/bin/python3
# -*- coding: utf-8 -*-
# filename: cmp.py




import os
import codecs
import copy


def readSignals(filename):
    # nested method that cut off certain prefix and postfix of a signal name
    def get_signal_shortname(sig):
        # check postfix
        if len(sig) > 6 and (sig[-6:-1].upper() == 'H6HSC' or sig[-6:-1].upper() == 'H1HSC'):
            sig = sig[:-6]
        elif sig[-5:-1].upper() == '_HSC':
            sig = sig[:-5]
        elif sig[-4:-1].upper() == 'HSC':
            sig = sig[:-4]
        elif sig[-3:-1].upper() == '_H':
            sig = sig[:-3]
        elif sig[-2].upper() == 'H':
            sig = sig[:-2]
        elif sig[-3:].upper() == '_UB':
            sig = sig[:-3]
        elif sig[-2:].upper() == 'UB':
            sig = sig[:-2]
        # check prefix
        if sig[:3].upper() == 'UB_':
            sig = sig[3:]
        elif sig[:2].upper() == 'UB':
            sig = sig[2:]

        return sig

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
                    sdict['signame'] = get_signal_shortname(value)
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


def createDBC(signals, messagesDict, headlines, badefs, dbcname):
    # sub-function of establishing mapping relationship from signals to the messages they belong to
    def SignalMaptoMessage(signals, messagesDict):
        for i,val in enumerate(signals):
            if messagesDict[val['messageID']]:
                messagesDict[val['messageID']]['signal_index'].append(i)

    # map signals to their messages
    SignalMaptoMessage(signals, messagesDict)

    # open file for writing
    fhd = codecs.open(dbcname,'w','utf8')

    # write headlines
    for el in headlines:
        fhd.write(el)

    fhd.writelines(['BU_: Merged DBC\r\n','\r\n','\r\n'])

    # write signal message information lines
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

    sigs1 = copy.deepcopy(siglist1)
    sigs2 = copy.deepcopy(siglist2)

    for ele1 in relist1:
        sigs1.remove(ele1)

    for ele2 in relist2:
        sigs2.remove(ele2)

    return sigs1,sigs2


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


def writeResult(diff1y2n,diff1n2y,fname1,fname2,resname):

    fhd = open(resname,'w')

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
    fhd.write('the conflict signals of %s and %s(conflicts will not be merged, signals in %s discarded)'%(fname1,fname2,fname2))
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


def merge(sigs1, sigs2, msg1, msg2, tuple_badefs, dbcnames, logname):
    # a method to see if two signals not overlap each other
    def no_overlap(s1, s2):
        if s1['messageID'] == s2['messageID']:
            end1 = int(s1['startbit'])
            end2 = int(s2['startbit'])
            start1 = int(s1['startbit']) - int(s1['length']) + 1
            start2 = int(s2['startbit']) - int(s2['length']) + 1
            if (start1 >= start2 and start1 <= end2) or (start2 >= start1 and start2 <= end1) or (start1 >= start2 and end1 <= end2) or (start2 >= start1 and end2 <= end1):
                return False # overlaps return false
            else:
                return True
        else:
            return True # message different return True

    # method that merge BA_DEF_ lines from two dbc files and write associated logs
    def merge_badef(badefs1, badefs2):
        fhd.write('Merging BA_DEFs: ')
        fhd.write(os.linesep)
        fhd.write(os.linesep)

        badefs = copy.deepcopy(badefs2)
        for token in badefs1:
            if token not in badefs2:
                fhd.write("\tadding line '{0} ...' from {1} to {2}".format(token[:20],dbcnames[0],dbcnames[1]))
                fhd.write(os.linesep)
                badefs.append(copy.deepcopy(token))

        return badefs

    # write comparison results to a log file
    diff1y2n, diff1n2y = compareSignalLists(sigs1, sigs2)
    writeResult(diff1y2n,diff1n2y,dbcnames[0], dbcnames[1], logname)

    # start merging, and write logs
    fhd = open(logname,'a')
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('Merging process')
    fhd.write(os.linesep)
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)

    # merge message collections
    fhd.write('Merging Messages: ')
    fhd.write(os.linesep)
    fhd.write(os.linesep)
    msgbase = copy.deepcopy(msg1) # deep copy signals1 as a base
    for el in msg2.items():
        msg_same = False
        for ms in msg1.items():
            if el[0] == ms[0]:
                msg_same = True
                break
        if msg_same == False:
            fhd.write('\tadding message ID = %s from %s to %s;'%(el[0],dbcnames[1],dbcnames[0]))
            fhd.write(os.linesep)
            msgbase[el[0]] = el[1]

    fhd.write(os.linesep)
    fhd.write(os.linesep)

    # merge signal collections
    fhd.write('Merging Signals: ')
    fhd.write(os.linesep)
    fhd.write(os.linesep)
    sigbase = copy.deepcopy(sigs1) # deep copy signals1 as a base
    for el in diff1n2y:
        if el['diffmode'] == 'noin': # el not conflict signa
            fhd.write('\tadding signal name = %s from %s to %s: '%(el['signame'],dbcnames[1],dbcnames[0]))
            nooverlap = True
            for sig in sigs1:
            #  for sig in sigbase:
                nooverlap = no_overlap(el,sig)
                if not nooverlap:
                    fhd.write(' discard due to overlap with %s;'%(sig['signame']))
                    fhd.write(os.linesep)
                    break
            if nooverlap:
                fhd.write(' success')
                fhd.write(os.linesep)
                sigbase.append(el)

    fhd.write(os.linesep)
    fhd.write(os.linesep)

    # merge BA_DEF lines
    badefs = merge_badef(tuple_badefs[0], tuple_badefs[1])

    fhd.write(os.linesep)
    fhd.write(os.linesep)
    fhd.close()

    return sigbase, msgbase, badefs




# program entrance
if __name__ == '__main__':
    dbc1 = 'AS26HYB.dbc'
    dbc2 = 'EP1_HYB.dbc'
    new_dbc_name = 'test_dbc_output005.dbc'
    merge_log_name = 'test_diff_out005.log'

    signals1,messagesDict1, headerlines1,badefs1 = readSignals(dbc1)
    signals2,messagesDict2, headerlines2,badefs2 = readSignals(dbc2)

    signalsAll, messagesDictAll, badefs = merge(signals1, signals2, messagesDict1, messagesDict2, (badefs1, badefs2), (dbc1,dbc2), merge_log_name)

    print(signals1[1])

    # create dbc
    fhd = open(merge_log_name,'a')
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('creating dbc with name: %s'%new_dbc_name)
    createDBC(signalsAll, messagesDictAll, headerlines1, badefs, new_dbc_name)
    fhd.write(' ... done')
    fhd.close()

