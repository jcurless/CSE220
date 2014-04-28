// Phillip Day, Jackson Curless, Dylan Coyle
//
//  Token.cpp
//  Lab5
//
//  Created by Bryce Holton.
//

#include "Token.h"
#include <stdlib.h>

Token::Token() : theLiteral(NULL)
               , leftChild(NULL)
               , rightChild(NULL)
               , theList(NULL)
{
}
Token::~Token()
{
    if (theList != NULL)
    {
        delete theList;
        theList = NULL;
    }

    if (theLiteral)
    {
        delete theLiteral;
        theLiteral = NULL;
    }
}
void Token::setCode(TokenCode newCode)
{
    code = newCode;
}
TokenCode Token::getCode()
{
    return code;
}
CommonLit *Token::getLiteral()
{
    return theLiteral;
}
void Token::setLiteral(CommonLit *literal1)
{
    if (theLiteral)
    {
        delete theLiteral;
        theLiteral = NULL;
    }
    theLiteral = literal1;
}
void Token::setTokenString(string str)
{
    theTokenString = str;
}
string Token::getTokenString()
{
    return theTokenString;
}
//What methods am I missing to implement a binary tree.
void Token::setLeftChild(Token *tok)
{
    leftChild = tok;
}
Token *Token::getLeftChild()
{
    return leftChild;
}
void Token::setRightChild(Token *tok)
{
    rightChild = tok;
}
Token *Token::getRightChild()
{
    return rightChild;
}
void Token::addToLineNumberList(LineNumberList *listItem)
{
    if (theList == NULL)
    {
        theList = listItem;
    }
    else
    {
        LineNumberList *tmp1 = theList;
        while (tmp1->getNextLineNumber() != NULL)
        {
            tmp1 = tmp1->getNextLineNumber();
        }
        tmp1->setNextLineNumber(listItem);
    }
}
LineNumberList *Token::getLineNumberList()
{
    return theList;
}
