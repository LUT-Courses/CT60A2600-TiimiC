#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LEN_SUKUNIMI 30

typedef struct btreeNode {
    char aNimi[LEN_SUKUNIMI];
    int iMaara;
    int iKorkeus;
    struct btreeNode *pVasenChild; // pointteri vasempaan lapseen
    struct btreeNode *pOikeaChild; // pointteri oikeaan lapseen
} BTREENODE;

BTREENODE* btree_vapautaMuisti(BTREENODE *pJuuri);
BTREENODE* btree_lueTiedosto(char aTiedostoNimi[]);
void btree_dfsHakuKirjoita(char aTiedostoNimi[], int iArvo, BTREENODE *pJuuri);
void btree_bfsHakuNimellaKirjoita(char aTiedostoNimi[], char aNimi[], BTREENODE *pJuuri);
void btree_tulostaPuu(BTREENODE *pJuuri);
void btree_kirjoitaTiedostoSyvyys(BTREENODE *pJuuri, char aTiedostoNimi[]);
BTREENODE* btree_poistaNodePohjaNimi(char aNimi[], BTREENODE* pJuuri);
BTREENODE* btree_poistaNodePohjaArvo(int iArvo, BTREENODE* pJuuri);
BTREENODE* lisaaPuuhunAVL(BTREENODE *pJuuri, BTREENODE *pUusi);

#endif // BINARYTREE_H
