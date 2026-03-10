#include <stdio.h>
#include "binaaripuuValikko.h"

//1 Syvyyshaku
//2 Leveyshaku
//3 Tulosta
//0 Lopeta

static int valikko(void);

int binaaripuuValikko(void) {
    int iValinta = -1;
    char aTiedostoNimi[20];
    
    
    do {
        iValinta = valikko();
        if (iValinta == 1) {
            
        } else if (iValinta == 2) {
            
        } else if (iValinta == 3) {
            
        } else if (iValinta == 0) {
            
        } else {
            
        }
    } while (iValinta != 0);

    return 0;
    
    
}

static int valikko(void) {
    int iValinta = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedosto syvyydellä\n");
    printf("3) Syvyyshaku arvon mukaan sekä kirjoita käyty polku tiedostoon\n");
    printf("4) Leveyshaku nimen mukaan sekä kirjoita käyty polku tiedostoon\n");
    printf("5) Tulosta puu syvyyden mukaan\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}