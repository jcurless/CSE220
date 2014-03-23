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
#include <ctype.h>



/*******************
 Static functions needed for the scanner
 You need to design the proper parameter list and
 return types for functions with ???.
 ******************/
static char get_char();
static int skip_comment();
static int skip_blanks(char *stringer);
static TokenCode get_word(char *stringer);
static double get_number();
static void get_string(char *stringer);
static TokenCode get_special(char *stringer);
static void downshift_word(char *da_word);
static BOOLEAN is_reserved_word(char *da_word, TokenCode* coder);

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

static char src_line[MAX_SOURCE_LINE_LENGTH]; //source line currently investigating
static int index_line;						  //index of the source line


typedef struct
{
    char *string;
    TokenCode token_code;
}
RwStruct;

//table with special characters
const RwStruct special_table[] = {
    {"^",UPARROW},{"*",STAR},{"(",LPAREN},{")",RPAREN},{"-",MINUS},{"+",PLUS},{"=",EQUAL},{"[",LBRACKET},
    {"]",RBRACKET},{":",COLON},{";",SEMICOLON},{"<",LT},{">",GT},{",",COMMA},{".",PERIOD},{"/",SLASH},{NULL,0},
    {":=",COLONEQUAL},{"<=",LE},{">=",GE},{"<>",NE},{"..",DOTDOT},{NULL,0}
};

//table with reserved words
const RwStruct rw_table[9][10] = {
    {{"do",DO},{"if",IF},{"in",IN},{"of",OF},{"or",OR},{"to",TO},{NULL,0}}, //Reserved words of size 2
    {{"and",AND},{"div",DIV},{"end",END},{"for",FOR},{"mod",MOD},{"nil",NIL},{"not",NOT},{"set",SET},{"var",VAR},{NULL,0}}, //Reserved words of size 3
    {{"case",CASE},{"else",ELSE},{"file",FFILE},{"goto",GOTO},{"then",THEN},{"type",TYPE},{"with",WITH},{NULL,0}}, //Reserved words of size 4
    {{"array",ARRAY},{"begin",BEGIN},{"const",CONST},{"label",LABEL},{"until",UNTIL},{"while",WHILE},{NULL,0}},  //Reserved words of size 5
    {{"downto",DOWNTO}, {"packed",PACKED},{"record",RECORD}, {"repeat",REPEAT},{NULL,0}},  // Reserved words of size 6
    {{"program", PROGRAM},{NULL,0}}, /* Reserved words of size 7*/
    {{"function", FUNCTION},{NULL,0}}, /* Reserved words of size 8*/
    {{"procedure", PROCEDURE},{NULL,0}}  /* Reserved words of size 9*/
};

Token* create_tok() //create a new token
{
	Token* token1 = (Token*)malloc(sizeof(Token));
	token1->coder = NO_TOKEN;
	token1->str1 = (char*)malloc(MAX_TOKEN_STRING_LENGTH); //create token string of max length
	*token1->str1 = '\0';
	token1->next = NULL;
	return token1;
}

int free_tok(Token* the_token) //free the token
{
	if(the_token->next !=NULL)
	{
		return -1;
	}
	
	free(the_token->str1);   //free token string
	free(the_token);		// free token
	
	return 0;
}

void ch_table() //creates the char_table
{
	unsigned int j;
	
	const char special[] = "^*()-+=[]:;<>,./";  //special characters

	for(j = 0; j<256; ++j)
	{ 
		char_table[j] = EOF; 
	}

	for(j = 0; j<sizeof(special)-1; ++j)
	{
		char_table[special[j]] = SPECIAL;
	}	

	for (j = 'A'; j<='Z'; ++j)
	{
		char_table[j] = LETTER; //for uppercase letters
	}
	
	for (j = 'a'; j<='z';++j)
	{
		char_table[j] = LETTER; //for lowercase letters
	}
  
	char_table['_'] = LETTER; //underscore is a letter

	for (j = '0'; j<='9';++j)
	{
		char_table[j] = DIGIT;
	}

	char_table['\''] = QUOTE; //assign the quote

	char_table[EOF] = EOF_CODE; //assign end of file
}


void init_scanner(FILE *source_file, char source_name[], char date[])
{
    src_file = source_file;
    strcpy(src_name, source_name);
    strcpy(todays_date, date);
	index_line = 0;		//initialize index of the source line
	*src_line = '\0';   //initialize the source line
    /*******************
     initialize character table, this table is useful for identifying what type of character
     we are looking at by setting our array up to be a copy the ascii table.  Since C thinks of
     a char as like an int you can use ch in get_token as an index into the table.
     *******************/
	ch_table(); //create the char_table
}

BOOLEAN get_source_line(char source_buffer[])
{
    char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
//    char source_buffer[MAX_SOURCE_LINE_LENGTH];  //I've moved this to a function parameter.  Why did I do that?
    static int line_number = 0;

    if(fgets(source_buffer, MAX_SOURCE_LINE_LENGTH, src_file) != NULL) //if  there is a source line
    {
        ++line_number;
        sprintf(print_buffer, "%4d: %s", line_number, source_buffer);
        print_line(print_buffer, src_name, todays_date);
        return (TRUE);
    }
    else
    {
        return (FALSE); //there is no more lines
    }
}

