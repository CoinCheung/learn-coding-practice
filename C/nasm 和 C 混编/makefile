out: Clan.o nasm.o
	ld  Clan.o nasm.o -o out

Clan.o: Clan.c
	gcc -g -c Clan.c -o Clan.o

nasm.o: nasm.asm
	nasm -F dwarf -g -f elf64 nasm.asm -o nasm.o

dd: dd.o
	ld dd.o -o dd

dd.o: dd.asm
	nasm -F dwarf -g -f elf64 dd.asm -o dd.o

clean:
	rm *.o out dd

