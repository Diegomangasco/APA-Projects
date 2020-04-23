//
// Created by UTENTE on 17/01/2020.
//

#ifndef LAB_12_02_PQ_H
#define LAB_12_02_PQ_H
typedef struct pqueue *PQ;

PQ      PQinit(int maxN);
void    PQfree(PQ pq);
int     PQempty(PQ pq);
void    PQinsert(PQ pq, int *mindist, int node);
int     PQextractMin(PQ pq, int *mindist);
void    PQchange (PQ pq, int *mindist, int k);

#endif //LAB_12_02_PQ_H
