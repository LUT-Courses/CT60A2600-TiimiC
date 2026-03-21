#include <stdio.h>
#include "../binarytree.h"
#include "binaaripuuValikko.h"

/// @brief Apufunktio joka tulostaa toiminnot ja antaa käyttäjän valita (0-5)
static int valikko(void);

/// @brief Apufunktio yksinkertaistamaan. Muuttujaparametri ja syöte valikko funktiosta. Muuttujaparametriin asetetaan tiedoston nimi.
static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);

int binaaripuuValikko(void) {
    int iValinta = -1;
    int iArvo = 0;
    char aTiedostoNimi[30];
    char aNimi[LEN_SUKUNIMI];
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
            printf("Anna etsittävä arvo: ");
            scanf("%d", &iArvo);
            kysyTiedostoNimi(aTiedostoNimi, "Anna kirjoitettavan tiedoston nimi: ");
            btree_dfsHakuKirjoita(aTiedostoNimi, iArvo, pJuuri);
            printf("Tiedosto '%s' kirjoitettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 4) {
            printf("Anna etsittävä sukunimi: ");
            scanf("%29s", aNimi);
            kysyTiedostoNimi(aTiedostoNimi, "Anna kirjoitettavan tiedoston nimi: ");
            btree_bfsHakuNimellaKirjoita(aTiedostoNimi, aNimi, pJuuri);
            printf("Tiedosto '%s' kirjoitettu\n", aTiedostoNimi);
            printf("\n");

        } else if (iValinta == 5) {
            btree_tulostaPuu(pJuuri);
            printf("\n");
        } else if (iValinta == 6) {
            btree_poistaNodePohja(aNimi, iArvo, pJuuri);
            printf("\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
        }
    } while (iValinta != 0);

    pJuuri = btree_vapautaMuisti(pJuuri);
    printf("Muisti vapautettu.\n");
    printf("Kiitos ohjelman käytöstä.\n");
    printf("\n");

    return 0;
}

static int valikko(void) {
    int iValinta = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedosto (DFS)\n");
    printf("3) Syvyyshaku arvon mukaan sekä kirjoita käyty polku tiedostoon (DFS)\n");
    printf("4) Leveyshaku nimen mukaan sekä kirjoita käyty polku tiedostoon (BFS)\n");
    printf("5) Tulosta puu (DFS)\n");
    printf("6) Poista pohjimmainen node\n");
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
