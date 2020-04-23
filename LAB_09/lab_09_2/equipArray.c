//
// Created by UTENTE on 13/12/2019.
//
#include "equipArray.h"
struct Array
{
    int vettore[8];
    int in_uso;
};
void uso(arr t)
{
    t->in_uso=0;
    return;
}
int torna_indice(arr t, int i)
{
    return t->vettore[i];
}
int torna_NULL(arr t, int index)
{
    if (t->vettore[index]!=-1) return 1;
    else return 0;
};
arr equip_all()
{
    arr t=malloc(sizeof(struct Array));
    return t;
}
void equip_free(arr t)
{
    free(t);
    return;
}
void azzera(arr t)
{
    int i;
    for(i=0;i<8;i++)
        t->vettore[i]=-1;
    return;
}
void aggiungi_oggetto(arr t, int index, inventario elenco)
{
    int i=0;
    if(t->in_uso!=8)
    {
        while(t->vettore[i++]!=-1);
        i--;
        t->vettore[i]=index;
        aggiorna_disppiu(elenco,index);
        t->in_uso++;
        return;
    }
    else
    {
        printf("Equipaggiamento pieno\n");
        return;
    }
}
void elimina_oggetto(arr t,int index, inventario elenco)
{
    int i=0;
    if(t->in_uso>0)
    {
        while(t->vettore[i++]!=index);
        i--;
        t->vettore[i]=-1;
        t->in_uso--;
        aggiorna_dispmeno(elenco, index);
        return;
    }
    else
    {
        printf("Il pg non è equipaggiato\n");
        return;
    }
}

