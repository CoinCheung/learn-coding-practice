CC = gcc
CFLAG = -g -c -std=c99
ODIR = ./build
_OBJs = bignumber.o test.o
OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))

main: $(OBJs)
	$(CC) $^ -o $@

$(ODIR)/%.o: %.c 
	$(CC) $(CFLAG) $< -o $@

clean:
	rm $(ODIR)/* test main
