// Phillip Day, Jackson Curless, Dylan Coyle
//
//  IdentifierBinaryTree.cpp
//  Lab5
//
//  Created by Bryce Holton on 3/28/14.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include "IdentifierBinaryTree.h"
#include "LineNumberList.h"
#include "Token.h"

using namespace std;

IdentifierBinaryTree::IdentifierBinaryTree() : theTreeRoot(NULL)
{

}
IdentifierBinaryTree::~IdentifierBinaryTree()
{
    Token *root = getTreeRoot();
    
    if (root != NULL)
    {
        depthFirstDeleteTree(root);
    }
}
void IdentifierBinaryTree::depthFirstDeleteTree(Token *tok)
{
    if (tok->getLeftChild() != NULL)
    {
        depthFirstDeleteTree(tok->getLeftChild());
    }
//    count << tok->getTokenString() << "\n";
    if (tok->getRightChild() != NULL)
    {
        depthFirstDeleteTree(tok->getRightChild());
    }
    delete tok;
    tok = NULL;
}

bool IdentifierBinaryTree::addIdentifier(Identify *tok, int lineNum)
{
    bool success = false;
    
    if (getTreeRoot() == NULL)
    {
        setTreeRoot(tok);
        tok->addToLineNumberList(new LineNumberList(lineNum));
        success = true;
    }
    else
    {
        string tokenName = tok->getTokenString();
        Token *parentNode = getTreeRoot();
        string treeNodeName;
        int stringComparison;
        
        while (parentNode != NULL)
        {
            treeNodeName = parentNode->getTokenString();
            stringComparison = tokenName.compare(treeNodeName);
            if (stringComparison == 0)
            {
                //They are the same identifier token we just need to add a new line number to the list.
                parentNode->addToLineNumberList(new LineNumberList(lineNum));              
                delete tok;         //We won't need tok and it won't be deleted in main.
		tok = NULL;
                return true;
            }
            else if (stringComparison < 0)
            {
                //Go to the left.
                if (parentNode->getLeftChild() == NULL)
                {
                    //Add tok to the left
                    tok->addToLineNumberList(new LineNumberList(lineNum));
                    parentNode->setLeftChild(tok);                  
                    return true;
                }
                else
                {
                    parentNode = parentNode->getLeftChild();
                }
            }
            else
            {
                //Go to the right.
                if (parentNode->getRightChild() == NULL)
                {
                    //Add tok to the right
                    tok->addToLineNumberList(new LineNumberList(lineNum));
                    parentNode->setRightChild(tok);
                    return true;
                }
                else
                {
                    parentNode = parentNode->getRightChild();
                }
            }
        }
    }
    return success;
}
