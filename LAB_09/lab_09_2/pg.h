//
// Created by UTENTE on 14/12/2019.
//

#ifndef LAB_09_2_PG_H
#define LAB_09_2_PG_H
#include "equipArray.h"
typedef struct pg
{
    char codice[7];
    char nome[50];
    char classe[50];
    stat_t *stat;
    arr equip;
    struct pg *next;
}pg;
void stampa_stat(pg *head);
void stampa_pg(pg *head, pg *tail, inventario elenco);
void calcola_stat(inventario *el, pg **x, int i, int true);
#endif //LAB_09_2_PG_H
