#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LEN_NIMI 30

typedef struct listNode {
    char aNimi[LEN_NIMI];
    int iMaara;
    struct listNode *pSeuraava;
    struct listNode *pEdellinen;
} LISTNODE;

LISTNODE* vapautaMuisti(LISTNODE *pAlku);
LISTNODE* lueTiedosto(char aTiedostoNimi[]);
void kirjoitaTiedostoAlkuLoppu(LISTNODE *pAlku, char aTiedostoNimi[]);
void kirjoitaTiedostoLoppuAlku(LISTNODE *pAlku, char aTiedostoNimi[]);
void tyhjennaTiedosto(char aTiedostoNimi[]);
LISTNODE* lajitteleLaskeva(LISTNODE *pAlku);
LISTNODE* lajitteleNouseva(LISTNODE *pAlku);
LISTNODE* poistaAlkioNimi(char aNimi[], LISTNODE* pAlku);
LISTNODE* poistaAlkioMaara(int iMaara, LISTNODE* pAlku);
LISTNODE* lisaaListaan(LISTNODE *alku, int kohta, char nimi[], int maara);

#endif // LINKEDLIST_H
