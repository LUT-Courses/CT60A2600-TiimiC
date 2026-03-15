#include <stdio.h>
#include "unity.h"
#include <stdlib.h>
#include "../src/binarytree.h"

void setUp(void) {} // tiedostojen poisto ja muistin tyhjennys ennen testejä
void tearDown(void) {}

void TiedostoTesti(void)
{

    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNode);                            // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    TEST_ASSERT_EQUAL_STRING("Korhonen", rootNode->aSukunimi); // tarkistetaan, nimen, ja node index
    TEST_ASSERT_EQUAL_INT(21419, rootNode->iMaara);

    rootNode = btree_vapautaMuisti(rootNode); //  tarkistaa että kaikki muisti vapautetaan oikein
}

void test_vapautaMuisti(void) {
    BTREENODE *root = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(root); // tarkistetaan, että puu on olemassa, eikä ole tyhjä
    root = btree_vapautaMuisti(root); //  muisti vapautetaan oikein
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TiedostoTesti);
    RUN_TEST(test_vapautaMuisti);
    return UNITY_END();
}
