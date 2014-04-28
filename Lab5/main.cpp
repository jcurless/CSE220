// Phillip Day, Jackson Curless, Dylan Coyle
//
//  main.cpp
//  Lab5
//
//  Created by Bryce Holton.
//

#include <iostream>
#include "common.h"
#include "Print.h"
#include "Scanner.h"
#include "IdentifierBinaryTree.h"
#include "Scanner.h"
#include "Identify.h"

using namespace std;

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
    IdentifierBinaryTree tree;
    
    token = scanner.getToken();
    while (token->getCode() != PERIOD && token->getCode() != END_OF_FILE)
    {
        print.printToken(token);
        if (token->getCode() == IDENTIFIER)
        {
            tree.addIdentifier(dynamic_cast<Identify *>(token), scanner.getLineNumber());
        }
        else if (token != NULL)
        {
            delete token;
            token = NULL;
        }
        token = scanner.getToken();
    }
    delete token;
    token = NULL;
    
    print.printTree(tree.getTreeRoot());

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

