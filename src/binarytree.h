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
BTREENODE* vapautaMuisti(BTREENODE *pAlku);
void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);
BTREENODE* lueTiedosto(char aTiedostoNimi[]);
void kirjoitaTiedostoAlkuLoppu(BTREENODE *pAlku, char aTiedostoNimi[]);
void kirjoitaTiedostoLoppuAlku(BTREENODE *pAlku, char aTiedostoNimi[]);
void tyhjennaTiedosto(char aTiedostoNimi[]);

#endif // BINARYTREE_H