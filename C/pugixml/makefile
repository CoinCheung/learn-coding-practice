CC = g++
CFLAGS = -c -g -I/usr/local/include

try: try.o
	$(CC) try.o -o try

try.o: try.cpp
	$(CC) $(CFLAGS) try.cpp -o try.o
	

clean:
	rm try try.o
