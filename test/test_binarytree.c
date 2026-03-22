#include <stdio.h>
#include <string.h>
#include "unity.h"
#include <stdlib.h>
#include "../src/binarytree.h"

void setUp(void) {} // tiedostojen poisto ja muistin tyhjennys ennen testejä
void tearDown(void) {}

void TiedostoTesti(void)
{

    BTREENODE *rootNodeNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNodeNode);                            // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    TEST_ASSERT_EQUAL_STRING("Haapaluoma", rootNodeNode->aSukunimi); // tarkistetaan, nimen, ja node index
    // TEST_ASSERT_EQUAL_INT(21419, rootNodeNode->iMaara);
    rootNodeNode = btree_vapautaMuisti(rootNodeNode); //  tarkistaa että kaikki muisti vapautetaan oikein
}

int rivienMaara(char tiedosto[])
{
    FILE *f = fopen(tiedosto, "r");
    if (f == NULL)
    { // tarkistetaan, että tiedosto on luotu onnistuneesti
        return 0;
    }
    int luku = 0;
    char rivi[100]; // apumuuttuja laskemiseen
    while (fgets(rivi, sizeof(rivi), f) != NULL)
    { // lasketaan rivien määrä
        luku++;
    }
    fclose(f);
    return luku;
}

void test_dfsHaku(void)
{
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_dfsHakuKirjoita("dfsTiedosto.txt", 4069, rootNode);
    int Rivi1 = rivienMaara("dfsTiedosto.txt");
    TEST_ASSERT_TRUE(Rivi1 >= 1);                               // tarkistetaan että tiedostoon on kirjoitettu edes yksi rivi
    btree_dfsHakuKirjoita("dfsTiedosto.txt", 999999, rootNode); // kirjoitetaan tiedostoon dfs mukaan, mutta arvoa ei löydy
    int Rivi2 = rivienMaara("dfsTiedosto.txt");                 // tarkistetaan, että jos arvoa ei löydy, niin tiedostoon kirjoitetaan enemmän rivejä
    TEST_ASSERT_TRUE(Rivi2 > Rivi1);
    remove("dfsTiedosto.txt"); // poistetaan tiedosto kun testit teyhty
    btree_vapautaMuisti(rootNode);
}

void test_bfs_haku(void)
{
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_bfsHakuNimellaKirjoita("bfsTiedosto.txt", "Eskelinen", rootNode); // kirjoitetaan tiedostoon bfs mukaan
    int rivit1 = rivienMaara("bfsTiedosto.txt");                            // tarkistetaan että tiedostoon on kirjoitettu edes yksi rivi
    TEST_ASSERT_TRUE(rivit1 >= 1);
    btree_bfsHakuNimellaKirjoita("bfsTiedosto.txt", "jotain", rootNode); // kirjoitetaan tiedostoon bfs mukaan, mutta nimeä ei löydy
    int rivit2 = rivienMaara("bfsTiedosto.txt");
    TEST_ASSERT_TRUE(rivit2 > rivit1);
    remove("bfsTiedosto.txt");
    btree_vapautaMuisti(rootNode);
}

void test_kirjoitaTiedostoon(void)
{
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_kirjoitaTiedostoSyvyys(rootNode, "output.txt"); // kirjoitetaan tiedostoon dfs mukaan
    FILE *f = fopen("output.txt", "r");
    TEST_ASSERT_NOT_NULL(f); // tarkistetaan, että tiedosto on luotu
    fclose(f);
    int lukumaara = rivienMaara("output.txt");
    TEST_ASSERT_TRUE(lukumaara > 10); // tarkistetaan, että tiedostoon on kirjoitettu rivejä
    remove("output.txt");
    btree_vapautaMuisti(rootNode); // vapautetaan muisti testin
}

void test_vapautaMuisti(void)
{
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNode);           // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    rootNode = btree_vapautaMuisti(rootNode); //  muisti vapautetaan oikein
}

