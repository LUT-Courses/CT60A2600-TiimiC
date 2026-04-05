#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../binarytree.h"
#include "binaaripuuValikko.h"

/// @brief Apufunktio joka tulostaa toiminnot ja antaa käyttäjän valita (0-5)
static int valikko(void);

/// @brief Apufunktio yksinkertaistamaan. Muuttujaparametri ja syöte valikko funktiosta. Muuttujaparametriin asetetaan tiedoston nimi.
static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);

int binaaripuuValikko(void) {
    int iValinta = -1;
    int iArvo = 0;
    char aTiedostoNimi[40];
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
            printf("Anna poistettava nimi tai arvo: ");
            scanf("%s", aNimi);
            if ( (iArvo = atoi(aNimi)) != 0) { // jos numero niin numeron perusteella
                //printf("%d",iArvo); //debug
                pJuuri = btree_poistaNodePohjaArvo(iArvo, pJuuri);
            } else {
                pJuuri = btree_poistaNodePohjaNimi(aNimi, pJuuri); // muuten nimen perusteella
            }
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
    printf("6) Poista pohjimmainen node (nimellä tai arvolla)\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}

static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]) {
    #ifdef DEBUG
    if (strstr(aSyote, "luettavan") != NULL) {
        strcpy(aTiedostoNimi, "data/miehet_15.txt");
    } else { // kirjoitustiedosto
        strcpy(aTiedostoNimi, "debug_puu.txt");
    }
    printf("[DEBUG] %s%s\n", aSyote, aTiedostoNimi);
    #else
        printf("%s", aSyote);
        scanf("%s", aTiedostoNimi);
    #endif
    return;
}
