#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED
#endif // PERSONAGGI_H_INCLUDED
#include "inventario.h"
typedef struct pg
{
    char codice[7];
    char nome[50];
    char classe[50];
    stat_t *stat;
    equi_t *equip;
    struct pg *next;
}pg,*link;
void stampa_stat(link head);
void calcola_stat(inv **el, link *x, int i);
void stampa_pg(link head, link tail);
link newnode(link next, link val);
void leggi_file(link *hp,link *tp);
void carica_pg(link *hp,link *tp,link val);
link aggiungi_elemento();
void elimina_pg(link *hp);
void aggiunta_ogg(link *head, inv **el);
void elimina_ogg(link *head, inv **el);