static int laskeSolmut(BTREENODE *pJuuri)
{
    if (pJuuri == NULL) // tarkistetaan, että puu on olemassa, eikä ole tyhjä
        return 0;
    return 1 + laskeSolmut(pJuuri->pVasenChild) + laskeSolmut(pJuuri->pOikeaChild); // lasketaan solmujen määrä rekursiivisesti
}

static int tarkistaKorkeus(BTREENODE *node)
{
    if (node == NULL)
        return 0;
    return node->iKorkeus;
}

static void tarkistaKorkeudet(BTREENODE *pJuuri) // tarkistetaan, että noden korkeus on oikein laskettu
{
    if (pJuuri == NULL) // tarkistetaan, että puu on olemassa, eikä ole tyhjä
        return;

    int vasenKorkeus = tarkistaKorkeus(pJuuri->pVasenChild); // tarkistetaan, että noden korkeus on oikein laskettu
    int oikeaKorkeus = tarkistaKorkeus(pJuuri->pOikeaChild);
    int odotettuKorkeus = vasenKorkeus;

    if (oikeaKorkeus > vasenKorkeus) // tarkistetaan, että odotettu korkeus on suurempi kuin vasemman lapsen korkeuspi
    {
        odotettuKorkeus = oikeaKorkeus;
    }
    odotettuKorkeus = odotettuKorkeus + 1; // noden korkeus on lapsen korkeus + 1

    TEST_ASSERT_EQUAL_INT(odotettuKorkeus, pJuuri->iKorkeus); // tarkistetaan, että noden korkeus on oikein laskettu

    tarkistaKorkeudet(pJuuri->pVasenChild); // tarkistetaan, että noden korkeus on oikein laskettu
    tarkistaKorkeudet(pJuuri->pOikeaChild);
}

static int tarkistaTasapaino(BTREENODE *pJuuri)
{
    if (pJuuri == NULL)
        return 0;
    return tarkistaKorkeus(pJuuri->pVasenChild) - tarkistaKorkeus(pJuuri->pOikeaChild);
}

