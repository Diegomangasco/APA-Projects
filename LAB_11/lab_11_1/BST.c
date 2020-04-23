//
// Created by UTENTE on 12/01/2020.
//
#include "BST.h"
#define MAX 3000
#define S 2
typedef struct BSTnode* link;
struct BSTnode { quotation* q; date* d; link l; link r; link p; int N;};
struct binarysearchtree { link root; link z; };
static link NEW(quotation* q, date* d, link p, link l, link r,int n)
{
    link x = malloc(sizeof *x);
    x->d=d;
    x->l = l;
    x->r = r;
    x->q->quote=0;
	x->q->num=0;
	x->q->den=0;
	x->N=n;
	x->p=p;
    return x;
}
BST BSTinit(int n)	//inizializzazione BST
{
    BST bst = malloc(sizeof *bst) ;
    bst->root= ( bst->z = NEW(qNULL(),dNULL(), NULL, NULL, NULL,0));
    return bst;
}
static void treeFree(link h, link z) {
    if (h == z) return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}
void BSTfree(BST bst) {
    if (bst == NULL) return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}
static void insertinnode(link head, quotation* q)
{
    head->q->num+=q->num;
	head->q->den+=q->den;
	head->q->quote=calc(q);
    return;
}
static link insertR(link h, quotation* q, date* d, link z) {
    if (h == z) return NEW(q, d, z, z, z, 1);
    int g=dcmp(d->year,d->month,d->day,h->d->year,h->d->month,h->d->day);
    if (g == -1){
        h->l = insertR(h->l, q, d, z);
		h->l->p=h;
	}
    else if(g==1) { h->r = insertR(h->r, q, d, z); h->r->p=h;}
	(h->N)++;
    else insertinnode(h,q);
    return h;
}
void BSTinsert_leafR(BST bst, quotation* q, date* d)
{
	int n=0;
    bst->root = insertR(bst->root, q, d, bst->root, bst->z, n);
}
static float findqR(link search, date* d)   //ricerca ricorsiva per data
{
	if(search->r==NULL && search->l==NULL) return -1;
    if(dcmp(search->d->year,search->d->month,search->d->day,d->year,d->month,d->day)==0)
        return search->q->quote;
    else if (dcmp(search->d->year,search->d->month,search->d->day,d->year,d->month,d->day)==-1)
        findqR(search->r,d);
    else findqR(search->l,d);
    return -1;
}
float findq(BST b, date* d) //wrapper per la ricerca per data
{
    link search = b->root;
    return findqR(search,d);
}
static void searchinorder(link search, date* d1, date* d2, float* max, float* min, link* findM, link* findm)
{
	if(search->l==NULL && search->r==NULL) return;
    searchinorder(search->l,d1,d2,max, min,findM,findm);
    if(dcmp(d1->year,d1->month,d1->day,search->d->year,search->d->month,search->d->day)==1  //controllo che il nodo sia nel range di date selezionato
        && dcmp(d2->year,d2->month,d2->day,search->d->year,search->d->month,search->d->day)==-1) {
        if(search->q->quote>*max)
        {
            *findM=search;
            *max=search->q->quote;
        }
        else if(search->q->quote<*min)
        {
            *findm=search;
            *min=search->q->quote;
        }
    }
    searchinorder(search->r,d1,d2,max,min,findM,findm);
    return;
}
void findrange(BST b, date* d1, date* d2)
{
    link search=b->root;
    float max=0,min=MAX;
    link findM,findm;
    searchinorder(search, d1, d2, &max, &min, &findM, &findm);
    printf("\nMassima quotazione %d/%d/%d %f\n", findM->d->year, findM->d->month, findM->d->day, findM->q->quote);
    printf("\nMinima quotazione %d/%d/%d %f\n", findm->d->year, findm->d->month, findm->d->day, findm->q->quote);
}
static link rotL(link h) 
{ 
	 link x = h->r; 
	 h->r = x->l; 
	 x->l->p = h; 
	 x->l = h; 
	 x->p = h->p; 
	 h->p = x; 
	 x->N = h->N; 
	 h->N = 1; 
	 h->N += (h->l) ? h->l->N : 0; h->N += (h->r) ? h->r->N : 0; 
	 return x;
}
static link rotR(link h) 
{ 
	link x = h->l; 
	h->l = x->r; 
	x->r->p = h; x->r = h; 
	x->p = h->p; 
	h->p = x; 
	x->N = h->N; 
	h->N = 1; 
	h->N += (h->l) ? h->l->N : 0; 
	h->N += (h->r) ? h->r->N : 0; 
	return x; 
}
static link partR(link h, int r) 
{ 
	int t = h->l->N; 
	if (t > r) 
	{ 
		h->l = partR(h->l, r); 
		h = rotR(h); 
	} 
	if (t < r) 
	{ 
		h->r = partR(h->r, r-t-1); 
		h = rotL(h); 
	}
	return h; 
}
static link balanceR(link h, link z) 
{
	int r; if (h == z) return z; 
	r = (h->N+1)/2-1; 
	h = partR(h, r); 
	h->l = balanceR(h->l, z); 
	h->r = balanceR(h->r, z); 
	return h; 
}
void BSTbalance(BST bst) 
{ 
	bst->root = balanceR(bst->root, bst->z); 
}
static void awey(link h, link z, int *min, int *max, int cont)
{
	if(h==z)
	{
		if(cont>*max)
			*max=cont;
		if(cont<*min)
			*min=cont;
		return;
	}
	awey(h->l,z,min,max,cont+1);
	awey(h->r,z,min,max,cont+1);
}
void searchWAY(BST bst)
{
	int min=MAX;
	int max=0;
	int cont=0;
	awey(bst->root, bst->z, &min, &max, cont);
	if(max/min>S) BSTbalance(bst);
	else printf("Albero gia' bilanciato\n");
}