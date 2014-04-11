/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#include "Token.h"

Token::Token()
	{
    	leftChild = NULL;
    	rightChild = NULL;
	}

Token::~Token()
	{
    	lines.Ldeleter();//frees up the memory
	}

void Token::setCode(TokenCode newCode)
	{
    	this->code = newCode;
	}
TokenCode Token::getCode()
	{
   		return this->code;
	}
void Token::setType(LiteralType newType)
	{
    	this->type = newType;
	}
LiteralType Token::getType()
	{
    	return this->type;
	}
void Token::setLiteral(int newInteger)
	{
    	this->literal.integer = newInteger;
	}
int Token::getIntLiteral()
	{
    	return this->literal.integer;
	}
void Token::setLiteral(float newReal)
	{
   		this->literal.real = newReal;
	}
float Token::getRealLiteral()
	{
    	return this->literal.real;
	}
void Token::setLiteral(string newString)
	{
    	this->literal.stringLiteral = (char*)malloc(sizeof(char) * newString.length() + 1);
    	strcpy(this->literal.stringLiteral, newString.c_str());
	}
string Token::getStringLiteral()
	{
    	return string(this->literal.stringLiteral);
	}
void Token::setTokenString(string s)
	{
    	this->tokenString = s;
	}
string Token::getTokenString()
	{
    	return this->tokenString;
	}
Linker Token::getList()
	{
		return this->lines;
	}
void Token::setList(int newLine)
	{
		lines.addToList(newLine);
	}
void Token::setLine(int line)
	{
		this->lines.set(line);
	}

Token *Token::getLeftChild()
	{
		return this->leftChild;
	}
void Token::setLeftChild(Token *newToken)
	{
		this->leftChild = newToken;
	}
Token *Token::getRightChild()
	{
		return this->rightChild;
	}
void Token::setRightChild(Token *newToken)
	{
		this->rightChild = newToken;
	}