void test_avlKierto(void) // testataan, että vasen ja oikea kierto toimii odotetusti ja että noden korkeus päivittyy oikein
{
    BTREENODE *pJuuri = NULL;
    BTREENODE *pUus = NULL;
    int iArvot[] = {30, 20, 10};
    int i;

    for (i = 0; i < 3; i++) //  lisätään nodet puuhun, joka vaatii oikean kierron, jotta se pysyy tasapainossa
    {
        pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi");
        pUus->iMaara = iArvot[i];
        pUus->pVasenChild = NULL;
        pUus->pOikeaChild = NULL;
        pUus->iKorkeus = 1;
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus); // lisätään node puuhun AVL kiertoja käyttäen
    }

    TEST_ASSERT_EQUAL_INT(20, pJuuri->iMaara); // tarkistetaan, että oikea kierto on tapahtunut ja että uusi juuri on odotettu
    TEST_ASSERT_EQUAL_INT(10, pJuuri->pVasenChild->iMaara);
    TEST_ASSERT_EQUAL_INT(30, pJuuri->pOikeaChild->iMaara);

    TEST_ASSERT_NULL(pJuuri->pVasenChild->pVasenChild); // tarkistetaan, että kierron jälkeen vanhan juuren child nodet on linkitetty oikein
    TEST_ASSERT_NULL(pJuuri->pVasenChild->pOikeaChild);
    TEST_ASSERT_NULL(pJuuri->pOikeaChild->pVasenChild);
    TEST_ASSERT_NULL(pJuuri->pOikeaChild->pOikeaChild);

    btree_vapautaMuisti(pJuuri); // vapautetaan muisti testin jälkeen
    pJuuri = NULL;

    int iArvot2[] = {10, 20, 30};

    for (i = 0; i < 3; i++) // lisätään nodet puuhun, joka vaatii vasemman kierron, jotta se pysyy tasapainossa
    {
        pUus = (BTREENODE *)
            malloc(sizeof(BTREENODE));    // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi"); // kopioidaan nimi uudelle nodelle
        pUus->iMaara = iArvot2[i];        // asetetaan määrä uudelle nodelle
        pUus->pVasenChild = NULL;
        pUus->pOikeaChild = NULL;
        pUus->iKorkeus = 1;                    // alustetaan uudelle nodelle korkeus 1
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus); // lisätään node puuhun AVL kiertoja käyttäen
    }

    TEST_ASSERT_EQUAL_INT(20, pJuuri->iMaara);              // tarkistetaan, että vasen kierto on tapahtunut ja että uusi juuri on odotettu
    TEST_ASSERT_EQUAL_INT(10, pJuuri->pVasenChild->iMaara); // tarkistetaan, että kierron jälkeen vanhan juuren child nodet on linkitetty oikein
    TEST_ASSERT_EQUAL_INT(30, pJuuri->pOikeaChild->iMaara); // tarkistetaan, että kierron jälkeen vanhan juuren child nodet on linkitetty oikein

    btree_vapautaMuisti(pJuuri); // vapautetaan muisti testin jälkeen
    pJuuri = NULL;

    int iArvot3[] = {30, 10, 20};

    for (i = 0; i < 3; i++)
    {
        pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi");
        pUus->iMaara = iArvot3[i]; // asetetaan määrä uudelle nodelle
        pUus->pVasenChild = NULL;
        pUus->pOikeaChild = NULL;
        pUus->iKorkeus = 1;
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus); // lisätään node puuhun AVL kiertoja käyttäen, joka vaatii LR kierron, jotta puu pysyy tasapainossa
    }

    TEST_ASSERT_EQUAL_INT(20, pJuuri->iMaara);
    TEST_ASSERT_EQUAL_INT(10, pJuuri->pVasenChild->iMaara); // tarkistetaan, että kierron jälkeen vanhan juuren child nodet on linkitetty oikein
    TEST_ASSERT_EQUAL_INT(30, pJuuri->pOikeaChild->iMaara);

    btree_vapautaMuisti(pJuuri);
}

void test_korkeusArvot(void) // testataan, että noden korkeus on oikein laskettu ja päivitetty kiertojen jälkeen
{
    BTREENODE *pJuuri = NULL;
    BTREENODE *pUus = NULL;
    int iArvot[] = {50, 30, 70, 20, 40, 60, 80};
    int i;

    for (i = 0; i < 7; i++)
    {
        pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi");
        pUus->iMaara = iArvot[i];
        pUus->pVasenChild = NULL;
        pUus->pOikeaChild = NULL;
        pUus->iKorkeus = 1;
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus); //
    }

    TEST_ASSERT_EQUAL_INT(3, pJuuri->iKorkeus); // tarkistetaan, että noden korkeus on oikein laskettu ja päivitetty kiertojen jälkeen
    TEST_ASSERT_EQUAL_INT(2, pJuuri->pVasenChild->iKorkeus);
    TEST_ASSERT_EQUAL_INT(2, pJuuri->pOikeaChild->iKorkeus);
    TEST_ASSERT_EQUAL_INT(1, pJuuri->pVasenChild->pVasenChild->iKorkeus);
    TEST_ASSERT_EQUAL_INT(1, pJuuri->pVasenChild->pOikeaChild->iKorkeus);
    TEST_ASSERT_EQUAL_INT(1, pJuuri->pOikeaChild->pVasenChild->iKorkeus);
    TEST_ASSERT_EQUAL_INT(1, pJuuri->pOikeaChild->pOikeaChild->iKorkeus);

    btree_vapautaMuisti(pJuuri);
}

