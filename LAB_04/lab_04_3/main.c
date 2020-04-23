#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int controllaregexp(char *regexp);
int switchcase(int c,char lettera,char *regexp);
char *cercaregexp(char *frase, char*regexp);
int main()
{
    char *src;
    char stringa1[80],stringa2[80];
    char *frase=malloc(80*sizeof(char)),*regexp=malloc(80*sizeof(char));
    printf("Inserisci una frase: ");
    gets(stringa1);
    frase=stringa1;
    printf("Inserisci l'espressione regolare da ricercare: ");
    gets(stringa2);
    regexp=stringa2;
    printf(" \n");
    src=cercaregexp(frase,regexp);
    if(*src!='\0')	//cercaregexp con successo
        printf("Indirizzo di memoria della prima occorrenza= %d",*src);
    else
        printf("Nessuna occorrenza trovata per la regexp inserita!");
    free(frase);
    free(regexp);
    return 0;
}
char *cercaregexp(char *frase, char *regexp)
{
    int i,c;
    char *tmp;
    char lettera;
    char *inizio;
    int trovato;
    tmp=regexp;
    *inizio='\0';
    for(i=0;*frase!='\0';i++)	//ciclo fino alla termianzione della frase
    {
        lettera=*frase;	//assegno a lettera il contenuto puntato da frase
        c=controllaregexp(regexp);	//trovo il tipo di regexp attualmente in analisi
        trovato=switchcase(c,lettera,regexp);
        if(!trovato)	//se non ho trovato corrispondenza con la regexp
        {
            regexp=tmp; 	//riporto la regexp in posizione iniziale memorizzata in tmp
            frase++;		//passo alla prossima lettera
            *inizio='\0';	//riporto inizio a puntare a NULL (occorrenza non trovata)
        }
        else
        {
            if(*inizio=='\0')
                inizio=frase;	//memorizzo l'indirizzo di memoria della possibile occorrenza
            if(c==1 || c==2)    //aumento per maiuscola o minuscola
                regexp=regexp+2;
            if(c==3 || c==4)    //aumento per esclusione e inclusione
            {
                while(*regexp!=']')
                    regexp++;
                regexp++;
            }
            if(c==5 || c==6)    //aumento per punto o carattere specifico
                regexp++;
            if(*regexp=='\0')	//finito la regexp -> ho trovato un'occorrenza
                return inizio;
            frase++;		//prossima lettera
        }
    }
    if(*regexp=='\0')	//ho finito la frase e anche la regexp
        return inizio;
    else
        return (char *)NULL;	//ho finito la frase, ma non la regexp
}
int controllaregexp(char *regexp)	//tipo di regexp richiesta
{
    if(*regexp==92) //ascii del backslash
    {
        regexp++;
        if(islower(*regexp))    //controllo minuscola
            return 1;
        else
            return 2;
    }
    if(*regexp==91) //ascii della parentesi quadra
    {
        regexp++;
        if(*regexp==94) //ascii di ^ (esclusione)
            return 3;
        else            //inclusione
            return 4;
    }
    if(*regexp==46) //asci del punto
        return 5;
    if (isalpha(*regexp)) //normale carattere
        return 6;
    return 0;
}
int switchcase(int c,char lettera,char *regexp)
{
    switch(c)	//analizzo la lettera della frase, a seconda della regexp richiesta
    {
    case 0: //regexp non valida
        fprintf(stderr,"Errore nella regexp!");
        exit(1);
    case 1: //minuscola
        if(islower(lettera)) return 1;
        else return 0;
        break;
    case 2: //maiuscola
        if(isupper(lettera)) return 1;
        else return 0;
        break;
    case 3: //esclusione
        regexp=regexp+2;
        while(*regexp!=']')
        {
            if(lettera==*regexp)	//se la lettera è compresa nella lista di quelle da escludere
                return 0;
            regexp++;
        }
        return 1;
        break;
    case 4: //inclusione
        regexp++;
        while(*regexp!=']')
        {
            if(lettera==*regexp)	//se trovo la lettera, nella lista di quelle da comprendere
                return 1;
            regexp++;
        }
        return 0;
        break;
    case 5: //punto
        if(isalpha(lettera))
            return 1;
        else
            return 0;
        break;
    case 6: //carattere specifico
        if(lettera==*regexp)
            return 1;
        else
            return 0;
        break;
    }
}
