#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LEN_SUKUNIMI 30

typedef struct btreeNode {
    char aSukunimi[LEN_SUKUNIMI];
    int iMaara;
    struct btreeNode *pVasenChild; // pointteri vasempaan lapseen
    struct btreeNode *pOikeaChild; // pointteri oikeaan lapseen
} BTREENODE;

BTREENODE* btree_vapautaMuisti(BTREENODE *pJuuri);
BTREENODE* btree_lueTiedosto(char aTiedostoNimi[]);
void btree_tulostaPuu(BTREENODE *pJuuri);
void btree_kirjoitaTiedostoSyvyys(BTREENODE *pJuuri, char aTiedostoNimi[]);

#endif // BINARYTREE_H
