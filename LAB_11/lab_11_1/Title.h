//
// Created by UTENTE on 12/01/2020.
//
#include "BST.h"
#ifndef LAB_11_01_TITLE_H
#define LAB_11_01_TITLE_H
typedef struct collection* c;
c insert(c head, char *name);
c newnode(char* name, c previous);
void leggifile(FILE *fp, c head);
c searchinlist(c head, char* name);
void searchinBST(c head, date* d);
void searchbyrangeBST(c head,date* d1, date* d2);
void balance(c search);
void searchLway(c search);
#endif //LAB_11_01_TITLE_H
