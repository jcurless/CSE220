// Phillip Day, Jackson Curless, Dylan Coyle
//
//  Real.Lit.h
//  Lab5
//
#ifndef _REALLIT_H
#define _REALLIT_H


#include "common.h"


class RealLit : public CommonLit
{
public:

    explicit RealLit(const float &data);


    ~RealLit();


    LiteralType getType();

private:

    float theData;
};

#endif 
