#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LEN_SUKUNIMI 30

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    int iMaara;
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]);
void kirjoitaTiedostoAlkuLoppu(SUKUNIMI *pAlku, char aTiedostoNimi[]);
void kirjoitaTiedostoLoppuAlku(SUKUNIMI *pAlku, char aTiedostoNimi[]);
void tyhjennaTiedosto(char aTiedostoNimi[]);
SUKUNIMI* lajitteleLaskeva(SUKUNIMI *pAlku);
SUKUNIMI* lajitteleNouseva(SUKUNIMI *pAlku);
SUKUNIMI* lisaaListaan(SUKUNIMI *alku, int kohta, char nimi[], int maara);
void Tulosta(SUKUNIMI *pAlku);


#endif // LINKEDLIST_H
