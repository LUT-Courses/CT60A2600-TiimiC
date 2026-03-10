#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valikko/linkedlistValikko.h"
#include "valikko/binaaripuuValikko.h"

int paaValikko(void);

int main(void) {
    int pvalinta = -1;

    do
    {
      pvalinta = paaValikko();
        if (pvalinta == 1) {
            linkedlistValikko();
        } else if (pvalinta == 2) {
            binaaripuuValikko();
        } else if (pvalinta == 0) {
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
        }
    } while (pvalinta != 0);

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
