#include <stdio.h>
#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "../src/linkedlist.h"

#define TEST_TIEDOSTO "testi.txt"
#define TEST_TULOSTIEDOSTO "tulos.txt"

void setUp(void)
{
    remove(TEST_TIEDOSTO);
    remove(TEST_TULOSTIEDOSTO);
}

void tearDown(void)
{
    remove(TEST_TIEDOSTO);
    remove(TEST_TULOSTIEDOSTO);
}

void luoTiedosto(char tiedostonNimi[], char nimet[][50], int luvut[], int maara)  // Luo testitiedoston, johon kirjoitetaan nimet ja määrät, jotka testit lukevat
{
    FILE *tiedosto = fopen(tiedostonNimi, "w");
    TEST_ASSERT_NOT_NULL(tiedosto); // tarkistetaan, että tiedosto on luotu onnistuneesti
    fprintf(tiedosto, "Sukunimi;Maara\n");
    for (int i = 0; i < maara; i++) // kirjoitetaan nimet ja määrät tiedostoon
    {
        fprintf(tiedosto, "%s;%d\n", nimet[i], luvut[i]);// kirjoitetaan nimi ja määrä riville muodossa "Nimi;Maara"
    }
    fclose(tiedosto);
}

int laskeSolmut(SUKUNIMI *alku) // Laskee listan solmujen määrän
{
    int laskuri = 0;
    SUKUNIMI *ptr = alku;
    while (ptr != NULL) // kuljetaan listaa läpi ja lasketaan solmut
    {
        laskuri++;
        ptr = ptr->pSeuraava; // siirrytään seuraavaan solmuun
    }
    return laskuri;
}

int tarkistaLista(SUKUNIMI *alku) // Tarkistaa, että listan solmut on linkitetty oikein sekä eteen- että taaksepäin
{
    if (alku == NULL) // tyhjä lista on aina oikein linkitetty
        return 1;

    SUKUNIMI *ptr = alku;
    SUKUNIMI *edellinen = NULL;

    while (ptr != NULL)// kuljetaan listaa läpi eteenpäin ja tarkistetaan linkit
    {
        if (ptr->pEdellinen != edellinen)// tarkistetaan, että edellinen solmu on oikein linkitetty
            return 0; // jos linkki ei täsmää, lista on väärin linkitetty
        edellinen = ptr;
        ptr = ptr->pSeuraava;// siirrytään seuraavaan solmuun
    }

    SUKUNIMI *viimeinen = edellinen; // viimeinen solmu on edellisen jälkeen
    ptr = viimeinen; // aloitetaan kulkeminen taaksepäin viimeisestä solmusta
    edellinen = NULL;
    while (ptr != NULL)
    {
        if (ptr->pSeuraava != edellinen)// tarkistetaan, että seuraava solmu on oikein linkitetty
            return 0;
        edellinen = ptr;// siirrytään edelliseen solmuun
        ptr = ptr->pEdellinen;// siirrytään edelliseen solmuun
    }

    return 1;
}

void TestiTiedostonLukeminen(void) // Testaa, että tiedosto luetaan oikein ja linked-list rakennetaan odotetusti
{
    char nimet[3][50] = {"Korhonen", "Virtanen", "Mäkelä"}; // testin nimet ja määrät, jotka kirjoitetaan tiedostoon
    int luvut[3] = {21419, 18456, 12345}; // testin määrät, jotka kirjoitetaan tiedostoon
    int montako = 3; // testattavien nimien ja määrien määrä

    luoTiedosto(TEST_TIEDOSTO, nimet, luvut, montako);// luodaan testitiedosto
    SUKUNIMI *lista = lueTiedosto(TEST_TIEDOSTO);

    TEST_ASSERT_NOT_NULL(lista);
    TEST_ASSERT_EQUAL_INT(montako, laskeSolmut(lista));// tarkistetaan, että listassa on odotettu määrä solmuja

    SUKUNIMI *ptr = lista;
    for (int i = 0; i < montako; i++) // tarkistetaan, että nimet ja määrät on luettu oikein ja solmut on linkitetty oikeassa järjestyksessä
    {
        TEST_ASSERT_EQUAL_STRING(nimet[i], ptr->aSukunimi);
        TEST_ASSERT_EQUAL_INT(luvut[i], ptr->iMaara);
        ptr = ptr->pSeuraava;
    }

    TEST_ASSERT_TRUE(tarkistaLista(lista));

    vapautaMuisti(lista);
}

