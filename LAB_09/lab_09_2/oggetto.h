//
// Created by UTENTE on 13/12/2019.
//

#ifndef LAB_09_2_OGGETTO_H
#define LAB_09_2_OGGETTO_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    char nome[50];
    char tip[50];
    int stati[6];
    int disp;
}ogg;
typedef struct
{
    int hp;
    int mp;
    int def;
    int atk;
    int magg;
    int spr;
}stat_t;
#endif //LAB_09_2_OGGETTO_H


