#!/usr/bin/python3
# -*- coding: utf-8 -*-
# filename: cmp004.py

'''
* fix the value changes of siglist1 and siglist2 when compareSignalsList(siglist1, siglist2) is called
* add merge() function, to merge information from two DBCs
* add the feature of creating log file
* modify writeResult() and createDBC() so that the name of logfile and new DBC could be assigned
* add copy.deepcopy() to protect the original information read from the DBCs from being disturbed by calculation
* modify the interaction lines printed to the screen
* refine the comments
*
* modify the dbc names in the main entrance, and two files will be created, one is the merged DBC, the other is the log of the process
'''


#============================================================#
# modules imported
#
#============================================================#

import os
import codecs
import copy


#============================================================#
# function definitions
#
#============================================================#

####
## function: signals,messagesDict, headerlines,badefs = readSignals(filename)
##
## read the signals information from DCB file, and put different information to different units
##
## input: name of the input DBC file
## return: return the common information such as the headlines, the fixed lines in the middle(BA_DEF = badefs), the list of signal dicts(sdict) and the list of message dicts(mdicts)
##
## sdict = {'signame': ,'startbit': ,'length': ,'factor': ,'offset': ,'messageID': ,'diffmode' ,'signal_line': ,'comment': ,'"GenSigWriteInterval"': ,'"GenSigPubLatency"': ,'"GenSigStartValue"': ,'values': },   the last 6 elements are all whole lines
## signals = [sdict1, sdict2, ...]
## mdict = {'message_line': ,'signal_index': ,'GenMsgSendType': ,'GenMsgCycleTime':, 'GenMsgDelayTime': },  where signal_index = [], the last 3 elements are whole lines
## messagesDict = {'messageID1': mdict1, 'messageID2': mdict2, ...}
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
## function: createDBC(signals, messagesDict, headlines, badefs, dbcname)
##
## write all the information to a new file to create a new DBC file
##
## input: list of sdicts, dict of mdicts over their messageID, the invariable head lines, and the invariable middle BA_DEF lines, the name of the new DBC file to be created
## return: none
##
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


####
## function: sigals1 ,signals2 = compareSignalLists(siglist1, siglist2)
##
## compare two signal collections and return the different part that the other does not have
##
## input: list of sdict got from DBC1 and DBC2
## return: list of sdict in singals1 while not in signals2, list of sdict in singals2 while not in signals1
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


####
## function: ret = compareSignals(sig1,sig2):
##
## compare two signal collections and return the difference number
##
## input: signal collection1, signal collection2
## return: the difference number: 1-exactly same, 2-messageID different, 3-startbit different, 4-length different, 5-factor different, 6-offset different
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
## write the name of uncommon signals and conflict signals to the log file
##
## input: list of signal dicts that dbc1 has while dbc2 does not have, list of signal dicts that dbc2 has while dbc1 does not have, dbc1 file name, dbc2 file name
## return: none
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


####
## function: signalAll, messagesDictAll = merge(signals1, signals2, messagesDict1, messagesDict2, dbcnames, logname)
##
## merge the two signal lists and message dicts to one each
##
## input: lists of sdicts of dbc1 and dbc2,
## return: merged list of sdicts got from dbc1 and dbc2, merged dict of mdicts got from dbc1 and dbc2
def merge(sigs1, sigs2, msg1, msg2, dbcnames, logname):
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
    fhd.close()

    return sigbase, msgbase


#============================================================#
# entrance of the script
#
#============================================================#
if __name__ == '__main__':
    dbc1 = 'AS26HYB.dbc'
    dbc2 = 'AS24_HYB.dbc'
    new_dbc_name = 'test_dbc_output004.dbc'
    merge_log_name = 'test_diff_out004.log'

    signals1,messagesDict1, headerlines1,badefs1 = readSignals(dbc1)
    signals2,messagesDict2, headerlines2,badefs2 = readSignals(dbc2)

    signalsAll, messagesDictAll = merge(signals1, signals2, messagesDict1, messagesDict2, (dbc1,dbc2), merge_log_name)

    print(signals1[1])

    # create dbc
    fhd = open(merge_log_name,'a')
    for i in range(30):  # separator
        fhd.write('==')
    fhd.write(os.linesep)
    fhd.write('creating dbc with name: %s'%new_dbc_name)
    createDBC(signalsAll,messagesDictAll, headerlines1,badefs1, new_dbc_name)
    fhd.write(' ... done')
    fhd.close()

    print(len(signals1))
