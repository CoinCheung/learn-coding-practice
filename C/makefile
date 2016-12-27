all: dd

dd:dd.o
	g++ dd.o -o dd

dd.o:dd.cpp
	g++ -c -g dd.cpp -o dd.o

clean:
	rm -rif *.o dd
