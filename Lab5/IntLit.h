// Phillip Day, Jackson Curless, Dylan Coyle
//
//  IntLit.h
//  Lab5
//
#ifndef _IntLit_H
#define _IntLit_H

#include "common.h"

class IntLit : public CommonLit
{
public:

    explicit IntLit(const int &data);


    ~IntLit();


    LiteralType getType();

private:

    int mData;
};

#endif
