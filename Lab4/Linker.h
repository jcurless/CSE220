/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#ifndef _Lab4_Linker_h
#define _Lab4_Linker_h

#include <iostream>
#include "common.h"
using namespace std;

class Linker {

private:
	int line;
	Linker *nextLine;
	Linker *current;

public:
	Linker();
	~Linker();
	void addToList(int newLine);
	void printList();
	void Ldeleter();
	void set(int line_number);
	/* for testing */
	Linker* getNext();
	int getLine();
};

#endif
