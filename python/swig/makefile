mymod.so:  wraptest.o test.o
	gcc -shared  wraptest.o test.o -o mymod.so

test.o: test.cpp 
	gcc  -g -fPIC test.c -o test.o

wraptest.o: mymod_wrap.c
	gcc  -fPIC mymod_wrap.c -I/usr/include/python3.6m  -o wraptest.o

mymod_wrap.c: mymod.i
	swig -python  mymod.i 

clean: 
	rm *.o *.cxx *.so
