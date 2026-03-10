#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

/// Muuttujaparametri ja syöte valikko funktiosta. Muuttujaparametriin asetetaan tiedoston nimi
void kysyTiedostoNimi(char aTiedostoNimi[], char aSyote[]) {
    printf("%s", aSyote);
    scanf("%s", aTiedostoNimi);
    return;
}

/// Varaa muisti uudelle structille (BTREENODE)
BTREENODE* varaaMuisti() {
    BTREENODE *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (BTREENODE*)malloc(sizeof(BTREENODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}
