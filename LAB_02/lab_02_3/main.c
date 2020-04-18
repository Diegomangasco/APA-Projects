#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct{     //struttura dati
char sequenza[6];   //sequenza specifica
char parola [10][25];   //matrice per le parole che contengono la sequenza
int index [10];     //vettore per contenere i numeri delle parole trovate
int cont;           //contatore per far avanzare le caselle di index
}sequenze;

int n;      //numero delle sequenze
void leggisequenze(FILE *fp,sequenze lista[20]);
void leggisorgente(sequenze lista[20]);
int scansiona(char parola1[6],char parola2[25],int i);
int controlloapo(char parola2[25]);
void controlloparola(char parola[25],sequenze lista[20],int t);
int main()
{
    FILE *fp;
    sequenze lista[20];
    fp=fopen("sequenze.txt","r");
    if(fp==NULL)    //controllo di consistenza del file sequenze.txt
    {
        fprintf(stderr,"Il file è vuoto!");
        exit(1);
    }
    leggisequenze(fp,lista);
    fclose(fp);
    leggisorgente(lista);
    return 0;
}
void leggisequenze(FILE *fp,sequenze lista[20])
{
    int i;
    fscanf(fp,"%d",&n); //lettura del numero delle sequenze
    if(n>20)            //non possono esserci più di venti sequenze
    {
        fprintf(stderr,"Troppe sequenze da controllare!");
        exit(2);
    }
    for(i=0;i<n;i++)    //memorizzazione sequenze nella struttura
        fscanf(fp,"%s",lista[i].sequenza);

}
void leggisorgente(sequenze lista[n])
{
    FILE *fp;
    char parola [25];
    int i,j,p,lung;
    char parola2[25],parola3[25];
    int t=0;
    for(i=0;i<n;i++)    //inizializzo i vettori index a -1 per un controllo nell'output
    {
        for(j=0;j<10;j++){
            lista[i].index[j]=-1;
            lista[i].cont=0;        //cont è il contatore delle parole trovate per la sequenza i-esima (massimo 10)
        }
    }
    fp=fopen("sorgente.txt","r");
    if(fp==NULL)    //controllo consistenza del file sorgente.txt
    {
        fprintf(stderr,"Il file è vuoto!");
        exit(3);
    }

    while(fscanf(fp,"%s",parola)!=EOF)  //leggo parola per parola
    {
        if(!controlloapo(parola))        //se la parola non contiene apostrofo
        {
            t++;
            controlloparola(parola,lista,t);    //lancio la funzione se la parola non contiene l'apostrofo
        }

        else        //se la parola contiene apostrofo
        {
            j=0;
            lung=strlen(parola);
            for(i=0;i<lung && !j;i++) //cerco l'apostrofo
            {
                if(parola[i]==39)
                    j=i;        //memorizzo l'indice dell'apostrofo
                else
                    parola2[i]=parola[i];   //copio la parola prima dell'apostrofo in parola2 e lancio controllaparola
            }
            parola2[i]='\0';        //aggiungo terminatore alla stringa parola2
            t++;                        //incremento t perchè si è aggiunta una nuova parola
            controlloparola(parola2,lista,t);

            for(i=j+1,p=0;i<lung;i++,p++) //copio la parola dopo l'apostrofo in parola3 e lancio controllaparola
                parola3[p]=parola[i];

            parola3[p]='\0';        //aggiungo terminatore alla stringa parola3
            printf("%c",parola3[p]);
            t++;                                    //incremento t perchè si è aggiunta una nuova parola
            controlloparola(parola3,lista,t);
        }
    }
    fclose(fp);

    for(i=0;i<n;i++)    //stampa delle sequenze con le rispettive parole e numeri corrispondenti
    {
        printf("Sequenza %s\n",lista[i].sequenza);
        for(j=0;j<10 && lista[i].index[j]!=-1;j++)  //stampo solo le parole e gli indici trovati, per questo avevo inizializzato il vettore index a -1
            printf("Parola: %s --> Numero: %d\n",lista[i].parola[j],lista[i].index[j]);

        printf("\n");
    }
}

int controlloapo(char parola2[25])
{
    int i;
    int flag=0;
    for(i=0;i<strlen(parola2) && !flag;i++)  //verifico se nella parola è presente l'apostrofo
    {
      if(parola2[i]==39)
            flag=1;
    }
    return flag;    //ritorno vero o falso
}
void controlloparola(char parola[25],sequenze lista[20],int t)
{
    int i,j,h,lung;
    parola[0]=tolower(parola[0]);   //nel caso ci siano lettere maiuscole
    lung=strlen(parola);
    int flag;
    for(j=0;j<n;j++)        //per tutte le sequenze memorizzate
    {
    for(i=0;i<lung;i++)     //controllo carattere per carattere la stringa
    {
        if(parola[i]==lista[j].sequenza[0]) //confornto prima lettera della sequenza con un carattere di parola
        {
            if(lista[j].cont<10)    //controllo se ho finito le occorrenze a disposizione (massimo 10)
            {
                flag=1;
                for(h=0;h<10 && flag;h++)   //controllo se ho già memorizzato quella parola per quella data sequenza ("nonostante" mi darebbe due volte l'occorrenza di "no", in questo modo evito che succeda)
                {
                    if(lista[j].index[h]==t)
                        flag=0;
                }
                if(flag)    //se non ho ancora memorizzato quella parola per la sequenza j
                {
                    if(scansiona(lista[j].sequenza,parola,i))
                    {
                        strcpy(lista[j].parola[lista[j].cont],parola);  //memorizzo la parola
                        lista[j].index[lista[j].cont]=t;                //memorizzo il numero della parola
                        lista[j].cont++;                                //aggiorno il contatore delle parole che contengono la sequenza j
                    }
                }
            }
        }
    }
}

}
int scansiona(char parola1[6],char parola2[25],int i)
{
    int h;
    int lung2=strlen(parola1);
    if(lung2==1)    //se la sequenza è composta da un solo carattere
        return 1;
    int flag=1;
    for(h=1, i= i+1;h<lung2 && flag;h++, i++)   //parto a controllare dal secondo carattere della sequenza passata e dal carattere successivo a quello già confrontato della parola
    {
        if(parola1[h]!=parola2[i])
            flag=0;
    }
    return flag;
}
