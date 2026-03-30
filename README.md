# C-project (C)

> **Short description**: This project reads and writes a file according to instructions.

---

## 📁 Project Structure

```
.
├── makefile              # Build targets: build, test, clean, docs, etc.
├── src/                  # C source files and headers
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
├── bin/                  # Build output (binary + object files)
│   └── app
├── test/                 # Unit tests
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
├── doc/                  # Documentation (Doxygen config + generated HTML, LATEX)
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

## 🛠 Prerequisites

- **Compiler**: `gcc` (or `clang`)
- **Make**: GNU Make
- **(Optional)**: `valgrind`, `doxygen`

Check versions:

```bash
gcc --version
make --version
```

---

## 🚀 Quick Start (Build / Run / Test)

```bash
# Build (creates ./bin/app)
make

# Build debug version (-DDEBUG)
make debug

# Run
./bin/app

# Run all unit tests
make tests

# Run binary tree tests (Unity)
make test_binarytree

# Run linkedlist tree tests (Unity)
make test_linkedlist

# Memory check (valgrind)
make memcheck

# Clean bin/
make clean
```

---

## 📚 Documentation

- Doxygen config: `doc/Doxyfile`

```bash
# Generate docs to doc/html/
make docs

# Or directly:
doxygen doc/Doxyfile
```

---

## 📏 Coding Standards

- **C standard**: C99 
- **Compiler flags**: `-Wall -pedantic`

---

## 🧪 Testing

Projektin yksikkötestit sijaitsevat `test/`-kansiossa.

Aja testit:

```bash
make test
make test_binarytree
make test_linkedlist
```

Muistivuotojen tarkistus:

```bash
make memcheck
```

`test_binarytree` käyttää Unity-testikirjastoa (`unity/Unity/src`).
`test_linkedlist` käyttää Unity-testikirjastoa (`unity/Unity/src`).

---

## 🗂️ Version History

| Version | Date       | Author      | Changes                                               |
|--------:|------------|-------------|-------------------------------------------------------|
| 0.1.0   | 2026-03-09 | Tiimi-C     | Tehty päävalikko ja linkedlist molempiin suuntiin.    |
| 0.2.0   | 2026-03-16 | Tiimi-C     | Tehty uusi päävalikko ja binaaripuuhaku dfs ja bfs tyylillä. |
| 0.3.0   | 2026-03-21 | Tiimi-C     | Tehty tasapainotettu binääripuu valintaan (2). |
| 0.3.1   | 2026-03-21 | Tiimi-C     | Päivitetty README:n make-komennot, testikomennot ja Doxygen-ohjeistus. |
| 0.4     | 2026-03-30 | Tiimi-C     | Linkitettyyn listaan lisää toimintoja (lajittelu, lisäys, poisto) |
Tag releases:
```bash
git tag -a v0.1.0 -m "Implemented the main menu and linked list"
git push origin v0.1.0
git tag -a v0.2.0 -m "New main menu and binary tree search"
git push origin v0.2.0
git tag -a v0.3.0 -m "Balanced binary tree option"
git push origin v0.3.0
git tag -a v0.3.1 -m "README, make targets, and Doxygen docs update"
git push origin v0.3.1
```

---

## 👤 Author & Course

- **Authors**: Eemil Lahti, Henri Penttinen, Sachin Nautiyal
- **Course**: CT60A2600 Ohjelmakehitys C-kielellä
- **Institution**: LUT University

---

## 📄 License

> *Private*

