//
// Created by UTENTE on 14/12/2019.
//

#ifndef LAB_09_2_PG_LIST_H
#define LAB_09_2_PG_LIST_H
#include "pg.h"
typedef pg *link;
link aggiungi_elemento();
void leggi_file(link *hp,link *tp);
link newnode(link next, link val);
void carica_pg(link *hp,link *tp,link val);
void elimina_pg(link *hp);
void aggiunta_ogg(link *head, inventario *el);
void elimina_ogg(link *head, inventario *el);
#endif //LAB_09_2_PG_LIST_H
