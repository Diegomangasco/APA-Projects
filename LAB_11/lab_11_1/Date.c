//
// Created by UTENTE on 12/01/2020.
//
#include "Date.h"
date* dinit()	//inizializzazione data
{
    date *d;
    d=malloc(sizeof(date));
    return d;
}
date* dNULL()	//azzera data
{
    date *d=dinit();
    d->day=0;
    d->hour=0;
    d->minutes=0;
    d->month=0;
    d->year=0;
    return d;
}
int dcmp(int a1, int m1, int g1, int a2, int m2, int g2)	//confronto tra date
{
    if(a1<a2) return -1;
    if(a1>a2) return 1;
    if(m1<m2) return -1;
    if(m1>m2) return 1;
    if(g1<g2) return -1;
    if(g1>g2) return 1;
    return 0;
}