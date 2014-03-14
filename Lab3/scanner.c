//
//  scanner.c
//  Lab3
//	
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//
//	Phillip Day, Jackson Curless, Dylan Coyle

#include <stdio.h>
#include "scanner.h"

/*******************
 Static functions needed for the scanner
 You need to design the proper parameter list and
 return types for functions with ???.
 ******************/
static char get_char(???);
static char skip_comment(???);
static char skip_blanks(???);
static ??? get_word(???);
static ??? get_number(???);
static ??? get_string(???);
static void get_special(*Token that_token);
static char* downshift_word(char downshift_string);
static BOOLEAN is_reserved_word(???);

typedef enum
{
    LETTER, DIGIT, QUOTE, SPECIAL, EOF_CODE,
}
CharCode;

/*********************
 Static Variables for Scanner
 Must be initialized in the init_scanner function.
 *********************/
static FILE *src_file;
static char src_name[MAX_FILE_NAME_LENGTH];
static char todays_date[DATE_STRING_LENGTH];
static CharCode char_table[256];  // The character table

static char* line_PTR = NULL; //global pointer to current line that is being evaluated

typedef struct
{
    char *string;
    TokenCode token_code;
}
RwStruct;

const RwStruct rw_table[9][10] = {
    {{"do",DO},{"if",IF},{"in",IN},{"of",OF},{"or",OR},{"to",TO},{NULL,0}}, //Reserved words of size 2
    {{"and",AND},{"div",DIV},{"end",END},{"for",FOR},{"mod",MOD},{"nil",NIL},{"not",NOT},{"set",SET},{"var",VAR},{NULL,0}}, //Reserved words of size 3
    {{"case",CASE},{"else",ELSE},{"file",FFILE},{"goto",GOTO},{"then",THEN},{"type",TYPE},{"with",WITH},{NULL,0}}, //Reserved words of size 4
    {{"array",ARRAY},{"begin",BEGIN},{"const",CONST},{"label",LABEL},{"until",UNTIL},{"while",WHILE},{NULL,0}},  //Reserved words of size 5
    {{"downto",DOWNTO}, {"packed",PACKED},{"record",RECORD}, {"repeat",REPEAT},{NULL,0}},  // Reserved words of size 6
    {{"program", PROGRAM},{NULL,0}}, // Reserved words of size 7
    {{"function", FUNCTION},{NULL,0}}, // Reserved words of size 8
    {{"procedure", PROCEDURE},{NULL,0}}  // Reserved words of size 9
};

void init_scanner(FILE *source_file, char source_name[], char date[])
{
    src_file = source_file;
    strcpy(src_name, source_name);
    strcpy(todays_date, date);

	//added by group 3/13
	for(i = 0; i < 256; i++) 
	{
    	//the LETTERS
    	if( (i>65 && i<92) || (i>97 && i<124) ) 
		{
    		char_table[i] = LETTER;
    	}
    	//the DIGITS
    	else if(i>48 && i<59) 
		{
    		char_table[i] = DIGIT;
    	}
    	//SPECIAL
    	else 
		{
    		char_table[i] = SPECIAL;
    	}
    }
    /*******************
     initialize character table, this table is useful for identifying what type of character
     we are looking at by setting our array up to be a copy the ascii table.  Since C thinks of
     a char as like an int you can use ch in get_token as an index into the table.
     *******************/
	char_table[16] = QUOTE;
	char_table[20] = EOF;

}

