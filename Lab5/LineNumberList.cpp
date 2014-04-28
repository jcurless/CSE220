// Phillip Day, Jackson Curless, Dylan Coyle
//
//  LineNumberList.cpp
//  Lab5
//
//  Created by Bryce Holton on 3/28/14.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include "LineNumberList.h"

LineNumberList::LineNumberList(const int &lineNumber): theLineNumber(lineNumber) , theNextLineNumber(NULL)
{
    
}
LineNumberList::~LineNumberList()
{
    if (theNextLineNumber != NULL)
    {
        delete theNextLineNumber;
    }
}
void LineNumberList::setLineNumber(int num)
{
    theLineNumber = num;
}
int LineNumberList::getLineNumber()
{
    return theLineNumber;
}
void LineNumberList::setNextLineNumber(LineNumberList *next)
{
    theNextLineNumber = next;
}
LineNumberList *LineNumberList::getNextLineNumber()
{
    return theNextLineNumber;
}
