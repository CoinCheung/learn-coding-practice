
#!/usr/bin/python
#Filename:myModule.py

#import pdb

#pdb.set_trace()

if __name__ =='__main__':  # attention should be paid that double underscore is used instead single underscore
	print "the module 'myModule is running itself'"
else:
	print "the module 'myModule is imported'"

version=1.0

def sayhi():
	print "hello world by myModule.py"

sayhi()
