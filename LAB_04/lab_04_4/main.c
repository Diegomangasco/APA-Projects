#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  //struttura per le corse
{
    int codice;
    char partenza[20];
    char arrivo[20];
    char data[15];
    char ora_p[10];
    char ora_a[10];
    int ritardo;
}treni;
void stampa_linker_file(treni *linker[20],int i);
void stampa_linker(treni *linker[20],int i);
void mergesort(int caso, treni *linker[20],treni corse[20], int l, int r);
void merge(int caso, treni *linker[20], treni corse[20],int p, int q, int r);
//treni ricerca(int caso, treni *linker[20],int l, int r);
int scelta();
int main()
{
    FILE *fp;
    int righe,i,file,scelta_fatta;
    int giusto=0;
    treni corse[20];
    treni *linker_p[20],*linker_a[20],*linker_d[20],*linker_c[20],*trovato;
    fp=fopen("treni.txt","r");
    fscanf(fp,"%d",&righe); //numero corse
    for(i=0;i<righe;i++)
    {
        fscanf(fp,"%d %s %s %s %s %s %d", &corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_p,corse[i].ora_a,&corse[i].ritardo);
        linker_p[i]=&corse[i];    //assegno al linker gli indirizzi di memoria del vettore di strutture
        linker_a[i]=&corse[i];
        linker_c[i]=&corse[i];
        linker_d[i]=&corse[i];
    }
    fclose(fp);
    printf("Dove desidera stampare i dati?\nInserisci 1 per stampare a video, 2 per stampare su file: ");
    scanf("%d",&file);
    while(!giusto)
    {
        if(file==1) //stampa a video
        {
            stampa_linker(linker_p,i);
            giusto=1;
        }
        else if (file==2)   //stampa su file
        {
            stampa_linker_file(linker_p,i);
            giusto = 1;
        }
        else
            printf("Inserisci un valore corretto!");
    }
    giusto=1;
    while(giusto)
    {
        scelta_fatta=scelta();
        switch (scelta_fatta)   //scelta dell'ordinamento
        {
           case 1:  //partenze
                mergesort(scelta_fatta,linker_p,corse,0,i-1);
                stampa_linker(linker_p,i);
            break;
           case 2:  //data
                mergesort(scelta_fatta,linker_d,corse,0,i-1);
                stampa_linker(linker_d,i);
            break;
           case 3:  //codice
                mergesort(scelta_fatta,linker_c,corse,0,i-1);
                stampa_linker(linker_c,i);
            break;
           case 4:  //arrivi
                mergesort(scelta_fatta,linker_a,corse,0,i-1);
                stampa_linker(linker_a,i);
            break;
           case 5:
                printf("Grazie e arrivederci.\n");
                giusto=0;
                break;
           default:
            printf("Opzione non disponibile, riprova.\n");
         }
    }
    printf("Per ricercare una corsa:\n1)per partenza\n2)per data\n3)per codice\n4)per arrivo\n");
    scanf("%d",scelta_fatta);
    /*switch(scelta_fatta)
    {

    }*/

    return 0;
}
void stampa_linker_file(treni *linker[20],int i)    //stampa su file attraverso i linker
{
    FILE *fp2;
    int j;
    fp2=fopen("stampa.txt","w");
    for(j=0;j<i;j++)
        fprintf(fp2,"%d %s %s %s %s %s %d\n",linker[j]->codice,linker[j]->partenza,linker[j]->arrivo,linker[j]->data,linker[j]->ora_p,linker[j]->ora_a,linker[j]->ritardo);
    fclose(fp2);
}
void stampa_linker(treni *linker[20],int i) //stampa attraverso i linker ordinati e non
{
    int j;
    for(j=0;j<i;j++)
        printf("\n%d %s %s %s %s %s %d\n",linker[j]->codice,linker[j]->partenza,linker[j]->arrivo,linker[j]->data,linker[j]->ora_p,linker[j]->ora_a,linker[j]->ritardo);
}
int scelta()
{
    int n;
    printf("\nInserisci un numero\n1)per ordinare la lista per partenze\n2)per ordinare la lista per data\n3)per ordinare la lista per codice\n4)per ordinare la lista per arrivi\n5)per terminare\n");
    scanf("%d",&n);
    return n;
}
void mergesort(int caso, treni *linker[20],treni corse[20], int l, int r)
{
    int q;
    if (l >= r)
        return;
    q = (l+r)/2;
    mergesort(caso,linker,corse,l,q);
    mergesort(caso,linker,corse,q+1,r);
    merge(caso,linker,corse,l,q,r);
}
void merge(int caso, treni *linker[20], treni corse[20], int p, int q, int r)
{
    int i, j, k;
    i = p;
    j = q+1;
    switch (caso)   //diverse ricombinazioni a seconda del caso scelto dall'utente
    {
    case 1: //partenze
        while (i<=q && j<=r)
        {
            if (strcmp(corse[i].partenza,corse[j].partenza)<0)
            {
              linker[k] = &corse[i];
              i++;
            }
            else
            {
              linker[k] = &corse[j];
              j++;
            }
            k++;
        }
        while (i <= q)
        {
            linker[k] = &corse[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            linker[k] = &corse[j];
            j++;
            k++;
        }
        break;

    case 2: //data
        while (i<=q && j<=r)
        {
            if (strcmp(corse[i].data,corse[j].data)<0)
            {
              linker[k] = &corse[i];
              i++;
            }
            else if (strcmp(corse[i].data,corse[j].data)==0)
            {
                if (strcmp(corse[i].ora_p,corse[j].ora_p)<0)
                    {
                        linker[k] = &corse[i];
                        i++;
                    }
                else
                    {
                        linker[k] = &corse[j];
                        j++;
                    }
            }
            else
            {
              linker[k] = &corse[j];
              j++;
            }
            k++;
        }
        while (i <= q)
        {
            linker[k] = &corse[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            linker[k] = &corse[j];
            j++;
            k++;
        }
        break;

    case 3: //codice
        /*while (i<=q && j<=r)
        {
            if (corse[i].codice<corse[j].codice)
            {
              linker[k] = &corse[i];
              i++;
            }
            else
            {
              linker[k] = &corse[j];
              j++;
            }
            k++;
        }
        while (i <= q)
        {
            linker[k] = &corse[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            linker[k] = &corse[j];
            j++;
            k++;
        }
        return;*/
        for(k=p;k<=r;k++)
        {
            if(i>q)
                linker[k]=&corse[j++];
            else if (j>r)
                linker[k]=&corse[i++];
            else if (corse[i].codice>=corse[j].codice)
                linker[k]=&corse[i++];
            else
                linker[k]=&corse[j++];
        }
        return;
        break;

    case 4: //arrivi
        while (i<=q && j<=r)
        {
            if (strcmp(corse[i].arrivo,corse[j].arrivo))
            {
              linker[k] = &corse[i];
              i++;
            }
            else
            {
              linker[k] = &corse[j];
              j++;
            }
            k++;
        }
        while (i <= q)
        {
            linker[k] = &corse[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            linker[k] = &corse[j];
            j++;
            k++;
        }
        break;
    }
    return;
}
/*void ricerca(int caso,treni *linker[20],int l,int r)
{
    switch(caso)
    {
    case 1: //partenze
        int m=(l+r)/2;
        if(strcmp(linker[m]->partenza,)==0)
            return linker;
        if(strcmp(linker->partenza,)<0)
            ricerca(caso,linker,m+1,r);
        else
            ricerca(caso,linker,l,m);
    }

}*/
