#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char pietra;	//type of stone
    int disp;		//availability
}stone;

/*The sequence to create a necklace isn't casual: a Z or a T can be followed by a Z or by a R, a R or a S can be followed by a T or by a S*/

int fz(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z);
int fr(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z);
int fs(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z);
int ft(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z);
void inizializza(stone *vett, int ****Z);
void alloc(stone *vett, int *****Z);
int main() {
    stone vett[4];
    int i;
    int ****Z, ****T,****R,****S;
    int max=0;
    int sol[4];
    vett[0].pietra='z';vett[1].pietra='r';vett[2].pietra='t';vett[3].pietra='s';
    printf("Inserisci il numero di zaffiri: ");
    scanf("%d",&vett[0].disp);
    printf("\n");
    printf("Inserisci il numero di rubini: ");
    scanf("%d",&vett[1].disp);
    printf("\n");
    printf("Inserisci il numero di topazi: ");
    scanf("%d",&vett[2].disp);
    printf("\n");
    printf("Inserisci il numero di smeraldi: ");
    scanf("%d",&vett[3].disp);
    printf("\n");
    alloc(vett,&Z);
    alloc(vett,&T);
    alloc(vett,&S);
    alloc(vett,&R);
    sol[0]=fz(vett[0].disp,vett[2].disp,vett[3].disp,vett[1].disp,R,S,T,Z);
    sol[1]=fr(vett[0].disp,vett[2].disp,vett[3].disp,vett[1].disp,R,S,T,Z);
    sol[2]=ft(vett[0].disp,vett[2].disp,vett[3].disp,vett[1].disp,R,S,T,Z);
    sol[3]=fs(vett[0].disp,vett[2].disp,vett[3].disp,vett[1].disp,R,S,T,Z);
    for(i=0;i<4;i++)
    {
        if(max<sol[i])
            max=sol[i];
    }
    printf("\nCollana massima: %d",max);	//necklace with more stones 
    return 0;
}
void alloc(stone *vett, int *****Z) //allocation of 4-dimensions matrix
{
    int i,j,k;
    (*Z)=malloc((vett[0].disp+1)*sizeof(int ***));
    for(i=0;i<(vett[0].disp+1);i++)
    {
        (*Z)[i] = malloc((vett[2].disp+1) * sizeof(int **));
        for (j = 0; j < (vett[2].disp+1); j++)
        {
            (*Z)[i][j] = malloc((vett[3].disp+1) * sizeof(int *));
            for (k = 0; k < (vett[3].disp+1); k++) (*Z)[i][j][k] = malloc((vett[1].disp+1) * sizeof(int));
        }
    }
    inizializza(vett,*Z);
    return;
}
void inizializza(stone *vett, int ****Z)    //initialization
{
    int i,j,k,t;
    for(i=0;i<=vett[0].disp;i++) {
        for (j = 0; j <=vett[2].disp; j++) {
            for (k = 0; k <=vett[3].disp; k++) {
                for (t = 0; t <=vett[1].disp; t++)
                    Z[i][j][k][t] = -1;
            }
        }
    }
    return;
}
int fz(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z)
{
    int one,two;
    if (z<=0)   //finished the Z
        return 0;
    if(Z[z][t][s][r]!=-1) return Z[z][t][s][r]; //if I had already calculated the cost of this partcular necklace, I return the result 
    one=fz(z-1,t,s,r,R,S,T,Z);  //add a Z
    two=fr(z-1,t,s,r,R,S,T,Z);  //add a R
    if(one>two) Z[z][t][s][r]=one+1;    //memorize the best solution
    else Z[z][t][s][r]=two+1;
    return Z[z][t][s][r];   //return best solution
}
int fr(int z, int t, int s, int r, int **** R, int ****S, int ****T, int ****Z)
{
    int one,two;
    if (r<=0)
        return 0;
    if(R[z][t][s][r]!=-1) return R[z][t][s][r];
    one=ft(z,t,s,r-1,R,S,T,Z);
    two=fs(z,t,s,r-1,R,S,T,Z);
    if(one>two) R[z][t][s][r]=one+1;
    else R[z][t][s][r]=two+1;
    return R[z][t][s][r];
}
int fs(int z, int t, int s, int r, int ****R, int ****S, int ****T, int ****Z)
{
    int one,two;
    if (s<=0)
        return 0;
    if(S[z][t][s][r]!=-1) return S[z][t][s][r];
    one=fs(z,t,s-1,r,R,S,T,Z);
    two=ft(z,t,s-1,r,R,S,T,Z);
    if(one>two) S[z][t][s][r]=one+1;
    else S[z][t][s][r]=two+1;
    return S[z][t][s][r];
}
int ft(int z, int t, int s, int r, int ****R,int ****S, int ****T, int ****Z)
{
    int one,two;
    if (t<=0)
        return 0;
    if(T[z][t][s][r]!=-1) return T[z][t][s][r];
    one=fz(z,t-1,s,r,R,S,T,Z);
    two=fr(z,t-1,s,r,R,S,T,Z);
    if(one>two) R[z][t][s][r]=one+1;
    else R[z][t][s][r]=two+1;
    return R[z][t][s][r];
}
