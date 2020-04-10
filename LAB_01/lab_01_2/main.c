#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  //struttura per contenere le parole con le rispettive cifrature
{
    char parola[10];
    char cifratura[10];
} cifrario;
void leggidizionario(FILE*fp2,FILE *fp);
void sostituisci(FILE *fp,int s,cifrario lista[s]);
int scorriparola(char linea[80],char parola [10],int j,int i);
int main()
{
    FILE *fp,*fp2;
    fp=fopen("sorgente.txt","r");
    fp2=fopen("dizionario.txt","r");

    if(fp==NULL) //controllo della consistenza dei file sorgente.txt
    {
        fprintf(stderr,"File sorgente.txt vuoto!\n");
        exit(1);
    }
    if(fp2==NULL)   //controllo della consistenza del file dizionario.txt
    {
        fprintf(stderr,"File dizionario.txt vuoto!\n");
        exit(2);
    }
    leggidizionario(fp2,fp);    //funzione per la lettura del dizionario
    fclose(fp2);
    fclose(fp);

    return 0;
}
void leggidizionario(FILE*fp2,FILE *fp)
{
    int s,i=0;
    fscanf(fp2,"%d",&s);
    cifrario lista [s]; //vettore di strutture per le s parole del dizionario
    while(i<s)
    {
        fscanf(fp2,"%s %s",&lista[i].cifratura,&lista[i].parola);   //acquisizione delle parole e della loro rispettiva cifratura
        i++;
    }

    sostituisci(fp,s,lista);    //funzione per la sostituzione
}
void sostituisci(FILE*fp,int s, cifrario lista[s])
{
    FILE *fp3;
    fp3=fopen("ricodificato.txt","w");
    char linea[80];
    int i,j,esci=0;
    int trovato=1;
    int lung;

    while(fgets(linea,80,fp)!=NULL) //leggo il file sorgente.txt
    {
        lung=strlen(linea);     //memorizzo la lunghezza della riga
        i=0;
        while(i<lung)
        {
            for(j=0;j<s && !esci;j++)   //se riesco a sostituire esco dal for, ripeto il ciclo per ogni parola del dizionario
            {
                if(lista[j].parola[0]==linea[i]) //confornto il carattere corrente di linea  con la prima lettera di ogni parola del dizionario
                {
                    trovato=scorriparola(linea,lista[j].parola,j,i);
                        if(trovato) //se ho trovato la parola da sostituire
                        {
                            fprintf(fp3,"%s",lista[j].cifratura); //cifro la parola, stampando sul nuovo file il corrispettivo in $numero$
                            i=i+strlen(lista[j].parola);        //porto l'indice di lettura dei caratteri di linea oltre la parola sostituita
                            esci=1;				//per uscita anticipata dal for (non c'è bisogno di controllare le altre parole del dizionario)
                        }
                }
            }
            if(!esci)   //confronto andato male, non è cambiato il flag
            {
                fprintf(fp3,"%c",linea[i]); //stampo carattere e proseguo con il prossimo da confrontare
                i++;			    //dato che ho stampato un solo carattere, i incrementa di uno				
            }
            else    //confronto con successo, il flag è cambiato (sono uscito in anticipo del ciclo)
                esci=0; //ricomincio un nuovo controllo impostando il flag a zero
        }
    }
    fclose(fp3);
}
int scorriparola(char linea [80],char parola[10],int j,int i)
{
    int h,t=1;
    for(h=i+1;h<i+(strlen(parola));h++,t++) //ciclo dall'indice i+1 di linea (all'indice i ho già fatto il controllo), per tutta la lunghezza della parola del dizionario
    {
        if(linea[h]!=parola[t]) 	//il confronto di un carattere fallisce
            return 0;
    }
    if(h==strlen(parola))   		//se ho raggiunto la fine della parola del dizionario senza intoppi, vuol dire che devo effettuare una sostituzione
        return 1;
    else
        return -1;          		//in caso di errore
}

