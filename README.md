---
# ArtNouveauGuest 🖼️
---
## Descriere: 
## ArtNouveauGuest

**ArtNouveauGuest** este o aplicație interactivă de tip galerie virtuală, dedicată exclusiv tablourilor în stilul Art Nouveau. Aplicația combină explorarea artistică cu mini-jocuri interactive și elemente de strategie.

## Descriere

Fiecare tablou din galerie poate fi vizualizat cu detalii complete, incluzând titlul, artistul, perioada istorică, tehnica folosită și prețul virtual în puncte, dacă opera este disponibilă pentru achiziție. Utilizatorul poate explora operele în mod individual, folosind opțiuni de zoom și vizualizare a detaliilor, pentru a înțelege mai bine compoziția fiecărei lucrări.

Galeria oferă funcționalități de filtrare și căutare avansată, permițând utilizatorului să selecteze operele după artist, temă, tehnică sau valoarea în puncte. Un element central al aplicației este sistemul de puncte și colecționare. Utilizatorul acumulează puncte prin participarea la mini-jocuri interactive și finalizarea provocărilor. Aceste puncte permit achiziționarea virtuală a tablourilor, construind astfel o colecție personală, care poate include atât opere comune, cât și tablouri rare sau deosebite.

### Mini-Jocuri

Aplicația include patru mini-jocuri tematice:

- **„Artistic Delight"** — utilizatorul ghicește culorile folosite în tabloul original, încercând să recreeze paleta de culori a artistului. Progresul este evaluat printr-un scor de asemănare, iar bonusurile sunt acordate pentru încercările rămase.

- **„Quick Art Look"** — inspirat de jocurile de memorie, provoacă utilizatorul să asocieze corect tablourile cu artiștii lor. Numărul de perechi variază în funcție de dificultate, iar răspunsurile greșite duc la penalizări.

- **„Art Quiz"** — testează cunoștințele utilizatorului despre artă prin întrebări variate: cine a pictat un anumit tablou, în ce an a fost realizat, ce tehnică a fost folosită sau dacă tabloul este considerat rar. Dificultatea influențează numărul de întrebări și penalizările pentru răspunsurile greșite.

- **„Art Puzzle"** — provoacă utilizatorul să rearanjeze fragmentele unui tablou celebru în ordinea corectă. Cu un număr limitat de mutări disponibile, jucătorul trebuie să gândească strategic pentru a maximiza punctajul, primind bonusuri pentru mutările nefolosite.

Fiecare mini-joc oferă trei niveluri de dificultate — Ușor, Mediu și Greu — care influențează complexitatea provocărilor și punctajul maxim obtenabil.

---
## Implementare Tema 1
---
Pentru **Tema 1** am realizat sistemul de bază al aplicației, concentrându-mă pe gestionarea artiștilor, tablourilor și colecțiilor utilizatorilor în galerie.

### Funcționalități Implementate

#### **Sistem de Artiști**
- Gestionare artiști clasici (decedați) și contemporani (în viață)
- Informații complete: nume, naționalitate, perioada artistică, ani de viață
- Sistem diferențiat:
  - Artiști în viață au cont propriu (username, email, istoric)
  - Artiști decedați sunt reprezentați de o persoană desemnată
- **Calcul automat popularitate**: scor 0-5 stele bazat pe tablouri colecționate și rare
- **Atribuire titluri**: Novice → Aspirant → Talentat → Expert → Maestru
- Galerie de imagini și afișare în două moduri (minimal/complet)

#### **Catalog de Tablouri**
- Detalii complete: titlu, tehnică, an realizare, dimensiuni
- Informații tehnice pentru pictare: culori folosite și tipuri de pensule
- Status: colecționat/necolecționat, rar/comun
- Galerie de imagini cu funcție "zoom"
- Legătură cu artistul creator

#### **Galeria**
- Management complet al artiștilor și operelor
- Funcții de căutare (artist după nume, tablou după titlu)
- Afișare completă a colecției

#### **Sistem de Colecționare**
- Profil utilizator cu colecție personală
- Adăugare tablouri în colecție (marchează automat ca "colecționat")
- Istoric activități automat
- Vizualizare colecție completă

### Implementări Tehnice

#### Cerințe Tema 1: 

- **4 clase cu compunere**: Artist, Tablou, Galerie, Utilizator
- **Constructori cu parametri** pentru toate clasele

