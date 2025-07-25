assembler: assembler.o
	gcc -Wall -ansi -pedantic assembler.o -o assembler

assembler.o: assembler.c crud.c
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o


