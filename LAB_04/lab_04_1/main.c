#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b);
int main()
{
    int a,b,mcd;
    printf("Inserisci due numeri di cui calcolare il MCD: ");
    scanf("%d %d",&a, &b);
    if(a>b)
        mcd=gcd(a,b);
    else
        mcd=gcd(b,a);
    printf("\nMassimo comun divisore: %d",mcd);
    return 0;
}
int gcd(int a, int b)
{
    if(a==b)
        return a;
    if((a==1) || (b==1))
	return 1;
    if(a%2==0 && b%2==0)
        return 2*gcd(a/2,b/2);
    if(a%2!=0 && b%2==0)
        return gcd(a,b/2);
    if(a%2!=0 && b%2!=0)
        return gcd(((a-b)/2),b);
}
