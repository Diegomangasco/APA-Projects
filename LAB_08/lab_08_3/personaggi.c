
#include "personaggi.h"
void stampa_stat(link head)
{
    printf("Lista statistiche: \n");
    for(;head!=NULL;head=head->next)
    {
        printf("Giocatore: %s\n",head->nome);
        printf("hp: %d\n",head->stat->hp);
        printf("mp: %d\n",head->stat->mp);
        printf("atk: %d\n",head->stat->atk);
        printf("def: %d\n",head->stat->def);
        printf("magg: %d\n",head->stat->magg);
        printf("spr: %d\n",head->stat->spr);
        printf("\n");
    }
}
void calcola_stat(inv **el, link *x, int i)
{
    link t=*x;
    inv *elenco=*el;
    t->stat->hp = t->stat->hp + elenco->vett[i].stati[0];
    if(t->stat->hp<1) t->stat->hp=1;
    t->stat->mp = t->stat->mp + elenco->vett[i].stati[1];
    if(t->stat->mp<1) t->stat->mp=1;
    t->stat->atk = t->stat->atk + elenco->vett[i].stati[2];
    if(t->stat->atk<1) t->stat->atk=1;
    t->stat->def = t->stat->def + elenco->vett[i].stati[3];
    if(t->stat->def<1) t->stat->def=1;
    t->stat->magg = t->stat->magg + elenco->vett[i].stati[4];
    if(t->stat->magg<1) t->stat->magg=1;
    t->stat->spr = t->stat->spr + elenco->vett[i].stati[5];
    if(t->stat->spr<1) t->stat->spr=1;
    //*el=elenco;
    //*x=t;
}
void stampa_pg(link head, link tail)
{
    int i,j;
    j=0;
    if(head==NULL)
    {
        printf("Lista vuota!");
        return;
    }
    if(head==tail)
    {
        printf("\nUnico personaggio:");
        printf("\nCodice: %s\n",head->codice);
        printf("Nome: %s\n",head->nome);
        printf("Classe: %s\n",head->classe);
        for(i=0;head->equip->vetteq[i]!=NULL;i++)
            printf("Oggetto %d: %s\n",i+1,head->equip->vetteq[i]->nome);
        return;
    }
    for(;head!=NULL;head=head->next)
    {
        j++;
        printf("\nPersonaggio %d",j);
        printf("\nCodice: %s\n",head->codice);
        printf("Nome: %s\n",head->nome);
        printf("Classe: %s\n",head->classe);
        for(i=0;i<8;i++)
        {
            if(head->equip->vetteq[i]->nome!=NULL)
                printf("Oggetto %d: %s\n",i+1,head->equip->vetteq[i]->nome);
            else printf("Oggetto %d: nd\n",i+1);
        }
    }
}
link newnode(link next, link val)
{
    int i;
    link x=malloc(sizeof(pg));
    x->equip=malloc(sizeof(equi_t));
    x->stat=malloc(sizeof(stat_t));;
    x->equip->in_uso=0;
    x->equip->vetteq=malloc(8*sizeof(ogg*));
    for(i=0;i<8;i++)
        x->equip->vetteq[i]=(ogg *)NULL;
    if(x==NULL)
        return NULL;
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
        fscanf(fp,"%s %s %s %d %d %d %d %d %d",val->codice,val->nome,val->classe,&val->stat->hp,&val->stat->mp,&val->stat->atk,&val->stat->def,&val->stat->magg,&val->stat->spr);
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
link aggiungi_elemento()
{
    int i;
    link val = malloc(sizeof(pg));
    stat_t *s=malloc(sizeof(stat_t));
    equi_t *e=malloc(sizeof(equi_t));
    val->equip=e;
    val->stat=s;
    val->equip->vetteq=malloc(8*sizeof(ogg*));
    for(i=0;i<8;i++)
        val->equip->vetteq[i]=(ogg*)NULL;
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
        free(head->equip->vetteq);
        free(head->equip);
        return;
    }
    t=head->next;
    p->next=t;
    free(head->stat);
    free(head->equip->vetteq);
    free(head->equip);
    return;
}
void aggiunta_ogg(link *head, inv **el)
{
    link x=*head;
    inv *elenco=*el;
    char pg[50];
    char oggetto[50];
    int i,j;
    int trovato = 0;
    if(elenco->n_disp==0)
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
    for(i=0;strcmp(elenco->vett[i].nome,oggetto)!=0;i++);
    if(i>=elenco->max_n)
    {
        printf("Oggetto non trovato\n");
        return;
    }
    if(elenco->n_disp==0)
    {
        printf("Tutti gli oggetti sono gia in dotazione a dei pg\n");
        return;
    }
    if(elenco->vett[i].disp==1)
    {
        x->equip->in_uso++;
        for(j=0;j<8 && !trovato;j++)
        {
            if(x->equip->vetteq[j]==NULL)
                trovato=1;
        }
        j--;
        if(j<8)
        {
            x->equip->vetteq[j]=&elenco->vett[i];
            elenco->vett[i].disp=0;
            calcola_stat(&elenco,&x,i);
            //*el=elenco;
            return;
        }
        else
        {
            printf("Il pg ha gia' in dotazione 8 oggetti, se si desidera cambiare oggetto, rimuovere prima quello vecchio e poi aggiungere quello nuovo\n");
            return;
        }
    }
    else
    {
        printf("Oggetto gia assegnato\n");
        return;
    }
}

void elimina_ogg(link *head, inv **el)
{
    char codice[7];
    char oggetto[50];
    int i;
    link x = *head;
    inv *elenco=*el;
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
    for(i=0;x->equip->vetteq[i]!=NULL;i++)
        printf("Oggetto %d: %s\n",i+1, x->equip->vetteq[i]->nome);
    printf("Inserisci il nome dell'oggetto da rimuovere: ");
    scanf("%s",oggetto);
    printf("\n");
    for(i=0;strcmp(x->equip->vetteq[i]->nome,oggetto)!=0;i++);
    x->equip->vetteq[i]=(ogg*)NULL;
    x->equip->in_uso--;
    elenco->n_disp++;
    for(i=0;strcmp(elenco->vett[i].nome,oggetto)!=0;i++);
    elenco->vett[i].disp=1;
    calcola_stat(&elenco,&x,i);
    //*el=elenco;
}


