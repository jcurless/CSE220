// Phillip Day, Jackson Curless, Dylan Coyle
//
//  Token.h
//  Lab5
//
//  Created by Bryce Holton.
//

#ifndef __Lab4__Token__
#define __Lab4__Token__

#include <iostream>
#include "common.h"
#include "LineNumberList.h"
#include "Literal.h"

using namespace std;

/**************
 this is a valid Pascal token.  A token must have a literal type,
 a literal value, and a token code.
 ***************/
class Token
{
private:
    TokenCode code;
    CommonLit *theLiteral;
    string theTokenString;
    Token *leftChild;
    Token *rightChild;
    LineNumberList *theList;
    
public:
    Token();
    virtual ~Token();
    void setCode(TokenCode newCode);
    virtual TokenCode getCode();
    CommonLit *getLiteral();
    void setLiteral(CommonLit *literal1);
    void setTokenString(string str);
    string getTokenString();
    void setLeftChild(Token *tok);
    Token *getLeftChild();
    void setRightChild(Token *tok);
    Token *getRightChild();
    void addToLineNumberList(LineNumberList *listItem);
    LineNumberList *getLineNumberList();
};

#endif /* defined(__Lab4__Token__) */
