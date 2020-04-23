#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int s;
    int k;
}evento;
int limit;
void leggi_file (evento **att, int *N);
void attSel(int N,evento *att);
void comb_s(int pos, int start, int *maxcount, evento **sol, evento *sol_p,evento *att, int N);
int conta(evento *sott, int pos);
void stampa_sol(evento *sol);
int casistica(evento *sol_p,int pos,int N,evento var);
void ordina(int N, evento **att);
int main() {
    evento *att;
    int num;
    leggi_file(&att,&num);
    ordina(num,&att);
    attSel(num,att);
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
            else if((*att)[i].k>(*att)[j].k)
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
void attSel(int N,evento *att)
{
    int pos=0,maxcount=0,start=0;
    evento *sol=malloc(N*sizeof(evento));
    evento *sol_p=malloc(N*sizeof(evento));
    comb_s(pos,start,&maxcount,&sol,sol_p,att,N);
    stampa_sol(sol);
}
void comb_s(int pos, int start, int *maxcount, evento **sol, evento *sol_p,evento *att, int N)
{
    int i;
    int count;
    int aumento;
    if(start>=N)
    {
        count=conta(sol_p,pos);
        if(count>*maxcount)
        {
            *maxcount=count;
            for(i=0;i<pos;i++)
                (*sol)[i]=sol_p[i];
            limit=pos;
        }
        return;
    }
    for(i=start;i<N;i++)
    {
        switch(casistica(sol_p,pos,N,att[i]))
        {
        case 0:
            aumento=0;
            break;
        case 1:
           sol_p[pos-1]=att[i];
           aumento=0;
           break;
        case 2:
            sol_p[pos]=att[i];
            aumento=1;
            break;
        }
        if(aumento)
            comb_s(pos+1,i+1,maxcount,sol,sol_p,att,N);
    }
    if(i==6) comb_s(pos,i+1,maxcount,sol,sol_p,att,N);
    return;
}
int casistica(evento *sol_p,int pos,int N,evento var)
{
    int i;
    for(i=0;i<pos;i++)
    {
        if((var.s>sol_p[i].s && var.s<sol_p[i].k)) return 0;
        if (var.s==sol_p[i].s && var.k>sol_p[i].k) return 1;
    }
    return 2;
}
int conta(evento *sott, int pos)
{
    int i;
    int dist=0;
    for(i=0;i<pos;i++)
        dist+=(sott[i].k-sott[i].s);
    return dist;
}
void stampa_sol(evento *sol)
{
    int i;
    for(i=0;i<limit;i++)
        printf("Evento %d p %d a %d\n",i+1,sol[i].s,sol[i].k);
    return;
}
