#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
int acquisizione(treni **linker_p, treni **linker_a, treni **linker_d, treni **linker_c, int volta);
void stampa_linker_file(treni *linker,int i);
void stampa_linker(treni *linker,int i);
void bubble(int caso, treni **linker, int i);
void ricerca_dic(treni *linker, char *citta,int l,int r);
void ricerca_lin(treni *linker,char *citta,int i);
int scelta();
int main()
{
    int i,file,scelta_fatta;
    char *citta=malloc(20*sizeof(char));
    int giusto=0;
    int ordine = 0;
    int volta = 0;
    int fine = 0;
    int caso;
    treni *linker_p,*linker_a,*linker_d,*linker_c;
    i=acquisizione(&linker_p, &linker_a, &linker_d, &linker_c, volta);
    volta++;
    do
    {
        printf("\nCosa desidera fare?\n1)Inserire un nuovo file\n2)Visualizzare il contenuto del file corrente\n3)Ordinare i dati del file\n5)Ricercare una stazione\n6)Terminare\n");
        scanf("%d",&caso);
        switch(caso)
        {
        case 1:
            i=acquisizione(&linker_p, &linker_a, &linker_d, &linker_c, volta);	//acquisizione nuovo file
            break;
        case 2:
            giusto=0;
            while(!giusto)
            {
                printf("Dove desidera stampare i dati?\nInserisci 1 per stampare a video, 2 per stampare su file: ");
                scanf("%d",&file);
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
            break;
        case 3:
            giusto=1;
            while(giusto)
            {
                scelta_fatta=scelta();
                switch (scelta_fatta)   //scelta dell'ordinamento
                {
                   case 1:  //partenze
                        ordine = 1;
                        bubble(scelta_fatta,&linker_p,i);
                        stampa_linker(linker_p,i);
                    break;
                   case 2:  //data
                        bubble(scelta_fatta,&linker_d,i);
                        stampa_linker(linker_d,i);
                    break;
                   case 3:  //codice
                        bubble(scelta_fatta,&linker_c,i);
                        stampa_linker(linker_c,i);
                    break;
                   case 4:  //arrivi
                        bubble(scelta_fatta,&linker_a,i);
                        stampa_linker(linker_a,i);
                    break;
                   case 5:
                        printf("Prossime operazioni: \n");
                        giusto=0;
                        break;
                   default:
                    printf("Opzione non disponibile, riprova.\n");
                 }
            }
            break;
        case 4:
            printf("Per ricercare una corsa a partire dalla stazione di partenza, inserisci il nome della citta': ");
            scanf("%s",citta);
            if(ordine)	//se ho ordinato per partenze
                ricerca_dic(linker_p,citta,0,i-1);
            else
                ricerca_lin(linker_p,citta,i);
            break;
        case 5:
            printf("Grazie ed arrivederci!\n");
            fine = 1;
            break;
        default:
            printf("Valore sbagliato, riprova\n");
        }
    }while(fine==0);
    return 0;
}
int acquisizione(treni **linker_p, treni **linker_a, treni **linker_d, treni **linker_c, int volta)
{
    int i,righe;
    FILE *fp;
    treni corse;
    char *nome = malloc(80*sizeof(char));
    printf("Inserisci il nome del file e l'estensione: ");
    scanf("%s", nome);
    fp=fopen(nome,"r");
    free(nome);
    fscanf(fp,"%d",&righe); //numero corse
    if(!volta)  //per la prima volta non ho bisogno di liberare i vettori
    {
        *linker_p=malloc(righe*sizeof(treni));
        *linker_a=malloc(righe*sizeof(treni));
        *linker_d=malloc(righe*sizeof(treni));
        *linker_c=malloc(righe*sizeof(treni));
        for(i=0;i<righe;i++)
        {
            fscanf(fp,"%d %s %s %s %s %s %d", &corse.codice,corse.partenza,corse.arrivo,corse.data,corse.ora_p,corse.ora_a,&corse.ritardo);
            (*linker_p)[i]=corse;    //assegno al contenuto puntato da **linker in posizione i, il contenuto di corse
            (*linker_a)[i]=corse;
            (*linker_c)[i]=corse;
            (*linker_d)[i]=corse;
        }
    }
    else
    {
        free(linker_p);
        free(linker_a);
        free(linker_c);
        free(linker_d);
        (*linker_p)=malloc(righe*sizeof(treni));
        (*linker_a)=malloc(righe*sizeof(treni));
        (*linker_d)=malloc(righe*sizeof(treni));
        (*linker_c)=malloc(righe*sizeof(treni));
        for(i=0;i<righe;i++)
        {
            fscanf(fp,"%d %s %s %s %s %s %d", &corse.codice,corse.partenza,corse.arrivo,corse.data,corse.ora_p,corse.ora_a,&corse.ritardo);
            (*linker_p)[i]=corse;    //assegno al contenuto puntato da **linker in posizione i, il contenuto di corse
            (*linker_a)[i]=corse;
            (*linker_c)[i]=corse;
            (*linker_d)[i]=corse;
        }
    }
    fclose(fp);
    return righe;
}
void stampa_linker_file(treni *linker,int i)    //stampa su file attraverso i linker
{
    FILE *fp2;
    int j;
    fp2=fopen("stampa.txt","w");
    for(j=0;j<i;j++)
        fprintf(fp2,"%d %s %s %s %s %s %d\n",linker[j].codice,linker[j].partenza,linker[j].arrivo,linker[j].data,linker[j].ora_p,linker[j].ora_a,linker[j].ritardo);
    fclose(fp2);
}
void stampa_linker(treni *linker,int i) //stampa attraverso i linker ordinati e non
{
    int j;
    for(j=0;j<i;j++)
        printf("\n%d %s %s %s %s %s %d\n",linker[j].codice,linker[j].partenza,linker[j].arrivo,linker[j].data,linker[j].ora_p,linker[j].ora_a,linker[j].ritardo);
}
int scelta()
{
    int n;
    printf("\nInserisci un numero\n1)per ordinare la lista per partenze\n2)per ordinare la lista per data\n3)per ordinare la lista per codice\n4)per ordinare la lista per arrivi\n5)per terminare\n");
    scanf("%d",&n);
    return n;
}

void bubble(int caso, treni **linker, int i)    //bubble sort (stabile) con i linker
{
    int t, j,r=i-1;
    treni tmp;
    //treni *l=malloc(i*sizeof(treni));
    switch (caso)   //diverse ricombinazioni a seconda del caso scelto dall'utente
    {
    case 1: //partenze
        for(t = 0; t<r; t++)
        {
            for(j = 0; j<r-t;j++)
            {
                if (strcmp((*linker)[j].partenza,(*linker)[j+1].partenza)>0)
                {
                    tmp=(*linker)[j];
                    (*linker)[j] = (*linker)[j+1];
                    (*linker)[j+1]=tmp;
                }
            }
        }
        return;
    case 2: //data
        for(t = 0; t<r; t++)
        {
            for(j = 0; j<r-t;j++)
            {
                if(strcmp((*linker)[j].data,(*linker)[j+1].data)>0)
                {
                    tmp=(*linker)[j];
                    (*linker)[j] = (*linker)[j+1];
                    (*linker)[j+1] = tmp;
                }
                else if (strcmp((*linker)[j].data,(*linker)[j+1].data)==0)
                {
                    if(strcmp((*linker)[j].ora_p,(*linker)[j+1].ora_p)>0)
                    {
                        tmp=(*linker)[j];
                        (*linker)[j] = (*linker)[j+1];
                        (*linker)[j+1] = tmp;
                    }
                }
            }
        }
        return;

    case 3: //codice
        for(t = 0; t<r; t++)
        {
            for(j = 0; j<r-t;j++)
            {
                if((*linker)[j].codice>=(*linker)[j+1].codice)
                {
                    tmp=(*linker)[j];
                    (*linker)[j] = (*linker)[j+1];
                    (*linker)[j+1] = tmp;
                }
            }
        }
        return;
    case 4: //arrivi
        for(t = 0; t<r; t++)
        {
            for(j = 0; j<r-t;j++)
            {
                if(strcmp((*linker)[j].arrivo,(*linker)[j+1].arrivo)>0)
                {
                    tmp=(*linker)[j];
                    (*linker)[j] = (*linker)[j+1];
                    (*linker)[j+1] = tmp;
                }
            }
        }
        return;
    }
    return;
}
void ricerca_dic(treni *linker,char *citta,int l,int r)
{
    int j=0;
    int m=(l+r)/2;
    if(l>r)
    {
        printf("Stazione di partenza %s, non trovata",citta);
        return;
    }
    if(strncmp(linker[m].partenza,citta,strlen(citta))==0)
    {
        while((strncmp(citta,linker[--m].partenza,strlen(citta))==0))   //ricerca all'indietro
              j--;
        m=(l+r)/2;
        printf("%d\n",j);
        while(j<=0) //stampo fino al valore trovato con la ricerca dicotomica
        {
            printf("Stazione di partenza trovata: %d %s %s %s %s %s %d\n",linker[m+j].codice,linker[m+j].partenza,linker[m+j].arrivo,linker[m+j].data,linker[m+j].ora_p,linker[m+j].ora_a,linker[m+j].ritardo);
            j++;
        }
        while(strncmp(citta,linker[++m].partenza,strlen(citta))==0)   //continuo la ricerca per altre possibili corse con partenza "citta"
            printf("Stazione di partenza trovata: %d %s %s %s %s %s %d\n",linker[m].codice,linker[m].partenza,linker[m].arrivo,linker[m].data,linker[m].ora_p,linker[m].ora_a,linker[m].ritardo);
        return;
    }
    if(strncmp(linker[m].partenza,citta,strlen(citta))>0)
        ricerca_dic(linker,citta,l,m-1);
    if(strncmp(linker[m].partenza,citta,strlen(citta))<0)
        ricerca_dic(linker,citta,m+1,r);
}
void ricerca_lin(treni *linker,char *citta,int i)
{
    int j;
    int trovato = 0;
    for(j=0;j<i;j++)    //ricerca lineare per stazione di partenza
    {

        if(strncmp(citta,linker[j].partenza,strlen(citta))==0)
        {
            trovato+=1; //possono esserci più treni in partenza dalla città scelta
            printf("Partenza %d da %s: ",trovato,citta);
            printf("%d %s %s %s %s %s %d\n",linker[j].codice,linker[j].partenza,linker[j].arrivo,linker[j].data,linker[j].ora_p,linker[j].ora_a,linker[j].ritardo);
        }
    }
    if (trovato==0)
        printf("Nessuna corsa con partenza da %s",citta);
    return;
}