Token* get_token()
{
    char ch; //This can be the current character you are examining during scanning.
    //char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    //char *token_ptr = token_string; //write some code to point this to the beginning of token_string
    Token* token1 = create_tok(); //create a new token
	
    
    //find the token type, token code, and the literal, then initialize it as a Token, then...

    //1.  Skip past all of the blanks and comments
	index_line += skip_blanks(src_line + index_line);		
	skip_comment();


	//now know that it is not comment block or space
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
	ch = get_char();

    //3.  Call the appropriate function to deal with the cases in 2.
	switch(char_table[ch]) 
	{
		case EOF_CODE: //if end of file
		{
			token1->coder = END_OF_FILE; //end of file tokencode that ends program
			break;
		}
		case LETTER:  //if a letter 
		{
			token1->coder= get_word(token1-> str1); //create new token code of type letter
			break;
		}
		case DIGIT:	//if a digit
		{
			sprintf(token1->str1, "%g", get_number());
			token1->coder = NUMBER; //create new tokencode of type number
			break;
		}
		case QUOTE:	//if a quote
		{
			get_string(token1->str1);
			token1->coder = STRING; //create new tokencode of type string
			break;
		}
		case SPECIAL:	//if a special character
		{
			token1->coder = get_special(token1->str1); //create new tokencode of type special
			break;
		}
		default:	
		{
			++index_line;
			break;
		}
	}
    return token1;
}

static char get_char() 
{
    /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */
    while(src_line[index_line] == '\0')  //while the index equals the null terminator  
	{
		if(get_source_line(src_line) == FALSE)		
		{
			return EOF;
		}
		index_line = skip_blanks(src_line);
    }
	return src_line[index_line];
    /*
     Write some code to set the character ch to the next character in the buffer
     */
}

static int skip_blanks(char *stringer)
{
    /*
     Write some code to skip past the blanks in the program and return a pointer
     to the first non blank character
     */
    char *beginning = stringer;
     
	while(isspace(*stringer))  //skip the blanks
	{
		++stringer; //increase the pointer
	}
	return stringer - beginning;
}

static int skip_comment()
{
	char current = get_char();
	
	if(current == '{')	
	{
		while(current != '}' && current != EOF) //while the current char is not the end of comment or file
		{
			++index_line;
			current = get_char();
		}
		if(current == '}')
		{
			++index_line; //increase the index of line after end of comment is reached 
		}
	}
	return index_line; //return the new index
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
     */
}

static TokenCode get_word(char *stringer)
{
    /*
     Write some code to Extract the word
     */
	TokenCode coder; //new TokenCode
	int counter = 0;
	char* begin = src_line + index_line;	
	while(char_table[src_line[index_line]] == LETTER || char_table[src_line[index_line]] == DIGIT) //while the char is a letter or digit
	{
		++index_line;
	}

	counter = src_line + index_line - begin;
	strncpy(stringer, begin, counter); //the new word

	downshift_word(stringer); //downshift the word

	if(!is_reserved_word(stringer, &coder)) //if the word is not a reserved word
	{
		return IDENTIFIER;
	}

    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */
    const RwStruct* iter;
    int len = strlen(stringer);
    iter = rw_table[len - 2];

	while(iter->token_code != NO_TOKEN)
	{
		if(strcmp(stringer, iter->string) == 0)
		{
			coder = iter->token_code; //see what reserved word it is
		}
		++iter;
	}
	
	return coder; //return the TokenCode
}

static double get_number()
{
    /*
     Write some code to Extract the number and convert it to a literal number.
     */
	int k = 0;
	float value = .0;
	
	sscanf(src_line+index_line, "%f%n", &value, &k); //get the number at that index
	
	index_line += k;
	return value;
}

static void get_string(char* stringer)
{
    /*
     Write some code to Extract the string
     */
	int current = ++index_line;
	int len = 0;
	
	while(src_line[index_line] != '\'' && src_line[index_line] != 0) //gets all the letters in a string
	{
		++index_line;
	}
	len = index_line - current;
	strncpy(stringer, src_line + current, len); //copies the sting to the pointer stringer
	stringer[len] = '\0';
	++index_line;
}

static TokenCode get_special(char *stringer)
{
	TokenCode coder = NO_TOKEN; //symbol pointer
	const RwStruct* iter;  //iterator through the Rw tables
	int current = index_line;
	int len;

	iter = special_table; //iterator for table of special characters

	while(iter->token_code != NO_TOKEN)
	{
		if(iter -> string[0] == src_line[index_line])
		{
			++index_line;
			if(iter->string[1] != '\0')
			{
				if(iter->string[1] == src_line[index_line+1])
				{
					++index_line;
					coder = iter->token_code; //sets the tokencode to special char
					break;
				}
			}
				
			coder = iter->token_code;
			len = index_line - current; 
			strncpy(stringer, (src_line + current), len); //sets the new sting size
			stringer[len] = '\0';
			break;
			
		}
		iter++; //iterate until done with special char
	}
	return coder; //returns special 
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
}

static void downshift_word(char *da_word)
{
	while(*da_word != 0)
	{
		*da_word = tolower(*da_word); //downshift the word to lowercase 
		da_word++; //increase the char pointer
	}
    /*
     Make all of the characters in the incoming word lower case.
     */
}
static BOOLEAN is_reserved_word(char *da_word, TokenCode* coder)
{
    //added by group 3/13

	int len = strlen(da_word);
	const RwStruct* iter; 
	*coder = NO_TOKEN; //new TokenCode to save reserved word

	if(len < 2 || len > 9) //if the length is not bewteen 2 and 9 return false
	{
		return FALSE;
	}

	iter = rw_table[len - 2];

	while(iter->token_code != NO_TOKEN)
	{
		if(strcmp(da_word, iter->string) == 0)
		{
			*coder = iter->token_code; //see what reserved word it is
			return TRUE;
		}
		++iter; //increase iterator
	}
	return FALSE;
	/*
     Examine the reserved word table and determine if the function input is a reserved word.
     */
}
