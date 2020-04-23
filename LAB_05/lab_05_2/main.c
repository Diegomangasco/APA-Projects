#include <stdio.h>
#include <stdlib.h>
void allocc(int ***mat,int nr,int nc);
void riempi_mat(int ***mat,int nr, int nc, FILE *fp);
void stampa_mat(int ***mat,int nr, int nc);
void separa(int **mat,int nr, int nc, int **bianchi, int **neri);
void stampa (int *bianchi, int n, int caso);
int main()
{
    FILE *fp;
    int nr,nc;
    int *bianchi, *neri;
    int caso,pari;
    int **mat;
    fp=fopen("mat.txt","r");
    fscanf(fp,"%d%d",&nr,&nc);  //prendo il numero di righe e di colonne
    allocc(&mat,nr,nc);
    riempi_mat(&mat,nr,nc,fp);
    stampa_mat(&mat,nr,nc);
    fclose(fp);
    separa(mat,nr,nc,&bianchi,&neri);

    if((nr*nc)%2==0)
        pari=1;
    else pari=0;

    if(pari)    //caso numero caselle pari
    {
        caso = 1;
        stampa(bianchi,(nr*nc)/2,caso);
        caso=0;
        stampa(neri,(nr*nc)/2,caso);
    }
    else        //caso numero caselle dispari
    {
        caso=1;
        stampa(bianchi,((nr*nc)/2)+1,caso);
        caso=0;
        stampa(neri,(nr*nc)/2,caso);
    }
    free(bianchi);
    free(neri);
}
void allocc(int ***mat, int nr, int nc)
{
    int i;
    int **m;    //alloco tramite un puntatore a puntatore di appoggio
    m=malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++)
        m[i]=malloc(nc*sizeof(int));
    *mat=m;     //assegno al puntatore a **mat, l'indirizzo del puntatore m
    free(m);
}
void riempi_mat(int ***mat,int nr,int nc, FILE *fp)
{
    int i,j;
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            fscanf(fp,"%d", &(*mat)[i][j]);
    }
}
void stampa_mat(int ***mat,int nr, int nc)
{
    int i,j;
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            printf("%d ",(*mat)[i][j]);
        printf("\n");
    }
}
void separa(int **mat,int nr, int nc, int **bianchi, int **neri)
{
    int nneri;
    int i,j;
    int pari;
    int caso;
    int vero_nero;
    int *n,*b;
    if((nr*nc)%2==0)    //caso numero celle pari
    {
        nneri=(nr*nc)/2;
        b=malloc(nneri*sizeof(int*));
        n=malloc(nneri*sizeof(int*));
        pari=1;
    }
    else        //caso numero celle dispari
    {
        nneri=(nr*nc)/2;
        b=malloc((nneri+1)*sizeof(int*));
        n=malloc(nneri*sizeof(int*));
        pari=0;
    }
    vero_nero=0;
    for(i=0;i<nr;i++)   //scandisco la matrice
    {
        for(j=0;j<nc;j++)
        {
            if(!vero_nero)  //se è bianco
            {
                *b=mat[i][j];
                b++;
                vero_nero=1;    //il prossimo dovrà essere nero
            }
            else    //se e nero
            {
                *n=mat[i][j];
                n++;
                vero_nero=0;    //il prossimo dovrà essere bianco
            }
        }
    }
    if(pari)
    {
        b=b-((nr*nc)/2);    //b e n tornano a puntare alla cella iniziale dei loro vettori
        n=n-((nr*nc)/2);
        bianchi=b;	//assegno ai puntatori bianchi e neri, gli indirizzi puntati da b e n
        neri=n;
        free(n);
        free(b);
    }
    else
    {
        b=b-(((nr*nc)/2)+1);
        n=n-((nr*nc)/2);
        *bianchi=b;
        *neri=n;
        free(n);
        free(b);
    }
    return;
}
void stampa (int *bianchi, int n, int caso)
{
    int i;
    if(caso)
    {
        printf("Bianchi: ");
        for (i=0;i<n;i++)
            printf("%d ",bianchi[i]);
        printf("\n");
    }
    else
    {
        printf("Neri: ");
        for (i=0;i<n;i++)
            printf("%d ",bianchi[i]);
        printf("\n");
    }
}

