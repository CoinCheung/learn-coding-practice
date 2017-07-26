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

fork: forktest.o
	gcc forktest.o -o fork

forktest.o: forktest.c
	gcc -c -g forktest.c -o forktest.o

clean:
	rm -rif *.o dd
