#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa

/// @brief Rekursiivinen apufunktio puuhun lisäykseen
static BTREENODE* lisaaPuuhun(BTREENODE *pJuuri, BTREENODE *pUusi);

/// @brief Apufunktio, varaa muisti uudelle structille (BTREENODE)
static BTREENODE* varaaMuisti(void);
/// @brief Apufunktio tiedostokirjoitukseen syvyyden kanssa
static void btree_kirjoitaSyvyys(BTREENODE *pJuuri, FILE *Tiedosto, int iSyvyys);

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

/// @brief Tulostetaan puu rekursiivisesti depth-first tyylillä
/// @param pJuuri 
void btree_tulostaPuu(BTREENODE *pJuuri) {
    if (pJuuri == NULL) {
        return;
    }
    btree_tulostaPuu(pJuuri->pVasenChild);
    printf("%s,%d\n", pJuuri->aSukunimi, pJuuri->iMaara);
    btree_tulostaPuu(pJuuri->pOikeaChild);
    return;
}
//kirjoitetaan tiedostoon syvyyden mukaan
void btree_kirjoitaTiedostoSyvyys(BTREENODE *pJuuri, char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;

    if ( (Tiedosto = fopen(aTiedostoNimi, "w")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    btree_kirjoitaSyvyys(pJuuri, Tiedosto, 0);
    fclose(Tiedosto);
    return;
}
//Apufunktio syvyyden mukaan kirjoittamiseen
static void btree_kirjoitaSyvyys(BTREENODE *pJuuri, FILE *Tiedosto, int iSyvyys) {
    if (pJuuri == NULL) {
        return;
    }
    btree_kirjoitaSyvyys(pJuuri->pVasenChild, Tiedosto, iSyvyys + 1);
    fprintf(Tiedosto, "%s,%d,%d\n", pJuuri->aSukunimi, pJuuri->iMaara, iSyvyys);
    btree_kirjoitaSyvyys(pJuuri->pOikeaChild, Tiedosto, iSyvyys + 1);
    return;
}
