/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#include "Linker.h"

Linker::Linker()
	{
		line = 0;
		nextLine = NULL;
	}
Linker::~Linker(){}
void Linker::addToList(int newLine)
	{
		Linker *current;
		Linker *previous;
		Linker *newNode = new Linker;
		newNode->line = newLine;
		previous = NULL;
		if(this->nextLine == NULL)
			{
				this->nextLine = newNode;
			}
		else
			{
				current = this;
				while(current != NULL)
					{
						previous = current;
						current = current->nextLine;
					}
				previous->nextLine = newNode;
				newNode->nextLine = current;
			}
	}

void Linker::printList()
	{
		Linker *current;
		current = this;
		while(current != NULL)
			{
				printf("%d\t", current->line);
				current = current->nextLine;
			}
	}

void Linker::Ldeleter()
	{
		Linker *temp;
		temp = NULL;
		while(this->nextLine != NULL)
			{
				temp = this->nextLine;
				this->nextLine = temp->nextLine;
				delete temp;
			}
	}

void Linker::set(int line_number)
{
this->line = line_number;
}

Linker* Linker::getNext() {
return this->nextLine;
}

int Linker::getLine() 
{
return this->line;
}
