#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef enum{
r_date,r_partenza,r_capolinea,r_ritardi,r_ritardo_tot,r_fine
}comando;
typedef struct{		//struttura per contenere i dati del file
int codice;
char partenza[30];
char capolinea[30];
char data[11];
char h_partenza[6];
char h_arrivo[6];
int ritardo;
}treno;
int j;			//istanziata globalmente per facilità nel passaggio alle numerose funzioni successive
treno lista[1000];	//istanziata globalmente per facilità nel passaggio alle numerose funzioni successive
comando leggicomando(char linea[20]);
void leggifile(char nome_file[10]);
void date();
void partenza();
void capolinea();
void ritardo();
void ritardi_tot();
void stampa_lista(int t);
int main()
{
    char nome_file[10]="treni.txt";
    char linea[20];
    int flag=1;
    leggifile(nome_file);
    while(flag){		//menù che si interrompe solo per volere dell'utente
        printf("\nChe informazione vorresti avere?\n\nDigita una tra queste parole: date, partenze, capolinea, ritardi, ritardo_totale\n\nDigita 'fine' per terminare\n");
        scanf("%s",linea);
        switch(leggicomando(linea)){	//switch-case comandato tramite il tipo comando (enum)
            case r_date:
                date();
                break;
            case r_partenza:
                partenza();
                break;
            case r_capolinea:
                capolinea();
                break;
            case r_ritardi:
                ritardo();
                break;
            case r_ritardo_tot:
                ritardi_tot();
                break;
            case r_fine:
                printf("\nGrazie per aver usato il nostro servizio\n");
                flag=0;				//fine utilizzo deciso dall'utente
                break;
            default:
                printf("\nComando errato!\n");	//errore nel comando
                break;
        }
    }

    return 0;
}
comando leggicomando(char linea[20])
{
    comando c;
    c=r_date;
    char tabella [6][20] ={"date","partenze","capolinea","ritardi","ritardo_totale","fine"};	//matrice con le possibili scelte
    while(c<5 && strcmp(linea,tabella[c]))	//confronto tra il comando e la lista presente in tabella
        c++;
    return c;	//valore per lo switch-case
}
void leggifile(char nome_file[10])
{
    int numero,i=0;
    FILE *fp;
    fp=fopen(nome_file,"r");
    fscanf(fp,"%d",&numero);
    while(i<numero)	//lettura del file e memorizzazione nella struttura
    {
        fscanf(fp,"%d %s %s %s %s %s %d",&lista[i].codice,lista[i].partenza,lista[i].capolinea,lista[i].data,lista[i].h_partenza,lista[i].h_arrivo,&lista[i].ritardo);
        i++;
    }
    j=i;	//j è globale, in modo che possa essere utilizzata da tutte le funzioni
}
void stampa_lista(int t)	//funzione per la stampa di alcuni risultati
{
  if(t==-1) //se non si trovano corrispondenze
	printf("\nControlla di aver inserito le informazioni in modo corretto\n");
  else
  	printf("%d %s %s %s %s %s %d\n",lista[t].codice,lista[t].partenza,lista[t].capolinea,lista[t].data,lista[t].h_partenza,lista[t].h_arrivo,lista[t].ritardo);
}
void date()	//funzione per il controllo delle corse tra due date
{
    char data1[10];
    char data2[10];
    int i,t=-1;
    printf("Inserisci un intervallo di date nella forma anno/mese/giorno: ");	//utilizzo la forma anno/mese/giorno per poter utilizzare un confronto fatto con la funzione strcmp
    scanf("%s %s",data1,data2);
    printf("\nCorse tra le date selezionate:\n");
    for(i=0;i<j;i++)
    {
        if(strcmp(lista[i].data,data1)>0 && strcmp(lista[i].data,data2)<0){ //cerco tutte le corse partite in un certo intervallo di date
            t=i;
            stampa_lista(t);
        }
    }
    if(t==-1)
        stampa_lista(t);
}
void partenza()	//funzione per il controllo delle stazioni di partenza
{
    char partenza[20];
    int i,t=-1;
    printf("Inserisci la stazione di partenza: ");
    scanf("%s",partenza);
    partenza[0]=tolower(partenza[0]);	//per evitare il confronto con le maiuscole
    printf("\nCorse con partenza richiesta:\n");
    for(i=0;i<j;i++)
    {
        lista[i].partenza[0]=tolower(lista[i].partenza[0]);
        if(!strcmp(lista[i].partenza,partenza)){	//quando trova la stazione di partenza cercata
            lista[i].partenza[0]=toupper(lista[i].partenza[0]);
            t=i;
            stampa_lista(t);
        }
    }
    if(t==-1)
        stampa_lista(t);
}
void capolinea()	//stessa funzione della funzione void partenza(), ma fatta per la ricerca dei capolinea
{
    char arrivo[20];
    int i,t=-1;
    printf("Inserisci la stazione di arrivo: ");
    scanf("%s",arrivo);
    arrivo[0]=tolower(arrivo[0]);
    printf("\nCorse con arrivo richiesto:\n");
    for(i=0;i<j;i++)
    {
        lista[i].capolinea[0]=tolower(lista[i].capolinea[0]);
        if(!strcmp(lista[i].capolinea,arrivo)){
            t=i;
            lista[i].capolinea[0]=toupper(lista[i].capolinea[0]);
            stampa_lista(t);
        }
    }
    if(t==-1)
        stampa_lista(t);
}
void ritardo()	//funzione per calcolare le corse in ritardo fra due date
{
    char data1[20];
    char data2[20];
    int i,t=-1;
    printf("Inserisci un intervallo di date nella forma anno/mese/giorno: ");
    scanf("%s %s",data1,data2);
    printf("\nRitardi tra le date selezionate:\n");
    for(i=0;i<j;i++)
    {
        if(strcmp(lista[i].data,data1)>0 && strcmp(lista[i].data,data2)<0)	//cerco tutte le corse in un certo intervallo di date
        {
            t=0;
            if(lista[i].ritardo>0){	//se la corsa presenta ritardo
                t=i;
            	stampa_lista(t);
            }
        }
    }
    if(t==-1)
        stampa_lista(t);
    if(t==0)    //caso particolare: corrispondenza trovata, ma senza ritardi
        printf("\nNon sono presenti corse in ritardo in questo intervallo di date\n");

}
void ritardi_tot()	//funzione per calcolare il ritardo totale di una certa tratta, specificata dal codice
{
    int i,t=-1;
    int codice;
    int ritardo_totale=0;
    printf("Inserisci il codice della linea:\n");
    scanf("%d",&codice);
    for(i=0;i<j;i++)
    {
        if(lista[i].codice==codice){		//confronto tra il codice inserito e i codici della lista
            ritardo_totale+=lista[i].ritardo;	//incremento del ritardo totale
	    t=0;
	}
    }
    if(t==-1)
        printf("Controlla di aver inserito le informazioni in modo corretto\n");
    else
    	printf("Il ritardo totale sulle linea %d e' di %d minuti\n",codice,ritardo_totale);
}
