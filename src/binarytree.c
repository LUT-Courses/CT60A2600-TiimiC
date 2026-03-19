#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

#define LEN_RIVI 40 // max rivi pituus tiedostossa

/// @brief Rekursiivinen apufunktio puuhun lisäykseen
static BTREENODE* lisaaPuuhun(BTREENODE *pJuuri, BTREENODE *pUusi);

// Apufunktiota AVL puuta varten
static BTREENODE* lisaaPuuhunAVL(BTREENODE *pJuuri, BTREENODE *pUusi);
static BTREENODE* kiertoVasen(BTREENODE *pNode);
static BTREENODE* kiertoOikea(BTREENODE *pNode);
static int tarkistaTasapaino(BTREENODE *pNode);
static int tarkistaKorkeus(BTREENODE *pNode);
static void paivitaKorkus(BTREENODE *pNode);

/// @brief Apufunktio, varaa muisti uudelle structille (BTREENODE)
static BTREENODE* varaaMuisti(void);
/// @brief Apufunktio tiedostokirjoitukseen DFS-järjestyksessä
static void btree_kirjoitaSyvyys(BTREENODE *pJuuri, FILE *Tiedosto);
static int dfsHaku(FILE *Tiedosto, int iArvo, BTREENODE *pJuuri);

typedef struct queueNode {
    BTREENODE *pPuuNode;
    struct queueNode *pSeuraava;
} QUEUENODE;

static void jonoonLisaa(QUEUENODE **ppAlku, QUEUENODE **ppLoppu, BTREENODE *pNode);
static BTREENODE* jonostaPoista(QUEUENODE **ppAlku, QUEUENODE **ppLoppu);

