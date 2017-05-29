#!/usr/bin/python
#filename: strtrans.py


import string

#----------------------------------------#
#method name: strtrans()
#maketrans(from,to) returns a table to reflect
#the map relationshiop between two strings 'from'
#and 'to' which are of the same length
#----------------------------------------#
def strtrans(text):
	table=string.maketrans(string.ascii_lowercase,string.ascii_lowercase[2:]+string.ascii_lowercase[0:2])

	return string.translate(text,table)

#------------------------------------------#
#main
#scenario that the script is not imported
#------------------------------------------#
if __name__=='__main__':
	txt="""g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."""

	print strtrans(txt)
