#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa

/// @brief Rekursiivinen apufunktio puuhun lisäykseen
static BTREENODE* lisaaPuuhun(BTREENODE *pJuuri, BTREENODE *pUusi);

/// @brief Apufunktio, varaa muisti uudelle structille (BTREENODE)
static BTREENODE* varaaMuisti(void);
static int dfsHaku(FILE *Tiedosto, int iArvo, BTREENODE *pJuuri);

BTREENODE* btree_lueTiedosto(char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;
    BTREENODE *pJuuri = NULL;
    BTREENODE *pUusi = NULL;
    char aRivi[LEN_RIVI];
    char *p1 = NULL; // ptr sukunimelle tiedostosta
    char *p2 = NULL; // ptr määrälle tiedostosta

    if ( (Tiedosto = fopen(aTiedostoNimi, "r")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, LEN_RIVI, Tiedosto); // otsikkorivi pois
    while (fgets(aRivi, LEN_RIVI, Tiedosto) != NULL) {
        if ((p1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan.\n", aRivi);
            exit(0);
        }
        if ((p2 = strtok(NULL, ";\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan.\n", p1);
            exit(0);
        }
        
        pUusi = varaaMuisti();
        strcpy(pUusi->aSukunimi, p1);
        pUusi->iMaara = atoi(p2);
        pUusi->pVasenChild = NULL;
        pUusi->pOikeaChild = NULL;

        // uusi node puuhun apufunktion avulla
        pJuuri = lisaaPuuhun(pJuuri, pUusi);
    }
    fclose(Tiedosto);
    return (pJuuri);
}

static BTREENODE* lisaaPuuhun(BTREENODE *pJuuri, BTREENODE *pUusi) {
    if (pJuuri == NULL) {
        return pUusi; // uusi paikka puussa
    }
    if (strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) < 0) {
        pJuuri->pVasenChild = lisaaPuuhun(pJuuri->pVasenChild, pUusi);
    } else if ( (strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) > 0 )||(strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) == 0 ) )  { // duplikaatit oikealle
        pJuuri->pOikeaChild = lisaaPuuhun(pJuuri->pOikeaChild, pUusi);
    }
    return (pJuuri);
}

static BTREENODE* varaaMuisti() {
    BTREENODE *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (BTREENODE*)malloc(sizeof(BTREENODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}

BTREENODE* btree_vapautaMuisti(BTREENODE *pJuuri) {

    return (pJuuri);
}

/// @brief Hakee kysytyn arvon puusta DFS tyylillä ja kirjoittaa käydyn polun tiedostoon
/// @param aTiedostoNimi Kirjoitettavan tiedoston nimi
/// @param iArvo Haettava arvo
/// @param pJuuri Puun ylin node (juuri)
void btree_dfsHakuKirjoita(char aTiedostoNimi[], int iArvo, BTREENODE *pJuuri) {
    FILE *Tiedosto = NULL;
    int loydetty = 0;

    if ( (Tiedosto = fopen(aTiedostoNimi, "w")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    loydetty = dfsHaku(Tiedosto, iArvo, pJuuri);
    if (loydetty == 0) {
        printf("Arvoa '%d' ei löytynyt \n", iArvo); }
    fclose(Tiedosto);
    return;
}

/// apufunktio btree_dfsHakuKirjoita funktiolle rekursiota hyödyntäen
static int dfsHaku(FILE *Tiedosto, int iArvo, BTREENODE *pJuuri) {
    if (pJuuri == NULL) {
        return (0); }
    // nykyinen node
    fprintf(Tiedosto, "%s,%d\n", pJuuri->aSukunimi, pJuuri->iMaara);
    if (pJuuri->iMaara == iArvo) {
        printf("Löydetty: %s,%d\n", pJuuri->aSukunimi, pJuuri->iMaara);
        return (1); }

    // Vasen child
    if (dfsHaku(Tiedosto, iArvo, pJuuri->pVasenChild)) {
        return (1); }
    // Oikea child
    if (dfsHaku(Tiedosto, iArvo, pJuuri->pOikeaChild)) {
        return (1); }
    return (0);
}

/// @brief Tulostetaan puu rekursiivisesti preorder DFS tyylillä
/// @param pJuuri 
void btree_tulostaPuu(BTREENODE *pJuuri) {
    if (pJuuri == NULL) {
        return;
    }
    printf("%s,%d\n", pJuuri->aSukunimi, pJuuri->iMaara);
    btree_tulostaPuu(pJuuri->pVasenChild);
    btree_tulostaPuu(pJuuri->pOikeaChild);
    return;
}
