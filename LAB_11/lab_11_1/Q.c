//
// Created by UTENTE on 12/01/2020.
//
#include "Q.h"
quotation* qinit()	//inizializzazione quotation
{
    quotation *q=malloc(sizeof(quotation));
    return q;
}
quotation* qNULL()	//azzera quotation
{
    quotation* q=qinit();
    q->quote=0;
	q->num=0;
	q->den=0;
    return q;
}
float calc(quotation *q)	//calcolo quotazione attuale
{
    q->quote=q->num/q->den;
	return q->quote;
}
