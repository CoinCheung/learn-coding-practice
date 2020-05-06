libtest.so: libtest.o
	g++ -shared -o libtest.so libtest.o 

libtest.o: libtest.cpp
	g++ -c -g -fPIC libtest.cpp -o libtest.o 

test: test.c
	gcc -g test.c -o test

clean:
	rm *.o *.so
