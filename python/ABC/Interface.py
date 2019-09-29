#!/usr/bin/python
#FileName: Interface.py
#This script is the instance of using the Interfaces

import abc

class RunDevice:
    def method1(self):pass #definition must be followed by 'pass'
    def method2(self):pass

class Device(RunDevice):
    def __init__(self, name):
        self.name=name

    def method1(self,name): #if necessary args can be assigned to the method
        print 'the name is:'+name

    def method2(self):
        self.method1(self.name)

if __name__=='__main__':
    device=Device('aoaoao')
    device.method2()
