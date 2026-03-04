#include <stdio.h>
#include <stdlib.h>
#include "hello.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus
#define MAX_NIMET 23156 // 1 yli jotta nullikka mahtuu

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* varaaMuisti();
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
void kysyTiedostoNimi(char aTiedostoNimi[]);
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]);
void tulostaAlkuLoppu(SUKUNIMI *pAlku);
void kirjoitaTiedostoAlkuLoppu();
void kirjoitaTiedostoLoppuAlku();

int main(void) {
    char aTiedostoNimi[20];
    int iLuetutRivit = 0;
    SUKUNIMI *pAlku = NULL; // alustetaan pointerit NULL

    kysyTiedostoNimi(aTiedostoNimi);
    pAlku = lueTiedosto(aTiedostoNimi);

    tulostaAlkuLoppu();

    vapautaMuisti(pAlku);
    printf("%s\n", hello_message());
    printf("Terve testi\n");
    return 0;
}

void kysyTiedostoNimi(char aTiedostoNimi[]) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", aTiedostoNimi);
    return;
}

// Luetaan tiedostosta sukunimi ja lisätään se uuteen sukunimi structiin.
// Samaan structiin lisätään pointteri seuraavaan ja edelliseen sukunimi structiin.
// Palauttaa osoittimen listan alkuu pAlku
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]) {
    int iLuetutRivit = 0;
    FILE* Tiedosto = NULL;
    SUKUNIMI *pAlku = NULL;
    SUKUNIMI *pUusi = NULL;
    SUKUNIMI *pViimeisin = NULL;
    char aRivi[LEN_RIVI];
    char *p1 = NULL; // ptr sukunimelle tiedostosta

    if ( (Tiedosto = fopen(aTiedostoNimi, "r")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, LEN_RIVI, Tiedosto); // Luetaan otsikkorivi pois
    while (fgets(aRivi, LEN_RIVI, Tiedosto) != NULL) {
        if ((p1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan.\n", aRivi);
            exit(0);
        }
        if (pViimeisin == NULL) {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pUusi->pSeuraava = NULL;
            pUusi->pEdellinen = NULL;
            pViimeisin = pUusi;
            pAlku = pViimeisin;
        } else {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pViimeisin->pSeuraava = pUusi;
            pUusi->pEdellinen = pViimeisin;
            pUusi->pSeuraava = NULL;
            pViimeisin = pUusi;
        }
    }
    fclose(Tiedosto);
    return (pAlku);
}

// Varaa muisti uudelle structille (SUKUNIMI)
SUKUNIMI* varaaMuisti() {
    SUKUNIMI *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (SUKUNIMI*)malloc(sizeof(SUKUNIMI))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}

// Vapauta muisti käymällä linked-list läpi alusta loppuun
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    return (pAlku);
}

void tulostaAlkuLoppu(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while (ptr != NULL) {
        printf("Henkilön sukunimi '%s'\n", ptr->aSukunimi);
        ptr = ptr->pSeuraava;
    }
    return;
}

