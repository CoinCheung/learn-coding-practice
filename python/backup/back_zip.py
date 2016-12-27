#!/usr/bin/python
#filename:back_zip.py


import FuncData
import os


#the structure of compres with argv a list,input is the list of the file paths
def compress(argv):
	comments=FuncData.EnterComments()
	target=FuncData.BuildTargets(comments)	

	command='zip -qr %s %s'%(target,' '.join(argv))
	errorcode=os.system(command)

	print '\n'

	if errorcode==0:
		print'the backup is accomplished successfully!!'
	else:
		print'the backup failed with errorcode',errorcode


