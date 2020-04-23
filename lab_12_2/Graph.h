//
// Created by UTENTE on 17/01/2020.
//

#ifndef LAB_12_02_GRAPH_H
#define LAB_12_02_GRAPH_H
#include "ST.h"
#include "DAG.h"
typedef struct graph *Graph;
Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fin);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHspD(Graph G, int id);
void  GRAPHspBF(Graph G, int id);
void wrapper(Graph G);
void searchedges(Edge *a, int *sol, int pos, Graph G, int *kard, int *maxweight, int *sol_best);
int dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *sol, Edge *a);
int GRAPHdfs_mod(Graph G, int id, int *sol, Edge *a);
void creationDAG(int *sol_best, Graph DG, Edge *a);
void maxwayDAG(Graph DG, int id);
#endif //LAB_12_02_GRAPH_H
