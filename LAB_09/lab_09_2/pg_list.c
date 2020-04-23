//
// Created by UTENTE on 14/12/2019.
//
#include "pg_list.h"
void leggi_file(link *hp,link *tp)
{
    link val;
    stat_t *s;
    FILE *fp = fopen("pg.txt","r");
    int count=0,i;
    char linea[100];
    while (fgets(linea,80,fp)!=NULL)
        count++;
    rewind(fp);
    s=malloc(sizeof(stat_t));
    val=malloc(sizeof(pg));
    val->stat=s;
    for(i=0;i<count;i++)
    {
        fscanf(fp,"%s %s %s %d %d %d %d %d %d",val->codice,val->nome,val->classe,&(val->stat->hp),&(val->stat->mp),&(val->stat->atk),&(val->stat->def),&(val->stat->magg),&(val->stat->spr));
        carica_pg(hp,tp,val);
    }
    free(val);
    free(s);
    fclose(fp);
    return;
}
void carica_pg(link *hp,link *tp,link val)
{
    link t;
    if(*hp==NULL)
        *hp=*tp=newnode(NULL,val);
    else
    {
        (*tp)->next=t=newnode(NULL,val);
        *tp=t;
    }
    return;
}
link newnode(link next, link val)
{
    int i;
    link x=malloc(sizeof(pg));
    x->stat=malloc(sizeof(stat_t));
    x->equip=equip_all();
    uso(x->equip);
    if(x==NULL)
        return NULL;
    azzera(x->equip);
    strcpy(x->classe,val->classe);
    strcpy(x->codice,val->codice);
    strcpy(x->nome,val->nome);
    x->stat->hp=val->stat->hp;
    x->stat->atk=val->stat->atk;
    x->stat->def=val->stat->def;
    x->stat->magg=val->stat->magg;
    x->stat->mp=val->stat->mp;
    x->stat->spr=val->stat->spr;
    x->next=next;
    return x;
}
link aggiungi_elemento()
{
    int i;
    link val = malloc(sizeof(pg));
    stat_t *s=malloc(sizeof(stat_t));
    val->equip=equip_all();
    val->stat=s;
    azzera(val->equip);
    printf("\nInserisci il codice: ");
    scanf("%s",val->codice);
    printf("\nInserisci il nome: ");
    scanf("%s",val->nome);
    printf("\nInserisci la classe: ");
    scanf("%s",val->classe);
    printf("\nInserisci statistica hp: ");
    scanf("%d",&val->stat->hp);
    printf("\nInserisci statistica mp: ");
    scanf("%d",&val->stat->mp);
    printf("\nInserisci statistica atk: ");
    scanf("%d",&val->stat->atk);
    printf("\nInserisci statistica def: ");
    scanf("%d",&val->stat->def);
    printf("\nInserisci statistica mag: ");
    scanf("%d",&val->stat->magg);
    printf("\nInserisci statistica spr: ");
    scanf("%d",&val->stat->spr);
    return val;
}
void elimina_pg(link *hp)
{
    link head = *hp;
    link t;
    link p=NULL;
    int i=0;
    char codice[7];
    printf("Inserisci il codice del personaggio da eliminare: ");
    scanf("%s",codice);
    for(;head!=NULL && strcmp(head->codice,codice)!=0;p=head, head=head->next) i++;
    if(head==NULL)
    {
        printf("\nPersonaggio non trovato!\n");
        return;
    }
    if(head==*hp)
    {
        *hp=(*hp)->next;
        free(head->stat);
        equip_free(head->equip);
        return;
    }
    t=head->next;
    p->next=t;
    free(head->stat);
    equip_free(head->equip);
    return;
}
void aggiunta_ogg(link *head, inventario *el)
{
    link x=*head;
    inventario elenco=*el;
    char pg[50];
    char oggetto[50];
    int i,j;
    int trovato = 0;
    if(!torna_disp(elenco))
    {
        printf("Tutti gli oggetti gia assegnati\n");
        return;
    }
    printf("Inserisci il pg a cui vuoi assegnare l'oggetto: ");
    scanf("%s",pg);
    printf("\n");
    printf("Inserisci l'oggetto: ");
    scanf("%s",oggetto);
    printf("\n");
    for(;x!=NULL && strcmp(x->nome,pg)!=0;x=x->next);
    if(x==NULL)
    {
        printf("Giocatore non trovato\n");
        return;
    }
    for(i=0;strcmp(torna_nome(elenco,i),oggetto)!=0;i++);
    if(i>=torna_max(elenco))
    {
        printf("Oggetto non trovato\n");
        return;
    }
    if(ifdisp(elenco, i))
    {
            aggiungi_oggetto(x->equip,i,elenco);
            calcola_stat(&elenco,&x,i,1);
            return;
    }
    else
    {
        printf("Oggetto gia assegnato\n");
        return;
    }
    return;
}
void elimina_ogg(link *head, inventario *el)
{
    char codice[7];
    char oggetto[50];
    int i;
    link x = *head;
    inventario elenco=*el;
    printf("Inserisci il codice del personaggio: ");
    scanf("%s",codice);
    printf("\n");
    for(;x!=NULL,strcmp(x->codice,codice)!=0;x=x->next);
    if(x==NULL)
    {
        printf("Personaggio non trovato\n");
        return;
    }
    printf("Oggetti attualmente in uso dal pg %s:\n",x->nome);
    for(i=0;torna_NULL(x->equip,i);i++)
        printf("Oggetto %d: %s\n",i+1, torna_nome(elenco,i));
    printf("Inserisci il nome dell'oggetto da rimuovere: ");
    scanf("%s",oggetto);
    printf("\n");
    for(i=0;strcmp(torna_nome(elenco,i),oggetto)!=0;i++);
    elimina_oggetto(x->equip,i, elenco);
    calcola_stat(el,&x,i,0);
    return;
}
