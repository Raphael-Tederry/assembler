assembler: assembler.o lines_container.o  
	gcc -Wall -ansi -pedantic assembler.o lines_container.o -o assembler

assembler.o: assembler.c pre_assembly.c lines_container.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o

lines_container.o: lines_container.c lines_container.h
	gcc -c -Wall -ansi -pedantic lines_container.c -o lines_container.o



clean:
	rm -f *.o assembler


