// Phillip Day, Jackson Curless, Dylan Coyle
//
//  StringLit.h
//  Lab5
//
#ifndef _STRINGLIT_H
#define _STRINGLIT_H


#include <string>
#include "common.h"


using namespace std;


class StringLit : public CommonLit
{
public:

    explicit StringLit(char *data);


    ~StringLit();


    LiteralType getType();

private:
    string theData;
};

#endif
