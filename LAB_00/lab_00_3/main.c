#include <stdio.h>
#include <stdlib.h>
#define MaxN 30

void ruota(int vett[MaxN], int dir, int P, int N);
int main()
{
    int vett[MaxN];
    int N;
    int P;
    int dir;
    int i;

    printf("Inserisci il numero di caselle (minore di 30): "); /*controllo del numero inserito*/
    scanf("%d",&N);
    if(!(N<=MaxN))
    {
        printf(stderr,"Il numero deve essere minore di trenta!");
        return -1;
    }

    i=0;
    do{
    printf("Inserisci un numero: "); /*acquisizione del vettore*/
    scanf("%d",&vett[i]);
    printf("\n");
    i++;
    }while(i<N);

    printf("Inserisci rispettivamente, i passi da fare e la direzione(1 per destra, -1 per sinistra): ");
    scanf("%d %d", &P, &dir);

    ruota(vett,dir,P,N);

    return 0;
}
void ruota(int vett[MaxN], int dir, int P, int N)
{
    int i,j;
    int conta;
    int vett2[N];
    conta=0;

    for(i=0;i<N;i++)
        vett2[i]=0;

    if(dir==1)
    {
        for (i=0;i<N;i++) /*conteggio delle caselle che possono essere spostate senza sforare*/
        {
            if((i+P)<N)
                conta++;
        }

        for (i=0;i<conta;i++)/*spostamento dei valori delle caselle, nelle nuove allocazioni del vett2*/
            vett2[i+P]=vett[i];

        j=0;
        for (i=conta;i<N;i++)/*spostamento nel vett2 dei valori che avrebbero sforato con i passi*/
        {
            vett2[j]=vett[i];
            j++;
        }
    }
    else
    {
        for (i=N-1;i>=0;i--) /*conteggio delle caselle che possono essere spostate senza sforare*/
        {
            if((i-P)>=0)
                conta++;
        }

        for (i=N-1;i-P>=0;i--)/*spostamento dei valori delle caselle, nelle nuove allocazioni del vett2*/
            vett2[i-P]=vett[i];

        j=0;
        for (i=conta;i<N;i++){/*spostamento nel vett2 dei valori che avrebbero sforato con i passi*/
            vett2[i]=vett[j];
            j++;
    }
    }

    for(i=0;i<N;i++)
        printf("%d ",vett2[i]);
}




