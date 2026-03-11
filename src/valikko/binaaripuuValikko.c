#include <stdio.h>
#include "../binarytree.h"
#include "binaaripuuValikko.h"

/// @brief Apufunktio joka tulostaa toiminnot ja antaa käyttäjän valita (0-5)
static int valikko(void);

/// @brief Apufunktio yksinkertaistamaan. Muuttujaparametri ja syöte valikko funktiosta. Muuttujaparametriin asetetaan tiedoston nimi.
static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);

int binaaripuuValikko(void) {
    int iValinta = -1;
    char aTiedostoNimi[20];
    BTREENODE *pJuuri = NULL; // alustetaan puun juuri NULL
    
    do {
        iValinta = valikko();
        if (iValinta == 1) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna luettavan tiedoston nimi: ");
            pJuuri = btree_lueTiedosto(aTiedostoNimi);
            printf("Tiedosto '%s' luettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 2) {
            kysyTiedostoNimi(aTiedostoNimi, "Anna kirjoitettavan tiedoston nimi: ");
            btree_kirjoitaTiedostoSyvyys(pJuuri, aTiedostoNimi);
            printf("Tiedosto '%s' kirjoitettu\n", aTiedostoNimi);
            printf("\n");
            
        } else if (iValinta == 3) {
            
        } else if (iValinta == 4) {

        } else if (iValinta == 5) {
            btree_tulostaPuu(pJuuri);
            printf("\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan\n");
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
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

static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]) {
    printf("%s", aSyote);
    scanf("%s", aTiedostoNimi);
    return;
}