#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DD 10
#define DR 20
typedef struct
{
    char name[100];
    int type;
    int entry;
    int exit;
    int priority;
    int final;
    float score;
    int difficulty;
}element;
int readfile(element **vector);
void wrapper(element *vector,int n);
void disp_rip(int pos,int *sol,int ***s,element *vector, int N, int k, int *count);
void comb_rip(int pos,int *sol,element *vector,int k, int count,int start, int **s, int front, int back, int seq, int *program, float *scoretot);
void stamp(int *program, element *vector, int **s);
int main() {
    element *vector;
    int n;
    n=readfile(&vector);
    wrapper(vector,n);
    return 0;
}
int readfile(element **vector)
{
    int num;
    int i=0;
    char linea[200];
    FILE *fp=fopen("elementi.txt","r");
    fgets(linea,80,fp);
    sscanf(linea,"%d",&num);
    (*vector)=malloc((num+1)*sizeof(element));
    while(i<num)
    {
        fgets(linea,200,fp);
        sscanf(linea,"%s %d %d %d %d %d %f %d",(*vector)[i].name,&(*vector)[i].type,&(*vector)[i].entry,&(*vector)[i].exit,&(*vector)[i].priority,&(*vector)[i].final,&(*vector)[i].score,&(*vector)[i].difficulty);
        i++;
    }
    strcpy((*vector)[num].name,"n");	//inserisco l'eleemnto nullo, perchè una diagonale può essere formata anche da meno di cinque elementi, in questo modo posso riempire gli "spazi vuoti"
    (*vector)[num].type=-1;
    (*vector)[num].entry=-1;
    (*vector)[num].exit=-1;
    (*vector)[num].priority=-1;
    (*vector)[num].score=-1.0;
    (*vector)[num].final=-1;
    (*vector)[num].difficulty=-1;
    return num;
}
void stamp(int *program, element *vector, int **s)
{
    int i,j;
    printf("Programma vincitore: \n");
    for(i=0;i<3;i++)
    {
        printf("Diagonale %d ",i+1);
        for(j=0;j<5;j++)
            printf("%s ",vector[s[program[i]][j]].name);
        printf("\n");
    }
}
void wrapper(element *vector,int n)
{
    int i;
    int pos=0,count=0;
    float scoretot=0.0;
    n++;
    int **s=malloc(n*sizeof(int*));
    for(i=0;i<n;i++) s[i]=malloc(5*sizeof(int));
    int *sol=malloc(5*sizeof(int));
    int *program=malloc(3*sizeof(int));
    int *sol2=malloc(3*sizeof(int));
    disp_rip(pos,sol,&s,vector,n,5,&count);
    comb_rip(pos,sol2,vector,3,count,0,s,0,0,0,program,&scoretot);
    stamp(program,vector,s);
}
void comb_rip(int pos,int *sol,element *vector,int k, int count,int start, int **s, int front, int back, int seq, int *program, float *scoretot)
{
    int i,j,d=0, diff=0, good=0;
    float score=0.0,scored=0.0;
    if(pos>=k)
    {
        if(seq==0) return;  //no elementi sequenziali
        if(front==0 || back==0) return; //no un avanti o no un indietro
        for (i=0;i<3;i++)
            for(j=0;j<5;j++)
            {
                if(vector[s[sol[i]][j]].type!=-1)
                    diff+=vector[s[sol[i]][j]].difficulty;
            }
        if(diff<=DR)
        {
            for(i=0;i<3;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(i==2)    //ultima diagonale
                    {
                        if(vector[s[sol[i]][j]].difficulty>=8)  //good serve per l'eventuale incremento bonus
                            good=1;
                        if(vector[s[sol[i]][j]].type!=-1)
                            scored+=vector[s[sol[i]][j]].score;
                    }
                    else
                    {
                        if(vector[s[sol[i]][j]].type!=-1)
                            score+=vector[s[sol[i]][j]].score;
                    }
                }
            }
            if(good==1)
            {
                scored=scored*1.5;
                score+=scored;
            }
            else
                score+=scored;
            if(score>*scoretot) //memorizzo se ottengo un miglioramento
            {
                *scoretot=score;
                for(i=0;i<3;i++) program[i]=sol[i];
            }
        }
        return;
    }
    for(i=start;i<count;i++)
    {
        if(front==0 || back==0) //cerco almeno un avanti e almeno un indietro
        {
            for (j = 0; j < 5; j++)
            {
                if (vector[s[i][j]].type == 2)
                    front = 1;
                else if (vector[s[i][j]].type == 1)
                    back = 1;
            }
        }
        if(seq==0)  //cerco almeno ua diagonale con elementi sequenziali
        {
            for(j=1;j<5 && !seq;j++)
            {
                if(vector[s[i][j-1]].type!=-1 && vector[s[i][j]].type!=-1)
                    seq=1;
            }
        }
        for(j=0;j<5;j++)
        {
            if(vector[s[i][j]].type!=-1)
                d+=vector[s[i][j]].difficulty;
        }
        if(d<=DD)
        {
            sol[pos]=i;
            comb_rip(pos+1,sol,vector,k,count,i+1,s,front,back,seq,program,scoretot);
        }
    }
}
void disp_rip(int pos,int *sol,int ***s,element *vector,int N,int k,int *count)
{
    int i,j;
    if(pos>=k)
    {
        printf("%d\n",*count);
        if((*count)>=N) {   //rialloco ogni volta che serve
            *s=(int **)realloc(*s,((*count)*2)*sizeof(int*));
            for(i=*count;i<(*count)*2;i++) (*s)[i]=malloc(5*sizeof(int));
        }
        for(i=0;i<k;i++)
            if(sol[i]!=19) break;   //se trovo almeno un elemento non nullo interrompo il ciclo
        if(i==k) return; //escludo le soluzioni vuote
        for(i=0;i<k;i++) (*s)[*count][i]=sol[i];    //memorizzo la diagonale trovata nella matrice
        (*count)++;
        return;
    }
    if(pos==0)
    {
        for (i = 0; i < N; i++)
        {
            if(vector[i].entry==1 && vector[i].priority!=1) //una diagonale deve iniziare per forza con un entrata frontale e con una precedenza 0
            {
                sol[pos] = i;
                disp_rip(pos+1,sol,s,vector,N,k,count);
            }
        }
    }
	else
	{
		for(j=0;j<N;j++)
		{
			if (vector[sol[pos - 1]].final != 1)    //se l'elemento inserito in precedenza non deve essere quello finale
			{
				if (vector[sol[pos - 1]].type != -1)    //se l'elemento inserito in precedenza non è quello vuoto, posso inserire sia un elemento a precedenza 0, sia uno a precedenza 1
				{
					if (vector[sol[pos - 1]].exit == vector[j].entry)   // i due elementi dovranno essere compatibili con la definizione di sequenzialità
					{
						sol[pos] = j;
						disp_rip(pos + 1, sol, s, vector, N, k, count);
					}
				}
				else
				{
				   if(vector[j].priority==0)    //se l'elemento precedente è nullo, devo per forza avere un elemento a precedenza 0
				   {
						sol[pos] = j;
						disp_rip(pos + 1, sol, s, vector, N, k, count);
					}
				}
			}
			else    //se deve essere il finale, posso solo inserire elementi vuoti per terminare la diagonale
			{
				for(i=pos;i<N;i++) sol[i]=19;
				disp_rip(5,sol,s,vector,N,k,count);
			}
		}
	}
}