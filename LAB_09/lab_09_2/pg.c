//
// Created by UTENTE on 14/12/2019.
//
#include "pg.h"
void stampa_stat(pg *head)
{
    printf("Lista statistiche: \n");
    for(;head!=NULL;head=head->next)
    {
        printf("Giocatore: %s\n",head->nome);
        printf("hp: %d\n",head->stat->hp);
        printf("mp: %d\n",head->stat->mp);
        printf("atk: %d\n",head->stat->atk);
        printf("def: %d\n",head->stat->def);
        printf("magg: %d\n",head->stat->magg);
        printf("spr: %d\n",head->stat->spr);
        printf("\n");
    }
}
void calcola_stat(inventario *el, pg **x, int i, int true) {
    pg *t = *x;
    inventario elenco = *el;
    if(true==1) {
        t->stat->hp = t->stat->hp + torna_stat(elenco, i, 0);
        if (t->stat->hp < 1) t->stat->hp = 1;
        t->stat->mp = t->stat->mp + torna_stat(elenco, i, 1);
        if (t->stat->mp < 1) t->stat->mp = 1;
        t->stat->atk = t->stat->atk + torna_stat(elenco, i, 2);
        if (t->stat->atk < 1) t->stat->atk = 1;
        t->stat->def = t->stat->def + torna_stat(elenco, i, 3);
        if (t->stat->def < 1) t->stat->def = 1;
        t->stat->magg = t->stat->magg + torna_stat(elenco, i, 4);
        if (t->stat->magg < 1) t->stat->magg = 1;
        t->stat->spr = t->stat->spr + torna_stat(elenco, i, 5);
        if (t->stat->spr < 1) t->stat->spr = 1;
    } else
    {
        t->stat->hp = t->stat->hp - torna_stat(elenco, i, 0);
        if (t->stat->hp < 1) t->stat->hp = 1;
        t->stat->mp = t->stat->mp - torna_stat(elenco, i, 1);
        if (t->stat->mp < 1) t->stat->mp = 1;
        t->stat->atk = t->stat->atk - torna_stat(elenco, i, 2);
        if (t->stat->atk < 1) t->stat->atk = 1;
        t->stat->def = t->stat->def - torna_stat(elenco, i, 3);
        if (t->stat->def < 1) t->stat->def = 1;
        t->stat->magg = t->stat->magg - torna_stat(elenco, i, 4);
        if (t->stat->magg < 1) t->stat->magg = 1;
        t->stat->spr = t->stat->spr - torna_stat(elenco, i, 5);
        if (t->stat->spr < 1) t->stat->spr = 1;
    }
    return;
}
void stampa_pg(pg *head, pg *tail, inventario elenco)
{
    int i,j;
    j=0;
    if(head==NULL)
    {
        printf("Lista vuota!");
        return;
    }
    if(head==tail)
    {
        printf("\nUnico personaggio:");
        printf("\nCodice: %s\n",head->codice);
        printf("Nome: %s\n",head->nome);
        printf("Classe: %s\n",head->classe);
        for(i=0;i<8;i++) {
            if (!torna_NULL(head->equip, i))
                printf("Oggetto %d: %s\n", i + 1, torna_nome(elenco, torna_indice(head->equip, i)));
            else printf("Oggetto %d: nd", i + 1);
        }
        return;
    }
    for(;head!=NULL;head=head->next)
    {
        j++;
        printf("\nPersonaggio %d",j);
        printf("\nCodice: %s\n",head->codice);
        printf("Nome: %s\n",head->nome);
        printf("Classe: %s\n",head->classe);
        for(i=0;i<8;i++)
        {
            if(torna_NULL(head->equip,i))
                printf("Oggetto %d: %s\n",i+1,torna_nome(elenco,torna_indice(head->equip,i)));
            else printf("Oggetto %d: nd\n",i+1);
        }
    }
}