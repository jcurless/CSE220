#Assignment 2 Makefile
#Dylan Coyle, Jackson Curless, Phillip Day

Assignment2: Assignment2.o
	gcc -o Assignment2 Assignment2.o

Assignment2.o: Assignment2.c
	gcc -c -o Assignment2.o Assignment2.c
