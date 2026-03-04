#include <stdio.h>
#include "hello.h"

#define LEN_SUKUNIMI 50
#define MAX_NIMET 23156 // 1 yli jotta nullikka mahtuu

int lueTiedosto();

int main(void) {
    char aSukunimet[MAX_NIMET][LEN_SUKUNIMI];

    printf("%s\n", hello_message());
    printf("Terve testi\n");
    return 0;
}


