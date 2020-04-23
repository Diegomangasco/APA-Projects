#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char let1;
    int n1;
    char let2;
    int n2;
    int in_uso;
}tessere;
int contatore = 0;
void leggi_tessere(tessere **elenco, int *num_tessere);
void matrice(tessere ***mat,tessere *el, int *i, int *j);
tessere inverti_tessere(tessere el);
void stampa_mat(tessere **mat, int dim);
void wrapper(tessere **mat,tessere *elenco, int righe, int n);
void disp_semp(tessere **mat,tessere *elenco, int dim, int pos, int *maxcount, int n, tessere ***sol);
int conta(tessere **mat, int dim);
int main()
{
    int righe,colonne;
    tessere *elenco;
    tessere **mat;
    int num_tessere;
    leggi_tessere(&elenco,&num_tessere);
    matrice(&mat,elenco,&righe,&colonne);
    stampa_mat(mat,righe);
    wrapper(mat,elenco,righe,num_tessere);
    return 0;
}
void stampa_mat(tessere **mat, int dim)
{
    int i,j;
    for(i=0;i<dim;i++)
    {
        printf("\n%d riga\n",i+1);
        for(j=0;j<dim;j++)
            printf("Tessera: lettera:%c numero%d lettera:%c numero:%d\n",mat[i][j].let1, mat[i][j].n1, mat[i][j].let2,mat[i][j].n2);
    }
    return;
}
void leggi_tessere(tessere **elenco,int *num_tessere)
{
    int i;
    tessere *el;
    char linea[80];
    FILE *fp=fopen("tiles.txt","r");
    fgets(linea,80,fp);
    sscanf(linea,"%d",num_tessere);
    el=malloc(*num_tessere*sizeof(tessere));
    for(i=0;i<*num_tessere;i++)
    {
        fgets(linea,80,fp);
        sscanf(linea,"%c %d %c %d",&el[i].let1,&el[i].n1,&el[i].let2,&el[i].n2);
        printf("\nTessera: lettera: %c numero %d lettera %c numero %d\n", el[i].let1, el[i].n1, el[i].let2, el[i].n2);
        el[i].in_uso=0;
    }
    *elenco=el;
    fclose(fp);
    return;
}
void matrice(tessere ***mat,tessere *el, int *i, int *j)
{
    int righe,colonne,t,h;
    int v1,v2;
    tessere **matrice;
    tessere y;
    FILE *fp=fopen("board.txt","r");
    fscanf(fp,"%d%d",&righe,&colonne);
    matrice=malloc(righe*sizeof(tessere*));
    for(t=0;t<righe;t++)
        matrice[t]=malloc(colonne*sizeof(tessere));
    for(t=0;t<righe;t++)
    {
        for(h=0;h<colonne;h++)
        {
            fscanf(fp,"%d/%d",&v1,&v2);
            if(v1==-1)
            {
                matrice[t][h].let1='n';
                matrice[t][h].let2='n';
                matrice[t][h].n1=0;
                matrice[t][h].n2=0;
            }
            else if(v2==0)
            {
                matrice[t][h].let1=el[v1].let1;
                matrice[t][h].let2=el[v1].let2;
                matrice[t][h].n1=el[v1].n1;
                matrice[t][h].n2=el[v1].n2;
                el[v1].in_uso=1;
            }
            else
            {
                y=inverti_tessere(el[v1]);
                matrice[t][h].let1=y.let1;
                matrice[t][h].let2=y.let2;
                matrice[t][h].n1=y.n1;
                matrice[t][h].n2=y.n2;
                el[v1].in_uso=1;
            }
        }
    }
    *i=righe;
    *j=colonne;
    *mat=matrice;
    return;
}
tessere inverti_tessere(tessere el)
{
    int tmp=0;
    char tmp2='\0';
    tmp2=el.let1;
    el.let1=el.let2;
    el.let2=tmp2;
    tmp=el.n1;
    el.n1=el.n2;
    el.n2=tmp;
    return el;
}
void wrapper(tessere **mat,tessere *elenco, int righe, int n)
{
    int pos=0;
    int maxcount=0;
    int i;
    tessere **sol;
    int dim=righe;
    sol=malloc(dim*sizeof(tessere*));
    for(i=0;i<dim;i++)
        sol[i]=malloc(dim*sizeof(tessere));
    disp_semp(mat,elenco,righe, pos, &maxcount,n,&sol);
    for(i=0;i<dim;i++)
    	free(mat[i]);
    printf("\n\nSoluzione:\n");
    stampa_mat(sol,dim);
    printf("\nPunteggio soluzione: %d\n",maxcount);
    printf("\nTabelle create: %d\n",contatore);
}
void disp_semp(tessere **mat,tessere *elenco, int dim, int pos, int *maxcount, int n, tessere ***sol)
{
    int i,j,t;
    int count;
    tessere y;
    if(pos<(dim*dim))
    {
        i=pos/dim; j=pos%dim;
        while(mat[i][j].let1!='n' && i<dim && j<dim)
        {
            pos++;
            i=pos/dim; j=pos%dim;
        }
    }
    else
    {
        contatore++;
        count=conta(mat,dim);
        if(count>*maxcount)
        {
            *maxcount=count;
            for(i=0;i<dim;i++)
            {
                for(j=0;j<dim;j++)
                {
                    (*sol)[i][j].let1=mat[i][j].let1;
                    (*sol)[i][j].let2=mat[i][j].let2;
                    (*sol)[i][j].n1=mat[i][j].n1;
                    (*sol)[i][j].n2=mat[i][j].n2;
                }
            }
        }
        return;
    }
    for(t=0;t<n;t++)
    {
        if(elenco[t].in_uso==0)
        {
            mat[i][j].let1=elenco[t].let1;
            mat[i][j].let2=elenco[t].let2;
            mat[i][j].n1=elenco[t].n1;
            mat[i][j].n2=elenco[t].n2;
            elenco[t].in_uso=1;
            disp_semp(mat,elenco,dim,pos+1,maxcount,n,sol);
            y=inverti_tessere(elenco[t]);
            mat[i][j].let1=y.let1;
            mat[i][j].let2=y.let2;
            mat[i][j].n1=y.n1;
            mat[i][j].n2=y.n2;
            disp_semp(mat,elenco,dim,pos+1,maxcount,n,sol);
            elenco[t].in_uso=0;
            mat[i][j].let1='n';
        }
    }
    return;
}
int conta(tessere **mat, int dim)
{
    int colore=1,countr,countc,i,j, counttot=0;
    for(i=0;i<dim;i++)    //controllo tubi orizzontali
    {
        countr=0;
        countr+=mat[i][0].n1;
        for(j=1;j<dim && colore;j++)
        {
            if(mat[i][j-1].let1==mat[i][j].let1)
                countr+=mat[i][j].n1;
            else colore=0;
        }
        if(colore!=0)
            counttot+=countr;
        else colore=1;
    }
    colore=1;
    for(j=0;j<dim;j++)
    {
        countc=0;
        countc+=mat[0][j].n2;
        for(i=1;i<dim && colore;i++)
        {
            if(mat[i-1][j].let2==mat[i][j].let2)
                countc+=mat[i][j].n2;
            else colore=0;
        }
        if(colore!=0)
            counttot+=countc;
        else colore=1;
    }
    return counttot;
}
