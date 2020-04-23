//
// Created by UTENTE on 12/01/2020.
//
#include "Q.h"
#ifndef LAB_11_01_DATE_H
#define LAB_11_01_DATE_H
typedef struct{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
}date;
date* dinit();
date* dNULL();
int dcmp(int a1, int m1, int g1, int a2, int m2, int g2);
#endif //LAB_11_01_DATE_H
