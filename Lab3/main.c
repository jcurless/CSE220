//
//  main.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//
//	Phillip Day, Jackson Curless, Dylan Coyle

#include <stdio.h>
#include "common.h"
#include "print.h"
#include "scanner.h"

FILE *init_lister(const char *name, char source_file_name[], char dte[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);

int main(int argc, const char * argv[])
{
    
   Token *token;
   Token *token_list = create_tok(); //This needs to be implemented as a linked list in scanner.h.
   char source_name[MAX_FILE_NAME_LENGTH];
   char date[DATE_STRING_LENGTH];
   FILE *source_file = init_lister(argv[1], source_name, date);
   init_scanner(source_file, source_name, date);
    
   do
   {
        token = get_token(); //get the Token
        add_token_to_list(token_list, token); //add the Token to the list
        print_token(token);		//print the token
   }while(!feof(source_file));//The sentinel value that ends the loop is "."

   quit_scanner(source_file, token_list); //clear the list
    
   return 0;
}

void add_token_to_list(Token *list, Token *new_token)
{
    //Add new_token to the list knowing that list is a linked list.
    	Token *end = list; 
    	while(end->next != NULL)
    	{
		end = end->next; 
	}
	end->next = new_token; //add Token to the end of the list 
}

void quit_scanner(FILE *src_file, Token *list)
{
    //write code to free all of the memory for the token list
	
	//added by group 3/13
	Token* clear = list;
	fclose(src_file);	//close the source file
	while(list->next != NULL)
	{
		list = list-> next;
		free_tok(clear);				//free the Token
	}
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
