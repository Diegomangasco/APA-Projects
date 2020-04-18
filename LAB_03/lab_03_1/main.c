#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXR 50
typedef enum
{
    false,true
}boolean;
void leggimatrice(FILE *fp,int matrice[MAXR][MAXR],int *nr,int *nc);
boolean riconsciMatrice (int matrice[][MAXR],int nr, int nc,int r, int c, int *base, int *altezza);
int main()
{
    FILE *fp;
    char nome_file[10];
    int matrice[50][50];
    int nr,nc;
    int i,j;
    int base,altezza;
    printf("Inserisci il nome del file: ");
    scanf("%s",nome_file);
    fp=fopen(nome_file,"r");        //apertura del file
    if(fp==NULL)
    {
	fprintf(stderr,"File vuoto!);
	exit(1);
    }
    leggimatrice(fp,matrice,&nr,&nc);    //funzione per leggere il file
    fclose(fp);
    printf("\nNumero effettivo di righe e di colonne utilizzate: %d %d\n",nr,nc);

    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
        {
            if(riconsciMatrice(matrice,nr,nc,i,j,&base,&altezza)==true)
                printf("\nRettangolo trovato in <%d %d> con base %d, altezza %d e area %d\n",i,j,base,altezza,base*altezza);	//stampa risultati
        }
    }
    return 0;
}
void leggimatrice(FILE *fp,int matrice[MAXR][MAXR],int *nr,int *nc)
{
    int i=0,j=0;
    int numero;
    char linea[80];
    int cont=0;
    while(i<MAXR && fgets(linea,80,fp)!=NULL)
    {
        if(!i)	//controllo la prima riga per aggiornare nc
        {
            for(j=0;j<strlen(linea);j++)
            {
                if(isdigit(linea[j]))	//controllo che il carattere non sia uno spazio, ma un numero
                    cont++;
            }
            *nc=cont;
        }
        i++;	//i mi serve per contare il numero di righe
    }
    *nr=i;
    rewind(fp);	//il puntatore a file è arrivato al fondo, per memorizzare la matrice ho bisogno di riportarlo in cima al file
    for(i=0;i<*nr;i++)
    {
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&matrice[i][j]);	//memorizzo la matrice
    }

    for(i=0;i<*nr;i++)		//stampo la matrice
    {
        for(j=0;j<*nc;j++)
            printf("%d ",matrice[i][j]);
        printf("\n");
    }

}
boolean riconsciMatrice(int matrice[][MAXR],int nr, int nc,int r, int c, int *base, int *altezza)
{
    int flag=0,flagr=1;
    int f,g;
    if(matrice[r][c]==0)    //se l'elemento è zero si ritorna falso
        return false;
    else
    {
        if(r==0 && c==0)	//caso particolare prima cella
            flag=1;
        if(r==0 && c!=0)    //caso particolare della prima riga
        {
            if(matrice[r][c-1]==1)  //controllo se l'elemento appartiene già ad un rettangolo controllato in precedenza
                return false;
            else
                flag=1;
        }
        if(r!=0 && c==0)    //caso particolare della prima colonna
        {
            if(matrice[r-1][c]==1)  //controllo se l'elemento appartiene già ad un rettangolo controllato in precedenza
                return false;
            else
                flag=1;
        }
        if(r!=0 && c!=0)    //se non sono in una situazione particolare
        {
            if((matrice[r-1][c]==1)||(matrice[r][c-1]==1))  //se l'elemento è già contenuto in un rettangolo precedentemente controllato
                return false;
            else
                flag=1;
        }
        if(flag)	//se flag è uguale a 1, significa che sono in presenza di un nuovo rettangolo
        {
            for(f=r;f<nr && flagr;f++)
            {
                for(g=c;g<nc && matrice[f][g+1]==1;g++); //controllo l'elemento nella cella successiva
                if(matrice[f+1][c]!=1)                  //controllo primo elemento del rettangolo nella riga sottostante, messo alla fine per eventuali rettangoli alti 1
                    flagr=0;                            //rettangolo finito
            }
            *base=g-c+1;	//calcolo della base e dell'altezza
            *altezza=f-r;
            return true;
        }
    }
}
