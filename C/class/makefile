CC = gcc
_OBJ = datastr.o
CFlags = -g -c

datastr: ./build/datastr.o
	$(CC) $< -o $@

./build/datastr.o: datastr.c
	$(CC) $(CFlags) $< -o $@

macro: ./macros_spread.c

./macros_spread.c: datastr.c
	$(CC) -E $< -o $@

try: try.o datastr.o
	$(CC) $^ -o $@

./build/try.o: try.c
	$(CC) $(CFlags) $^ -o $@

clean:
	rm ./build/* ./macros_spread.c try *.o
