#include <stdio.h>
#include <stdlib.h>
#define NMAX 10
typedef struct
{
    int val;
    int cont;
}valori;
valori majority (int *vett,int N);

int main()
{
    int N,i;
    int contatore;
    valori maggioritario;
    int vettore[NMAX];
    printf("Quanti valori desidera inserire? ");
    scanf("%d",&N);
    if(N>NMAX)	//controllo che N non superi il limite superiore
    {
        fprintf(stderr,"Valore troppo alto!");
        exit(1);
    }
    for (i=0;i<N;i++)	//inserimento dei valori
    {
       printf("Inserisci valore: ");
       scanf("%d",&vettore[i]);
    }
    maggioritario=majority(vettore,N);
    contatore=0;
    if(maggioritario.cont!=0)	//ricerco se il valore ritornato è il maggioritario
    {
        for(i=0;i<N;i++)
        {
            if(maggioritario.val==vettore[i])
                contatore++;
        }
        if(contatore>N/2)	//condizione maggioritario
            printf("Valore maggioritario trovato: %d",maggioritario.val);
        else
            printf("Non esiste maggioritario");
    }
    else
        printf("Non esiste maggioritario");
    return 0;
}
valori majority (int *vett,int N)
{
    valori dx, sx;
    int *sin,*dest;
    int a;
    if(N==1)	//terminazione il vettore di lunghezza 1 ha maggioritario
    {
        sx.val=*vett;	//memorizzo il valore
        sx.cont++;	//agiorno cont
        return sx;
    }
    a=N/2;
    sin=vett;
    sx=majority(sin,a);	//chiamate ricorsive
    dest=vett+N;
    dx=majority(dest,N-a);
    if(sx.val==dx.val)	//se sono uguali, il loro valore può essere il maggioritario
    {
        sx.cont = sx.cont+dx.cont;	//aggiorno il contatore
        return sx;
    }
    else
    {
        if(sx.cont==dx.cont)	//se i valori non sono uguali, ma i contatori sono uguali
        {
            sx.val=-1;
            sx.cont=0;
            return sx;
        }
        if(sx.cont>dx.cont)	//se i contatori non sono uguali e nemmeno i valori
            return sx;
        else return dx;
    }
}
/*il programma si basa sull'osservazione che, se un elemento è il maggioritario, allora esso deve comparire in almeno una coppia di valori ottenuta con la ricorsione
se i valori di ritorno sono diversi, ma hanno i contatori uguali, azzero la ricerca, dato che, se uno di essi è il maggioritario, lo ritroverò in seguito.*/
