#include <stdio.h>
#include <stdlib.h>
#include "hello.h"

#define LEN_SUKUNIMI 30 // max sukunimi pituus
#define MAX_NIMET 23156 // 1 yli jotta nullikka mahtuu

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* varaaMuisti();
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
void kysyTiedostoNimi(char aTiedostoNimi[]);
int lueTiedosto();

int main(void) {
    char aTiedostoNimi[20];
    SUKUNIMI *pAlku = NULL; // alustetaan pointerit NULL



    printf("%s\n", hello_message());
    printf("Terve testi\n");
    return 0;
}

void kysyTiedostoNimi(char aTiedostoNimi[]) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", aTiedostoNimi);
    return;
}

int lueTiedosto(char aTiedostoNimi[]) {


}

SUKUNIMI* varaaMuisti() {
    SUKUNIMI *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (SUKUNIMI*)malloc(sizeof(SUKUNIMI))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
}


