// Phillip Day, Jackson Curless, Dylan Coyle
//
//  LineNumberList.h
//  Lab5
//
//  Created by Bryce Holton on 3/28/14.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#ifndef __Lab4__LineNumberList__
#define __Lab4__LineNumberList__

#include <iostream>

class LineNumberList
{
    
public:
    LineNumberList(const int &lineNumber = 0);
    ~LineNumberList();
    void setLineNumber(int num);
    int getLineNumber();
    void setNextLineNumber(LineNumberList *next);
    LineNumberList *getNextLineNumber();

private:
    int theLineNumber;
    LineNumberList *theNextLineNumber;
};

#endif 
