#!/usr/bin/python3
#filename: getshortname.py
## write for MengHaotian, help him read the signal names and get rid of the postfix as '_h6HSC6' '_h6' 'HSC6' '_h6HSC1' '_h1' 'HSC1'


import os
import codecs

def readSignals(filename):
    signals = []

    file = codecs.open(filename,encoding = 'latin1')
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

        elif linelist[0] == '' and len(linelist) != 1 and linelist[1] == 'SG_':  # if the line is a signal descriptor
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




## function: sig_shortname_list = get_signal_shortname(signals)
## read the list of the signal dictionaries, get their names and remove the postfixes such as '_h6HSC6' '_h6' 'HSC6' '_h6HSC1' '_h1' 'HSC1'
## the return is a list of the short names
##
def get_signal_shortname(signals):
    shortnames = []
    for el in signals:
        name = el['signame']
        #  print(name[-4:-1])
        if name[-7:] == '_h6HSC6' or name[-7:] == '_h1HSC1':
            name = name[0:-7]
        elif name[-4:] == 'HSC1' or name[-4:] == 'HSC6':
            name = name[0:-4]
        elif name[-3:] == '_h6' or name[-3:] == '_h1':
            name = name[0:-3]
        shortnames.append(name)

    return shortnames

###
###
###

def write_short_names(resname, shortname):
    fhd = open(resname, 'w')
    for el in shortname:
        fhd.write(el)
        fhd.write(os.linesep)
    fhd.close()




if __name__ == '__main__':
    resname1 = 'result_DBC_shortname1.txt'
    resname2 = 'result_DBC_shortname6.txt'


    fname1 = './AS23P/V01.dbc'
    fname2 = './AS23P/HSC6.dbc'
    signals1 = readSignals(fname1)
    signals2 = readSignals(fname2)

    #  print(signals1)
    #  print(shortname2)

    shortname1 = get_signal_shortname(signals1)
    shortname2 = get_signal_shortname(signals2)

    #  print(shortname1)
    #  print(shortname2)

    write_short_names(resname1, shortname1)
    write_short_names(resname2, shortname2)


