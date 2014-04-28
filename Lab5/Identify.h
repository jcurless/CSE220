// Phillip Day, Jackson Curless, Dylan Coyle
//
//  Identify.h
//  Lab5
//
#ifndef _IDENTIFY_H
#define _IDENTIFY_H


#include "Token.h"


class Identify : public Token
{
public:

    explicit Identify();


    ~Identify();


    TokenCode getCode();
};

#endif
