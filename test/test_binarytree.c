#include <stdio.h>
#include "unity.h"
#include "../src/binarytree.h"

void setUp(void) {} // tiedostojen poisto ja muistin tyhjennys ennen testejä
void tearDown(void) {}

void TiedostoTesti(void)
{

    BTREENODE *rootNode = btree_lueTiedosto("data/sukunimet_2025.txt");
    TEST_ASSERT_NOT_NULL(rootNode);                            // tarkistetaan, että puu on luettu
    TEST_ASSERT_EQUAL_STRING("Korhonen", rootNode->aSukunimi); // tarkistetaan, nimen, ja node arvon
    TEST_ASSERT_EQUAL_INT(21419, rootNode->iMaara);

    rootNode = btree_vapautaMuisti(rootNode); //  tarkistaa että kaikki muisti vapautetaan oikein
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TiedostoTesti);
    return UNITY_END();
}