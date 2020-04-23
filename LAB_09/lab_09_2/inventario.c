//
// Created by UTENTE on 13/12/2019.
//
#include "inventario.h"
struct inv
{
    ogg *vett;
    int n_disp;
    int max_n;
};
int ifdisp(inventario elenco, int index)
{
    if(elenco->vett[index].disp==0) return 0;
    else return 1;
}
int torna_max(inventario elenco)
{
    return elenco->max_n;
}
int torna_disp(inventario elenco)
{
    if(elenco->n_disp==0) return 0;
    else return 1;
}
char *torna_nome(inventario elenco,int index)
{
    return elenco->vett[index].nome;
}
int torna_stat(inventario elenco,int i, int j)
{
    return elenco->vett[i].stati[j];
}
inventario leggi_oggetti()
{
    int righe,i;
    FILE *fp=fopen("inventario.txt","r");
    fscanf(fp,"%d",&righe);
    inventario elenco=malloc(sizeof(struct inv));
    elenco->max_n=righe;
    elenco->n_disp=righe;
    elenco->vett=malloc(righe*sizeof(ogg));
    for(i=0;i<righe;i++)
    {
        fscanf(fp,"%s%s%d%d%d%d%d%d",elenco->vett[i].nome,elenco->vett[i].tip,&elenco->vett[i].stati[0],&elenco->vett[i].stati[1],&elenco->vett[i].stati[2],&elenco->vett[i].stati[3],&elenco->vett[i].stati[4],&elenco->vett[i].stati[5]);
        elenco->vett[i].disp=1;
    }
    return elenco;
}
void aggiorna_disppiu(inventario elenco, int index)
{
    elenco->n_disp--;
    elenco->vett[index].disp=0;
    return;
}
void aggiorna_dispmeno(inventario elenco, int index)
{
    elenco->n_disp++;
    elenco->vett[index].disp=1;
    return;
}