- **Cerințe**:
  - Constructor de copiere
  - Operator= pentru clasa Tablou
  - Destructor 

- **operator<<** pentru toate clasele

- **Funcționalități complexe**:
  - Calcul popularitate artiști
  - Sistem atribuire titluri bazat pe scor
  - Afișare diferențiată (minimal/complet)

- **Scenariu complet** cu meniu interactiv (11 opțiuni)

- **Smart pointers**: `shared_ptr`, `weak_ptr` pentru gestionare memorie

- **Fișiere**: `tastatura.txt`

### Testare

**Opțiunea 11** din meniu testează cerințele:
- Constructor de copiere
- Operator de atribuire
- Destructor

Output așteptat include mesaje debug pentru fiecare funcție apelată.

###  Structura Proiectului
```
ArtNouveauGuest/
├── headers/          # Fișiere .h
├── src/              # Fișiere .cpp
├── main.cpp          # Meniu și scenarii de utilizare
└──  tastatura.txt     # Input pentru testare automată
```

### Dataset Inițial

Galeria conține:
- **7 artiști**: Mucha, Klimt, Beardsley, Lalique (clasici) + 3 contemporani
- **8 tablouri**: opere celebre (Zodiac, Sărutul, Salome) + lucrări moderne

---
## Implementare Tema 2
---

Pentru **Tema 2** am extins aplicația cu un sistem de mini-jocuri interactive bazat pe moștenire și polimorfism, adăugând gestionarea excepțiilor și încărcarea datelor din fișiere JSON.

### Funcționalități Implementate

#### Ierarhie Mini-Jocuri

Am creat o ierarhie de clase pentru mini-jocuri cu clasa de bază abstractă `MiniJoc` și 4 clase derivate:

**MiniJoc** (clasă de bază abstractă)
- Atribute comune: nume, descriere, dificultate, puncte obținute/maxime
- Funcții virtuale pure pentru comportament specific fiecărui joc
- Funcții non-virtuale (Non-Virtual Interface) pentru control centralizat
- Membri statici: `total_jocuri_jucate`, `total_puncte_acordate`

**ArtisticDelight** — joc de ghicit culori
- Utilizatorul ghicește culorile folosite în tabloul original
- Evaluare scor de asemănare cu paleta originală
- Sistem de sugestii (prima literă a culorii)
- Bonus pentru încercări rămase

**QuickArtLook** — joc de asociere tablou-artist
- Asociere tablouri cu artiștii corecți
- Număr de perechi variabil în funcție de dificultate (3/5/8)
- Penalizări pentru răspunsuri greșite

**ArtQuiz** — quiz despre artă
- Întrebări generate automat: artist, an, tehnică, raritate
- Număr de întrebări variabil (5/8/12 în funcție de dificultate)
- Verificare răspunsuri case-insensitive

**ArtPuzzle** — puzzle cu fragmente de tablou (commit final)
- Rearanjare fragmente în ordinea corectă
- Număr limitat de mutări (6/15/25)
- Bonus pentru mutări nefolosite

#### Sistem de Excepții

Ierarhie proprie de excepții derivată din `std::exception`:

- **GalerieException** (clasă de bază)
- **PuncteInsuficienteException** — când utilizatorul nu are destule puncte pentru achiziție
- **TablouIndisponibilException** — când tabloul nu există sau nu e disponibil
- **JocInvalidException** — când jocul cerut nu există
- **IncarcareDataException** — erori la citirea fișierelor JSON

#### Încărcare Date din JSON

- Fișiere: `artisti.json`, `tablouri.json`, `utilizatori.json`
- Biblioteca nlohmann/json integrată prin CMake FetchContent
- Tratare erori de parsare cu excepții personalizate

#### Sistem de Puncte Extins

- Utilizatorul acumulează puncte din mini-jocuri
- Funcție `cumparaTablou()` cu verificare puncte (aruncă excepție dacă insuficiente)
- Afișare puncte în profil utilizator

### Implementări Tehnice - Tema 2

- **Moșteniri**: 1 clasă de bază (`MiniJoc`) + 4 clase derivate
- **Funcții virtuale pure**:
  - `initializeaza_implementare()` — inițializare specifică fiecărui joc
  - `calculeaza_puncte_implementare()` — calculare puncte specifică temei
  - `afiseaza_reguli_implementare()` — afișare reguli
  - `clone()` — constructor virtual
  - `getTipJoc()` — returnează tipul jocului
