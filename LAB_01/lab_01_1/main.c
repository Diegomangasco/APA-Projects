#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 8	//squadre
#define m 4	//giornate
void giornata(int punteggi[m][n]);
void leggifile (FILE *fp);

int main(int argc, char *argv[])
{
    FILE *fp;
    if(argc!=2)
    {
        fprintf(stderr,"Errore nel numero dei parametri!");
        exit(1);
    }

    fp=fopen(argv[1],"r");	
    if(fp==NULL)		//controllo di consistenza del file
    {
        fprintf(stderr,"File vuoto!");
        exit(2);
    }
    leggifile(fp);
    fclose(fp);

    return 0;
}
void leggifile(FILE *fp)
{
    
    int i,j;
    int punti[m][n];

    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            fscanf(fp,"%d",&punti[h][t]);	//riempimento della matrice con i punteggi

    }

    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",punti[i][j]);	//stampa della matrice punti
        printf("\n");
    }

    giornata(punti);

    fclose(fp);
}
void giornata(int punteggi[m][n])
{
    int i,j;
    int max,cont;
    int somme[m][n];
    for(i=0;i<n;i++)
        somme[0][i]=punteggi[0][i];	//riempimento della prima riga di somme

    for(i=1;i<m;i++)
    {
        for(j=0;j<n;j++)
            somme[i][j] = somme[i-1][j] + punteggi[i][j];	//calcolo delle somme per ogni giornata, di ogni j-esima squadra
    }

    printf("\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ", somme[i][j]);		//stampa della matrice somme
        printf("\n");
    }

    printf("\n");
    for(i=0;i<m;i++)		
    {
        cont=0;
        max=somme[i][0];	//assegnazione del massimo per ogni giornata
        for(j=0;j<n-1;j++)
        {
            if(somme[i][j+1]>=max){
                max=somme[i][j+1];	//ricerca del massimo tre le n sqaudre
                cont=j+1;
                }
        }
        printf("Giornata %d --> Capolista squadra %d",i+1,cont+1);	//per ogni m-esima giornata (indicata come i+1 per partire dalla prima) stampo la capolista (indicata con cont+1 per partire dalla prima squadra)
        printf("\n");
    }
}
