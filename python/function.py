#!/usr/bin/python
#filename:function.py


def sayhello():
	print "hello world"

def telltrue(b):
	if b==True:
		print "b is",b
	else:
		print "b is",False


sayhello()

a=True
telltrue(a)
telltrue(not a)

#####################################

def withReturn():
	pass

print withReturn


def max(a,b=0):
	if a>b:
		return a
	else:
		return b

res=max(a=5)
print res
