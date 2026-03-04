#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_RIVI 40 // max rivi pituus tiedostossa
#define LEN_SUKUNIMI 30 // max sukunimi pituus

typedef struct sukunimi {
    char aSukunimi[LEN_SUKUNIMI];
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI* varaaMuisti();
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku);
void kysyTiedostoNimi(char aTiedostoNimi[]);
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]);
void tulostaAlkuLoppu(SUKUNIMI *pAlku);
void tulostaLoppuAlku(SUKUNIMI *pAlku);
void kirjoitaTiedostoAlkuLoppu();
void kirjoitaTiedostoLoppuAlku();
int valikko();

int main(void) {
    int iValinta = 0;
    char aTiedostoNimi[20];
    SUKUNIMI *pAlku = NULL; // alustetaan pointerit NULL

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            kysyTiedostoNimi(aTiedostoNimi);
            pAlku = lueTiedosto(aTiedostoNimi);
            printf("Tiedosto '%s' luettu\n", aTiedostoNimi);
            printf("\n");
        } else if (iValinta == 2) {
            tulostaAlkuLoppu(pAlku); //väliaike debug
        } else if (iValinta == 3) {
            tulostaLoppuAlku(pAlku); //väliaikane debug
        } else if (iValinta == 4) {
            // tyhjennä tiedosto
        } else if (iValinta == 0) {
            printf("Lopetetaan\n");
        } else {
            printf("Tuntematon valinta\n");
            printf("\n");
        }
    } while (iValinta != 0);
    
    pAlku = vapautaMuisti(pAlku);
    printf("Muisti vapautettu.\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}
int valikko() {
    int iValinta = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedostoon nimet alusta loppuun\n");
    printf("3) Kirjoita tiedostoon nimet lopusta alkuun\n");
    printf("4) Tyhjennä tiedosto\n");
    printf("0) Lopeta\n");
    printf("\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}

// Muuttujaparametri main funktiosta johon asetetaan tiedoston nimi 
void kysyTiedostoNimi(char aTiedostoNimi[]) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", aTiedostoNimi);
    return;
}

// Luetaan tiedostosta sukunimi ja lisätään se uuteen sukunimi structiin.
// Samaan structiin lisätään pointteri seuraavaan ja edelliseen sukunimi structiin.
// Palauttaa osoittimen listan alkuu pAlku
SUKUNIMI* lueTiedosto(char aTiedostoNimi[]) {
    FILE* Tiedosto = NULL;
    SUKUNIMI *pAlku = NULL;
    SUKUNIMI *pUusi = NULL;
    SUKUNIMI *pViimeisin = NULL;
    char aRivi[LEN_RIVI];
    char *p1 = NULL; // ptr sukunimelle tiedostosta

    if ( (Tiedosto = fopen(aTiedostoNimi, "r")) == NULL ) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, LEN_RIVI, Tiedosto); // Luetaan otsikkorivi pois
    while (fgets(aRivi, LEN_RIVI, Tiedosto) != NULL) {
        if ((p1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan.\n", aRivi);
            exit(0);
        }
        if (pViimeisin == NULL) {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pUusi->pSeuraava = NULL;
            pUusi->pEdellinen = NULL;
            pViimeisin = pUusi;
            pAlku = pViimeisin;
        } else {
            pUusi = varaaMuisti();
            strcpy(pUusi->aSukunimi, p1);
            pViimeisin->pSeuraava = pUusi;
            pUusi->pEdellinen = pViimeisin;
            pUusi->pSeuraava = NULL;
            pViimeisin = pUusi;
        }
    }
    fclose(Tiedosto);
    return (pAlku);
}

// Varaa muisti uudelle structille (SUKUNIMI)
SUKUNIMI* varaaMuisti() {
    SUKUNIMI *pUusi = NULL;

    // muistin varauksen virheen käsittely
    if ((pUusi = (SUKUNIMI*)malloc(sizeof(SUKUNIMI))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    return (pUusi);
}

// Vapauta muisti käymällä linked-list läpi alusta loppuun
SUKUNIMI* vapautaMuisti(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    return (pAlku);
}

void tulostaAlkuLoppu(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while (ptr != NULL) {
        printf("Henkilön sukunimi '%s'\n", ptr->aSukunimi);
        ptr = ptr->pSeuraava;
    }
    return;
}
// Kulkee ensin listan loppuun ja sitten tulostaa
// nimet kulkien alkuun
void tulostaLoppuAlku(SUKUNIMI *pAlku) {
    SUKUNIMI *ptr = pAlku;
    while ( (ptr != NULL) && (ptr->pSeuraava != NULL) ) {
        ptr = ptr->pSeuraava;
    }
    while (ptr != NULL) {
        printf("Henkilön sukunimi '%s'\n", ptr->aSukunimi);
        ptr = ptr->pEdellinen;
    }
    return;
}
