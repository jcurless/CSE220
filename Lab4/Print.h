/* Assignment4
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day

*Program Description:
*Header file for Print.cpp. Contains the Print class defintion.
*
*Created by Bryce Holton.
*
*/


#ifndef _Lab4_Print_h
#define _Lab4_Print_h

#include <iostream>
#include "common.h"
#include "Token.h"

using namespace std;

class Print
{
private:
    string sourceFileName;
    string currentDate;
    int pageNumber;
    
    void printPageHeader();
    
public:
    Print(char source_name[], char date[]);
    ~Print();
    void printReferenceHeader();
    void Liner(char line[]);
    void printToken(Token *token);
};

#endif