void KirjoitusTesti(void)
{
    char nimet[5][50] = {"Eka", "Toka", "Kolmas", "Neljäs", "Viides"}; // testin nimet ja määrät, jotka kirjoitetaan tiedostoon
    int luvut[5] = {100, 200, 300, 400, 500};
    int montako = 5;

    luoTiedosto(TEST_TIEDOSTO, nimet, luvut, montako); // luodaan testitiedosto
    SUKUNIMI *lista = lueTiedosto(TEST_TIEDOSTO); // luetaan tiedosto linked-listaksi

    kirjoitaTiedostoAlkuLoppu(lista, TEST_TULOSTIEDOSTO);// kirjoitetaan lista tiedostoon alusta loppuun

    FILE *tiedosto = fopen(TEST_TULOSTIEDOSTO, "r");
    TEST_ASSERT_NOT_NULL(tiedosto);
    char rivi[100];
    for (int i = 0; i < montako; i++)// tarkistetaan, että tiedostoon on kirjoitettu nimet ja määrät oikeassa järjestyksessä
    {
        TEST_ASSERT_TRUE(fgets(rivi, sizeof(rivi), tiedosto) != NULL);// tarkistetaan, että rivin lukeminen onnistuu
        char nimi[50];
        int luku;
        sscanf(rivi, "%[^,],%d", nimi, &luku);// parsitaan nimi ja luku riviltä
        TEST_ASSERT_EQUAL_STRING(nimet[i], nimi);// tarkistetaan, että nimi on odotettu
        TEST_ASSERT_EQUAL_INT(luvut[i], luku);//    tarkistetaan, että luku on odotettu
    }
    fclose(tiedosto);

    kirjoitaTiedostoLoppuAlku(lista, TEST_TULOSTIEDOSTO);

    tiedosto = fopen(TEST_TULOSTIEDOSTO, "r");
    TEST_ASSERT_NOT_NULL(tiedosto);
    for (int i = montako - 1; i >= 0; i--) // tarkistetaan, että tiedostoon on kirjoitettu nimet ja määrät oikeassa järjestyksessä, mutta nyt lopusta alkuun
    {
        TEST_ASSERT_TRUE(fgets(rivi, sizeof(rivi), tiedosto) != NULL); // tarkistetaan, että rivin lukeminen onnistuu
        char nimi[50];
        int luku;
        sscanf(rivi, "%[^,],%d", nimi, &luku);
        TEST_ASSERT_EQUAL_STRING(nimet[i], nimi);// tarkistetaan, että nimi on odotettu
        TEST_ASSERT_EQUAL_INT(luvut[i], luku);// tarkistetaan, että luku on odotettu
    }
    fclose(tiedosto);

    vapautaMuisti(lista);
}

