#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef enum
{
   false,true
}boolean;
void stampaCodifica(void *p,int size,boolean bigEndian);
void stampabit(char buffer[]);
void convertiinbit(char buffer[],unsigned int n,int *t);
boolean endian();

int main()
{
    float af;
    double ad;
    long double ald;
    boolean bigEndian;
    bigEndian=endian();
    if(bigEndian==true)
        printf("Il calcolatore utilizza la codifica Big Endian\n");
    else
        printf("Il calcolatore utilizza la codifica Little Endian\n");

    printf("Dimensione float: %d bytes (%d bits)\nDimensione double: %d bytes (%d bits)\nDimensione long double: %d bytes (%d bits)\n",sizeof(af),sizeof(af)*8,sizeof(ad),sizeof(ad)*8,sizeof(ald),sizeof(ald)*8);

    printf("Inserisci un numero decimale (con virgola) ed eventuale esponente (in base 10): ");
    scanf("%fe",&af);   //acquisizione del numero in af e copiatura nelle altre due variabili
    ad=(double)af;
    ald=(long double)af;
    printf("Float: \n");
    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    printf("Double: \n");
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    printf("Long double: \n");
    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);
    return 0;
}
boolean endian()    //funzione per capire che tipo di codifica usa il mio pc
{
    unsigned int i=1;
    char *b = (char*)&i;    //ora b punta alla cella di memoria che prima era puntata da p
    if(*b)                  //dato che b è di tipo char, ogni cella occupa in memoria uno spazio di un byte
        return false;        // se la prima cella (quella puntata da b) contiene 7 bits di zeri ed un bit di 1, allora siamo di fronte ad una codifica big endian
    else
        return true;       // se la prima cella (quella puntata da b) contiene 8 bits di zeri, allora siamo di fronte ad una codifica little endian
}
void stampaCodifica(void *p,int size,boolean bigEndian)
{
    int i,t;
    int lung =size*8;   //numero di bit
    char buffer[lung];
    unsigned char *vett;

    vett=(unsigned char*)p;    //copio le variabili puntate da p in vett, dato che ogni casella di vett, può contenere 8 bit
    t=0;
    if(!bigEndian)
    {
        for(i=size-1;i>=0;i--) //scorro i singoli byte nella convenzione Little Endian
        {
            convertiinbit(buffer,(unsigned int)vett[i],&t);   //passo alla funzione la stringa per memorizzare, il byte corrente e il contatore che mi indica a che casella di buffer sono arrivato
        }

    }
    else
    {
        for(i=0;i<size;i++) //scorro i singoli byte nella convenzione Little Endian
        {
             convertiinbit(buffer,(unsigned int)vett[i],&t);  //passo alla funzione la stringa per memorizzare, il byte corrente e il contatore che mi indica a che casella di buffer sono arrivato
        }
    }
    buffer[lung]='\0';  //terminazione del buffer
    stampabit(buffer);
}
void stampabit(char buffer[])
{
    int i;
    int size2=strlen(buffer);
    printf("Segno: %c ",buffer[0]); //bit di segno
    int size=size2/8;
    switch(size)
    {
    case 4: //stampa del float secondo lo standard IEEE 754
        printf("\nEsponente: ");
        for(i=1;i<9;i++)
            printf("%c ",buffer[i]);
        printf("\nMantissa: ");
        for(i=9;i<size2;i++)
            printf("%c ",buffer[i]);
        printf("\n");
        break;
    case 8: //stampa del double secondo lo standard IEEE 754
        printf("\nEsponente ");
        for(i=1;i<12;i++)
            printf("%c ",buffer[i]);
        printf("\nMantissa ");
        for(i=12;i<size2;i++)
            printf("%c ",buffer[i]);
        printf("\n");
        break;
    case 12:  //stampa del long double secondo lo standard IEEE 754
        printf("Segno: %c \n",buffer[16]);
        printf("\nEsponente ");
        for(i=17;i<32;i++)
            printf("%c ",buffer[i]);
        printf("\nMantissa: ");
        for(i=33;i<size2;i++)
            printf("%c ",buffer[i]);
        printf("\n");
        break;
    }
    printf("\n");

}
void convertiinbit(char buffer[],unsigned int n,int *t)   //funzione per memorizzare i bits del byte passato, in buffer
{
   int k;
   for(k=7;k>=0;k--)
   {
       if(n>=pow(2,k))
       {
        buffer[*t]='1';
        n=n-pow(2,k);
       }
       else{
        buffer[*t]='0';
       }
       *t=*t+1; //aggiorno la variabile puntata da t (il contatore per le celle di buffer)
   }

}
