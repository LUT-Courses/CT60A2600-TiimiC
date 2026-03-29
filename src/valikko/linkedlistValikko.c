#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linkedlist.h"
#include "linkedlistValikko.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus

/// @brief Apufunktio joka tulostaa toiminnot ja antaa käyttäjän valita (0-5)
static int valikko(void);

/// @brief Apufunktio yksinkertaistamaan. Muuttujaparametri ja syöte valikko funktiosta. Muuttujaparametriin asetetaan tiedoston nimi.
static void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);

int linkedlistValikko(void) {
    int iValinta = -1;
    char aTiedostoNimi[40];
    char aNimi[LEN_SUKUNIMI];
    int iMaara = 0;
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
        } else if (iValinta == 5) {
            pAlku = lajitteleNouseva(pAlku);
            printf("Lista lajiteltu nousevasti (bubble sort).\n");
            printf("\n");
        } else if (iValinta == 6) {
            pAlku = lajitteleLaskeva(pAlku);
            printf("Lista lajiteltu laskevasti.\n");
            printf("\n");
        } else if (iValinta == 7) {
            char nimi[LEN_SUKUNIMI];
            int maara = 0;
            int kohta = 0;
        
            printf("Anna mihin kohtaan listassa lisätään (0 = alku): ");
            scanf("%d", &kohta);
            printf("Anna lisättävä sukunimi: ");
            scanf("%s", nimi);
            printf("Anna määrä: ");
            scanf("%d", &maara);
        
            pAlku = lisaaListaan(pAlku, kohta, nimi, maara);
            printf("Nimi '%s' lisätty listaan kohtaan %d.\n\n", nimi, kohta);
        } else if (iValinta == 8) {
            printf("Anna poistettava nimi tai arvo: ");
            scanf("%s", aNimi);
            if ( (iMaara = atoi(aNimi)) != 0) { // jos numero niin numeron perusteella
                //printf("%d",iArvo); //debug
                pAlku = poistaAlkioMaara(iMaara, pAlku);
            } else {
                pAlku = poistaAlkioNimi(aNimi, pAlku); // muuten nimen perusteella
            }
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
    printf("\n");
    return 0;
}

static int valikko(void) {
    int iValinta = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedostoon nimet alusta loppuun\n");
    printf("3) Kirjoita tiedostoon nimet lopusta alkuun\n");
    printf("4) Tyhjennä tiedosto\n");
    printf("5) Lajittele lista arvon mukaan (nouseva, bubble sort)\n");
    printf("6) Lajittele lista arvon mukaan (laskeva)\n");
    printf("8) Poista alkio (nimellä tai arvolla)\n");
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
        strcpy(aTiedostoNimi, "debug.txt");
    }
    printf("[DEBUG] %s%s\n", aSyote, aTiedostoNimi);
    #else
        printf("%s", aSyote);
        scanf("%s", aTiedostoNimi);
    #endif
    return;
}