- **Non-Virtual Interface**: funcții publice non-virtuale apelează funcții protected virtuale
- **Pointer la clasă de bază**: `Galerie` conține `vector<shared_ptr<MiniJoc>>`
- **Apel polimorfic**: `joc->initializeaza()`, `joc->calculeazaPuncte()` prin pointer de bază
- **Copy-and-swap**: implementat în clasa `Galerie`
- **dynamic_cast**: `std::dynamic_pointer_cast<ArtisticDelight>` pentru funcționalități specifice
- **Smart pointers**: `shared_ptr`, `unique_ptr` pentru gestionare memorie
- **Membri statici**: `MiniJoc::total_jocuri_jucate`, `MiniJoc::total_puncte_acordate`
- **Excepții**: ierarhie proprie cu 4 clase specifice
- **STL**: `vector`, `map`, `string`, `algorithm`
- **Commit final**: clasa `ArtPuzzle` adăugată fără modificarea codului existent

### Testare Tema 2

- **Opțiunea 12** — Test excepții
- **Opțiunea 13** — Afișează jocuri disponibile
- **Opțiunea 14** — Joacă un joc (interactiv)
- **Opțiunea 15** — Test MiniJoc + dynamic_cast + polimorfism

---

## Structura Proiectului
```
ArtNouveauGuest/
├── headers/
│   ├── Artist.h
│   ├── Tablou.h
│   ├── Galerie.h
│   ├── Utilizator.h
│   ├── MiniJoc.h
│   ├── ArtisticDelight.h
│   ├── QuickArtLook.h
│   ├── ArtQuiz.h
│   ├── ArtPuzzle.h
│   └── Exceptii.h
├── src/
│   ├── Artist.cpp
│   ├── Tablou.cpp
│   ├── Galerie.cpp
│   ├── Utilizator.cpp
│   ├── MiniJoc.cpp
│   ├── ArtisticDelight.cpp
│   ├── QuickArtLook.cpp
│   ├── ArtQuiz.cpp
│   ├── ArtPuzzle.cpp
│   └── Exceptii.cpp
├── data/
│   ├── artisti.json
│   ├── tablouri.json
│   └── utilizatori.json
├── main.cpp
├── CMakeLists.txt
└── README.md
```

## Dataset

Galeria conține:
- **7 artiști**: Mucha, Klimt, Beardsley, Lalique (clasici) + 3 contemporani
- **8 tablouri**: opere celebre (Zodiac, Sărutul, Salome) + lucrări moderne
- **4 mini-jocuri**: Artistic Delight, Quick Art Look, Art Quiz, Art Puzzle

## Meniu Principal
```
========================================
      GALERIE DE ARTĂ - MENIU
========================================
1.  Afișează toți artiștii
2.  Afișează toate tablourile
3.  Caută artist (profil minimal)
4.  Caută artist (profil complet)
5.  Caută tablou (detalii minime)
6.  Caută tablou (detalii complete)
7.  Afișează galeria completă
8.  Testează utilizator și colecție
9.  Afișează statistici artist
10. Tablouri rare ale unui artist
11. Test cerințe (Tablou)
12. Test excepții
13. Afișează jocuri disponibile
14. Joacă un joc
15. Test MiniJoc + dynamic_cast + Copy and Swap
0.  Ieșire
========================================
```

## Compilare și Rulare
```bash
mkdir build
cd build
cmake ..
make
./oop
```

## Tehnologii Utilizate

- **nlohmann/json** pentru parsare JSON
- **Smart Pointers** (shared_ptr, unique_ptr, weak_ptr)
- **STL** (vector, map, string, algorithm)

  ---
## Implementare Tema 3
---

Pentru **Tema 3** am extins aplicația cu design patterns (Singleton, Factory), clase șablon generice și funcții șablon, îmbunătățind arhitectura și reutilizabilitatea codului.

### Funcționalități Implementate

#### Design Patterns

**Singleton Pattern (Galerie)**
- Asigură existența unei singure instanțe a galeriei în întreaga aplicație
- Acces global prin `Galerie::getInstance()`
- Implementare thread-safe cu mutex
- Elimină posibilitatea de creare accidentală a mai multor galerii
- Reprezintă "sursa unică de adevăr" pentru toate datele galeriei

