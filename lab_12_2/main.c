#include <stdio.h>
#include "Graph.h"
int main() {
    FILE *fp=fopen("grafo2.txt","r");
    Graph g;
    g=GRAPHload(fp);
    printf("Collections that we must remove to create a DAG:\n");
    wrapper(g);


    return 0;
}