void TestiMuistinHallinta(void) //  Testaa, että muisti vapautetaan oikein ja ettei vapautettuja solmuja enää käytetä
{
    char nimet[3][50] = {"Testi ", "Testi2", "Testi3"}; // testin nimet ja määrät, jotka kirjoitetaan tiedostoon
    int luvut[3] = {111, 222, 333};

    luoTiedosto(TEST_TIEDOSTO, nimet, luvut, 3);//  luodaan testitiedosto
    SUKUNIMI *lista = lueTiedosto(TEST_TIEDOSTO);
    TEST_ASSERT_NOT_NULL(lista);

    lista = vapautaMuisti(lista);
    TEST_ASSERT_NULL(lista);

    SUKUNIMI *tyhjaLista = NULL;
    tyhjaLista = vapautaMuisti(tyhjaLista);
    TEST_ASSERT_NULL(tyhjaLista);

    int isoMaara = 1000;
    FILE *tiedosto = fopen(TEST_TIEDOSTO, "w");
    fprintf(tiedosto, "Sukunimi;Maara\n");
    for (int i = 0; i < isoMaara; i++)
    {
        fprintf(tiedosto, "Iso%d;%d\n", i, i);
    }
    fclose(tiedosto);

    lista = lueTiedosto(TEST_TIEDOSTO);
    TEST_ASSERT_NOT_NULL(lista);
    TEST_ASSERT_EQUAL_INT(isoMaara, laskeSolmut(lista));

    lista = vapautaMuisti(lista);
    TEST_ASSERT_NULL(lista);
}

void TestaaTapaukset(void) // Testaa erilaisia tapauksia, kuten sama nimi useamman kerran, nollat ja negatiiviset määrät, sekä tyhjä tiedosto
{
    FILE *tiedosto = fopen(TEST_TIEDOSTO, "w");
    fprintf(tiedosto, "Sukunimi;Maara\n");
    fclose(tiedosto);

    SUKUNIMI *lista = lueTiedosto(TEST_TIEDOSTO);
    TEST_ASSERT_NULL(lista);

    char yksNimi[1][50] = {"Ainoa"}; // testin nimi ja määrä, jotka kirjoitetaan tiedostoon
    int yksLuku[1] = {999};// luodaan testitiedosto, jossa on vain yksi nimi ja määrä
    luoTiedosto(TEST_TIEDOSTO, yksNimi, yksLuku, 1);

    lista = lueTiedosto(TEST_TIEDOSTO);// luetaan tiedosto linked-listaksi
    TEST_ASSERT_NOT_NULL(lista);
    TEST_ASSERT_EQUAL_INT(1, laskeSolmut(lista));// tarkistetaan, että listassa on odotettu määrä solmuja
    TEST_ASSERT_EQUAL_STRING("Ainoa", lista->aSukunimi);// tarkistetaan, että nimi on odotettu
    TEST_ASSERT_EQUAL_INT(999, lista->iMaara);// tarkistetaan, että luku on odotettu
    TEST_ASSERT_NULL(lista->pEdellinen); // tarkistetaan, että edellinen solmu on NULL, koska listalla on vain yksi solmu
    TEST_ASSERT_NULL(lista->pSeuraava);// tarkistetaan, että seuraava solmu on NULL, koska listalla on vain yksi solmu

    kirjoitaTiedostoAlkuLoppu(lista, TEST_TULOSTIEDOSTO); // kirjoitetaan lista tiedostoon alusta loppuun
    tiedosto = fopen(TEST_TULOSTIEDOSTO, "r");
    char rivi[100];
    TEST_ASSERT_TRUE(fgets(rivi, sizeof(rivi), tiedosto) != NULL);
    fclose(tiedosto);

    vapautaMuisti(lista);

    char samatNimet[3][50] = {"Sama", "Sama", "Sama"};
    int samatLuvut[3] = {100, 200, 300};
    luoTiedosto(TEST_TIEDOSTO, samatNimet, samatLuvut, 3);

    lista = lueTiedosto(TEST_TIEDOSTO); // luetaan tiedosto linked-listaksi, jossa on sama nimi useamman kerran, mutta eri määrillä
    TEST_ASSERT_NOT_NULL(lista); // tarkistetaan, että lista on luettu onnistuneesti
    TEST_ASSERT_EQUAL_INT(3, laskeSolmut(lista));// tarkistetaan, että listassa on odotettu määrä solmuja

    int samaMaara = 0;
    SUKUNIMI *ptr = lista;
    while (ptr != NULL) // kuljetaan listaa läpi ja lasketaan, kuinka monta kertaa sama nimi esiintyy
    {
        if (strcmp(ptr->aSukunimi, "Sama") == 0) // tarkistetaan, että nimi on "Sama"
            samaMaara++;
        ptr = ptr->pSeuraava;
    }
    TEST_ASSERT_EQUAL_INT(3, samaMaara); // tarkistetaan, että sama nimi esiintyy odotettu määrä kertoja

    vapautaMuisti(lista);// vapautetaan muisti testin jälkeen

    char erikoisetNimet[3][50] = {"Nolla", "Miinus", "Plussa"};
    int erikoisetLuvut[3] = {0, -500, 500};
    luoTiedosto(TEST_TIEDOSTO, erikoisetNimet, erikoisetLuvut, 3);

    lista = lueTiedosto(TEST_TIEDOSTO); // luetaan tiedosto linked-listaksi, jossa on nollat ja negatiiviset määrät
    TEST_ASSERT_NOT_NULL(lista);// tarkistetaan, että lista on luettu onnistuneesti

    ptr = lista; // tarkistetaan, että nimet ja määrät on luettu oikein ja solmut on linkitetty oikeassa järjestyksessä
    TEST_ASSERT_EQUAL_INT(0, ptr->iMaara);// tarkistetaan, että luku on odotettu
    ptr = ptr->pSeuraava;// tarkistetaan, että luku on odotettu
    TEST_ASSERT_EQUAL_INT(-500, ptr->iMaara);// tarkistetaan, että luku on odotettu
    ptr = ptr->pSeuraava;// tarkistetaan, että luku on odotettu
    TEST_ASSERT_EQUAL_INT(500, ptr->iMaara);// tarkistetaan, että luku on odotettu

    vapautaMuisti(lista);
}

