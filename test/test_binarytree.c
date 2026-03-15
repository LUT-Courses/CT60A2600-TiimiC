#include <stdio.h>
#include "unity.h"
#include <stdlib.h>
#include "../src/binarytree.h"

void setUp(void) {} // tiedostojen poisto ja muistin tyhjennys ennen testejä
void tearDown(void) {}




void TiedostoTesti(void)
{

    BTREENODE *rootNodeNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNodeNode);                            // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    TEST_ASSERT_EQUAL_STRING("Korhonen", rootNodeNode->aSukunimi); // tarkistetaan, nimen, ja node index
    TEST_ASSERT_EQUAL_INT(21419, rootNodeNode->iMaara);
    rootNodeNode = btree_vapautaMuisti(rootNodeNode); //  tarkistaa että kaikki muisti vapautetaan oikein
}

int rivienMaara(char tiedosto[]) {
    FILE *f = fopen(tiedosto, "r");
    if (f == NULL) {  // tarkistetaan, että tiedosto on luotu onnistuneesti
        return 0;
    }
    int luku = 0;
    char rivi[100]; // apumuuttuja laskemiseen
    while (fgets(rivi, sizeof(rivi), f) != NULL) { // lasketaan rivien määrä
        luku++;
    }
    fclose(f);
    return luku;
}

void test_dfsHaku(void) {
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_dfsHakuKirjoita("dfsTiedosto.txt", 4069, rootNode);
    int Rivi1 = rivienMaara("dfsTiedosto.txt");
    TEST_ASSERT_TRUE(Rivi1 >= 1); // tarkistetaan että tiedostoon on kirjoitettu edes yksi rivi
    btree_dfsHakuKirjoita("dfsTiedosto.txt", 999999, rootNode); // kirjoitetaan tiedostoon dfs mukaan, mutta arvoa ei löydy
    int Rivi2 = rivienMaara("dfsTiedosto.txt"); // tarkistetaan, että jos arvoa ei löydy, niin tiedostoon kirjoitetaan enemmän rivejä
    TEST_ASSERT_TRUE(Rivi2 > Rivi1);
    remove("dfsTiedosto.txt"); // poistetaan tiedosto kun testit teyhty
    btree_vapautaMuisti(rootNode);
}


void test_bfs_haku(void) {
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_bfsHakuNimellaKirjoita("bfsTiedosto.txt", "Eskelinen", rootNode); // kirjoitetaan tiedostoon bfs mukaan
    int rivit1 = rivienMaara("bfsTiedosto.txt"); // tarkistetaan että tiedostoon on kirjoitettu edes yksi rivi
    TEST_ASSERT_TRUE(rivit1 >= 1);
    btree_bfsHakuNimellaKirjoita("bfsTiedosto.txt", "jotain", rootNode); // kirjoitetaan tiedostoon bfs mukaan, mutta nimeä ei löydy
    int rivit2 = rivienMaara("bfsTiedosto.txt");
    TEST_ASSERT_TRUE(rivit2 > rivit1);
    remove("bfsTiedosto.txt");
    btree_vapautaMuisti(rootNode);
}


void test_kirjoitaTiedostoon(void) {
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    btree_kirjoitaTiedostoSyvyys(rootNode, "output.txt"); // kirjoitetaan tiedostoon dfs mukaan
    FILE *f = fopen("output.txt", "r");
    TEST_ASSERT_NOT_NULL(f);  // tarkistetaan, että tiedosto on luotu
    fclose(f);
    int lukumaara = rivienMaara("output.txt");
    TEST_ASSERT_TRUE(lukumaara > 10);   // tarkistetaan, että tiedostoon on kirjoitettu rivejä
    remove("output.txt");
    btree_vapautaMuisti(rootNode); // vapautetaan muisti testin
}


void test_vapautaMuisti(void) {
    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNode); // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    rootNode = btree_vapautaMuisti(rootNode); //  muisti vapautetaan oikein
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TiedostoTesti);
    RUN_TEST(test_vapautaMuisti);
    RUN_TEST(test_dfsHaku);
    RUN_TEST(test_bfs_haku);
    RUN_TEST(test_kirjoitaTiedostoon);
    return UNITY_END();
}
