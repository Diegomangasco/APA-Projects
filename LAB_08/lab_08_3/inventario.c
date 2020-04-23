
#include "inventario.h"
inv *leggi_oggetti()
{
    int righe,i;
    FILE *fp=fopen("inventario.txt","r");
    fscanf(fp,"%d",&righe);
    inv *elenco=malloc(sizeof(inv));
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

//ricerca e stampa caratteristiche
#endif // INVENTARIO_H_INCLUDED
