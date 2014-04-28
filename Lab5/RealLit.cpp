// Phillip Day, Jackson Curless, Dylan Coyle
//
//  RealLit.cpp
//  Lab5
//
#include "RealLit.h"


RealLit::RealLit(const float &data)
{
    LiteralData ld;
    ld.floaterData = data;
    setLiteralData(ld);
}

RealLit::~RealLit()
{
}

CommonLit::LiteralType RealLit::getType()
{
    return CommonLit::RealLit;
}