BOOLEAN get_source_line(char source_buffer[])
{
    char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
//    char source_buffer[MAX_SOURCE_LINE_LENGTH];  //I've moved this to a function parameter.  Why did I do that?
    static int line_number = 0;

    if (fgets(source_buffer, MAX_SOURCE_LINE_LENGTH, src_file) != NULL)
    {
        ++line_number;
        sprintf(print_buffer, "%4d: %s", line_number, source_buffer);
        print_line(print_buffer, src_name, todays_date);
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}

Token* get_token()
{
    char ch; //This can be the current character you are examining during scanning.
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr = token_string; //write some code to point this to the beginning of token_string
    Token *token;
	CharCode coder;
    
    //find the token type, token code, and the literal, then initialize it as a Token, then...
    ch = *line_PTR;
    int looper = FALSE;
	get_char(ch);

    //1.  Skip past all of the blanks and comments
	do
	{
		if(ch == ' ')
		{
			skip_blanks(ch);

			if(ch == '\0')
			{
				looper = TRUE;
				get_char(ch);
			}
		}
		if(ch == '{')
		{
			looper = TRUE;
			ch = skip_comment(ch);
			get_char(ch); //get char again to see what current char is because it could be space or comment again
		}
		else
		{
			looper = FALSE;
		}
	}while(looper);


	//now know that it is not comment block or space
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
	coder = char_table[ch];

    //3.  Call the appropriate function to deal with the cases in 2.
	if(coder == LETTER)
	{
		get_word(token_string, &token);
	}
	else if(coder == DIGIT)
	{
		get_number(ch);
	}
	else if(coder == QUOTE)
	{
		get_string(ch);
	}
	else
	{
		get_special(&token);
	}
    return token;
}

static char get_char(char source_buffer[]) //might have to rewrite this function
{
    static int cur_pos = 0;
    /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */
    if (source_buffer[cur_pos] == '\0') 
	{
        if (!get_source_line(source_buffer)) 
		{
            return EOF;
        }
        cur_pos = 0;
    }
    return source_buffer[cur_pos++];
    /*
     Write some code to set the character ch to the next character in the buffer
     */
}

static char skip_blanks(char *char_PTR)
{
    /*
     Write some code to skip past the blanks in the program and return a pointer
     to the first non blank character
     */
	while(*line_PTR == ' ' && *line_PTR != '\0')
	{
		line_PTR++;
	}
	*char_PTR = *line_PTR;
	return *char_PTR;
}

static char skip_comment(char cur_char)
{
	while(cur_char != '}')
	{
		if(cur_char == '\0')
		{
			get_char(cur_char);
		}
		else
		{
			line_PTR++;
			cur_char = *line_PTR;
		}
	}
	line_PTR++;

	cur_char = *line_PTR;
	return cur_char;
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
     */
}

static ??? get_word(???)
{
    /*
     Write some code to Extract the word
     */

    //Downshift the word, to make it lower case

    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */
}
static ??? get_number(???)
{
    /*
     Write some code to Extract the number and convert it to a literal number.
     */
}
static ??? get_string(???)
{
    /*
     Write some code to Extract the string
     */
}
static void get_special(Token *that_token)
{
	char const *that_ptr = SYMBOL_STRINGS + 5; //symbol pointer

	int sym_code;
	for(i=5; i <= 20; i++)
	{
		if(strcmp(line_PTR, that_ptr) == 0)
		{
			if(*(line_PTR + 1) == '=' && *line_PTR == ':')
			{
				sym_code = 21;
				line_PTR += 2;
				break;
			}
			else if(*(line_PTR + 1) == '=' && *line_PTR == '<')
			{
				sym_code = 22;
				line_PTR += 2;
				break;
			}
			else if(*(line_PTR +1) == '=' && *line_PTR == '>')
			{
				sym_code = 23;
				line_PTR += 2;
				break;
			}
			else if(*(line_PTR + 1) == '>' && *line_PTR == '<')
			{
				sym_code = 24;
				line_PTR += 2;
				break;
			}
			else if(*(line_PTR + 1) == '.' && *line_PTR == '.')
			{
				sym_code = 25;
				line_PTR += 2;
				break;
			}
			else
			{
				line_PTR++;
				sym_code = i;
				break
			}
		}
		line_PTR++;
	}
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
}
static char* downshift_word(char downshift_string)
{
	int i;
	int len = strlen(downshift_string);
	printf("%i\n", len);
	for(i=0; i < len; i++)
	{
		downshift_string[i] = tolower(downshift_string[i]);
	}
	return downshift_string;

    /*
     Make all of the characters in the incoming word lower case.
     */
}
static BOOLEAN is_reserved_word(char const *rwPtr)
{
    //added by group 3/13
	char *rw_table_PTR = rw_table;
	for(int i=0; i<=9; i++)
	{
		for(int j=0; j<=10; j++)
		{
			rw_table_PTR = &rw_table[i][j];
			if(strcmp(rwPtr, rw_table_PTR->string) == 0)
			{
				return TRUE;
			}
		}
	}
	/*
     Examine the reserved word table and determine if the function input is a reserved word.
     */
    return FALSE;
}
