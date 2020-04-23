//
// Created by UTENTE on 12/01/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef LAB_11_01_Q_H
#define LAB_11_01_Q_H
typedef struct {
    float quote;
    float num;
	float den;
}quotation;
quotation* qinit();
quotation* qNULL();
float calc(quotation *q);
#endif //LAB_11_01_Q_H
