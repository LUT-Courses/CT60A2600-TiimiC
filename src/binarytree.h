#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LEN_SUKUNIMI 30

typedef struct btreeNode {
    char aSukunimi[LEN_SUKUNIMI];
    int iMaara;
    struct btreeNode *pVasenChild; // pointteri vasempaan lapseen
    struct btreeNode *pOikeaChild; // pointteri oikeaan lapseen
} BTREENODE;

BTREENODE* varaaMuisti(void);
BTREENODE* vapautaMuisti(BTREENODE *pJuuri);
void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);
BTREENODE* lueTiedosto(char aTiedostoNimi[]);
void tulostaPuu(BTREENODE *pJuuri);

#endif // BINARYTREE_H