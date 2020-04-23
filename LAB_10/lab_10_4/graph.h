//
// Created by UTENTE on 29/12/2019.
//

#ifndef LAB_10_4_GRAPH_H
#define LAB_10_4_GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct graph *g;
typedef struct {int v; int w; int wt;} edge;
typedef char **ST;
struct node{int wt; struct node *next; int vertex;};
int STsearch(ST table, char *label, int N);
g *GRAPHcreate(g *G, int r, int c, int j);
void GRAPHfree(g G);
static int **matrix(int r, int c, int val);
int vertexnumber(ST table,int N);
void GRAPHinsert(g G,int id1, int id2, int wt);
void GRAPHremove(g G, int id1, int id2, int wt);
void insertE(g G, edge E);
void removeE(g G, edge E);
static edge edgecreate(int v, int w, int wt);
void filescan(FILE *fp, g *G);
void stampalpha(g G);
void insertionsort(char **first, int N);
void nearvertex(g G);
void list(g *G);
struct node *newnode(struct node *end, g G, int i, int j);
#endif //LAB_10_4_GRAPH_H