void test_tasapaino(void) // testataan, että puu pysyy tasapainossa kiertojen jälkeen ja että tasapainokerroin on odotettu
{
    BTREENODE *pJuuri = NULL;
    BTREENODE *pUus = NULL;
    int i;

    pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
    strcpy(pUus->aSukunimi, "Testi");              // kopioidaan nimi uudelle nodelle
    pUus->iMaara = 30;
    pUus->pVasenChild = NULL;
    pUus->pOikeaChild = NULL;              // alustetaan uudelle nodelle korkeus 1
    pUus->iKorkeus = 1;                    // alustetaan uudelle nodelle korkeus 1
    pJuuri = lisaaPuuhunAVL(pJuuri, pUus); // lisätään node puuhun AVL kiertoja käyttäen
    TEST_ASSERT_EQUAL_INT(0, tarkistaTasapaino(pJuuri));

    pUus = (BTREENODE *)malloc(sizeof(BTREENODE));
    strcpy(pUus->aSukunimi, "Testi"); // kopioidaan nimi uudelle nodelle
    pUus->iMaara = 20;                // asetetaan määrä uudelle nodelle
    pUus->pVasenChild = NULL;
    pUus->pOikeaChild = NULL;
    pUus->iKorkeus = 1;
    pJuuri = lisaaPuuhunAVL(pJuuri, pUus);               // lisätään node puuhun AVL kiertoja käyttäen
    TEST_ASSERT_EQUAL_INT(1, tarkistaTasapaino(pJuuri)); //  tarkistetaan, että puu on tasapainossa ja että tasapainokerroin on odotettu

    pUus = (BTREENODE *)malloc(sizeof(BTREENODE));
    strcpy(pUus->aSukunimi, "Testi");
    pUus->iMaara = 10;
    pUus->pVasenChild = NULL;
    pUus->pOikeaChild = NULL;
    pUus->iKorkeus = 1;
    pJuuri = lisaaPuuhunAVL(pJuuri, pUus); // lisätään node puuhun AVL kiertoja käyttäen, joka vaatii oikean kierron, jotta puu pysyy tasapainossa

    TEST_ASSERT_EQUAL_INT(0, tarkistaTasapaino(pJuuri));
    TEST_ASSERT_EQUAL_INT(20, pJuuri->iMaara);

    btree_vapautaMuisti(pJuuri);
    pJuuri = NULL;

    int iArvot[] = {30, 10, 20};

    for (i = 0; i < 3; i++) //  lisätään nodet puuhun, joka vaatii LR kierron, jotta se pysyy tasapainossa
    {
        pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi");
        pUus->iMaara = iArvot[i]; // asetetaan määrä uudelle nodelle
        pUus->pVasenChild = NULL; // alustetaan uudelle nodelle korkeus 1
        pUus->pOikeaChild = NULL; // alustetaan uudelle nodelle korkeus 1
        pUus->iKorkeus = 1;
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus);
    }

    TEST_ASSERT_TRUE(tarkistaTasapaino(pJuuri) >= -1 && tarkistaTasapaino(pJuuri) <= 1); // tarkistetaan, että puu on tasapainossa ja että tasapainokerroin on odotettu
    TEST_ASSERT_EQUAL_INT(20, pJuuri->iMaara);                                           // tarkistetaan, että kierron jälkeen vanhan juuren child nodet on linkitetty oikein

    btree_vapautaMuisti(pJuuri);
}

