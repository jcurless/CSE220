// Phillip Day, Jackson Curless, Dylan Coyle
//
//  IdentifierBinaryTree.h
//  Lab5
//
//  Created by Bryce Holton on 3/28/14.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#ifndef __Lab4__IdentifierBinaryTree__
#define __Lab4__IdentifierBinaryTree__

#include <iostream>
#include "Identify.h"

class Token;

class IdentifierBinaryTree
{
    
public:
    IdentifierBinaryTree();
    ~IdentifierBinaryTree();
    
public:
    inline Identify *getTreeRoot()
    {
        return theTreeRoot;
    }

    inline void setTreeRoot(Identify *root)
    {
        theTreeRoot = root;
    }

    bool addIdentifier(Identify *tok, int lineNum);
    void depthFirstDeleteTree(Token *tok);

private:
    Identify *theTreeRoot;
};

#endif
