all: server client
.PHONY: all 

cc = gcc
cflags = -c -g

server: server.o
	$(cc) server.o -o server

server.o: server.c
	$(cc) $(cflags) serverbak.c -o server.o

client: client.o
	$(cc) client.o -o client

client.o:client.c
	$(cc) $(cflags) clientbak.c -o client.o

clean:
	rm *.o server client