void TiedostonTyhjennysTesti(void) // Testaa, että tyhjennaTiedosto-funktio toimii odotetusti ja että tyhjennettyä tiedostoa voidaan lukea ilman ongelmia
{
    char nimet[2][50] = {"Testi1", "Testi2"};
    int luvut[2] = {111, 222};

    luoTiedosto(TEST_TIEDOSTO, nimet, luvut, 2);

    FILE *tiedosto = fopen(TEST_TIEDOSTO, "r");
    char rivi[100];
    int rivit = 0;
    while (fgets(rivi, sizeof(rivi), tiedosto)) // tarkistetaan, että tiedostossa on rivejä ennen tyhjennystä
        rivit++;// lasketaan rivien määrä
    fclose(tiedosto);// tarkistetaan, että tiedostossa on odotettu määrä rivejä
    TEST_ASSERT_TRUE(rivit > 1);// tiedostossa pitäisi olla ainakin otsikkorivi ja yksi data rivi

    tyhjennaTiedosto(TEST_TIEDOSTO); // tyhjennetään tiedosto

    tiedosto = fopen(TEST_TIEDOSTO, "r");
    int ekaMerkki = fgetc(tiedosto);// tarkistetaan, että tiedosto on tyhjä tyhjennyksen jälkeen, eli ensimmäinen merkki on EOF
    TEST_ASSERT_EQUAL_INT(EOF, ekaMerkki);// tarkistetaan, että tiedostossa ei ole rivejä tyhjennyksen jälkeen
    fclose(tiedosto);

    SUKUNIMI *lista = lueTiedosto(TEST_TIEDOSTO);// tarkistetaan, että tyhjennettyä tiedostoa voidaan lukea ilman ongelmia, eli että lista on NULL
    TEST_ASSERT_NULL(lista);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TestiTiedostonLukeminen);
    RUN_TEST(KirjoitusTesti);
    RUN_TEST(TestiMuistinHallinta);
    RUN_TEST(TestaaTapaukset);
    RUN_TEST(TiedostonTyhjennysTesti);
    return UNITY_END();
}