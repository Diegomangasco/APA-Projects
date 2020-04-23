
#include "personaggi.h"
int main()
{
    link head=NULL;
    link tail = NULL;
    link val;
    inv *elenco;
    int oggetti=0;
    int scelta;
    int fine=0;
    do
    {
        printf("\nDecidi l'azione: \n1)Carica l'elenco dei pg\n2)Carica l'elenco degli oggetti\n3)Aggiungi pg\n4)Elimina un pg\n5)Visualizzazione elenco\n6)Aggiungi un oggetto ad un pg\n7)Togli un oggetto ad un pg\n8)Stampa delle statistiche\n9)Termina\n");
        scanf("%d",&scelta);
        switch (scelta)
        {
        case 1: //lettura del file pg.txt ed inserimento in lista dei personaggi
            leggi_file(&head,&tail);
            break;
        case 2: //lettura del file inventario.txt ed inserimento int un puntatore a inv
            elenco=leggi_oggetti();
            oggetti=1;
            break;
        case 3: //aggiunta di un elemento a video
            val=aggiungi_elemento();
            carica_pg(&head,&tail,val);
            break;
        case 4: //eliminazione di un pg previa richiesta del codice
            elimina_pg(&head);
            break;
        case 5: //stampa della lista
            stampa_pg(head,tail);
            break;
        case 6: //aggiunta di oggetti ai personaggi
            if(oggetti)
                aggiunta_ogg(&head,&elenco);
            else
                printf("Non hai ancora inserito oggetti!\n");
            break;
        case 7:
            elimina_ogg(&head, &elenco);
            break;
        case 8:
            stampa_stat(head);
            break;
        case 9:
            printf("\nGrazie ed arrivederci!");
            fine=1;
            break;
        default:
            printf("\nComando errato, riprova\n");
        }
    }while(fine==0);
    return 0;
    return 0;
}
