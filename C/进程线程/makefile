CC = gcc
CFLAGS = -Wall -g -c
LFLAGS = -lpthread 
COBJS = test_thread.o

test_thread: test_thread.o
	$(CC) $(LFLAGS) $(COBJS) -o test_thread

test_thread.o: test_thread.c
	$(CC) $(CFLAGS) test_thread.c -o test_thread.o
