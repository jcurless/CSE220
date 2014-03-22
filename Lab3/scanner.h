//
//  scanner.h
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//
//	Phillip Day, Jackson Curless, Dylan Coyle

#ifndef Lab3_scanner_h
#define Lab3_scanner_h

#include "common.h"
#include "print.h"

Token* create_tok(); //to create new token
int free_tok(Token* the_token); //free the token
void ch_table();				//create the char_table

void init_scanner();
Token* get_token();

#endif
