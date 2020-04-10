#include <stdio.h>
#include <stdlib.h>

int conta(char S[21],int n);

int main()
{
    char file[21];
    char linea[50];
    int n;
    int N;
    int num;
    int i=0;
    FILE *fp;
    printf("Inserisci il nome del file: ");
    scanf("%s",file);
    printf("Inserisci la lunghezza delle sottostringhe: ");
    scanf("%d",&n);

    fp=fopen(file,"r");
    fscanf(fp,"%d",&N);

    while(i<N && fscanf(fp,"%s",linea)!=EOF){
        num=conta(linea,n);
        i++;
        printf("\n %d : numero sotto parole riga %d",num, i+1);
    }


    fclose(fp);
   return 0;
}
int conta(char S[],int n)
{
    int l=strlen(S);
    int i;
    int j;
    int conta;
    int num=0;
    for(i=0;i<(l+1)-n;i++) /*scandisco tutta la stringa*/
    {
        conta=0;
       for (j=0;j<n;j++) /*per ogni elemento guardo esso ed i tre successivi*/
       {
           if(S[i+j]=='a' || S[i+j]=='e' || S[i+j]=='o' || S[i+j]=='u' || S[i+j]=='i')
            conta++;
       }
       if(conta>=2) /*se ho trovato almeno due vocali*/
       {
           num++;
           for(j=i;j<i+n;j++)
            printf("%c",S[j]); /*stampa delle sequenze*/
       }
       printf("\n");

    }
    return num;
}
