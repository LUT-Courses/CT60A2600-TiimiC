#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

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
