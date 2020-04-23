#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DD 12
#define DP 40
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
void greedysolution(int N,element *vector);
void selectionsort(element *front, int f);
void stamp(element **program);
void score(element **program);
int main() {
    element *vector;
    int n;
    n=readfile(&vector);
    greedysolution(n,vector);
    return 0;
}
int readfile(element **vector)
{
    int num;
    int i=0;
    element *h;
    char linea[200];
    FILE *fp=fopen("elementi.txt","r");
    fgets(linea,80,fp);
    sscanf(linea,"%d",&num);
    h=malloc(num*sizeof(element));
    while(i<num)
    {
        fgets(linea,200,fp);
        sscanf(linea,"%s %d %d %d %d %d %f %d",h[i].name,&h[i].type,&h[i].entry,&h[i].exit,&h[i].priority,&h[i].final,&h[i].score,&h[i].difficulty);
        i++;
    }
    *vector=h;
    return num;
}
void selectionsort(element *front, int f)
{
    int i;
    int j;
    int x;
    element tmp;
    for(i=0;i<f;i++)
    {
        x=i;
        for(j=i+1;j<f;j++)
        {
            if((front[j].score < front[x].score))
                x=j;
        }
        tmp=front[i];
        front[i]=front[x];
        front[x]=tmp;
    }
    return;
}
void stamp(element **program)
{
    printf("\n");
    int i,j,flag=1;
    float score=0.0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        {
            if (program[i][j].score != -1)
                printf("%s ", program[i][j].name);
            else break;
        }
        printf("\n");
    }
}
void score(element **program)
{
    int i,j,flag=1;
    float score =0.0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        {
            if (program[i][j].score != -1)
            {
                if (i == 2 && flag)
                {
                    if(program[i][j].difficulty>=8) {
                        score += program[i][j].score*1.5;
                        flag = 0;
                    }
                }
                else score+=program[i][j].score;
            }
            else break;
        }
    }
}
void greedysolution(int N,element *vector) {
    int i, j, h;
    int flag=1;
    int infront = 0, back = 0, seq = 0;
    int diff,difftot=0;
    element **program = malloc(3 * sizeof(element *));
    for (i = 0; i < 3; i++)
    {
        program[i] = malloc(5 * sizeof(element));
        for(h=0;h<5;h++) program[i][h].score=-1;
    }
    selectionsort(vector, N);
    for (h=0, j=N-1;h<3;h++) {
        while(vector[j].entry!=1) j--;
        program[h][0] = vector[j];
        difftot+=program[h][0].difficulty;
        if(program[h][0].type==2) infront=1;
        else if (program[h][0].type==1) back=1;
    }
    for (h = 0; h < 3 && flag; h++)
    {
        diff=program[h][0].difficulty;
        for (i = 1; i < 5; i++)
        {
            if(difftot>=DP) //superata massima difficoltà programma
            {
                flag=0;
                break;
            }
            if (diff >= DD) break;  //superata massima difficoltà diagonale
            if (program[h][i - 1].final == 1) break;    //elemento inserito in precedenza è finale
            if (infront == 0)   //se non ho ancora un elemento di tipo avanti
            {
                j = N - 1;
                while(j>=0)
                {
                    if((diff+vector[j].difficulty>=DD) || (difftot+vector[j].difficulty>=DP)) j--;
                    else if (vector[j].type != 2) j--;
                    else break;
                }
                if(j<0) break;
                program[h][i] = vector[j];
                infront = 1;
                diff += program[h][i].difficulty;
            }
            else if (back == 0) //se non ho ancora un elemento di tipo indietro
            {
                j = N - 1;
                while(j>=0)
                {
                    if((diff+vector[j].difficulty>=DD) || (difftot+vector[j].difficulty>=DP)) j--;
                    else if (vector[j].type != 1) j--;
                    else break;
                }
                if(j<0) break;
                program[h][i] = vector[j];
                back = 1;
                diff += program[h][i].difficulty;
            }
            else if (seq == 0 && program[h][i - 1].priority == 0)
            {
                j = N - 1;
                while(j>=0)
                {
                    if((diff+vector[j].difficulty>=DD) || (difftot+vector[j].difficulty>=DP)) j--;
                    else if (vector[j].entry!=program[h][i-1].exit) j--;
                    else break;
                }
                if(j<0) break;
                program[h][i] = vector[j];
                seq = 1;
                diff += program[h][i].difficulty;
            }
            else
            {
                j=N-1;
                while(j>=0)
                {
                    if((diff+vector[j].difficulty>=DD) || (difftot+vector[j].difficulty>=DP)) j--;
                    else break;
                }
                if(j<0) break;
                program[h][i] = vector[j];
                diff += program[h][i].difficulty;
            }
            difftot+=diff;
        }
    }
    stamp(program);
}
