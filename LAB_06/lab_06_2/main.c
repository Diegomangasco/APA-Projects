#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct anag
{
    char codice[6];
    char nome[50];
    char cognome[50];
    char data[11];
    char via[50];
    char paese[50];
    int cap;
    struct anag *next;
}anag,*link;
char *ruota_data(char *data);
link new_node(link next,anag val);
link Instrova_data(link hp,anag val);
anag inser_tast();
link inser_file(char *s, link head);
void stampa_lista(link hp);
void stampa_lista_file(link hp);
void stampa_elemento(link c);
link ricerca_codice(char *codice, link *hp, int rimuovi);
link cancella_date(link *hp);

int main()
{
    link c;
    int scelta,fine = 0;
    char codice[6];
    link head = NULL;   //inizializzazione di head
    link t;
    do
    {   //menu di scelta
        printf("\nBuongiorno, inserisci un numero per indicare l'azione:\n");
        printf("1)Aggiunta elemento da video\n");
        printf("2)Aggiunta elementi da file\n");
        printf("3)Stampa a video\n");
        printf("4)Stampa su file\n");
        printf("5)Ricerca elemento per codice\n");
        printf("6)Estrazione e cancellazione da codice\n");
        printf("7)Estrazione e cancellazione con range di date\n");
        printf("8)Termina\n");
        scanf("%d",&scelta);

        switch(scelta)
        {
        case 1: //inserimento da tastiera
            head=Instrova_data(head,inser_tast());
            break;
        case 2: //inserimento da file
            head=inser_file("anagrafica.txt",head);
            break;
        case 3: //stampa a video
            stampa_lista(head);
            break;
        case 4: //stampa su file
            stampa_lista_file(head);
            break;
        case 5: //ricerca per codice
            printf("Inserisci il codice da ricercare: ");
            scanf("%s",codice);
            c=ricerca_codice(codice,&head,0);
            if(c!=NULL)
            {
                printf("\nElemento trovato: \n");
                stampa_elemento(c);
            }
            else
                printf("\nElemento non trovato!\n");
            break;
        case 6: //cancellazione tramite codice
            printf("Inserisci il codice da ricercare: ");
            scanf("%s",codice);
            c=ricerca_codice(codice,&head,1);   //head è passato per riferimento in modo che, se il nodo da cancellare fosse il primo, lo si può modificare direttamente
            if(c!=NULL)
            {
                printf("\nElemento selezionato da rimuovere: \n");
                stampa_elemento(c);
                free(c);    //cancellazione dell'elemento
            }
            else
                printf("\nElemento non trovato!\n");
            break;
        case 7:
            t=cancella_date(&head);
            if(t!=NULL)
            {
               for(;t!=NULL;t=t->next)
               {
                   printf("\nValore eliminato: \n");
                   stampa_elemento(t);
               }
            }
            else
                printf("\nIntervallo non trovato\n");
            break;
        case 8: //terminazione
            printf("Grazie ed arrivederci!\n");
            fine=1;
            break;
        default:    //errore
            printf("Valore inserito non corretto, riprova\n");
        }
    }while(!fine);
    return 0;
}
anag inser_tast()
{
    anag val;
    printf("Inserisci il codice: ");
    scanf("%s",val.codice);
    printf("\n");
    printf("Inserisci il nome: ");
    scanf("%s",val.nome);
    printf("\n");
    printf("Inserisci il cognome: ");
    scanf("%s",val.cognome);
    printf("\n");
    printf("Inserisci la data di nascita gg/mm/aaaa: ");
    scanf("%s",val.data);
    printf("\n");
    printf("Inserisci la via: ");
    scanf("%s",val.via);
    printf("\n");
    printf("Inserisci la citta': ");
    scanf("%s",val.paese);
    printf("\n");
    printf("Inserisci il CAP: ");
    scanf("%d",&val.cap);
    printf("\n");
    return val;
}
link inser_file(char *s, link head)
{
    int count=0,i;
    anag val;
    char linea[90];
    FILE *fp=fopen(s,"r");
    while(fgets(linea,80,fp)!=NULL) //conto le righe del file
        count++;
    rewind(fp); //ritorno all'inizio del file
    for(i=0;i<count;i++)
    {
        fscanf(fp,"%s%s%s%s%s%s%d",val.codice,val.nome,val.cognome,val.data,val.via,val.paese,&val.cap);
        head=Instrova_data(head,val);   //inserisco, ad uno ad uno, i nuovi elementi letti dal file nella lista
    }
    fclose(fp);
    return head;
}
char *ruota_data(char *data)    //ruoto le date per averle in forma aaaa/mm/gg per la strcmp
{
    int lung=10;
    int i;
    char *m;
    m=malloc((lung+1)*sizeof(char));
    for(i=0;i<lung;i++)
    {
        switch(i)
        {
        case 0:
            m[i]=data[6];
            break;
        case 1:
            m[i]=data[7];
            break;
        case 2:
            m[i]=data[8];
            break;
        case 3:
            m[i]=data[9];
            break;
        case 4:
            m[i]='/';
            break;
        case 5:
            m[i]=data[3];
            break;
        case 6:
            m[i]=data[4];
            break;
        case 7:
            m[i]='/';
            break;
        case 8:
            m[i]=data[0];
            break;
        case 9:
            m[i]=data[1];
            break;
        }
    }
    m[i]='\0';
   /* char *m,*h;
    char *gg,*mm,*aa;
    m=malloc(11*sizeof(char));
    h=m;
    gg=strtok(data,"/");
    mm=strtok(NULL,"/");
    aa=strtok(NULL,"/0");
    strcpy(m,aa);
    m=m+4;
    *m='/';
    m++;
    strcpy(m,mm);
    m=m+2;
    *m='/';
    m++;
    strcpy(m,gg);
    m=m+2;
    *m=NULL;
    return h;*/
    return m;
}
link new_node(link next,anag val)   //creazione di un nuovo nodo
{
    link x;
    x=malloc(sizeof(anag));
    if(x==NULL)
        return NULL;
    else
    {
        x->next=next;
        x->cap=val.cap;
        strcpy(x->codice,val.codice);
        strcpy(x->nome,val.nome);
        strcpy(x->cognome,val.cognome);
        strcpy(x->data,val.data);
        strcpy(x->paese,val.paese);
        strcpy(x->via,val.via);
    }
    return x;
}
link Instrova_data(link hp,anag val)    //funzione per trovare il punto dove inserire il nuovo nodo
{
    link p;
    link x=hp;
    if(x==NULL) return new_node(NULL,val);  //se la lista è vuota
    if(strcmp(ruota_data(val.data),ruota_data(x->data))>0) return new_node(hp,val); //se l'elemento deve essere il primo
    for(p=hp, x=hp->next;x!=NULL && strcmp(ruota_data(val.data),ruota_data(x->data))<0; p=x, x=x->next);    //ricerco il punto di inserimento
    p->next = new_node(x,val);  //creo il nuovo nodo
    return hp;
}
void stampa_lista(link hp)
{
    link x;
    int cont=1;
    printf("Anagrafica:\n");
    for(x=hp;x!=NULL;x=x->next)
    {
        printf("\nPersona %d\n",cont);
        printf("Codice: %s\n",x->codice);
        printf("Nome: %s\n",x->nome);
        printf("Cognome: %s\n",x->cognome);
        printf("Data di nascita: %s\n",x->data);
        printf("Via: %s\n",x->via);
        printf("Citta': %s\n",x->paese);
        printf("CAP: %d\n",x->cap);
        cont++;
        printf("\n");
    }
    return;
}
void stampa_lista_file(link hp)
{
    FILE *fp=fopen("stampa.txt","w");
    link x;
    int cont=1;
    fprintf(fp,"Anagrafica:\n");
    for(x=hp;x!=NULL;x=x->next)
    {
        fprintf(fp,"\nPersona %d\n",cont);
        fprintf(fp,"Codice: %s\n",x->codice);
        fprintf(fp,"Nome: %s\n",x->nome);
        fprintf(fp,"Cognome: %s\n",x->cognome);
        fprintf(fp,"Data di nascita: %s\n",x->data);
        fprintf(fp,"Via: %s\n",x->via);
        fprintf(fp,"Citta': %s\n",x->paese);
        fprintf(fp,"CAP: %d\n",x->cap);
        fprintf(fp,"\n");
        cont++;
    }
}
void stampa_elemento(link c)
{
    printf("Codice: %s\n",c->codice);
    printf("Nome: %s\n",c->nome);
    printf("Cognome: %s\n",c->cognome);
    printf("Data di nascita: %s\n",c->data);
    printf("Via: %s\n",c->via);
    printf("Citta': %s\n",c->paese);
    printf("CAP: %d\n",c->cap);
    return;
}
link ricerca_codice(char *codice,link *hp,int rimuovi)
{
    link x, p;
    for(x=*hp,p=NULL;x!=NULL && strcmp(x->codice,codice)!=0;p=x, x=x->next);
    if(x!=NULL && !rimuovi) return x;   //se la funzione è stata chiamata dalla ricerca semplice
    if(x!=NULL && rimuovi)              //se la funzione è stata chiamata dalla ricerca con cancellazione
    {
        if(x==*hp) *hp=x->next;         //se il nodo trovato è primo
        else p->next=x->next;
        return x;
    }
    if(x==NULL) return NULL;            //lista vuota o nodo non trovato
}
link cancella_date(link *hp)
{
    char data1[12],data2[12];
    link x=*hp;
    link p = NULL,t,g;
    int header = 0;
    printf("\nInserisci una data da cui iniziare a cancellare: ");
    scanf("%s",data1);
    printf("\nInserisci una data a cui terminare la cancellazione: ");
    scanf("%s",data2);
    for(;x!=NULL && strcmp(ruota_data(x->data),ruota_data(data2))>0;p=x,x=x->next);
    if(x==*hp) header=1;
    if(x==NULL) return NULL;
    g=t=x;
    x=x->next;
    for(;x!=NULL && strcmp(ruota_data(x->data),ruota_data(data1))>=0;g=x,x=x->next);
    if(header==0)
    {
        p->next=x;
        g->next=NULL;
    }
    else
    {
        *hp=x;
        g->next=NULL;
    }
    return t;
}
