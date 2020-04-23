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
   fscanf(fp,"%d%d",&N,&E); //lettura numero nodi e numero archi da file
   sol = malloc(N*sizeof(int)); //
   archi=(vertex *)malloc(E*sizeof(vertex));    //vettore di struct
   vett=malloc(N*sizeof(int));  //vettore dove memorizzo i singoli nodi, senza ripetizioni
   for(i=0;i<N;i++)
       vett[i]=-1;  //inizializzo vett a -1, dato che esiste il nodo zero
   printf("Archi presi dal file:\n");
   for(i=0;i<E;i++)
   {
       fscanf(fp,"%d%d",&n1,&n2);
       if(n1>=N || n2>=N)   //controllo che i nodi siano nel range giusto
       {
           fprintf(stderr,"Errore nel file grafo.txt");
           exit(1);
       }
       else
       {
           archi[i].x=n1;
           archi[i].y=n2;
           printf("%d %d\n",archi[i].x, archi[i].y);    //stampa del file a video
       }
   }
   fclose(fp);
   for(i=0,j=0;i<E && j<N;i++)  //riempo vett
   {
       trovato1=trovato2=0; //flag per controllare che non abbia già preso dei valori in un arco
       for(t=0;t<N;t++) //ciclo per scandire vett (inizializzato tutto a -1)
       {
           if(vett[t]==archi[i].x)  //se l'elemento i vett[t] è uguale al primo nodo di un arco
            trovato1=1;
           if(vett[t]==archi[i].y)  //se l'elemento i vett[t] è uguale al secondo nodo di un arco
            trovato2=1;
       }
       if(trovato1!=1)  //i flag sono rimasti a zero, non ho trovato in vett i nodi di archi[i]
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
   for(i=0;i<N;i++) //stampa di vett
        printf("%d ",vett[i]);
   printf("\n");
   vertexcover(sol,pos,archi,vett,N,E);
   free(sol);
   free(vett);
   free(archi);
   return 0;
}
void vertexcover(int *sol, int pos, vertex *archi,int *vett,int N, int E)
{
    int i,j;
    int count;
    int *marcatore=calloc(E,sizeof(int));   //marcatore inizializzato a zero
    if(pos>=N)  //caso terminale
    {
        count=0;
       for(i=0;i<N;i++) //ciclo su ogni elemento di sol
       {
           if(sol[i]==1)    //preso l'elemento di vett in posizione i
           {
              for(j=0;j<E;j++)
              {
                  if(vett[i]==archi[j].x || vett[i]==archi[j].y)    //vett[i] rappresenta l'elemento di vett scelto come soluzione dal vettore sol
                  {
                    if(marcatore[j]==0) //se non sono ho ancora controllato quell'arco (per non controllare più volte uno stesso arco)
                    {
                        count++;    //aggoirno il contatore
                        marcatore[j]=1; //arco controllato
                    }
                  }
              }
           }
       }
       free(marcatore);
       if(count==E) //se count = E, il vertex cover copre tutti gli archi
       {
            printf("Vertex cover: ( "); //stampa del vertex cover
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
    vertexcover(sol,pos+1,archi,vett,N,E);  //discese ricorsive
    sol[pos]=1;
    vertexcover(sol,pos+1,archi,vett,N,E);
    return;
}
