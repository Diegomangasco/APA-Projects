//
// Created by UTENTE on 13/12/2019.
//

#ifndef LAB_09_2_EQUIPARRAY_H
#define LAB_09_2_EQUIPARRAY_H
#include "inventario.h"
typedef struct Array *arr;
void aggiungi_oggetto(arr t, int index, inventario elenco);
void azzera(arr t);
void elimina_oggetto(arr t,int index,inventario elenco);
arr equip_all();
void equip_free(arr t);
int torna_indice(arr t, int i);
int torna_NULL(arr t, int index);
void uso(arr t);
#endif //LAB_09_2_EQUIPARRAY_H
