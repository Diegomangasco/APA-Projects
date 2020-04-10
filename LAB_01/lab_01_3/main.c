#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int controllo(char selettore[8]);
void gira(int indice, int riga[30],int posizioni,char direzione[9],int lim);
int main()
{
    char selettore [8],indice,direzione[9],posizioni;
    int matrice[30][30];
    int nr,nc;
    int i=1,r,j;
    int riga[30];
    FILE *fp;
    char nome_file[21];
    printf("Inserisci il nome del file\n");
    scanf("%s",nome_file);
    fp=fopen(nome_file,"r");		//controllo di consistenza del file
    if(!fp)
    {
        fprintf(stderr,"File vuoto.\n");
        exit(1);
    }
    fscanf(fp,"%d %d", &nr, &nc);
    if(nr>30 || nc>30)			//controllo che i valori presenti nel file rispettino i limiti
    {
        fprintf(stderr,"Matrice troppo grande");
        exit(2);
    }
    while(i)				//richiesta iterativa
    {
        printf("Inserisci Riga o Colonna, Indice, Direzione, Posizioni, o Fine: ");
        scanf("%s %c %s %c", selettore, &indice, direzione, &posizioni);
        r = controllo(selettore);
        switch(r){	//a seconda della richiesta (riga colonna o fine)
    case 1:
        for(j=0;j<nr;j++)
            riga[j]=matrice[(int)atoi(indice)][j];	//copio nel vettore riga, la riga selezionata
        gira((int)atoi(indice),riga,(int)atoi(posizioni),direzione,nc);
        for(j=0;j<nc;j++)
            matrice[(int)atoi(indice)][j]=riga[j];	//ricopio riga modificata dalla funzione, nella matrice
        break;
    case 2:
        for(j=0;j<nr;j++)
            riga[j]=matrice[j][(int)atoi(indice)];	//copio nel vettore riga, la colonna selezionata
        gira((int)atoi(indice),riga,(int)atoi(posizioni),direzione,nr);
        for(j=0;j<nr;j++)
            matrice[j][(int)atoi(indice)]=riga[j];	//ricopio riga modificata dalla funzione, nella matrice
        break;
    case 3:						//terminazione
        i=0;
	break;
    default;
	printf("Errore! Riprova\n");	
        }
    }

    return 0;
}
int controllo(char selettore[8])	//funzione per il controllo del selettore
{
    if(!strcmp(selettore,"riga"))
        return 1;
    if(!strcmp(selettore,"colonna"))
        return 2;
    if(!strcmp(selettore,"fine"))
        return 3;
    else
        return 3;
}
void gira(int indice, int riga[30],int posizioni,char direzione[9],int lim)
{
    int vett[30];
    int i,j;

    if((!strcmp(direzione,"destra")) || (!strcmp(direzione,"giu")))	//interpreto i le direzioni "destra" e "giù" come la stessa cosa, dato che lavoro su riga
    {
        j=0;
        for(i=0;i<lim;i++)
        {
            if((i+posizioni)<lim)			//copio le prime caselle di riga, nelle ultime caselle di vett
                vett[i+posizioni]=riga[i];
            else{
                vett[j]=riga[i];			//quando ho superato la lunghezza della riga o colonna (nr o nc), copio le ultime caselle di riga, nelle prime posizioni di vett
                j++;
            }
        }

        for(i=0;i<lim;i++)		//ricopio vett, in riga, così da trasformarla
            riga[i]=vett[i];
    }
    else				//caso "sinistra" o "su"
    {
        j=lim-1;
        for(i=lim-1;i>-1;i--)		
        {
            if((i-posizioni)>=0)
                vett[i-posizioni]=riga[i];	//copio le ultime caselle di riga nelle prime caselle di vett
            else{
                vett[j]=riga[i];		//quando ho superato la lunghezza (nr o nc) massima, copio le prime caselle di riga, nelle ultime caselle di vett
                j--;
            }
        }
         for(i=0;i<lim;i++)
            riga[i]=vett[i];			//ricopio vett, in riga, così da trasformarla
    }

}
