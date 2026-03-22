#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_SUKUNIMI 50

typedef struct btreeNode
{
    char aSukunimi[LEN_SUKUNIMI];
    int iMaara;
    struct btreeNode *pVasenChild;
    struct btreeNode *pOikeaChild;
    int iKorkeus;
} BTREENODE;

BTREENODE *btree_lueTiedosto(char aTiedostoNimi[]);
BTREENODE *btree_vapautaMuisti(BTREENODE *pJuuri);
void btree_dfsHakuKirjoita(char aTiedostoNimi[], int iArvo, BTREENODE *pJuuri);
void btree_bfsHakuNimellaKirjoita(char aTiedostoNimi[], char aNimi[], BTREENODE *pJuuri);
void btree_tulostaPuu(BTREENODE *pJuuri);
void btree_kirjoitaTiedostoSyvyys(BTREENODE *pJuuri, char aTiedostoNimi[]);
BTREENODE *btree_poistaNodePohjaNimi(char aNimi[], BTREENODE *pJuuri);
BTREENODE *btree_poistaNodePohjaArvo(int iArvo, BTREENODE *pJuuri);
BTREENODE *lisaaPuuhunAVL(BTREENODE *pJuuri, BTREENODE *pUusi);

#endif