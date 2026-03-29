#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus

/// @brief Apufunktio, varaa muisti uudelle structille (SUKUNIMI)
static SUKUNIMI* varaaMuisti(void);

// mergesort apufunktiot
static SUKUNIMI* mergeSortLaskeva_etsiKeski(SUKUNIMI *pAlku);
static SUKUNIMI* mergeSortLaskeva_yhdista(SUKUNIMI *pVasen, SUKUNIMI *pOikea);

/// Luetaan tiedostosta sukunimi ja lisätään se uuteen sukunimi structiin.
/// Samaan structiin lisätään pointteri seuraavaan ja edelliseen sukunimi structiin.
/// Palauttaa osoittimen listan alkuu pAlku
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;
    SUKUNIMI *pAlku = NULL;
    SUKUNIMI *pUusi = NULL;
    SUKUNIMI *pViimeisin = NULL;
    char aRivi[LEN_RIVI];
    char *p1 = NULL; // ptr sukunimelle tiedostosta
    char *p2 = NULL; // ptr määrälle tiedostosta
    int iMaara = 0;

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
        if ((p2 = strtok(NULL, ";\n")) == NULL) {
            printf("Riviltä '%s' puuttuu määrä, lopetetaan.\n", p1);
            exit(0);
        }
        iMaara = atoi(p2);
        if (pViimeisin == NULL) {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pUusi->iMaara = iMaara;
            pUusi->pSeuraava = NULL;
            pUusi->pEdellinen = NULL;
            pViimeisin = pUusi;
            pAlku = pViimeisin;
        } else {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pUusi->iMaara = iMaara;
            pViimeisin->pSeuraava = pUusi;
            pUusi->pEdellinen = pViimeisin;
            pUusi->pSeuraava = NULL;
            pViimeisin = pUusi;
        }
    }
    fclose(Tiedosto);
    return (pAlku);
}

static SUKUNIMI* varaaMuisti() {
    SUKUNIMI *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (SUKUNIMI*)malloc(sizeof(SUKUNIMI))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}

/// Vapauttaa muistin käymällä linked-list läpi alusta loppuun
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    return (pAlku);
}

/// Kirjoittaa tiedostoon kulkemalla listan alusta loppuun
void kirjoitaTiedostoAlkuLoppu(SUKUNIMI *pAlku, char aTiedostoNimi[]) {
    FILE *Tiedosto = NULL;
    SUKUNIMI *ptr = pAlku;

    Tiedosto = fopen(aTiedostoNimi, "w");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aSukunimi, ptr->iMaara);
        ptr = ptr->pSeuraava;
    }

    fclose(Tiedosto);
    return;
}
/// Kulkee ensin listan loppuun ja sitten kirjoittaa
/// nimet kulkien alkuun
void kirjoitaTiedostoLoppuAlku(SUKUNIMI *pAlku, char aTiedostoNimi[]) {
    FILE *Tiedosto = NULL;
    SUKUNIMI *ptr = pAlku;

    Tiedosto = fopen(aTiedostoNimi, "w");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    while ( (ptr != NULL) && (ptr->pSeuraava != NULL) ) {
        ptr = ptr->pSeuraava;
    }
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aSukunimi, ptr->iMaara);
        ptr = ptr->pEdellinen;
    }

    fclose(Tiedosto);
    return;
}

/// Tyhjentää tiedoston
void tyhjennaTiedosto(char aTiedostoNimi[]) {
    FILE *Tiedosto = NULL;

    Tiedosto = fopen(aTiedostoNimi, "w");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fclose(Tiedosto);
    return;
}

// https://www.w3resource.com/c-programming-exercises/linked_list/c-linked_list-exercise-39.php
/// @brief Lajittelee listan rekursiivisesti arvon mukaan laskevasti (isoin ensin)
/// @param pAlku Osoitin listan ensimmäiseen alkioon 
/// @return Palauttaa osoittimen listan ensimmäiseen alkioon
SUKUNIMI* lajitteleLaskeva(SUKUNIMI *pAlku) {
    SUKUNIMI* pVasen = NULL;
    SUKUNIMI* pOikea = NULL;
    SUKUNIMI* pKeski = NULL;
    SUKUNIMI* pLajiteltu = NULL;

    if (pAlku == NULL || pAlku->pSeuraava == NULL) { // lista on NULL tai vain 1 alkion pituinen
        return (pAlku);
    }
    pKeski = mergeSortLaskeva_etsiKeski(pAlku);
    pVasen = pAlku;
    pOikea = pKeski->pSeuraava;
    pKeski->pSeuraava = NULL; // katkaistaan yhteys keskeltä

    pVasen = lajitteleLaskeva(pAlku);
    pOikea = lajitteleLaskeva(pOikea);
    
    pLajiteltu = mergeSortLaskeva_yhdista(pVasen, pOikea);
    return (pLajiteltu);
}

/// @brief Etsii slow, fast pointer tekniikalla listan keskikohdan
/// @param pAlku
/// @return Palauttaa osoittimen listan keskikohtaan
static SUKUNIMI* mergeSortLaskeva_etsiKeski(SUKUNIMI *pAlku) {
    SUKUNIMI* slowPtr = pAlku;
    SUKUNIMI* fastPtr = pAlku;

    while ((fastPtr->pSeuraava != NULL) && (fastPtr->pSeuraava->pSeuraava != NULL)) {
        slowPtr = slowPtr->pSeuraava;
        fastPtr = fastPtr->pSeuraava->pSeuraava;
    }
    return (slowPtr);
}

/// @brief Yhdistää kaksi lajiteltua linkedlist puoliskoa laskevaan (descending) muotoon.
/// @param pVasen  
/// @param pOikea 
/// @return Palauttaa osoittimen lajitellun yhdistetyn listan alkuun
static SUKUNIMI* mergeSortLaskeva_yhdista(SUKUNIMI *pVasen, SUKUNIMI *pOikea) {
    SUKUNIMI* yhdistetty = NULL;

    if (pVasen == NULL) {
        yhdistetty = pOikea;
    } else if (pOikea == NULL) {
        yhdistetty = pVasen;
    } else if (pVasen->iMaara > pOikea->iMaara) {
        yhdistetty = pVasen;
        yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pVasen->pSeuraava, pOikea);
    } else if (pOikea->iMaara > pVasen->iMaara) {
        yhdistetty = pOikea;
        yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pOikea->pSeuraava, pVasen);
    } else { // jos arvot samat niin aakkosten perusteella
        if ( (strcmp(pVasen->aSukunimi, pOikea->aSukunimi)) > 0 ) { // vasen isompi
            yhdistetty = pVasen;
            yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pVasen->pSeuraava, pOikea);
        } else { // oikea isompi tai duplikaatti
            yhdistetty = pOikea;
            yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pOikea->pSeuraava, pVasen);
        }
    }
    return (yhdistetty);
}