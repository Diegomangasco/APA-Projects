#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int s;
    int k;
}evento;
void leggi_file (evento **att, int *N);
void ordina(int N, evento **att);
int distanza(evento var);
void dyn(int N, int *E, int *L, evento *att);
void result(int *L, evento *att, int i);
int controllo(evento val1, evento val2);
int main()
{
    evento *att;
    int num;
    int *E,*L;
    leggi_file(&att,&num);
    E=malloc(num*sizeof(int));
    L=malloc(num*sizeof(int));
    ordina(num,&att);
    dyn(num,E,L,att);
    return 0;
}
void ordina(int N, evento **att)
{
    int i,j;
    evento tmp;
    for(i=0;i<N;i++)
    {
        for(j=i+1;j<N;j++)
        {
            if((*att)[i].s>(*att)[j].s)
            {
                tmp=(*att)[i];
                (*att)[i]=(*att)[j];
                (*att)[j]=tmp;
            }
            else if(((*att)[i].s==(*att)[j].s) && ((*att)[i].k>(*att)[j].k))    //se le ore di partenza
            {
                tmp=(*att)[i];
                (*att)[i]=(*att)[j];
                (*att)[j]=tmp;
            }
        }
    }
    return;
}
void leggi_file(evento **att, int *N)
{
    FILE *fp=fopen("att.txt","r");
    char linea[80];
    int num;
    int i=0;
    fgets(linea,80,fp);
    sscanf(linea,"%d",&num);
    *att=malloc(num*sizeof(evento));
    while(i<num)
    {
        fgets(linea,80,fp);
        sscanf(linea,"%d %d",&(*att)[i].s,&(*att)[i].k);
        i++;
    }
    *N=num;
    return;
}
void dyn(int N, int *E, int *L, evento *att)
{
    int i,j;
    int best=0,indice;
    E[0]=distanza(att[0]);
    L[0]=-1;
    for(i=1;i<N;i++)
    {
        L[i]=-1;
        E[i]=0;
        for(j=0;j<i;j++)
        {
            if(controllo(att[j],att[i]) && E[i]<E[j]+distanza(att[i]))
            {
                E[i]=E[j]+distanza(att[i]);
                L[i]=j;
            }
        }
        if(E[i]>best)
        {
            best=E[i];
            indice = i;
        }
    }
    result(L,att,indice);
    return;
}
void result(int *L, evento *att, int i)
{
    if(L[i]==-1)
    {
        printf("Evento: s %d k %d\n",att[i].s,att[i].k);
        return;
    }
    printf("Evento: s %d k %d\n",att[i].s,att[i].k);
    result(L,att,L[i]);
    return;
}
int distanza (evento var)
{
    return var.k - var.s;
}
int controllo(evento val1, evento val2)
{
    if(val1.k<=val2.s) return 1;
    else return 0;
}


