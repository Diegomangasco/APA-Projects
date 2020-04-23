#include "Title.h"
int main() {
    FILE *fp = fopen("F1.txt", "r");
    c head = NULL;
    c search;
    int fine = 0;
    int scelta;
    char name[20];
    date *d1 = malloc(sizeof(date));
    date *d2 = malloc(sizeof(date));
    leggifile(fp, head);
    do {
        printf("Azioni: \n1)Ricerca della quotazione di un titolo in una data specifica\n2)Ricerca della quotazione massima e minima di un titolo"
               "in un range di date\n3)Ricerca della quotazione massima e minima di un titolo4)Bilanciamento d un titolo\5)Fine\n");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                printf("Inserisci un titolo da ricercare: ");
                scanf("%s", name);
                if ((search = searchinlist(head, name)) != NULL) {
                    printf("\nInserisci una data aa/mm/gg: ");
                    scanf("%d/%d/%d", &d1->year, &d1->month, &d1->day);
                    searchinBST(search, d1);
                }
                break;
            case 2:
                printf("Inserisci un titolo da ricercare: ");
                scanf("%s", name);
                if ((search = searchinlist(head, name)) != NULL) {
                    printf("\nInserisci la prima data aa/mm/gg: ");
                    scanf("%d/%d/%d", &d1->year, &d1->month, &d1->day);
                    printf("\nInserisci la seconda data aa/mm/gg: ");
                    scanf("%d/%d/%d", &d2->year, &d2->month, &d2->day);
                    searchbyrangeBST(search, d1, d2);
                }
                break;
            case 3:
                printf("Inserisci un titolo da ricercare: ");
                scanf("%s", name);
                if ((search = searchinlist(head, name)) != NULL) {
                    d1->year = 1800;      //massimizzo e minimizzo il range di date, per fare una ricerca del massimo e del minimo su tutto l'albero
                    d1->month = 2;
                    d1->day = 16;
                    d2->year = 2030;
                    d2->month = 2;
                    d2->day = 16;
                    searchbyrangeBST(search, d1, d2);
                }
                break;
            case 4:
                printf("Inserisci un titolo da ricercare: ");
                scanf("%s", name);
                if ((search = searchinlist(head, name)) != NULL) searchLway(search);
                break;
            case 5:
                fine = 0;
                break;
        }
    } while (fine == 1);
    return 0;
}
