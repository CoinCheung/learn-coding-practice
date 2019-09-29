#!/usr/bin/python
#Filename='AbstractClass.py'

import abc

# The base class
class AbstractBase(object):
    __metaclass__=abc.ABCMeta

    def method1(self):
        print 'this is method 1 of the Abstract Base'

    @abc.abstractmethod
    def method2(self):
        pass

    @abc.abstractmethod
    def method3(self):
        print 'now it is in abstract method 3'
        self.method2()
        print 'now abstract method3 is over'


# The registered subclass
class RegisterSubClass(object):

    var=9

    def method2(self,input):
        self.var2=1009
        print input

    def method3(self):
        print 'now it is in abstract method 3'
        self.method2('aoaoao')
        print 'now abstract method3 is over'

AbstractBase.register(RegisterSubClass)


# The successor subclass
class ImplementedSubClass(AbstractBase):
    def method2(self,input):
        print input

    def method3(self):
        print'this is method3 in the class of ImplementedSubClass'

if __name__=='__main__':
    in_A=raw_input('input something:')

    print 'the registered subclass'
    sub=RegisterSubClass()
    print issubclass(RegisterSubClass,AbstractBase)
    print isinstance(RegisterSubClass(),AbstractBase)
#    sub.method1()
    sub.method2(in_A)
    sub.method3()

    print RegisterSubClass.var
    sub.var=3
    print RegisterSubClass.var
    print sub.var2

#    print 'the implementation of the base'
#    print issubclass(ImplementedSubClass,AbstractBase)
#    print isinstance(RegisterSubClass(),AbstractBase)
#    imsub=ImplementedSubClass()
#    imsub.method1()
#    imsub.method2(in_A)
#    imsub.method2()
