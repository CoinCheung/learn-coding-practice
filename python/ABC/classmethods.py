#! /usr/bin/python
#================================================#
# FileName: classmethods.py
# Used to verify the usage of different sorts of methods
#================================================#


class myclass(object):
    a=3
    def __init__(self):
        self.b=4
        pass

    def method1(self):
        print 'instance method'
        print 'a=',myclass.a,' b=',self.b

    @classmethod
    def method2(cls):
        print 'class method of base'
        print 'cls.a=',cls.a,' myclass.a=',myclass.a

    @staticmethod
    def method3():
        print'static method without args'

class subclass1(myclass):
    @staticmethod
    def method2():
        print 'class method overwirten as instance method'
    @classmethod
    def method3(cls):
        print 'static method2 is overwritten as instance method'


if __name__ == '__main__':
    obj=myclass()
    obj.method1()
    obj.method2()
    myclass.method2()
    obj.method3()
    myclass.method3()

    sc=subclass1()
    sc.method2()
    subclass1.method2()
    subclass1.method3()
    sc.method3()
