#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int x;
    int y;
}vertex;
void vertexcover(int *sol, int pos, vertex *archi, int *vett, int N, int E);
int main()
{
   FILE *fp;
   vertex *archi;
   int i,N,E,j,t;
   int n1,n2;
   int *sol,*vett;
   int trovato1=0,trovato2=0;
   int pos = 0;
   fp=fopen("grafo.txt","r");
   fscanf(fp,"%d%d",&N,&E); 	//read the number of nodes and the number of edges from the input file
   sol = malloc(N*sizeof(int)); 
   archi=(vertex *)malloc(E*sizeof(vertex));    //structs vector
   vett=malloc(N*sizeof(int));  
   for(i=0;i<N;i++)
       vett[i]=-1;  //initialization
   printf("Archi presi dal file:\n");
   for(i=0;i<E;i++)
   {
       fscanf(fp,"%d%d",&n1,&n2);
       if(n1>=N || n2>=N)   //control on the numbers of input nodes
       {
           fprintf(stderr,"File error in grafo.txt");
           exit(1);
       }
       else
       {
           archi[i].x=n1;
           archi[i].y=n2;
           printf("%d %d\n",archi[i].x, archi[i].y);    //stamp
       }
   }
   fclose(fp);
   for(i=0,j=0;i<E && j<N;i++)  //vett will contain the singles nodes of the graph, without repetition
   {
       trovato1=trovato2=0; 
       for(t=0;t<N;t++) //cicle to control vett (all initialized at -1)
       {
           if(vett[t]==archi[i].x)  //if the first node of the element i is equal to vett[t]
            trovato1=1;
           if(vett[t]==archi[i].y)  //if the second node of the element i is equal to vett[t]
            trovato2=1;
       }
       if(trovato1!=1)  //the flag remain at 0 --> new node
       {
           vett[j]=archi[i].x;
           j++;
       }
       if(trovato2!=1)
       {
           vett[j]=archi[i].y;
           j++;
       }
   }
   printf("Vett: ");
   for(i=0;i<N;i++) 	//vett stamp
        printf("%d ",vett[i]);
   printf("\n");
   vertexcover(sol,pos,archi,vett,N,E);	//recursive function
   free(sol);
   free(vett);
   free(archi);
   return 0;
}
void vertexcover(int *sol, int pos, vertex *archi,int *vett,int N, int E)	//function that uses a power set of repeated partial permutations
{
    int i,j;
    int count;
    if(pos>=N)  //terminal case
    {
	int *marcatore=calloc(E,sizeof(int));   //mark vector
        count=0;
       for(i=0;i<N;i++) //cicle on vector sol
       {
           if(sol[i]==1)    //took the i element of sol
           {
              for(j=0;j<E;j++)
              {
                  if(vett[i]==archi[j].x || vett[i]==archi[j].y)    //vett[i] represents the element choosen in the power set
                  {
                    if(marcatore[j]==0) //if the edge j has not yet been controlled
                    {
                        count++;    
                        marcatore[j]=1; //controlled
                    }
                  }
              }
           }
       }
       free(marcatore);
       if(count==E) 	//if count is equal to E, a new the vertex cover has found
       {
            printf("Vertex cover: ( "); //vertex cover stamp
            for(i=0;i<N;i++)
            {
                if(sol[i]==1)
                    printf("%d ",vett[i]);
            }
            printf(")\n");
        }
        return;
    }
    sol[pos]=0;
    vertexcover(sol,pos+1,archi,vett,N,E);  	//recursion
    sol[pos]=1;
    vertexcover(sol,pos+1,archi,vett,N,E);	//recursion
    return;
}
