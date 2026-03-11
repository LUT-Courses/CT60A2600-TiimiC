#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valikko/linkedlistValikko.h"
#include "valikko/binaaripuuValikko.h"

int paaValikko(void);

int main(void) {
    int ivalinta = -1;

    do
    {
      ivalinta = paaValikko();
        if (ivalinta == 1) {
            printf("\n");
            linkedlistValikko();
        } else if (ivalinta == 2) {
            printf("\n");
            binaaripuuValikko();
        } else if (ivalinta == 0) {
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
        }
    } while (ivalinta != 0);

    return 0;
}

int paaValikko(void) {
        int pvalinta = 0;
        printf("1) Linked list\n");
        printf("2) Binaaripuu\n");
        printf("0) Lopeta\n");
        printf("Valintasi: ");
        scanf("%d", &pvalinta);
        return pvalinta;
    }
