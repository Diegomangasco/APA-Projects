#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char pietra;
    int numero;
    int valore;
    int max_rip;
}pietre;
int iterazioni=0, iterazioni2=0;
void powerset(char *sol, pietre *val, int pos,int finito,int lung,char **magg, int *maxcount);
void wrapper(char *sol, pietre *val, int pos, int finito,int lung);
int conta_zaffiri(char *sol, int pos,int *z,int *s);
int conta(int z, int s,char *sol, int pos,pietre *val);
int controllo(char *sol, int i, int pos);
void stampa_collana(char *magg,int maxcount);
int main()
{
    pietre *val;
    int i;
    int lung;
    int finito=0;
    int pos=0;
    char *sol;
    val=malloc(4*sizeof(pietre));
    val[0].pietra='z';
    val[1].pietra='r';
    val[2].pietra='t';
    val[3].pietra='s';
    printf("Inserisci il numero di zaffiri: ");
    scanf("%d",&val[0].numero);
    printf("\n");
    printf("Inserisci il valore degli zaffiri: ");
    scanf("%d",&val[0].valore);
    printf("\n");
    printf("Inserisci il numero di rubini: ");
    scanf("%d",&val[1].numero);
    printf("\n");
    printf("Inserisci il valore dei rubini: ");
    scanf("%d",&val[1].valore);
    printf("\n");
    printf("Inserisci il numero di topazi: ");
    scanf("%d",&val[2].numero);
    printf("\n");
    printf("Inserisci il valore degli topazi: ");
    scanf("%d",&val[2].valore);
    printf("\n");
    printf("Inserisci il numero di smeraldi: ");
    scanf("%d",&val[3].numero);
    printf("\n");
    printf("Inserisci il valore degli smeraldi: ");
    scanf("%d",&val[3].valore);
    printf("\n");
    printf("Inserisci il massimo numero di ripetizioni consecutive: ");
    scanf("%d",&val[0].max_rip);
    printf("\n");
    val[1].max_rip=val[2].max_rip=val[3].max_rip=val[0].max_rip;
    lung=1;
    for(i=0;i<4;i++)
        lung+=val[i].numero;
    sol=malloc(lung*sizeof(char));
    for(i=0;i<lung;i++)
        sol[i]='\0';
    wrapper(sol,val,pos,finito,lung);
    return 0;
}
void stampa_collana(char *magg, int maxcount)
{
    int i=0;
    printf("Collana: ");
    while(magg[i]!='\0')
        printf("%c ",magg[i++]);
    printf("\n");
    printf("Valore: %d\n",maxcount);
    return;
}
void wrapper(char *sol, pietre *val, int pos, int finito,int lung)
{
    char *magg=malloc((lung+1)*sizeof(char));
    int maxcount=0;
    powerset(sol,val,pos,finito,lung,&magg,&maxcount);
    stampa_collana(magg,maxcount);
    printf("Soluzioni totali trovate: %d\n",iterazioni);
    printf("Soluzioni accettabili secondo il criterio del numero di zaffiri e smeraldi: %d\n", iterazioni2);
}
void powerset(char *sol, pietre *val, int pos, int finito,int lung,char **magg,int *maxcount)
{
    int i,z,s;
    int count;
    if(finito==1 || pos==(lung-1))
    {
        iterazioni++;
        if(conta_zaffiri(sol,pos,&z,&s)) //se gli zaffiri non superano il numero di smeraldi
        {
            iterazioni2++;
            count=conta(z,s,sol,pos,val);
            if(count>*maxcount)
            {
                *maxcount=count;
                for(i=0;i<=pos;i++)
                    (*magg)[i]=sol[i];
                (*magg)[i]='\0';
            }
        }
        return; //se gli zaffiri hanno superato gli smeraldi, collana non valida
    }
    for(i=0;i<4;i++)
    {
        if(pos==0)  //primo caso
        {
            sol[pos]=val[i].pietra;
            val[i].numero--;
            val[i].max_rip--;
            powerset(sol,val,pos+1,0,lung,magg,maxcount);
            val[i].max_rip=3;
            val[i].numero++;
        }
        else
        {
            if(controllo(sol,i,pos))
            {
                if(val[i].numero!=0 && val[i].max_rip!=0)
                {
                    sol[pos]=val[i].pietra;
                    val[i].max_rip--;
                    val[i].numero--;
                    powerset(sol,val,pos+1,0,lung,magg,maxcount);
                    val[i].max_rip=3;
                    val[i].numero++;
                }
            }
        }
    }
    powerset(sol,val,pos,1,lung,magg,maxcount);
}
int controllo(char *sol, int i, int pos)
{
    switch(i)
    {
    case 0:
        if(sol[pos-1]=='z') return 1;
        if(sol[pos-1]=='t') return 1;
        return 0;
        break;
    case 1:
        if(sol[pos-1]=='t') return 1;
        if(sol[pos-1]=='z') return 1;
        return 0;
        break;
    case 2:
        if(sol[pos-1]=='r') return 1;
        if(sol[pos-1]=='s') return 1;
        return 0;
        break;
    case 3:
        if(sol[pos-1]=='s') return 1;
        if(sol[pos-1]=='r') return 1;
        return 0;
        break;
    }
}
int conta_zaffiri(char *sol,int pos,int*z,int *s)   //verifico se il numero di zaffiri è minore o uguale a quello di smeraldi
{
    int i=0;
    *z=0;*s=0;
    while(i<=pos)
    {
        if(sol[i]=='z')
            (*z)++;
        if(sol[i]=='s')
            (*s)++;
        i++;
    }
    if(*z>*s) return 0;
    else return 1;
}
int conta(int z,int s,char*sol,int pos,pietre *val) //funzione per il calcolo del valore totale della collana
{
    int i=0,count;
    count = (z*val[0].valore)+(s*val[3].valore);
    while(i<=pos)
    {
       switch(sol[i])
       {
       case 't':
        count+=val[2].valore;
        break;
       case 'r':
        count+=val[1].valore;
        break;
       }
       i++;
    }
    return count;
}
