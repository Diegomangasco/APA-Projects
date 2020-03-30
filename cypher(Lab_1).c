#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  //structure to contain words and their coding
{
    char parola[10];
    char cifratura[10];
} cifrario;
void leggidizionario(FILE*fp2,int *s, cifrario **lista);
void sostituisci(FILE *fp,int s,cifrario lista[s]);
int scorriparola(char linea[80],char parola [10],int j,int i);
int main()
{
    FILE *fp,*fp2;
    int s;
    cifrario *lista;
    fp=fopen("sorgente.txt","r");
    fp2=fopen("dizionario.txt","r");

    if(fp==NULL) 
    {
        fprintf(stderr,"File sorgente.txt vuoto!\n");
        exit(1);
    }
    if(fp2==NULL)   
    {
        fprintf(stderr,"File dizionario.txt vuoto!\n");
        exit(2);
    }
    leggidizionario(fp2,&s,&lista);   
    sostituisci(fp,s,lista);  
    fclose(fp2);
    fclose(fp);

    return 0;
}
void leggidizionario(FILE*fp2,int *s, cifrario **lista)	//read dictionary
{
    int i=0;
    fscanf(fp2,"%d",s);
    *lista=malloc(s*sizeof(cifrario));
    while(i<*s)
    {
        fscanf(fp2,"%s %s",lista[i].cifratura,lista[i].parola);   
        i++;
    }   
}
void sostituisci(FILE*fp,int s, cifrario lista[s])
{
    FILE *fp3;
    fp3=fopen("ricodificato.txt","w");
    char linea[80];
    int i,j,esci=0;
    int trovato=1;
    int lung;

    while(fgets(linea,80,fp)!=NULL) //read file source
    {
        lung=strlen(linea);     
        i=0;
        while(i<lung)
        {
            for(j=0;j<s && !esci;j++)   //repeat for all the dictionary worlds
            {
                if(lista[j].parola[0]==linea[i]) //first character is equal
                {
                    trovato=scorriparola(linea,lista[j].parola,j,i);
                        if(trovato) //if all the worlds must be changed
                        {
                            fprintf(fp3,"%s",lista[j].cifratura); //stamp the coding $numero$
                            i=i+strlen(lista[j].parola);        //go to the next world
                            esci=1;				//don't control the other dictionary worlds
                        }
                }
            }
            if(!esci)   //don't change anything
            {
                fprintf(fp3,"%c",linea[i]); //stamp the character
                i++;			    //next character				
            }
            else    
                esci=0; //new cicle
        }
    }
    fclose(fp3);
}
int scorriparola(char linea [80],char parola[10],int j,int i)
{
    int h,t=1;
    for(h=i+1;h<i+(strlen(parola));h++,t++) //from i+1 index (i has already controlled) to the last character of dictionary world
    {
        if(linea[h]!=parola[t]) 	
            return 0;
    }
    if(h==strlen(parola))   		//sostitution is permitted
        return 1;
    else
        return -1;          	
}

