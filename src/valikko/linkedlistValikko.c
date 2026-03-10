#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linkedlist.h"
#include "linkedlistValikko.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus

static int valikko(void);

int linkedlistValikko(void) {
    int iValinta = -1;
    char aTiedostoNimi[20];
    SUKUNIMI *pAlku = NULL; // alustetaan pointerit NULL



    do {
        iValinta = valikko();
        if (iValinta == 1) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna luettavan tiedoston nimi: ");
            pAlku = lueTiedosto(aTiedostoNimi);
            printf("Tiedosto '%s' luettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 2) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna kirjoitettavan tiedoston nimi: ");
            kirjoitaTiedostoAlkuLoppu(pAlku, aTiedostoNimi);
            printf("Tiedosto '%s' kirjoitettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 3) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna kirjoitettavan tiedoston nimi: ");
            kirjoitaTiedostoLoppuAlku(pAlku, aTiedostoNimi); 
            printf("Tiedosto '%s' kirjoitettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 4) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna tyhjennettävän tiedoston nimi: ");
            tyhjennaTiedosto(aTiedostoNimi);
            printf("Tiedosto '%s' tyhjennetty\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
        }
    } while (iValinta != 0);
    
    pAlku = vapautaMuisti(pAlku);
    printf("Muisti vapautettu.\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

static int valikko(void) {
    int iValinta = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedostoon nimet alusta loppuun\n");
    printf("3) Kirjoita tiedostoon nimet lopusta alkuun\n");
    printf("4) Tyhjennä tiedosto\n");
    printf("0) Lopeta\n");
    printf("\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}
