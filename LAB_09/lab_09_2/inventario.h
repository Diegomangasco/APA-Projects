//
// Created by UTENTE on 13/12/2019.
//

#ifndef LAB_09_2_INVENTARIO_H
#define LAB_09_2_INVENTARIO_H
#include "oggetto.h"
typedef struct inv *inventario;
inventario leggi_oggetti();
void aggiorna_disppiu(inventario elenco, int index);
void aggiorna_dispmeno(inventario elenco, int index);
int torna_stat(inventario elenco,int i, int j);
char *torna_nome(inventario elenco,int index);
int torna_disp(inventario elenco);
int torna_max(inventario elenco);
int ifdisp(inventario elenco, int index);
#endif //LAB_09_2_INVENTARIO_H
