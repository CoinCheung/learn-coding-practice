#!/usr/bin/python
#filename:readfile.py

"this script is written to manifest the usage of python read file method"

#read all the data at one time
file=open("if.py")
all_txt=file.read()
print all_txt
file.close()


#read a portion data at one time
file=open("if.py")
while True:
	data=file.read(5).rstrip()
	if not data:
		break
	print data,
file.close()
print '\n'


#read assigned number of lines at one time
file=open("printFunClss.py")
while True:
	lines=file.readlines(1)
	print lines
	if not lines:
		break
	for token in lines:
		print token
file.close()

