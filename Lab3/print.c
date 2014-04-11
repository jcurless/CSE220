//
//  print.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//
//	Phillip Day, Jackson Curless, Dylan Coyle

#include "print.h"


const char* const SYMBOL_STRINGS[] =
{
    "<no token>", "<IDENTIFIER>", "<NUMBER>", "<STRING>",
    "^","*","(",")","-","+","=","[","]",":",";",
    "<",">",",",".","/",":=","<=",">=","<>","..",
    "<END OF FILE>", "<ERROR>",
    "AND","ARRAY","BEGIN","CASE","CONST","DIV","DO","DOWNTO",
    "ELSE","END","FILE","FOR","FUNCTION","GOTO","IF","IN",
    "LABEL","MOD","NIL","NOT","OF","OR","PACKED","PROCEDURE",
    "PROGRAM","RECORD","REPEAT","SET","THEN","TO","TYPE","UNTIL",
    "VAR","WHILE","WITH",
};

static int line_count = 0;
static void print_page_header(char source_name[], char date[]);

void print_line(char line[], char source_name_to_print[], char date_to_print[])
{
    	char save_ch;
	char *save_chp = NULL;
    	if(line_count == 0)
    	{
		print_page_header(source_name_to_print, date_to_print);
		++line_count;
	}
    	if(line_count > MAX_LINES_PER_PAGE)
    	{
	 	print_page_header(source_name_to_print, date_to_print);
        	line_count = 1; //start line count over after printing new header
	}
    	if (strlen(line) > MAX_PRINT_LINE_LENGTH)
    	{
        	save_chp = &line[MAX_PRINT_LINE_LENGTH];
	}
    	if (save_chp)
    	{
        	save_ch = *save_chp;
        	*save_chp = '\0';
    	}
    	printf("%s", line);
    	++line_count; //increase line count
    	if (save_chp)
	{
        	*save_chp = save_ch;
    	}
}

static void print_page_header(char source_name[], char date[])
{
    static int page_number = 0;

    putchar(FORM_FEED_CHAR);
    printf("Page    %d  %s  %s\n\n", ++page_number, source_name, date);
}

void print_token(Token *the_token)
{
	printf("    >> %-17s%s\n", SYMBOL_STRINGS[the_token->coder], the_token->str1); //print the token using the SYMBOL_STINGS table
	line_count++; //increase line count
}
