#!/usr/bin/python
#filename:printFunClss.py

#in this instance the functions and classes are printed


def function(x,y):
	'A function written randomly
	if x>y:
		pass
	else:
		pass


class myClass:
	def __init__(self,x):
		if x==1:
			print' the input is 1, bitch!!'
		else:
			print' the input is not 1, bitch!!'

	def func(self):
		print'hello world, fuck you whore!!'
	pass


myObj=myClass(1)
myObj.func()

print'the function is printed',function

print' the class is printed',myClass
