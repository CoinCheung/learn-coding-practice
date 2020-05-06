#!/usr/bin/python
#filename:FuncData.py


import os
import time
import cPickle as pickle

#############################################
#the first time to run
#establish the target data file, and write the original storage directory
#############################################
currentpath=os.getcwd()
dirfile=currentpath+os.sep+'dir.dat'

flag=os.path.exists(dirfile)
if not flag:
	target_dir=os.path.abspath('backup'+os.sep)
	f=open(dirfile,'wb')
	pickle.dump(target_dir,f,True)	
	f.close()
###############################################

f=open(dirfile,'rb')
target_dir=pickle.load(f)
f.close()

#allow the user to make comments on the backup, the comments will be contained in the backup file name
def EnterComments(): 
	comment=raw_input('enter the comments of the backup,default none-->')
	return comment


#return the backup target directory
def BuildTargets(comments):
	today=time.strftime('%Y%m%d')
	file=open(dirfile,'rb')
	target_dir=pickle.load(file)
	file.close()
	path=target_dir+os.sep+today
	
	if not os.path.exists(path):
		print 'create the directory',today
		os.system('mkdir '+path)

	if len(comments)==0:
		target=path+os.sep+time.strftime('%Y%m%d%H%M%S')+'.zip'
	else:
		target=path+os.sep+time.strftime('%Y%m%d%H%M%S')+'-'+comments.replace(' ','_')+'.zip'

	return target

#find the line with the string 'orignal', and replace it with a new line
def modifyline(filetitle,original,new):
	try:
		lines=open(filetitle,'r').readlines()
		linenum=len(lines)
		for i in range(0,linenum):
			if original in lines[i]:
				lines[i]=lines[i].replace(original,new)

		open(filetitle,'w').wirtelines(lines)
	except Exception,e:
		print e

#set the storage directory of the backup
def setbackupdir(pth):
	f=open(dirfile,'wb')
	pickle.dump(pth,f,True)
	f.close()
