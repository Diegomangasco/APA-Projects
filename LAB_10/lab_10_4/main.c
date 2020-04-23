#include "graph.h"
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"Errore nel numero dei parametri passati");
        exit(1);
    }
    g G;
    int scelta;
    FILE *fp=fopen(argv[1],"r");
    filescan(fp,&G);
    printf("E' stata creata la matrice delle adiacenze, desidera creare anche una lista delle adiacenze?\nSe sì prema 1\nSe no prema 0\n");
    scanf("%d",&scelta);
    if(scelta==1)
        list(&G);
    stampalpha(G);
    nearvertex(G);
    GRAPHfree(G);
    fclose(fp);
    return 0;
}