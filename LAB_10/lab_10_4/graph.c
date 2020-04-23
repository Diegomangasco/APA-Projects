//
// Created by UTENTE on 29/12/2019.
//
#include "graph.h"
struct graph {int V; int E; int **mat; struct node *vetta ;ST table;};
int STsearch(ST table, char *label, int N)
{
    int i;
    for(i=0;i<N;i++)
        if(strcmp(table[i],label)==0) break;
    if(i==N)
        return -1;
    else return i;
}
g *GRAPHcreate(g *G, int r, int c, int j)
{
    (*G)->mat=matrix(r,c,0);
    (*G)->E=j;
    return G;
}
void GRAPHfree(g G)
{
    int i;
    for(i=0;i<G->V;i++)
    {
        free(G->table[i]);
        free(G->mat[i]);
    }
    free(G->mat);
    free(G);
    return;
}
static int **matrix(int r, int c, int val)
{
    int i,j;
    int **m=malloc(r*sizeof(int*));
    for(i=0;i<r;i++) m[i]=malloc(c*sizeof(int));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++) m[i][j]=val;
    return m;
}
void GRAPHinsert(g G,int id1, int id2, int wt)
{
    insertE(G,edgecreate(id1,id2,wt));
}
void GRAPHremove(g G, int id1, int id2, int wt)
{
    removeE(G,edgecreate(id1,id2,0));
}
void insertE(g G,edge E)
{
    if(G->mat[E.v][E.w]==0)
        G->E++;
    G->mat[E.v][E.w]=E.wt;  //perchè grafo non orientato e pesato
    G->mat[E.w][E.v]=E.wt;
    return;
}
void removeE(g G, edge E)
{
    if(G->mat[E.v][E.w]!=0)
        G->E--;
    G->mat[E.v][E.w]=E.wt;  //perchè grafo non orientato e pesato
    G->mat[E.w][E.v]=E.wt;
    return;
}
static edge edgecreate(int v, int w, int wt)
{
    edge e;
    e.v=v; e.w=w; e.wt=wt;
    return e;
}
void filescan(FILE *fp, g *G)
{
    int i,j, quantity=0, id;
    int id1,id2;
    int wt;
    char linea[300];
    char label1[31], label2[31], label3[31], label4[31];
    j=0;
    while(fgets(linea,200,fp)!=NULL) j++;
    (*G)=malloc(sizeof(struct graph));
    (*G)->table=malloc(2*j*sizeof(char*));
    for(i=0;i<2*j;i++) { (*G)->table[i]=malloc(31*sizeof(char)); (*G)->table[i][0]='\0';}
    rewind(fp);
    for(i=0;i<j;i++)
    {
        fgets(linea,200,fp);
        sscanf(linea,"%s %s %s %s %d",label1,label2,label3,label4,&wt);
        id=STsearch((*G)->table,label1,2*j);
        if(id==-1)
        {
            strcpy((*G)->table[quantity],label1);
            quantity++;
        }
        id=STsearch((*G)->table,label3,2*j);
        if(id==-1)
        {
            strcpy((*G)->table[quantity],label3);
            quantity++;
        }
    }
    (*G)->V=quantity;
    G=GRAPHcreate(G, (*G)->V,(*G)->V,j);
    rewind(fp);
    while(fscanf(fp,"%s %s %s %s %d", label1,label2,label3,label4,&wt)==5)
    {
        id1=STsearch((*G)->table,label1, (*G)->V);
        id2=STsearch((*G)->table,label3, (*G)->V);
        if(id1>=0 && id2>=0)
            GRAPHinsert(*G,id1,id2,wt);
    }
    return;
}
void insertionsort(char **first, int N)
{
    int i,j;
    char *tmp=malloc(31*sizeof(char));
    for(i=1;i<N;i++)
    {
        strcpy(tmp,first[i]);
        j=i-1;
        while(j>=0 && strcmp(first[j],tmp)>0)
        {
            strcpy(first[j+1],first[j]);
            j--;
        }
        strcpy(first[j+1],tmp);
    }
    free(tmp);
    return;
}
void stampalpha(g G)
{
    int i;
    char **first=malloc(G->V*sizeof(char*));
    for(i=0;i<G->V;i++)
        first[i]=G->table[i];
    insertionsort(first,G->V);
    printf("Verteces's alphabetical order:\n");
    for(i=0;i<G->V;i++)
        printf("%s\n",first[i]);
}
void nearvertex(g G)
{
    int i,j,t;
    char **vect=malloc(G->V*sizeof(char*));
    for(i=0;i<G->V;i++)
    {
        printf("\nAdjacent vertex of %s (alphabetical order):\n",G->table[i]);
        t=0;
        for(j=0;j<G->V;j++)
        {
            if(G->mat[i][j]!=0)
                vect[t++]=G->table[j];
        }
        insertionsort(vect,t);
        for(j=0;j<t;j++)
            printf("%s ",vect[j]);
    }
    return;
}
void list(g *G)
{
    int i,j;
    struct node *h;
    (*G)->vetta=malloc((*G)->V*sizeof(struct node));
    for(i=0;i<(*G)->V;i++) (*G)->vetta[i].next=NULL;
    for(i=0;i<(*G)->V;i++)
    {
        h=(*G)->vetta[i].next;
        for(j=0;j<(*G)->V;j++)
        {
            if((*G)->mat[i][j]!=0)
            {
                while(h!=NULL) h=h->next;
                h->next=newnode(NULL,*G, i, j);
            }
        }
    }
    return;
}
struct node *newnode(struct node *end, g G, int i, int j)
{
    struct node *x;
    x=malloc(sizeof(struct node));
    if (x==NULL) return NULL;
    x->next=end;
    x->wt=G->mat[i][j];
    x->vertex=j;
    return x;
}

