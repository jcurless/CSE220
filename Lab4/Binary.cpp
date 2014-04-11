/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#include "Binary.h"

Binary::Binary()
	{
  		root = NULL; //constructs a root
	}
Binary::~Binary()
	{
  		destroy();//calls to delete the tree when finished
	}

void Binary::destroy()
	{
		destroyer(root);//clears out the tree
	}

void Binary::add(Token *token, int line)
	{
		if(root != NULL)//there are already tokens on the tree
			{
				if(token != NULL)
					{
						adder(token, root, line); //Calls for the logic of where to add the new token and adds it
					}
			}
		else//when the first token is being added to the tree
			{
				root = token;
				root->setLeftChild(NULL);//sets up the space for child tokens
				root->setRightChild(NULL);
			}
	}//close add

void Binary::print()
	{
		printer(root);//print the tree part of the output
	}

void Binary::adder(Token *token, Token *Noder, int line)//does the "dirty work" of adding another token
	{
		string first = token->getTokenString();//grabs the first string
		string second = Noder->getTokenString();//grabs the second string
		if(first.compare(second) < 0) //if it is greater
			{
				if(Noder->getLeftChild() != NULL)//if there is something in the left child
					{
						adder(token, Noder->getLeftChild(), line);//send the string through
					}
				else
					{
						Noder->setLeftChild(token);
						Noder->getLeftChild()->setLeftChild(NULL);
						Noder->getLeftChild()->setRightChild(NULL);
					}
			}
		else if(first.compare(second) > 0)//if it is less than
			{
				if(Noder->getRightChild() != NULL)
					{
						adder(token, Noder->getRightChild(), line);
					}
				else
					{
						Noder->setRightChild(token);
						Noder->getRightChild()->setLeftChild(NULL);
						Noder->getRightChild()->setRightChild(NULL);
					}
			}
		else if(first.compare(second) == 0)
			{
				Noder->setList(line);//only add the line number, but discard the excess token
				delete token;
			}
	}//close adder


void Binary::destroyer(Token *Noder)//supplements the destroy function; keeps track of our place
	{
		if(Noder != NULL)
			{
				destroyer(Noder->getLeftChild());
				destroyer(Noder->getRightChild());
				delete Noder;
			}
	}



void Binary::printer(Token *Noder)//supplement to print the tree
	{
		if(Noder != NULL)
			{
				printer(Noder->getLeftChild());
				printf("%s\t\t\t",Noder->getTokenString().c_str() );
				Noder->getList().printList();
				cout<<"\n";
				printer(Noder->getRightChild());
			}
	}


