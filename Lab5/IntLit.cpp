// Phillip Day, Jackson Curless, Dylan Coyle
//
//  IntLit.h
//  Lab5
//
#include "IntLit.h"


IntLit::IntLit(const int &data)
{
    LiteralData ld;
    ld.intData = data;
    setLiteralData(ld);
}

IntLit::~IntLit()
{
}

CommonLit::LiteralType IntLit::getType()
{
    return CommonLit::IntegerLit;
}


