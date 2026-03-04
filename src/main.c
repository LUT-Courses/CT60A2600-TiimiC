#include <stdio.h>
#include "hello.h"

#define LEN_SUKUNIMI 30
#define MAX_NIMET 23156 // 1 yli jotta nullikka mahtuu

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* varaaMuisti();
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
int lueTiedosto();

int main(void) {
    SUKUNIMI *pAlku = NULL; // alustetaan pointerit NULL



    printf("%s\n", hello_message());
    printf("Terve testi\n");
    return 0;
}

int lueTiedosto() {


}


