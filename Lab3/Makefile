#Lexer Makefile
#CSE 220
#Jackson Curless
#Dylan Coyle
#Phillip Day

Lexer: main.o print.o scanner.o
	gcc main.o print.o scanner.o -o Lexer

main.o: main.c
	gcc -c main.c

print.o: print.c
	gcc -c print.c

scanner.o: scanner.c
	gcc -c scanner.c
