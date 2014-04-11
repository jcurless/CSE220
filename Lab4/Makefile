#CrossReference Makefile
#Dylan Coyle, Jackson Curless, Phillip Day

CrossReference: main.o Print.o Scanner.o Linker.o Token.o Binary.o 
	g++ main.o Print.o Scanner.o Linker.o Token.o Binary.o -o CrossReference

main.o: main.cpp
	g++ -c main.cpp

Print.o: Print.cpp
	g++ -c Print.cpp

Scanner.o: Scanner.cpp
	g++ -c Scanner.cpp

Linker.o: Linker.cpp
	g++ -c Linker.cpp

Token.o: Token.cpp
	g++ -c Token.cpp

Binary.o: Binary.cpp
	g++ -c Binary.cpp

