//
// Created by UTENTE on 17/01/2020.
//
#include <limits.h>
#include "Graph.h"
#include "PQ.h"
#define MAX 100
#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;
    GRAPHedges(G, a);

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void  removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
        G->ladj[v] = G->ladj[v]->next;
        G->E--;
    }
    else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
            }
}

void GRAPHspD(Graph G, int id) {
    int v;
    link t;
    PQ pq = PQinit(G->V);
    int *st, *mindist;
    st = malloc(G->V*sizeof(int));
    mindist = malloc(G->V*sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for (v = 0; v < G->V; v++){
        st[v] = -1;
        mindist[v] = maxWT;
        PQinsert(pq, mindist, v);
    }

    mindist[id] = 0;
    st[id] = id;
    PQchange(pq, mindist, id);

    while (!PQempty(pq)) {
        if (mindist[v = PQextractMin(pq, mindist)] != maxWT) {
            for (t=G->ladj[v]; t!=G->z ; t=t->next)
                if (mindist[v] + t->wt < mindist[t->v]) {
                    mindist[t->v] = mindist[v] + t->wt;
                    PQchange(pq, mindist, t->v);
                    st[t->v] = v;
                }
        }
    }

    printf("\n Shortest path tree\n");
    for (v = 0; v < G->V; v++)
        printf("parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));

    printf("\n Minimum distances from node %s\n", STsearchByIndex(G->tab, id));
    for (v = 0; v < G->V; v++)
        printf("mindist[%s] = %d \n", STsearchByIndex(G->tab, v), mindist[v]);

    PQfree(pq);
}

void GRAPHspBF(Graph G, int id){
    int v, w, negcycfound;
    link t;
    int *st, *mindist;

    st = malloc(G->V*sizeof(int));
    mindist = malloc(G->V*sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for ( v = 0; v < G->V; v++) {
        st[v]= -1;
        mindist[v] = maxWT;
    }

    mindist[id] = 0;
    st[id] = id;

    for (w = 0; w < G->V - 1; w++)
        for (v = 0; v < G->V; v++)
            if (mindist[v] < maxWT)
                for (t = G->ladj[v]; t != G->z ; t = t->next)
                    if (mindist[t->v] > mindist[v] + t->wt) {
                        mindist[t->v] = mindist[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v = 0; v < G->V; v++)
        if (mindist[v] < maxWT)
            for (t = G->ladj[v]; t != G->z ; t = t->next)
                if (mindist[t->v] > mindist[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));

        printf("\n Minimum distances from node %s\n", STsearchByIndex(G->tab, id));
        for (v = 0; v < G->V; v++)
            printf("mindist[%s] = %d \n", STsearchByIndex(G->tab, v), mindist[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}
int GRAPHdfs_mod(Graph G, int id, int *sol, Edge *a) {
    int v, time = 0, *pre, *post, *st;
    int result;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }
    if(dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st, sol,a)==0) return 0;
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) {
            result = dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, sol,a);
            if (result==0) return 0;
        }
    if(result==0) return 0;
    else return 1;
}
static int searchEdge(Edge x, Edge *a, int E)
{
    int i;
    for(i=0;i<E;i++)
        if(x.v==a[i].v && x.w==a[i].w) return i;
    return 0;
}
int dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *sol, Edge *a) {
    link t;
    int v, w = e.w;
    Edge x;
    int result;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
    {
        if(sol[searchEdge(EDGEcreate(w, t->v, t->wt), a, G->E)]==0)
        {
            if (pre[t->v] == -1) result=dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, sol, a);
            else {
                v = t->v;
                x = EDGEcreate(w, v, t->wt);
                if (post[v] == -1) return 0;
            }
        }
    }
    post[w] = (*time)++;
    return 1;
}
static int card (int *sol, int pos)
{
    int i;
    int count=0;
    for(i=0;i<pos;i++) {
        if (sol[i] == 1) count++;
    }
    return count;
}
void wrapper(Graph G)
{
    int *sol=calloc(G->E,sizeof(int));
    int *sol_best=calloc(G->E,sizeof(int));
    Edge *a=malloc(G->E*sizeof(Edge));
    GRAPHedges(G,a);
    int pos=0;
    Graph DG=G;
    int kard=MAX;
    int maxweight=0;
    searchedges(a,sol,pos,G,&kard, &maxweight, sol_best);
    printf("\nCreation of DAG: \n");
    creationDAG(sol_best, DG, a);
}
void searchedges(Edge *a, int *sol, int pos, Graph G, int *kard, int *maxweight, int *sol_best)
{
    int i;
    int k;
    int weight=0;
    if(pos>=G->E)
    {
        k = card(sol, pos);
        if (k < *kard) {
            if (GRAPHdfs_mod(G, 0, sol, a)) {
                *kard = k;
                printf("\nCollection: ");
                for (i = 0; i < pos; i++) {
                    if (sol[i] == 1) {
                        printf("(%c %c) ", *STsearchByIndex(G->tab,a[i].v), *STsearchByIndex(G->tab,a[i].w));
                        weight+=a[i].wt;
                    }

                }
                if(weight>*maxweight)
                {
                    *maxweight=weight;
                    for(i=0;i<pos;i++)
                        sol_best[i]=sol[i];
                }
            }
        }
        return;
    }
    sol[pos]=0;
    searchedges(a,sol,pos+1,G, kard, maxweight, sol_best);
    sol[pos]=1;
    searchedges(a,sol,pos+1,G, kard, maxweight, sol_best);
}
void creationDAG(int *sol_best, Graph DG, Edge *a)
{
    int v=0;
    link t,p,d;
    int i;
    int f;
    for(v=0;v<DG->V;v++)
    {
        for(t=DG->ladj[v], p=DG->ladj[v]; p!=DG->z || t!=DG->z; p=t,t=t->next)
        {
            if (sol_best[f=searchEdge(EDGEcreate(v,t->v,t->wt),a,DG->E)]==1)
            {
                d=t;
                p->next=t->next;
                free(d);
            }
        }
    }
    GRAPHstore(DG,stdout);
    for(i=0;i<DG->V;i++)
        maxwayDAG(DG,i);
}
void maxwayDAG(Graph DG, int id)
{
    int *ts;
    int i, j, tmp;
    link t;
    int *st, *d;
    ts=DAGrts((Dag)DG); //reverse topological order vector
    st = malloc(DG->V*sizeof(int));
    d = malloc(DG->V*sizeof(int));
    for (i = 0; i < DG->V; i++)
    {
        st[i] = -1;
        d[i] = 0;
    }
    d[id]=maxWT;
    st[id]=id;
    for(i=0, j=DG->V-1; i>=j; i++, j--)
    {
        tmp=ts[i];
        ts[i]=ts[j];
        ts[j]=tmp;
    }

    for(i=0;i<DG->V;i++)
    {
        if(d[i]!=0) {
            for (t = DG->ladj[ts[i]]; t != NULL; t = t->next) {
                if (d[i] < d[t->v] + t->wt) {
                    d[i] = d[t->v] + t->wt;
                    st[t->v] = i;
                }
            }
        }
    }
    printf("Maxdist from %c: ",*(STsearchByIndex(DG->tab,id)));
    for(i=0;i<DG->V;i++) printf("%c %d ", *(STsearchByIndex(DG->tab,st[i])),d[i]);

}