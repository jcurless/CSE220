/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day

*Program Description: main.cpp
*Takes a file containing text as a parameter. Opens the file and creates a new Scanner object to iterate
*through the file line by line tokenizing the text. A pointer to the new token is returned from Scanner
*and its type is checked to see if it is an identifer. If it is an identifer, the binary tree object determines
*where in the tree it should be placed based on alphabetical precedence. If the token is not an identifer
*it is deleted by called in the deconstructor and freeing the memory. When a period '.' is reached, signifying
*the end of file, the binary tree is printed and each token is deleted. Then the final period token is deleted
*and the source file is closed.
*
*Created by Bryce Holton.
*
*/


#include <iostream>
#include "common.h"
#include "Print.h"
#include "Scanner.h"
#include "Token.h"
#include "Binary.h"
#include "Linker.h"

FILE *init_lister(const char *name, char source_file_name[], char dte[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);

int main(int argc, const char * argv[])
{
    Token *token = NULL;
    char source_name[MAX_FILE_NAME_LENGTH];
    char date[DATE_STRING_LENGTH];
    FILE *source_file = init_lister(argv[1], source_name, date);
    Print print(source_name, date);
    Scanner scanner(source_file, source_name, date, print);
    Binary tree;

    do
    	{
        	token = scanner.getToken();
        	print.printToken(token);
        	if (token->getCode() != PERIOD && token->getCode() != END_OF_FILE)//check if the token is not def. garbage
        		{
            		if(token->getCode() == IDENTIFIER)//check if it's an identifier
            			{
                			tree.add(token, scanner.getLineNumber());//if so, add it to the tree
            			}
            		else delete token;//otherwise it is garbage and must be banished forthwith
        		}
    	}
    while (token->getCode() != PERIOD && token->getCode() != END_OF_FILE);//keeps the loop going until a sentinel value

    //**housekeeping**
    print.printReferenceHeader();
    tree.print();
    delete token;
    fclose(source_file);
    return 0;
}
FILE *init_lister(const char *name, char source_file_name[], char dte[])
{
    time_t timer;
    FILE *file;

    strcpy(source_file_name, name);
    file = fopen(source_file_name, "r");
    time(&timer);
    strcpy(dte, asctime(localtime(&timer)));
    return file;
}

