all: dd

dd:dd.o header.o
	g++ dd.o header.o -o dd

test: test.o header.o
	gcc header.o test.o -o test

test.o: test.c
	gcc -c -g test.c  

dd.o:dd.cpp
	g++ -c -g dd.cpp -o dd.o

header.o: header.c
	gcc -c -g header.c -o header.o


clean:
	rm -rif *.o dd
