//
// Created by UTENTE on 12/01/2020.
//
#include "Date.h"
#ifndef LAB_11_01_BST_H
#define LAB_11_01_BST_H
typedef struct binarysearchtree *BST;
void BSTfree(BST bst);
BST BSTinit();
void BSTinsert_leafR (BST bst, quotation* q, date* d);
float findq(BST b, date* d);
void findrange(BST b, date* d1, date* d2);
void BSTbalance(BST bst);
void searchWAY(BST bst);
#endif //LAB_11_01_BST_H
