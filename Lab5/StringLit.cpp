// Phillip Day, Jackson Curless, Dylan Coyle
//
//  StringLit.cpp
//  Lab5
//
#include "StringLit.h"

StringLit::StringLit(char *data)
{
    LiteralData ld;
    ld.strData = data;
    setLiteralData(ld);
}

StringLit::~StringLit()
{

}

CommonLit::LiteralType StringLit::getType()
{
    return CommonLit::StringLit;
}


