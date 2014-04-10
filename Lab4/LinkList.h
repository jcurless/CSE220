//
//  LinkList.h
//  Lab4
//  Phillip Day, Jackson Curless, Dylan Coyle
//
//  LinkList.h header file to implement LinkedList object.
//

#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED


#include <iostream>
#include "common.h"


using namespace std;

class LinkList
{

    private:

    int liner;
    LinkedList *nextLine;
    LinkedList *current;

    public:
    LinkList();
    ~LinkList();
    void addTo(int new_line);
    void printTheList();
    void deleteTheList();
    void setter(int line_num);

    LinkedList* getNext();
    int getLine();
};
#endif // LINKLIST_H_INCLUDED
