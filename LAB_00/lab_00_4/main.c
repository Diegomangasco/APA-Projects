#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void leggifile(int nr, FILE *fp, int nc);
void sottomatrici(int dim, int mat[20][20],int nr, int nc);
int sommamassima(int valore,int i,int j,int somma);
void salvamatrice(int matsomma[20][20],int dim);
void stampamagg(int dimmax);
int matsomma[20][20];
int magmatrix[20][20];

int main()
{
    char file[21];
    FILE *fp;
    int nr,nc;

    printf("Inserisci il nome del file: ");
    scanf("%s",file);
    fp=fopen(file,"r");
    fscanf(fp,"%d %d", &nr, &nc); //lettura del numero di righe e di colonne
    leggifile(nr,fp,nc);    //funzione per spazzolare il file
    fclose(fp);

    return 0;
}
void leggifile(int nr, FILE *fp, int nc)
{
    int min;
    int i;
    int j;
    int dim;
    int mat[20][20];
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            fscanf(fp,"%d ",&mat[i][j]); //salvo in mat, i dati del file
    }

    for(i=0;i<nr;i++) //stampa della matrice letta
    {
        for(j=0;j<nc;j++)
            printf("%d ",mat[i][j]);

        printf("\n");
    }

    if(nr<=nc)  //ricerco il minimo tra righe e colonne per la condizione successiva
        min=nr;
    else
        min=nc;

    do{
    printf("Inserisci la dimensione delle sottomatrici (per terminare il processo inserire 0): ");
    scanf("%d",&dim);
    sottomatrici(dim,mat,nr,nc);
    }while(dim>1 && dim<min);
}
void sottomatrici(int dim,int mat[20][20],int nr, int nc)
{
    int i,j,a,b;
    int t=0;
    int d=0;
    int somma=0;
    int somma_1=0;
    int dimmax;

    printf("\n");

    while((dim+d)<=nr) //condizione per non sforare la matrice con le righe
    {
        t=0;
        while((dim+t)<=nc) //condizione per non sforare la matrice con le colonne
        {
            for(i=d,a=0;i<dim+d;i++,a++) //i parte da zero e si incrementa, quando sono finite le sottomatrici che partono dalla prima riga
            {
                for(j=t, b=0;j<dim+t;j++,b++) //j parte da zero e si incrementa prima di i per considerare tutte le sottomatrici che partono dalla prima riga
                {
                    printf("%d ",mat[i][j]);
                    somma_1=sommamassima(mat[i][j],a,b,somma_1); //ottengo la somma degli elementi della sottomatrice
                }

                printf("\n");
            }

            if(somma_1>somma) //controllo se la somma degli elementi della sottomatrice, supera quella precedente
            {
                somma=somma_1; //aggiorno somma
                salvamatrice(matsomma,dim); //salvo la matrice
            }
            somma_1=0; //riporto somma_1 a zero (così da poter ricominciare con una nuova sottomatrice)
            t++;
        } //mi sposto una colonna più in là
        d++; //mi sposto una riga sotto
    }


    stampamagg(dim);

}
int sommamassima(int valore,int i,int j,int somma) //i e j, sarebbero a e b, che partono sempre da zero e arrivano a dim
{
  matsomma[i][j]=valore; //memeorizzo i valori della sottomatrice in esame in matsomma, portando sempre a e b a zero, riscrivo continuamente la matsomma
  return somma += valore;
}
salvamatrice(int matsomma[20][20],int dim)
{
    int i,j;
    for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
            magmatrix[i][j]=matsomma[i][j]; //copio la matrice con la somma maggiore (attuale) in magmatrix

        printf("\n");
    }

}

void stampamagg(int dimmax) //stampa del risultato
{
    int i,j;
    printf("\n");
    printf("Matrice con somma maggiore tra le %d x %d\n", dimmax, dimmax);

    for(i=0;i<dimmax;i++)
    {
        for(j=0;j<dimmax;j++)
            printf("%d ",magmatrix[i][j]);

        printf("\n");

    }
}

