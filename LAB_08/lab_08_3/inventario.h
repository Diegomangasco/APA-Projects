#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED
#endif // INVENTARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nome[50];
    char tip[50];
    int stati[6];
    int disp;
}ogg;
typedef struct
{
    ogg *vett;
    int n_disp;
    int max_n;
}inv;
typedef struct
{
    int hp;
    int mp;
    int def;
    int atk;
    int magg;
    int spr;
}stat_t;
typedef struct
{
    int in_uso;
    ogg **vetteq;
}equi_t;
inv *leggi_oggetti();