/// @brief lukee tiedostosta nimet ja lisää ne puuhun käyttäen apufunktiota
/// @param aTiedostoNimi kirjoitettavan tiedoston nimi 
/// @return palauttaa puun ylimmän noden pJuuri
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
    if (pUusi->iMaara < pJuuri->iMaara) {
        pJuuri->pVasenChild = lisaaPuuhun(pJuuri->pVasenChild, pUusi);
    } else if (pUusi->iMaara > pJuuri->iMaara) {
        pJuuri->pOikeaChild = lisaaPuuhun(pJuuri->pOikeaChild, pUusi);
    } else if (strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) < 0) { // jos sama maara nimiä niin verrataan aakkosilla
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
    if (pJuuri == NULL) {
        return NULL;
    }

    pJuuri->pVasenChild = btree_vapautaMuisti(pJuuri->pVasenChild);
    pJuuri->pOikeaChild = btree_vapautaMuisti(pJuuri->pOikeaChild);
    free(pJuuri);
    return NULL;
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

/// @brief Hakee kysytyn nimen puusta BFS tyylillä ja kirjoittaa käydyn polun tiedostoon
/// @param aTiedostoNimi Kirjoitettavan tiedoston nimi
/// @param aNimi Haettava nimi
/// @param pJuuri Puun ylin node (juuri)
void btree_bfsHakuNimellaKirjoita(char aTiedostoNimi[], char aNimi[], BTREENODE *pJuuri) {
    FILE *Tiedosto = NULL;
    QUEUENODE *pAlku = NULL;
    QUEUENODE *pLoppu = NULL;
    BTREENODE *pNykyinen = NULL;
    int iLoydetty = 0;

    if ( (Tiedosto = fopen(aTiedostoNimi, "w")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    if (pJuuri == NULL) {
        fclose(Tiedosto);
        return;
    }

    jonoonLisaa(&pAlku, &pLoppu, pJuuri);

    while (pAlku != NULL) {
        pNykyinen = jonostaPoista(&pAlku, &pLoppu);
        fprintf(Tiedosto, "%s,%d\n", pNykyinen->aSukunimi, pNykyinen->iMaara);

        if (strcmp(pNykyinen->aSukunimi, aNimi) == 0) {
            printf("Löydetty: %s,%d\n", pNykyinen->aSukunimi, pNykyinen->iMaara);
            iLoydetty = 1;
            break;
        }

        if (pNykyinen->pVasenChild != NULL) {
            jonoonLisaa(&pAlku, &pLoppu, pNykyinen->pVasenChild);
        }
        if (pNykyinen->pOikeaChild != NULL) {
            jonoonLisaa(&pAlku, &pLoppu, pNykyinen->pOikeaChild);
        }
    }

    while (pAlku != NULL) {
        (void)jonostaPoista(&pAlku, &pLoppu);
    }

    if (iLoydetty == 0) {
        printf("Nimeä '%s' ei löytynyt\n", aNimi);
    }

    fclose(Tiedosto);
    return;
}

static void jonoonLisaa(QUEUENODE **ppAlku, QUEUENODE **ppLoppu, BTREENODE *pNode) {
    QUEUENODE *pUusi = NULL;

    if ((pUusi = (QUEUENODE*)malloc(sizeof(QUEUENODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    pUusi->pPuuNode = pNode;
    pUusi->pSeuraava = NULL;

    if (*ppLoppu == NULL) {
        *ppAlku = pUusi;
        *ppLoppu = pUusi;
        return;
    }

    (*ppLoppu)->pSeuraava = pUusi;
    *ppLoppu = pUusi;
    return;
}

static BTREENODE* jonostaPoista(QUEUENODE **ppAlku, QUEUENODE **ppLoppu) {
    QUEUENODE *pPoistettava = NULL;
    BTREENODE *pRet = NULL;

    if (*ppAlku == NULL) {
        return NULL;
    }

    pPoistettava = *ppAlku;
    pRet = pPoistettava->pPuuNode;
    *ppAlku = pPoistettava->pSeuraava;

    if (*ppAlku == NULL) {
        *ppLoppu = NULL;
    }

    free(pPoistettava);
    return pRet;
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
///kirjoitetaan tiedostoon syvyyden mukaan
void btree_kirjoitaTiedostoSyvyys(BTREENODE *pJuuri, char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;

    if ( (Tiedosto = fopen(aTiedostoNimi, "w")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    btree_kirjoitaSyvyys(pJuuri, Tiedosto);
    fclose(Tiedosto);
    return;
}
///Apufunktio syvyyden mukaan kirjoittamiseen
static void btree_kirjoitaSyvyys(BTREENODE *pJuuri, FILE *Tiedosto) {
    if (pJuuri == NULL) {
        return;
    }
    fprintf(Tiedosto, "%s,%d\n", pJuuri->aSukunimi, pJuuri->iMaara);
    btree_kirjoitaSyvyys(pJuuri->pVasenChild, Tiedosto);
    
    btree_kirjoitaSyvyys(pJuuri->pOikeaChild, Tiedosto);
    return;
}

/// @brief lisää noden AVL puuhun
/// @param pJuuri käsiteltävän (ali)puun juuri
/// @param pUusi uusi node joka lisätään
/// @return käsitellyn alipuun (mahd. uusi) juuri
static BTREENODE* lisaaPuuhunAVL(BTREENODE *pJuuri, BTREENODE *pUusi) {
    int iTasapainoKerroin;

    if (pJuuri == NULL) {
        return pUusi; } // uusi paikka puussa

    if (pUusi->iMaara < pJuuri->iMaara) { // uuden noden määrä pienempi, menee vasen
        pJuuri->pVasenChild = lisaaPuuhunAVL(pJuuri->pVasenChild, pUusi); 
    } else if (pUusi->iMaara > pJuuri->iMaara) { // uuden noden määrä isompi, menee oikea
        pJuuri->pOikeaChild = lisaaPuuhunAVL(pJuuri->pOikeaChild, pUusi);
    } else if (strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) < 0) { // jos sama maara nimiä niin verrataan aakkosilla (ensin tulevan vasemmalle)
        pJuuri->pVasenChild = lisaaPuuhunAVL(pJuuri->pVasenChild, pUusi);
    } else if ( (strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) > 0 )||(strcmp(pUusi->aSukunimi, pJuuri->aSukunimi) == 0 ) )  { // duplikaatit oikealle
        pJuuri->pOikeaChild = lisaaPuuhunAVL(pJuuri->pOikeaChild, pUusi);
    }
    paivitaKorkus(pJuuri); // päivitetään nykyisen noden korkeus
    iTasapainoKerroin = tarkistaTasapaino(pJuuri); // max tasapaino varianssi +-1, 0 tasapainossa

    if (iTasapainoKerroin > 1 && // LL case vasen->vasen
        (pUusi->iMaara < pJuuri->pVasenChild->iMaara || // vertaillaan määrä, meneekö node vasen
        (pUusi->iMaara == pJuuri->pVasenChild->iMaara && // jos sama määrä, tarkista meneekö aakkosten perusteella vasemmalle
        strcmp(pUusi->aSukunimi, pJuuri->pVasenChild->aSukunimi) < 0)) ) {
        return kiertoOikea(pJuuri);
    }
    if (iTasapainoKerroin < -1 && // RR case oikea->oikea
        (pUusi->iMaara > pJuuri->pOikeaChild->iMaara || // vertaillaan määrä, meneekö node oikea
        (pUusi->iMaara == pJuuri->pOikeaChild->iMaara && // jos sama määrä, tarkista meneekö aakkosten perusteella oikealle
        strcmp(pUusi->aSukunimi, pJuuri->pOikeaChild->aSukunimi) >= 0)) ) {
        return kiertoVasen(pJuuri);
    }
    if (iTasapainoKerroin > 1) { // LR case vasen->oikea. LL ei osunut joten riittää kun vertaillaan tasapainoa
        pJuuri->pVasenChild = kiertoVasen(pJuuri->pVasenChild);
        return kiertoOikea(pJuuri);
    }
    if (iTasapainoKerroin < -1) { // RL case oikea->vasen. RR ei osunut joten riittää kun vertaillaan tasapainoa
        pJuuri->pOikeaChild = kiertoOikea(pJuuri->pOikeaChild);
        return kiertoVasen(pJuuri);
    }

    return (pJuuri);
}