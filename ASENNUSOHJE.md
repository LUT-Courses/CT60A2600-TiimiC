# 📦 Asennusohje

Tämä dokumentti opastaa sinua projektin asentamisesta, kääntämisestä ja käyttämisestä.

---

## 📋 Sisällysluettelo

1. [Johdanto](#johdanto)
2. [Vaatimukset](#vaatimukset)
3. [Pikaopas](#pikaopas)
4. [Kloonaus ja asennus](#kloonaus-ja-asennus)
5. [Rakentaminen](#rakentaminen)
6. [Ohjelman käyttö](#ohjelman-käyttö)
7. [Testit](#testit)
8. [Vianmääritys](#vianmääritys)

---

## 🎯 Johdanto

Tämä C-projekti implementoi kaksi keskeistä tietorakennetta:

### **Linkitetty lista (Doubly Linked List)**
- Kahteen suuntaan linkitetty lista sukunimille ja niiden määrille
- Toiminnot: tiedoston lukeminen/kirjoitus, lajittelu (nouseva/laskeva), lisääminen, poistaminen
- Käytetään bubble sort -algoritmia lajitteluun

### **Binääripuu (Binary Search Tree)**
- Tasapainotettu binäärihakupuu
- Toiminnot: tiedoston lukeminen/kirjoitus, syvyyshaku (DFS), leveyhaku (BFS), poistaminen
- Tulee muistista vapautettua ohjelman lopuksi

---

## 🛠 Vaatimukset

Ennen aloitusta varmista, että sinulla on:

- **gcc** tai **clang** kääntäjä
- **GNU Make**
- **git** (kloonaamista varten)
- **(Valinnainen) valgrind** – muistivuotojen tarkistukseen
- **(Valinnainen) doxygen** – dokumentaation luomiseen

### Versioiden tarkistus

```bash
gcc --version
make --version
git --version
valgrind --version
doxygen --version
```

---

## � Pikaopas

Tässä tärkeimmät komennot:

```bash
# 1. Kloonaus (vaatii GitHub-tunnistautumisen)
# Vaihtoehto A: SSH-avain (suositeltu)
git clone --recurse-submodules git@github.com:LUT-Courses/CT60A2600-TiimiC.git

# Vaihtoehto B: HTTPS-tunnistautuminen
git clone --recurse-submodules https://github.com/LUT-Courses/CT60A2600-TiimiC.git 

cd CT60A2600-TiimiC

# 2. Rakentaminen
make

# 3. Ohjelman käyttö
./bin/app

# 4. Testien ajo
make test

# 5. Puhdistaminen
make clean
```

Lisätiedot: Katso [Kloonaus ja asennus](#kloonaus-ja-asennus) tai [Vianmääritys](#vianmääritys).

---

## �💾 Kloonaus ja asennus

### 1. Kloonaa repositorio (sisältää Unityn)

> **Huomio:** Projekti on yksityinen. Sinulla tulee olla GitHub-tunnus ja read-only käyttöoikeus.

#### Vaihtoehto A: SSH-avain (suositeltu)

```bash
git clone --recurse-submodules git@github.com:LUT-Courses/CT60A2600-TiimiC.git
cd CT60A2600-TiimiC
```

#### Vaihtoehto B: HTTPS-tunnistautuminen

```bash
git clone --recurse-submodules https://käyttäjänimi@github.com/LUT-Courses/CT60A2600-TiimiC.git
cd CT60A2600-TiimiC
```

Kun saat kehotuksen, kirjaudu sisään GitHub tunnuksilla tai käytä Personal Access Tokenia


Projekti sisältää Unity-testikirjaston `unity/Unity/`-kansiossa Git-submoduulina, joten `--recursive` lippu kloonauksessa lataa sen automaattisesti.

### 2. Tarkista projektin rakenne

```bash
ls -la
```

Sinulla pitäisi olla:
- `src/` – lähdekoodit ja valikot
- `test/` – yksikkötestit
- `bin/` – rakennuksen tuotos (luodaan automaattisesti 'make' avulla)
- `data/` – datatiedostot
- `doc/` – dokumentaatio (Doxygen-config, architecture.md)
- `makefile` – rakentamisohjeet
- `unity/` – Unity-testikirjasto

---

## 🔨 Rakentaminen

### Rakentamisen eri tavoilla

#### **1. Normaali rakentaminen**

```bash
make
```

Tämä kääntää kaikki tiedostot ja luo `bin/app`-ohjelman.

#### **2. Debug-versio (lisä-informaatiolla)**

```bash
make debug
```

Luo debug-version kanssa `-DDEBUG`-lippua, joka sallii debug-tulosteen.
Luettavat sekä kirjoitettavat tiedostot ovat ennaltamääriteltyjä nopeuttamaan testausta.

#### **3. Puhdistaminen**

```bash
make clean
```

Poistaa kaikki rakennuksen tulokset `bin/`-kansiosta.

---

## ▶️ Ohjelman käyttö

### Ohjelman käynnistäminen

```bash
./bin/app
```

Ohjelma avaa päävalikon, josta voit valita, mitä haluat tehdä.

### Päävalikko

```
1) Linked list
2) Binaaripuu
0) Lopeta
Valintasi:
```

---

## 📝 Linked List -valikko (Valinta 1)

Kun valitset **1**, pääset linkitetyn listan valikkooon:

```
1) Lue tiedosto
2) Kirjoita tiedosto
3) Kirjoita tiedosto (käänteinen järjestys)
4) Tyhjennä tiedosto
5) Lajittele nousevasti (Bubble Sort)
6) Lajittele laskevasti
7) Lisää alkio listaan
8) Poista alkio (nimellä tai arvolla)
0) Takaisin
Valintasi:
```

### Esimerkit

**Lue tiedosto:**
- Valinta: `1`
- Anna tiedoston nimi esim. `data/miehet_2025.txt`

**Kirjoita tiedosto:**
- Valinta: `2`
- Anna tuotetiedoston nimi esim. `output.txt`
- Tiedosto kirjoitetaan alusta loppuun

**Kirjoita tiedosto (käänteinen järjestys):**
- Valinta: `3`
- Anna tuotetiedoston nimi esim. `output_reverse.txt`
- Tiedosto kirjoitetaan lopusta alkuun

**Tyhjennä tiedosto:**
- Valinta: `4`
- Anna tiedoston nimi esim. `output.txt`
- Tiedosto tyhjennetään (poistetaan kaikki sisältö)

**Lajittele nousevasti:**
- Valinta: `5`
- Käytetään bubble sort -algoritmia
- Lista järjestetään aakkosjärjestykseen (A-Ö)

**Lajittele laskevasti:**
- Valinta: `6`
- Käytetään bubble sort -algoritmia
- Lista järjestetään käänteiseen aakkosjärjestykseen (Ö-A)

**Lisää alkio:**
- Valinta: `7`
- Anna kohta (1 = listan alku) esim. 3
- Anna nimi esim. `Pertti`
- Anna määrä esim. `6767`

**Poista alkio:**
- Valinta: `8`
- Anna poistettava nimi tai arvo (numero) esim. `Jaakko` tai `666` 

---

## 🌳 Binääripuu -valikko (Valinta 2)

Kun valitset **2**, pääset binääripuun valikkooon:

```
1) Lue tiedosto
2) Kirjoita tiedosto (DFS - Syvyyshaku)
3) Hae arvolla (DFS)
4) Hae nimellä (BFS - Leveyhaku)
5) Tulosta puu (näytä rakenne)
6) Poista alkio (nimellä tai arvolla)
0) Takaisin
Valintasi:
```

### Esimerkit

**Lue tiedosto:**
- Valinta: `1`
- Anna tiedoston nimi esim. `data/naiset_15.txt`

**Kirjoita tiedosto (DFS - Syvyyshaku):**
- Valinta: `2`
- Anna tuotetiedoston nimi esim. `tree_output.txt`
- Puu kirjoitetaan syvyyshaun järjestyksessä

**Hae arvolla (DFS):**
- Valinta: `3`
- Anna etsittävä numero esim. `42`
- Tulokset kirjoitetaan tiedostoon

**Hae nimellä (BFS):**
- Valinta: `4`
- Anna etsittävä nimi esim. `Virtanen`
- Tulokset kirjoitetaan tiedostoon

**Tulosta puu:**
- Valinta: `5`
- Näyttää puun rakenteen konsolissa (preorder DFS tulostus)

**Poista alkio:**
- Valinta: `6`
- Anna poistettava nimi esim. `Mäkinen` tai arvo esim. `123`

---

## 🧪 Testit

Projektissa on yksikkötestit Unity-testikirjastolla.

### Kaikkien testien ajaminen

```bash
make test
```

Tämä:
1. Käänsi binääripuun testit
2. Käänsi linkitetyn listan testit
3. Ajaa molemmat testit

### Vain binääripuun testit

```bash
make test_binarytree
```

### Vain linkitetyn listan testit

```bash
make test_linkedlist
```

### Testin tulokset

Testit näyttävät:
- Onnistuneet testit
- Epäonnistuneet testit
- Testien yhteenveto

---

## 💾 Muistivuotojen tarkistus

Jos sinulla on **valgrind** asennettuna:

```bash
valgrind --leak-check=full ./bin/app
```

Tämä:
1. Käynnistää ohjelman Valgrind-valvonnan alaisena
2. Tarkistaa muistivuodot
3. Näyttää raportit ohjelman lopuksi

Esimerkki:
```
==12345== ERROR SUMMARY: 0 errors from 0 contexts
==12345== LEAK SUMMARY:
==12345==    definitely lost: 0 bytes in 0 blocks
```

---

## 📊 Dokumentaation luominen

Jos sinulla on **Doxygen** asennettuna:

```bash
make docs
```

Tai suoraan:

```bash
doxygen doc/Doxyfile
```

Dokumentaatio luodaan `doc/html/`-kansioon. Avaa `doc/html/index.html` selaimessa.

---

## 🐛 Vianmääritys

### Ongelma: "gcc: command not found"

**Ratkaisu:** Asenna kääntäjä
```bash
# Ubuntu
sudo apt-get install build-essential

# macOS
brew install gcc
```

### Ongelma: "make: command not found"

**Ratkaisu:** Asenna GNU Make
```bash
# Ubuntu
sudo apt-get install make

# macOS
brew install make


### Ongelma: Testit epäonnistuvat

**Ratkaisu:** Varmista, että Unity-kansio on olemassa
```bash
ls -la unity/Unity/src/
```

Jos kansiota ei ole, kloonaa uudelleen (muista tunnistautua SSH-avaimella tai Personal Access Tokenilla):
```bash
# SSH-avaimella (suositeltu)
git clone --recurse-submodules git@github.com:LUT-Courses/CT60A2600-TiimiC.git

# Tai HTTPS-tunnistautumisella
git clone --recurse-submodules https://käyttäjänimi@github.com/LUT-Courses/CT60A2600-TiimiC.git
```

### Ongelma: "Permission denied (publickey)"

**Ratkaisu:** SSH-avaimesi ei ole konfiguroitu oikein. Lisää SSH avain github tiliisi.

**Testaa yhteys**
```bash
ssh -T git@github.com
```

Pitäisi näyttää: `Hi [käyttäjänimi]! You've successfully authenticated...`

---
