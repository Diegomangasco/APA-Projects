#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count=0;
typedef struct
{
	char **canzoni;
	int num_canzoni;
}persone;
persone *leggi_file(int *n,char s[20]);
void playlist(char **sol, int pos, persone *linker, int k);
int main()
{
    int i;
    int n;
    int t;
    char **sol;
    int pos;
    persone *amici;
    char s[20];
    strcpy(s,"brani.txt");
    amici=leggi_file(&n,s);
    printf("%s\n",amici->canzoni[0]);
    sol=malloc(n*sizeof(char *));	//allocazione di sol
    for(i=0;i<n;i++)
        sol[i]= malloc(256*sizeof(char));
    pos=t=0;
    playlist(sol,pos,amici,n);
    printf("%d\n",count);
    free(sol);
    return 0;
}
persone *leggi_file(int *n, char s[20])
{
    int i,j;
    persone *vett;
    FILE *fp;
    char stringa[256];
    fp=fopen(s,"r");
    fscanf(fp,"%d",n);
    vett=(persone *)malloc(*n*sizeof(persone));
    for(i=0;i<*n;i++)	//leggo il file e memorizzo i dati nella struttura
    {
        fscanf(fp,"%d",&vett[i].num_canzoni);
        vett[i].canzoni=calloc(vett[i].num_canzoni,sizeof(char*));	//a seconda del numero di canzoni alloco il vettore di puntatori
        for(j=0;j<vett[i].num_canzoni;j++)
        {
            fscanf(fp,"%s",stringa);
            vett[i].canzoni[j]=strdup(stringa);
        }
    }
    fclose(fp);
    return vett;
}
void playlist(char **sol, int pos, persone *linker, int k)
{
    int i;
	if(pos>=k)	//se ho raggiunto una playlist di 5 canzoni
	{
	    printf("Playlist:\n");
		for(i=0;i<k;i++)
			printf("%s\n",sol[i]);	//stampa di sol
		printf("\n");
		count++;	//tengo il conto delle soluzioni
		return;
	}
	for(i=0;i<linker[pos].num_canzoni;i++)	//ciclo per tutte le canzoni inserite da ogni amico
	{
		strcpy(sol[pos],linker[pos].canzoni[i]);
		playlist(sol,pos+1,linker,k);	
	}
	return;
}
