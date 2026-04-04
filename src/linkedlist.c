#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus

/// @brief Apufunktio, varaa muisti uudelle structille (LISTNODE)
static LISTNODE* varaaMuisti(void);

// mergesort apufunktiot
static LISTNODE* mergeSortLaskeva_etsiKeski(LISTNODE *pAlku);
static LISTNODE* mergeSortLaskeva_yhdista(LISTNODE *pVasen, LISTNODE *pOikea);

/// Luetaan tiedostosta sukunimi ja lisätään se uuteen sukunimi structiin.
/// Samaan structiin lisätään pointteri seuraavaan ja edelliseen sukunimi structiin.
/// Palauttaa osoittimen listan alkuu pAlku
LISTNODE* lueTiedosto(char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;
    LISTNODE *pAlku = NULL;
    LISTNODE *pUusi = NULL;
    LISTNODE *pViimeisin = NULL;
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
            strcpy(pUusi->aNimi, p1);
            pUusi->iMaara = iMaara;
            pUusi->pSeuraava = NULL;
            pUusi->pEdellinen = NULL;
            pViimeisin = pUusi;
            pAlku = pViimeisin;
        } else {
            pUusi = varaaMuisti();
            strcpy(pUusi->aNimi, p1);
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

static LISTNODE* varaaMuisti(void) {
    LISTNODE *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (LISTNODE*)malloc(sizeof(LISTNODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}

/// Vapauttaa muistin käymällä linked-list läpi alusta loppuun
LISTNODE* vapautaMuisti(LISTNODE *pAlku) {
    LISTNODE *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    return (pAlku);
}

/// Kirjoittaa tiedostoon kulkemalla listan alusta loppuun
void kirjoitaTiedostoAlkuLoppu(LISTNODE *pAlku, char aTiedostoNimi[]) {
    FILE *Tiedosto = NULL;
    LISTNODE *ptr = pAlku;

    Tiedosto = fopen(aTiedostoNimi, "w");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aNimi, ptr->iMaara);
        ptr = ptr->pSeuraava;
    }

    fclose(Tiedosto);
    return;
}
/// Kulkee ensin listan loppuun ja sitten kirjoittaa
/// nimet kulkien alkuun
void kirjoitaTiedostoLoppuAlku(LISTNODE *pAlku, char aTiedostoNimi[]) {
    FILE *Tiedosto = NULL;
    LISTNODE *ptr = pAlku;

    Tiedosto = fopen(aTiedostoNimi, "w");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    while ( (ptr != NULL) && (ptr->pSeuraava != NULL) ) {
        ptr = ptr->pSeuraava;
    }
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aNimi, ptr->iMaara);
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
LISTNODE* lajitteleLaskeva(LISTNODE *pAlku) {
    LISTNODE* pVasen = NULL;
    LISTNODE* pOikea = NULL;
    LISTNODE* pKeski = NULL;
    LISTNODE* pLajiteltu = NULL;

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
static LISTNODE* mergeSortLaskeva_etsiKeski(LISTNODE *pAlku) {
    LISTNODE* slowPtr = pAlku;
    LISTNODE* fastPtr = pAlku;

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
static LISTNODE* mergeSortLaskeva_yhdista(LISTNODE *pVasen, LISTNODE *pOikea) {
    LISTNODE* yhdistetty = NULL;

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
        if ( (strcmp(pVasen->aNimi, pOikea->aNimi)) > 0 ) { // vasen isompi
            yhdistetty = pVasen;
            yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pVasen->pSeuraava, pOikea);
        } else { // oikea isompi tai duplikaatti
            yhdistetty = pOikea;
            yhdistetty->pSeuraava = mergeSortLaskeva_yhdista(pOikea->pSeuraava, pVasen);
        }
    }
    return (yhdistetty);
}

/// @brief Lajittelee listan bubble sortilla nousevasti (pienin ensin)
/// @param pAlku Osoitin listan ensimmäiseen alkioon
/// @return Palauttaa osoittimen listan alkuun
LISTNODE* lajitteleNouseva(LISTNODE *pAlku) {
    int iVaihtoTehty = 0;
    LISTNODE *ptr = NULL;
    char aApuNimi[LEN_SUKUNIMI];
    int iApuMaara = 0;

    if (pAlku == NULL || pAlku->pSeuraava == NULL) {
        return pAlku;
    }

    do {
        iVaihtoTehty = 0;
        ptr = pAlku;

        while (ptr->pSeuraava != NULL) {
            int iVaihda = 0;

            if (ptr->iMaara > ptr->pSeuraava->iMaara) {
                iVaihda = 1;
            } else if (ptr->iMaara == ptr->pSeuraava->iMaara) {
                if (strcmp(ptr->aNimi, ptr->pSeuraava->aNimi) > 0) {
                    iVaihda = 1;
                }
            }

            if (iVaihda == 1) {
                strcpy(aApuNimi, ptr->aNimi);
                iApuMaara = ptr->iMaara;

                strcpy(ptr->aNimi, ptr->pSeuraava->aNimi);
                ptr->iMaara = ptr->pSeuraava->iMaara;

                strcpy(ptr->pSeuraava->aNimi, aApuNimi);
                ptr->pSeuraava->iMaara = iApuMaara;
                iVaihtoTehty = 1;
            }
            ptr = ptr->pSeuraava;
        }
    } while (iVaihtoTehty == 1);

    return pAlku;
}

/// @brief Poistaa alkion listasta nimen perusteella
/// @param aNimi Poistettavan alkion nimi
/// @param pAlku Osoitin listan ensimmäiseen alkioon
/// @return Palauttaa osoittimen listan alkuun
LISTNODE* poistaAlkioNimi(char aNimi[], LISTNODE* pAlku) {
    LISTNODE *ptr = pAlku;
    int iPoistettu = 0;

    while (ptr != NULL) {
        if ( strcmp(aNimi, ptr->aNimi) == 0 ) {
            if (ptr->pEdellinen == NULL) { // poistetaan listan ensimmäinen
                pAlku = ptr->pSeuraava;
                if (pAlku != NULL) { // varomääre jos listassa onkin vain yksi alkio
                    pAlku->pEdellinen = NULL; //  ja poistettaessa ensimmäinen alkio se menee tyhjäksi
                }
            } else if (ptr->pSeuraava == NULL) { // poistetaan listan viimeinen
                ptr->pEdellinen->pSeuraava = NULL;
            } else {
                ptr->pEdellinen->pSeuraava = ptr->pSeuraava; // poistetaan listan keskeltä
                ptr->pSeuraava->pEdellinen = ptr->pEdellinen;
            }
            printf("'%s,%d' poistettu.\n", ptr->aNimi, ptr->iMaara);
            free(ptr);
            iPoistettu = 1;
            break; // poistetaan vain ensimmäinen vastaan tuleva
        }
        ptr = ptr->pSeuraava;
    }
    if (iPoistettu == 0) {
        printf("'%s' ei löytynyt osumaa.\n", aNimi);
    }
    return (pAlku);
}

/// @brief Poistaa alkion listasta arvon (määrä) perusteella
/// @param iMaara
/// @param pAlku
/// @return Palauttaa osoittien listan alkuun
LISTNODE* poistaAlkioMaara(int iMaara, LISTNODE* pAlku) {
    LISTNODE *ptr = pAlku;
    int iPoistettu = 0;

    while (ptr != NULL) {
        if (iMaara == ptr->iMaara) {
            if (ptr->pEdellinen == NULL) { // poistetaan listan ensimmäinen
                pAlku = ptr->pSeuraava;
                if (pAlku != NULL) { // varomääre jos listassa onkin vain yksi alkio
                    pAlku->pEdellinen = NULL; //  ja poistettaessa ensimmäinen alkio se menee tyhjäksi
                }
            } else if (ptr->pSeuraava == NULL) { // poistetaan listan viimeinen
                ptr->pEdellinen->pSeuraava = NULL;
            } else {
                ptr->pEdellinen->pSeuraava = ptr->pSeuraava; // poistetaan listan keskeltä
                ptr->pSeuraava->pEdellinen = ptr->pEdellinen;
            }
            printf("'%s,%d' poistettu.\n", ptr->aNimi, ptr->iMaara);
            free(ptr);
            iPoistettu = 1;
            break; // poistetaan vain ensimmäinen vastaan tuleva
        }
        ptr = ptr->pSeuraava;
    }
    if (iPoistettu == 0) {
        printf("'%d' ei löytynyt osumaa.\n", iMaara);
    }
    return (pAlku);
}

LISTNODE* lisaaListaan(LISTNODE *alku, int kohta, char nimi[], int maara) {
    kohta--; //jotta indexi saadaan 0 pohjaiseksi
    LISTNODE *uusi = varaaMuisti(); // varataan muisti uudelle structille
    strcpy(uusi->aNimi, nimi);
    uusi->iMaara = maara;
    if (alku == NULL || kohta == 0) {
        uusi->pSeuraava = alku; // uusi osoittaa vanhaan alkuun
        uusi->pEdellinen = NULL; // uusi on uusi alku, joten edellinen on NULL

        if (alku != NULL) {
            alku->pEdellinen = uusi; // vanhan alkuun edellinen osoittaa uuteen alkupäähän
        }
        return uusi; // uusi on uusi alku, joten palautetaan se
    }
    LISTNODE *ptr = alku; // aloitetaan listan alusta
    int i = 0;
    while (ptr->pSeuraava != NULL && i < kohta - 1) { // kuljetaan listaa eteenpäin, kunnes saavutetaan haluttu kohta tai listan loppu
        ptr = ptr->pSeuraava; // siirrytään seuraavaan alkioon
        i++;
    }
    uusi->pSeuraava = ptr->pSeuraava; // uusi osoittaa siihen, mihin ptr osoitti ennen (eli seuraavaan alkioon)
    uusi->pEdellinen = ptr; //
    if (ptr->pSeuraava != NULL) { // jos ptr ei ole listan viimeinen alkio, asetetaan seuraavan alkion edellinen osoittamaan uuteen alkioon
        ptr->pSeuraava->pEdellinen = uusi; // seuraavan alkion edellinen osoittaa uuteen alkioon
    }
    ptr->pSeuraava = uusi;
    return alku;
}