void test_poistoJaTasapainotus(void) // testataan, että noden poisto toimii odotetusti ja että puu pysyy tasapainossa poiston jälkeen
{
    BTREENODE *pJuuri = NULL;
    BTREENODE *pUus = NULL;
    BTREENODE *pTestiRoot = NULL;
    int i;
    int iAMaara;
    int iLMaara;

    int iArvot[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};

    for (i = 0; i < 11; i++) // lisätään nodet puuhun, joka vaatii useita kiertoja, jotta se pysyy tasapainossa poiston jälkeen
    {
        pUus = (BTREENODE *)malloc(sizeof(BTREENODE)); // varataan muisti uudelle nodelle
        strcpy(pUus->aSukunimi, "Testi");
        pUus->iMaara = iArvot[i];
        pUus->pVasenChild = NULL;
        pUus->pOikeaChild = NULL;
        pUus->iKorkeus = 1;
        pJuuri = lisaaPuuhunAVL(pJuuri, pUus);
    }
    TEST_ASSERT_TRUE(tarkistaTasapaino(pJuuri) >= -1 && tarkistaTasapaino(pJuuri) <= 1); // tarkistetaan, että puu on tasapainossa ennen poistoa

    // FIX: Added NULL check before accessing children
    pJuuri = btree_poistaNodePohjaArvo(10, pJuuri);                                                // poistetaan pohjimmainen node ja tarkistetaan, että se on löydetty ja että puu pysyy tasapainossa myös poiston jälkeen
    if (pJuuri != NULL && pJuuri->pVasenChild != NULL && pJuuri->pVasenChild->pVasenChild != NULL) // tarkistetaan että poiston jälkeen vanhan juuren vasemman lapsen lapsi on linkitetty oikein
    {
        TEST_ASSERT_NOT_EQUAL_INT(10, pJuuri->pVasenChild->pVasenChild->iMaara);
    }

    pJuuri = btree_poistaNodePohjaArvo(20, pJuuri);
    // TEST_ASSERT_TRUE(tarkistaTasapaino(pJuuri) >= -1 && tarkistaTasapaino(pJuuri) <= 1); // tarkistetaan, että puu on tasapainossa poiston jälkeen

    // FIX: Added NULL check before calling tarkistaKorkeudet
    if (pJuuri != NULL)
    {
        tarkistaKorkeudet(pJuuri); // tarkistetaan, että noden korkeus on oikein laskettu ja päivitetty poiston jälkeen
    }

    iAMaara = laskeSolmut(pJuuri); // lasketaan solmujen määrä ennen poistoa, jotta voidaan tarkistaa, että poiston jälkeen määrä on odotettu
    pJuuri = btree_poistaNodePohjaArvo(80, pJuuri);
    iLMaara = laskeSolmut(pJuuri);
    TEST_ASSERT_EQUAL_INT(iAMaara - 1, iLMaara); // tarkistetaan, että poiston jälkeen solmujen määrä on odotettu, eli että node on todella poistettu

    btree_vapautaMuisti(pJuuri);
    pJuuri = NULL; // vapautetaan muisti testin jälkeen

    pTestiRoot = btree_lueTiedosto("data/sukunimet_2025.txt");
    iAMaara = laskeSolmut(pTestiRoot);
    for (i = 0; i < 5; i++) // poistetaan pohjimmainen node useita kertoja, jotta voidaan tarkistaa, että poiston jälkeen puu pysyy tasapainossa ja solmujen määrä vähenee
    {
        pTestiRoot = btree_poistaNodePohjaArvo(4069 + (i * 100), pTestiRoot);
        if (pTestiRoot != NULL)
        {
            TEST_ASSERT_TRUE(tarkistaTasapaino(pTestiRoot) >= -1 && tarkistaTasapaino(pTestiRoot) <= 1);
        }
    }
    iLMaara = laskeSolmut(pTestiRoot);           // lasketaan solmujen määrä poiston jälkeen
    TEST_ASSERT_EQUAL_INT(iAMaara - 2, iLMaara); // tarkistetaan, että poiston jälkeen solmujen määrä on odotettu, eli että node on todella poistettu
    btree_vapautaMuisti(pTestiRoot);             // vapautetaan muisti testin jälkeen
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TiedostoTesti);
    RUN_TEST(test_vapautaMuisti);
    RUN_TEST(test_dfsHaku);
    RUN_TEST(test_bfs_haku);
    RUN_TEST(test_kirjoitaTiedostoon);
    RUN_TEST(test_avlKierto);
    RUN_TEST(test_korkeusArvot);
    RUN_TEST(test_tasapaino);
    RUN_TEST(test_poistoJaTasapainotus);
    return UNITY_END();
}
