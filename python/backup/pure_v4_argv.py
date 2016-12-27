#!/usr/bin/python
#filename:pure_v4_argv.py

import sys
import os


option={'-v','-zip','-tar','-p'}# the options of the command line

###############################################
#check if the options are entered and if the options are correct
###############################################

#check if there is options assigned
if len(sys.argv)==1:
	print 'options should be assigned!!'
	os._exit(0)

#check if the options are correct
flag=0
for op in option:
	if op==sys.argv[1]:
		flag=1
		break
	else:
		pass

if not flag==1:
	print 'there is not such options as',sys.argv[1]
	os._exit(0)
	
###############################################
#option: -v
#inquiry the version 
###############################################
if sys.argv[1]=='-v':
	if len(sys.argv)!=2: #check if their are redundant parameter
		print"cannot identify the parameter:'"
		for token in sys.argv[2:]:
			print token,
			print "'"
			os._exit(0)
	print "version is: 4.0"

###############################################
#option: -p
#change the path of backup files, not accessible
###############################################
elif sys.argv[1]=='-p':
	import FuncData
	
	if len(sys.argv)==2:
		pth=os.path.expanduser(raw_input('enter the abstract path you would like the the backup to stored-->'))
		if not os.path.exists(pth):
			print' the path assigned does not exists:\n',pth
			os._exit(0)
		else:
			FuncData.setbackupdir(pth)
			print 'the target path:'
			print pth
			print' is reset successfully!\n'
	else:
		pass
###############################################
#option: -zip
#scenario that the files are compressed with zip
###############################################
elif sys.argv[1]=='-zip':
	#check if the files to be backed up is assigned
	if len(sys.argv)<3:
		print 'the files to be backed up are not assigned'
		os._exit(0)

	#check if all the files are available
	for pth in sys.argv[2:]:
		if not os.path.exists(pth):
			print'the file does not exists: \n',pth
			os._exit(0)
	
	import back_zip
	back_zip.compress(sys.argv[2:])

###############################################
#option: -tar
#scenario that the backup implemented with tar
###############################################
elif sys.argv[1]=='-tar': 
	#check if the files to be backed up is assigned
	if len(sys.argv)<3:
		print 'the files to be backed up are not assigned'
		os._exit(0)

	#check if all the files are available
	for pth in sys.argv[2:]:
		if not os.path.exists(pth):
			print'the file does not exists: \n',pth
			os._exit(0)
	
	import back_tar
	back_tar.compress(sys.argv[2:])
	
###############################################
#other options
###############################################
else:
	print 'wrong parameters!!'

