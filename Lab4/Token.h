/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day

*Program Description: Token.h
*Header file contains the Token class definition.
*
*Created by Bryce Holton.
*
*/


#ifndef _Lab4_Token_h
#define _Lab4_Token_h

#include <iostream>
#include <stdlib.h>
#include "common.h"
#include "Linker.h"

using namespace std;

/**************
this is a valid Pascal token. A token must have a literal type,
a literal value, and a token code.
***************/
class Token
{
private:
    TokenCode code;
    LiteralType type;
    union
    {
        int integer;
        float real;
        char *stringLiteral;
    }
    literal;
    string tokenString;
    //Pointers to the Token's left and right child nodes
    Token *leftChild;
    Token *rightChild;
    //LinkedLit object for holding the line number the Token was found on and a pointer to the next
    //Linker object in the linked list.
    Linker lines;

public:
    Token();
    ~Token();
    void setCode(TokenCode newCode);
    TokenCode getCode();
    void setType(LiteralType newType);
    LiteralType getType();
    void setLiteral(int newInteger);
    int getIntLiteral();
    void setLiteral(float newReal);
    float getRealLiteral();
    void setLiteral(string newString);
    string getStringLiteral();
    void setTokenString(string s);
    string getTokenString();
    void setNextToken(Token *newToken);
    Token* getNextToken();
    Linker getList();
    void setList(int newLine);
    Token* getLeftChild();
    void setLeftChild(Token *newToken);
    Token* getRightChild();
    void setRightChild(Token *newToken);
    void setLine(int line);
};

#endif /* defined(__Lab4__Token__) */