**Factory Pattern (JocFactory)**
- Creează instanțe de mini-jocuri fără a cunoaște clasa concretă
- Metodă statică: `JocFactory::creeazaJoc(tipJoc, dificultate)`
- Suportă toate tipurile de jocuri: "ArtisticDelight", "QuickArtLook", "ArtQuiz", "ArtPuzzle"
- Permite adăugarea de jocuri noi fără modificarea codului existent
- Încapsulează logica de instanțiere într-un singur loc

#### Clasă Șablon Generic

**Collection\<T\>** — container generic pentru orice tip de date
- Funcționează cu orice clasă (`Artist`, `Tablou`, `MiniJoc`, etc.)
- Metodă `adauga(T element)` — adaugă elemente în colecție
- Metodă `filtreaza(Predicate pred)` — filtrează după predicate
- Metodă `cautaDupaPredicate(Predicate pred)` — caută primul element ce îndeplinește condiția
- Iteratori pentru parcurgere (`begin()`, `end()`)
- Gestionare internă cu `std::vector<T>`

#### Funcții Șablon (Utils.h)

Set de funcții generice reutilizabile:

**`cautaDupaNume<T>(container, nume)`**
- Caută elemente după nume în orice container
- Returnează pointer către element sau `nullptr`

**`filtreazaElemente<T>(container, predicate)`**
- Filtrează elemente folosind un predicat
- Returnează un nou vector cu elementele filtrate

**`numaraElemente<T>(container, predicate)`**
- Numără elementele care îndeplinesc o condiție
- Returnează `size_t`

**`transforma<T, R>(container, transformer)`**
- Transformă o colecție de tip `T` într-una de tip `R`
- Folosește o funcție de transformare custom

#### Documentație Doxygen

- Comentarii Doxygen complete pentru toate clasele și funcțiile
- Parametri documentați cu `@param`
- Valori returnate specificate cu `@return`
- Descrieri clare ale funcționalităților
- Exemple de utilizare în comentarii
- Generare automată documentație HTML

#### Code Formatting

- Fișier `.clang-format` pentru formatare automată
- Standard C++17
- Indentare consistentă (4 spații)
- Stilul de formatare: LLVM
- Aplicabil pe întreg proiectul

### Implementări Tehnice - Tema 3

- **Singleton Pattern**: implementat cu Meyer's Singleton (thread-safe prin C++11)
- **Factory Pattern**: metodă statică de fabrică cu switch pentru tipuri de jocuri
- **Clasă șablon**: `Collection<T>` cu cel puțin 3 metode template
- **Funcții șablon**: minimum 4 funcții generice în `Utils.h`
- **Documentație Doxygen**: comentarii complete pentru toate clasele și funcțiile publice
- **Code formatter**: configurare `.clang-format` pentru consistență stilistică
- **Smart pointers**: folosire consistentă `shared_ptr`, `unique_ptr`
- **Lambda expressions**: în funcțiile de filtrare și transformare
- **STL algorithms**: `std::find_if`, `std::count_if`, `std::transform`

### Testare Tema 3

**Opțiunea 16** — Test complet Milestone 3

Testează:
- Singleton Pattern (verifică că `getInstance()` returnează aceeași instanță)
- Factory Pattern (creează toate tipurile de jocuri)
- Clasă șablon (testează `Collection<T>` cu tipuri diferite)
- Funcții șablon (testează toate funcțiile din `Utils.h`)

Output așteptat include confirmarea că toate testele au trecut cu succes.

---

## Structura Proiectului (Final - Tema 3)
```
ArtNouveauGuest/
├── headers/
│   ├── Artist.h
│   ├── Tablou.h
│   ├── Galerie.h              # Modificat cu Singleton Pattern
│   ├── Utilizator.h
│   ├── MiniJoc.h
│   ├── ArtisticDelight.h
│   ├── QuickArtLook.h
│   ├── ArtQuiz.h
│   ├── ArtPuzzle.h
│   ├── Exceptii.h
│   ├── Collection.h           # NOU - Clasă șablon
│   ├── Utils.h                # NOU - Funcții șablon
│   └── JocFactory.h           # NOU - Factory Pattern
├── src/
│   ├── Artist.cpp
│   ├── Tablou.cpp
│   ├── Galerie.cpp            # Modificat cu Singleton
│   ├── Utilizator.cpp
│   ├── MiniJoc.cpp
│   ├── ArtisticDelight.cpp
│   ├── QuickArtLook.cpp
│   ├── ArtQuiz.cpp
│   ├── ArtPuzzle.cpp
│   ├── Exceptii.cpp
│   └── JocFactory.cpp         # NOU
├── data/
│   ├── artisti.json
│   ├── tablouri.json
│   └── utilizatori.json
├── .clang-format              # NOU - Configurare formatter
├── Doxyfile                   # NOU - Config Doxygen
├── main.cpp                   # Modificat cu opțiunea 16
├── CMakeLists.txt             # Modificat (adăugat JocFactory.cpp)
└── README.md
```

