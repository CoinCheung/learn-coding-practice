CC = gcc
OBJs = main.o
CFLAG = -c -g -std=c99

main: main.o shell
	$(CC) $< -o $@

main.o: main.c
	$(CC) $(CFLAG) $< -o $@

shell: shell.c
	$(CC) $< -o $@

clean:
	rm main.o shell.o main shell


