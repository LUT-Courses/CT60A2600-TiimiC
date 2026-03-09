# C-project (C)

> **Short description**: This project reads and writes a file according to instructions.

---

## 📁 Project Structure

```
.
├── Makefile              # Build targets: build, run, test, clean, etc.
├── src/                  # C source files and headers
│   └── main.c
├── bin/                  # Compiled binaries (output of build)
│   └── app               # Example executable name
├── test/                 # Test sources (e.g., Unity/CMocka) + fixtures
│   ├── test_main.c
│   └── fixtures/
├── data/
│   ├── miehet_2025.txt
│   ├── naiset_2025.txt
│   ├── sukunimet_2025.txt
│   ├── verkko_iso_lyhenteilla.txt
│   ├── verkko_iso.txt
│   ├── verkko_pieni.txt
│   └── README.md         # Describe data sources and formats
└── doc/                  # Documentation (design notes, Doxygen config)
    ├── readme.md
    ├── html/
    └── config
```

> **Notes**
> - `bin/` is generated—usually excluded from version control.
> - Place configuration and design decisions in `doc/`.

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
# Build (creates ./bin/app by default)
make

# Run
./bin/app

# Tests
make test

# Memory check
make memcheck

# Clean
make clean
```

---

## 📚 Documentation

- High-level design: `doc/design.md`
- API docs: generate with Doxygen

```bash
# Generate docs
doxygen doc/Doxyfile
```

---

## 📏 Coding Standards

- **C standard**: C99 
- **Compiler flags**: `-Wall -pedantic`

---

## 🧪 Testing

- Place test sources in `test/`. Choose a C test framework (e.g., Unity, CMocka) or write simple assertion-based tests.
- Document how to run tests here.

```bash
make test
```

---

## 🗂️ Version History

> *(Update this table as you progress. Use semantic versioning if possible.)*

| Version | Date       | Author      | Changes                                               |
|--------:|------------|-------------|-------------------------------------------------------|
| 0.1.0   | 2026-03-01 | Your Name   | Initial scaffold: folders, Makefile, sample main      |

Tag releases:
```bash
git tag -a v0.1.0 -m "Initial scaffold"
git push origin v0.1.0
```

---

## 👤 Author & Course

- **Authors**: Eemil Lahti, Henri Penttinen, Sachin Nautiyal
- **Course**: CT60A2600 Ohjelmakehitys C-kielellä
- **Institution**: LUT University

---

## 📄 License

> *Private*