## Dataset

Galeria conține:
- **7 artiști**: Mucha, Klimt, Beardsley, Lalique (clasici) + 3 contemporani
- **8 tablouri**: opere celebre (Zodiac, Sărutul, Salome) + lucrări moderne
- **4 mini-jocuri**: Artistic Delight, Quick Art Look, Art Quiz, Art Puzzle

## Meniu Principal (Actualizat)
```
========================================
      GALERIE DE ARTĂ - MENIU
========================================
1.  Afișează toți artiștii
2.  Afișează toate tablourile
3.  Caută artist (profil minimal)
4.  Caută artist (profil complet)
5.  Caută tablou (detalii minime)
6.  Caută tablou (detalii complete)
7.  Afișează galeria completă
8.  Testează utilizator și colecție
9.  Afișează statistici artist
10. Tablouri rare ale unui artist
11. Test cerințe (Tablou)
12. Test excepții
13. Afișează jocuri disponibile
14. Joacă un joc
15. Test MiniJoc + dynamic_cast + Copy and Swap
16. Test Milestone 3 (Design Patterns & Templates)
0.  Ieșire
========================================
```

## Compilare și Rulare
```bash
mkdir build
cd build
cmake ..
make
./oop
```

## Tehnologii Utilizate

- **C++17** standard
- **nlohmann/json** pentru parsare JSON
- **Smart Pointers** (shared_ptr, unique_ptr, weak_ptr)
- **STL** (vector, map, string, algorithm)
- **Doxygen** pentru documentație automată
- **clang-format** pentru formatare consistentă

## Versioning

- **v0.1** — Milestone 1: Clase de bază, compunere, smart pointers
- **v0.2** — Milestone 2: Moștenire, polimorfism, excepții, JSON
- **v0.3** — Milestone 3: Design Patterns, Templates, Doxygen

---

## Detalii Proiect:


### Folosiți template-ul corespunzător grupei voastre!

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |
| Tiberiu M | https://github.com/MaximTiberiu/oop-template |
| Marius MC | https://github.com/mcmarius/oop-template     |

### Important!

Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar dacă documentați riguros acest proces.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

Codul din proiect trebuie să poată fi ușor de înțeles și de modificat de către altcineva. Pentru detalii, veniți la ore.

O cerință nu se consideră îndeplinită dacă este realizată doar prin cod generat.

- **Fără cod de umplutură/fără sens!**
- **Fără copy-paste!**
- **Fără variabile globale!**
- **Fără atribute publice!**
- **Pentru T2 și T3, fără date în cod!** Datele vor fi citite din fișier, aveți exemple destule.
- **Obligatoriu** fișiere cu date mai multe din care să citiți, obligatoriu cu biblioteci externe: fișiere (local sau server) sau baze de date
- obligatoriu (TBD) să integrați cel puțin două biblioteci externe pe lângă cele pentru stocare

### Tema 0

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [X] constructori de inițializare cu parametri pentru fiecare clasă
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [X] cât mai multe `const` (unde este cazul) și funcții `private`
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [X] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions
- [X] code review #1 2 proiecte

## Tema 2

#### Cerințe
- [X] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [X] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [X] apelarea constructorului din clasa de bază din constructori din derivate
  - [X] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [X] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [X] smart pointers (recomandat, opțional)
- [X] excepții
  - [X] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [X] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [X] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [X] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [X] minim 75-80% din codul propriu să fie C++
- [X] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [X] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`
- [X] code review #2 2 proiecte

## Tema 3

#### Cerințe
- [X] 2 șabloane de proiectare (design patterns)
- [X] o clasă șablon cu sens; minim **2 instanțieri**
  - [X] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [X] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [X] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`
- [X] code review #3 2 proiecte

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC folosind Git Bash:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Resurse

- adăugați trimiteri **detaliate** către resursele externe care v-au ajutat sau pe care le-ați folosit
