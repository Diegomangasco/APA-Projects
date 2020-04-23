//
// Created by UTENTE on 12/01/2020.
//
#include "Title.h"
struct title
{
    char name[20];
};
struct collection
{
    c next;
    c previous;
    BST b;
    struct title t;
};
c newnode(char* name, c previous)
{
    c new=malloc(sizeof(struct collection));
    new->next=NULL;
    new->b=BSTinit();
    new->previous=previous;
    strcpy(new->t.name,name);
    return new;
}
c insert(c head, char *name)
{
    c x;
    c p;
    if(head!=NULL) {
        for (x = head, p=head; x != NULL; p=x, x = x->next);
        x = newnode(name,p);
    }
    else
        head = newnode(name, NULL);
    return head;
}
void leggifile(FILE *fp, c head)
{
    int n,num;
    char name[20];
    fscanf(fp,"%d",&n);
    int i,j;
    int nn;
    float v;
    date *d=malloc(sizeof(date));
    quotation* q=malloc(sizeof(quotation));
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%s %d",name,&num);
        head = insert(head,name);
        for(j=0;j<num;j++)
        {
            fscanf(fp,"%d/%d/%d %d:%d %f %d",&d->year, &d->month, &d->day, &d->hour, &d->minutes, &v, &nn);
            q->num=v*nn;
			q->den=(float)nn;
            BSTinsert_leafR(search(head,name)->b,q,d);
        }
    }
    free(d);
    free(q);
}
c searchinlist(c head, char* name)	//ricerca in lista
{
    c search;
    for(search=head;search!=NULL && strcmp(name,search->t.name)==0; search=search->next);
    if(search==NULL)
    {
        printf("\nTitolo non trovato\n");
        return NULL;
    }
    else
    {
        printf("\nTitolo trovato\n");
        printf("%s\n",search->t.name);
        return search;
    }
    return NULL;
}
void searchinBST(c head, date* d)
{
    float result;
    result=findq(head->b,d);
    if(result==-1)
    {
        printf("Giornata non trovata!\n");
        return;
    }
    printf("Quotazione per la data inserita: %f\n",result);
    return;
}
void searchbyrangeBST(c head,date* d1, date* d2)
{
    printf("\nTitolo %s: \n",head->t.name);
    findrange(head->b,d1,d2);
}
void balance(c search)
{
	BSTbalance(search->b);
}
void searchLway(c search)
{
	searchWay(search->b);
}