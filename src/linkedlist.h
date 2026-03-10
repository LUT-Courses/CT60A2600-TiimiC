#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LEN_SUKUNIMI 30

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    int iMaara;
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* varaaMuisti(void);
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]);
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]);
void kirjoitaTiedostoAlkuLoppu(SUKUNIMI *pAlku, char aTiedostoNimi[]);
void kirjoitaTiedostoLoppuAlku(SUKUNIMI *pAlku, char aTiedostoNimi[]);
void tyhjennaTiedosto(char aTiedostoNimi[]);

#endif // LINKEDLIST_H
