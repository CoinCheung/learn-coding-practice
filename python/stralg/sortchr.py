#!/usr/bin/python
#filename: sortchr.py


from __future__ import division
import os
import string


text=''.join([line.rstrip() for line in open('mess.txt').read()])

def method1(text):
	s=filter(lambda x: x in string.letters,text)
	print s

def method2(text):
	occ={} #an empty dictionary
	for ch in text:
		occ[ch]=occ.get(ch,0)+1 #get the number of ch from the dictionary. if ch not in the dictionary, get 0
	avgoc=len(text)//len(occ) #'//' is the division of integers
	print occ
	print ''.join([c for c in occ if occ[c]<avgoc])

if __name__=='__main__':
	print'method through filter:'
	method1(text)
	print ''

	print'method through dictionary:'
	method2(text)
