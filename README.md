# C-project (C)

> **Lyhyt kuvaus**: Linkitetyn listan ja binääripuun toteutus C-kielellä, sisältäen erilaisia toimintoja.

---

## 📁 Projektin rakenne

```
.
├── makefile              # Rakentamisen tavoitteet: build, test, clean, docs, jne.
├── src/                  # C-lähdekoodit ja otsikkotiedostot
│   ├── main.c
│   ├── linkedlist.c
│   ├── linkedlist.h
│   ├── binarytree.c
│   ├── binarytree.h
│   └── valikko/
│       ├── linkedlistValikko.c
│       ├── linkedlistValikko.h
│       ├── binaaripuuValikko.c
│       └── binaaripuuValikko.h
├── bin/                  # Rakentamisen tuotos (binääri + objektitiedostot)
│   └── app
├── test/                 # Yksikkötestit
│   ├── test_binarytree.c
│   └── test_linkedlist.c
├── data/
│   ├── miehet_15.txt
│   ├── miehet_2025.txt
│   ├── naiset_15.txt
│   ├── naiset_2025.txt
│   ├── sukunimet_2025.txt
│   ├── verkko_iso_lyhenteilla.txt
│   ├── verkko_iso.txt
│   ├── verkko_pieni.txt
│   └── readme.md
├── doc/                  # Dokumentaatio (Doxygen-konfiguraatio + luodut HTML, LATEX)
│   ├── html/
│   ├── latex/
│   ├── architecture.md
│   ├── Doxyfile
│   └── readme.md
│
└── unity/
    └── Unity/
```

---

## 🛠 Vaatimukset

- **Kääntäjä**: `gcc` (tai `clang`)
- **Make**: GNU Make
- **(Valinnainen)**: `valgrind`, `doxygen`

Tarkista versiot:

```bash
gcc --version
make --version
```

---

## 🚀 Pika-aloitus (Rakentaminen / Suorittaminen / Testaus)

```bash
# Rakentaminen (luo ./bin/app)
make

# Rakentaminen debug-versiolla (-DDEBUG)
make debug

# Suorittaminen
./bin/app

# Kaikkien yksikkötestien suorittaminen
make test

# Binääripuun testien suorittaminen (Unity)
make test_binarytree

# Linkitetyn listan testien suorittaminen (Unity)
make test_linkedlist

# Muistintarkistus (valgrind)
make memcheck

# Puhdista bin/
make clean
```

---

## 📚 Dokumentaatio

- Doxygen-konfiguraatio: `doc/Doxyfile`

```bash
# Luo dokumentaatio doc/html/-kansioon
make docs

# Tai suoraan:
doxygen doc/Doxyfile
```

---

## 📏 Koodauskäytännöt

- **C-standardi**: C99
- **Käääntäjän liput**: `-Wall -pedantic`

---

## 🧪 Testaus

Projektin yksikkötestit sijaitsevat `test/`-kansiossa.

Aja testit:

```bash
make test               # Kaikki testit
make test_binarytree    # Binaaripuun testit
make test_linkedlist    # Linkedlistin testit
```

Muistivuotojen tarkistus:

```bash
make memcheck   # Ajaa käännetyn ohjelman valgrind työkalun kanssa
```

`test_binarytree` käyttää Unity-testikirjastoa (`unity/Unity/src`).
`test_linkedlist` käyttää Unity-testikirjastoa (`unity/Unity/src`).

---

## 🗂️ Versiohistoria
Tagit
| Versio  | Päivämäärä | Tekijä      | Muutokset                                             |
|---------|------------|-------------|-------------------------------------------------------|
| 0.1.0   | 2026-03-09 | Tiimi-C     | Tehty päävalikko ja linkedlist molempiin suuntiin.    |
| 0.2.0   | 2026-03-16 | Tiimi-C     | Tehty uusi päävalikko ja binaaripuuhaku dfs ja bfs tyylillä. |
| 0.3.0   | 2026-03-21 | Tiimi-C     | Tehty tasapainotettu binääripuu valintaan (2). |
| 0.3.1   | 2026-03-21 | Tiimi-C     | Päivitetty README:n make-komennot, testikomennot ja Doxygen-ohjeistus. |
| 0.4     | 2026-03-30 | Tiimi-C     | Linkitettyyn listaan lisää toimintoja (lajittelu, lisäys, poisto) |

---

## 👤 Tekijät ja kurssi

- **Tekijät**: Eemil Lahti, Henri Penttinen, Sachin Nautiyal
- **Kurssi**: CT60A2600 Ohjelmakehitys C-kielellä
- **Oppilaitos**: LUT-yliopisto

---

testi

## 📄 Lisenssi

> *Yksityinen*

