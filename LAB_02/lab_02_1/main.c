#include <stdio.h>
#include <stdlib.h>
void leggifile(FILE *fp,int matrice[50][50],int nr,int nc);
void contaarea(int matrice[50][50],int nr, int nc);
int verifica (int matrice[50][50],int i,int j,int nr,int nc);
typedef struct      //struttura per contenere le informazioni sui rettangoli
{
    int max_area;
    int base;
    int h;
    int x;
    int y;
}contenitore;
int altezza,base;
int main()
{
    FILE *fp;
    char nome_file[10];
    int matrice[50][50];
    int nr,nc;
    printf("Inserisci il nome del file: ");
    scanf("%s",nome_file);
    fp=fopen(nome_file,"r");        //apertura del file
    fscanf(fp,"%d%d",&nr,&nc);      //lettura del numero di righe e colonne
    leggifile(fp,matrice,nr,nc);    //funzione per leggere il file
    fclose(fp);
    contaarea(matrice,nr,nc);       //funzione per le operazioni
    return 0;
}
void leggifile(FILE *fp,int matrice[50][50],int nr,int nc)
{
    int i,j;
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            fscanf(fp,"%d",&matrice[i][j]);
    }

    for(i=0;i<nr;i++)           //stampa della matrice
    {
        for(j=0;j<nc;j++)
            printf("%d ",matrice[i][j]);
        printf("\n");
    }
}
void contaarea(int matrice[50][50],int nr, int nc)
{
    int i,j;
    int area;
    contenitore elemento[3];       //vettore di strutture dove contenere i tre rettangoli richiesti
    elemento[0].max_area=0;
    elemento[1].h=0;
    elemento[2].base=0;

    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
        {
            area=verifica(matrice,i,j,nr,nc);   //funzione per il calcolo delle aree
            if(area!=0)
            {
                if(area>=elemento[0].max_area)  //confronto tra il massimo e l'area appena calcolata
                {
                    elemento[0].max_area=area;
                    elemento[0].x=i;
                    elemento[0].y=j;
                    elemento[0].h=altezza;
                    elemento[0].base=base;
                }
                if(altezza>=elemento[1].h)
                {
                    elemento[1].max_area=area;
                    elemento[1].x=i;
                    elemento[1].y=j;
                    elemento[1].h=altezza;
                    elemento[1].base=base;
                }
                if(base>=elemento[2].base)
                {
                    elemento[2].max_area=area;
                    elemento[2].x=i;
                    elemento[2].y=j;
                    elemento[2].h=altezza;
                    elemento[2].base=base;
                }
            }

        }
    }
    printf("Rettangolo con area massima --> area %d base %d altezza %d <%d %d>\n",elemento[0].max_area,elemento[0].base,elemento[0].h,elemento[0].x,elemento[0].y);
    printf("Rettangolo con altezza massima --> area %d base %d altezza %d <%d %d>\n",elemento[1].max_area,elemento[1].base,elemento[1].h,elemento[1].x,elemento[1].y);
    printf("Rettangolo con base massima --> area %d base %d altezza %d <%d %d>",elemento[2].max_area,elemento[2].base,elemento[2].h,elemento[2].x,elemento[2].y);
}

int verifica(int matrice[50][50],int i, int j,int nr,int nc)
{
    int f,g;
    int area=0;
    int flagr=1;
    altezza=0;base=0;
    if(matrice[i][j]==0)    //se l'elemento è zero si ritorna un'area nulla
        return 0;
    else
    {
        if(i==0 && j!=0)    //caso particolare della prima riga
        {
            if(matrice[i][j-1]==1)  //controllo se l'elemento appartiene già ad un rettangolo controllato in precedenza
                return 0;
        }
        if(j==0 && i!=0)    //caso particolare della prima colonna
        {
            if(matrice[i-1][j]==1)  //controllo se l'elemento appartiene già ad un rettangolo controllato in precedenza
                return 0;
        }
        if(i!=0 && j!=0)    //se non sono in una situazione particolare
        {
            if((matrice[i-1][j]==1)||(matrice[i][j-1]==1))  //se l'elemento è già contenuto in un rettangolo precedentemente controllato
                return 0;
            else
            {
                for(f=i;f<nr && flagr;f++)
                {
                    area++;                                 //contributo del primo elemento
                    for(g=j;g<nc && matrice[f][g+1]==1;g++) //controllo l'elemento nella cella successiva
                        area++;                             //eventuale contributo della cella adiacente
                    if(matrice[f+1][j]!=1)                  //controllo primo elemento del rettangolo nella riga sottostante, messo alla fine per eventuali rettangoli alti 1
                        flagr=0;                            //rettangolo finito
                }
                altezza=f-i;  //calcolo altezza
                base=g-j+1;     //calcolo base
                return area;
            }
        }
    }
}

