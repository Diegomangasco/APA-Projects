#include <stdio.h>
#include <stdlib.h>
#define N 10

void ricerca (int vett[N]);

int main()
{
    int v[N];
    int i;
    fprintf(stdout,"Inserisci dieci numeri\n");
    for(i=0;i<10;i++)
        fscanf(stdin,"%d",&v[i]);
    ricerca(v);

    return 0;
}
void ricerca(int vett[N])
{
    int i;
    int j;
    int t;
    t=0;
    for (i=0;i<N;i++)
    {
      if(vett[i]==0)
      {
          if (i!=0)
          {
              for(j=t;j<i;j++)
                fprintf(stdout,"%d ",vett[j]);

            fprintf(stdout,"\n");
            t=i+1;
          }
          else
            t=i+1;
      }
    }

    for (j=t;j<i;j++)
        fprintf(stdout,"%d ",vett[j]);

}
