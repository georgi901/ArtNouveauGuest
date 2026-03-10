# ArtNouveauGuest 🖼️

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-Build-green.svg)
![OOP](https://img.shields.io/badge/OOP-Project-orange.svg)

---

## Description

**ArtNouveauGuest** is an interactive virtual gallery application dedicated exclusively to Art Nouveau paintings. The app combines artistic exploration with interactive mini-games and strategy elements.

Each painting in the gallery can be viewed with full details, including the title, artist, historical period, technique used, and virtual price in points (if the work is available for purchase). Users can explore artworks individually, using zoom and detail viewing options to better understand the composition of each piece.

The gallery provides advanced filtering and search features, allowing users to select artworks by artist, theme, technique, or point value. A core element of the application is the **points and collecting system** — users earn points by participating in interactive mini-games and completing challenges. These points can be used to virtually purchase paintings, building a personal collection that may include both common works and rare or exceptional pieces.

This project was completed as part of the **Object-Oriented Programming** course in the **first year** of my **Bachelor's degree in Computer Science**.

---

## Mini-Games

The application includes four themed mini-games:

- **"Artistic Delight"** — the user guesses the colors used in the original painting, trying to recreate the artist's color palette. Progress is evaluated through a similarity score, and bonuses are awarded for remaining attempts.
- **"Quick Art Look"** — inspired by memory games, it challenges the user to correctly match paintings with their artists. The number of pairs varies by difficulty, and wrong answers lead to penalties.
- **"Art Quiz"** — tests the user's art knowledge through varied questions: who painted a certain work, what year it was made, what technique was used, or whether the painting is considered rare. Difficulty affects the number of questions and penalties for wrong answers.
- **"Art Puzzle"** — challenges the user to rearrange fragments of a famous painting in the correct order. With a limited number of available moves, the player must think strategically to maximize their score, earning bonuses for unused moves.

Each mini-game offers three difficulty levels — Easy, Medium, and Hard — which influence the complexity of the challenges and the maximum achievable score.

---

## Phase 1 — Core System

The first phase focused on building the core system: managing artists, paintings, and user collections within the gallery.

### Features

**Artist System**
- Management of classic (deceased) and contemporary (living) artists
- Full information: name, nationality, artistic period, years of life
- Differentiated system: living artists have their own account (username, email, history); deceased artists are represented by a designated person
- **Automatic popularity calculation**: score from 0–5 stars based on collected and rare paintings
- **Title attribution**: Novice → Aspirant → Talented → Expert → Master
- Image gallery and two display modes (minimal / full)

**Painting Catalog**
- Full details: title, technique, year, dimensions
- Technical painting info: colors used and brush types
- Status: collected / uncollected, rare / common
- Image gallery with zoom feature
- Link to the creator artist

**Gallery**
- Complete management of artists and artworks
- Search functions (artist by name, painting by title)
- Full collection display

**Collecting System**
- User profile with personal collection
- Add paintings to collection (automatically marks as "collected")
- Automatic activity history
- Full collection viewer

### Technical Details

- **4 classes with composition**: Artist, Painting, Gallery, User
- **Parameterized constructors** for all classes
- Copy constructor, `operator=`, and destructor for the Painting class
- `operator<<` for all classes
- **Complex functionality**: popularity calculation, title attribution system, differentiated display (minimal / full)
- **Interactive menu** with 11 options
- **Smart pointers**: `shared_ptr`, `weak_ptr` for memory management
- Input file: `tastatura.txt`

### Testing

**Option 11** in the menu tests: copy constructor, assignment operator, and destructor. Expected output includes debug messages for each function called.

---

## Phase 2 — Mini-Games, Inheritance & Exceptions

The second phase extended the application with an interactive mini-game system based on inheritance and polymorphism, added custom exception handling, and JSON data loading.

### Class Hierarchy

**MiniJoc** (abstract base class)
- Common attributes: name, description, difficulty, points earned / max
- Pure virtual functions for game-specific behavior
- Non-virtual interface (NVI) for centralized control
- Static members: `total_jocuri_jucate`, `total_puncte_acordate`

**ArtisticDelight** — color guessing game
- User guesses colors used in the original painting
- Similarity score evaluation with the original palette
- Hint system (first letter of the color)
- Bonus for remaining attempts

**QuickArtLook** — painting-artist matching game
- Match paintings with the correct artists
- Variable number of pairs by difficulty (3 / 5 / 8)
- Penalties for wrong answers

**ArtQuiz** — art knowledge quiz
- Auto-generated questions: artist, year, technique, rarity
- Variable number of questions (5 / 8 / 12 by difficulty)
- Case-insensitive answer checking

**ArtPuzzle** — painting fragment puzzle (added in final commit)
- Rearrange fragments in the correct order
- Limited number of moves (6 / 15 / 25)
- Bonus for unused moves

### Custom Exception Hierarchy

Derived from `std::exception`:

- **GalerieException** (base class)
- **PuncteInsuficienteException** — when the user doesn't have enough points for a purchase
- **TablouIndisponibilException** — when the painting doesn't exist or isn't available
- **JocInvalidException** — when the requested game doesn't exist
- **IncarcareDataException** — errors when reading JSON files

### JSON Data Loading

- Files: `artisti.json`, `tablouri.json`, `utilizatori.json`
- nlohmann/json library integrated via CMake FetchContent
- Parse errors handled with custom exceptions

### Extended Points System

- Users accumulate points from mini-games
- `cumparaTablou()` function with point checking (throws exception if insufficient)
- Points displayed in user profile

### Technical Details

- **Inheritance**: 1 base class (`MiniJoc`) + 4 derived classes
- **Pure virtual functions**: `initializeaza_implementare()`, `calculeaza_puncte_implementare()`, `afiseaza_reguli_implementare()`, `clone()`, `getTipJoc()`
- **Non-Virtual Interface**: public non-virtual functions call protected virtual functions
- **Base class pointer**: `Galerie` contains `vector<shared_ptr<MiniJoc>>`
- **Polymorphic calls**: `joc->initializeaza()`, `joc->calculeazaPuncte()` through base pointer
- **Copy-and-swap**: implemented in the `Galerie` class
- **dynamic_cast**: `std::dynamic_pointer_cast<ArtisticDelight>` for type-specific functionality
- **Smart pointers**: `shared_ptr`, `unique_ptr`
- **Static members**: `MiniJoc::total_jocuri_jucate`, `MiniJoc::total_puncte_acordate`
- **Custom exceptions**: own hierarchy with 4 specific classes
- **STL**: `vector`, `map`, `string`, `algorithm`
- **Final commit**: `ArtPuzzle` class added without modifying existing code

### Testing

- **Option 12** — Test exceptions
- **Option 13** — Display available games
- **Option 14** — Play a game (interactive)
- **Option 15** — Test MiniJoc + dynamic_cast + copy-and-swap + polymorphism

---

## Project Structure

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

The gallery contains:

- **7 artists**: Mucha, Klimt, Beardsley, Lalique (classic) + 3 contemporary
- **8 paintings**: famous works (Zodiac, The Kiss, Salome) + modern pieces
- **4 mini-games**: Artistic Delight, Quick Art Look, Art Quiz, Art Puzzle

## Main Menu

```
========================================
       ART GALLERY — MAIN MENU
========================================
1.  Display all artists
2.  Display all paintings
3.  Search artist (minimal profile)
4.  Search artist (full profile)
5.  Search painting (minimal details)
6.  Search painting (full details)
7.  Display full gallery
8.  Test user and collection
9.  Display artist statistics
10. Rare paintings by an artist
11. Test requirements (Painting)
12. Test exceptions
13. Display available games
14. Play a game
15. Test MiniJoc + dynamic_cast + Copy and Swap
0.  Exit
========================================
```

## Build & Run

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --parallel 6
./build/oop
```

## Technologies

- **C++17**
- **nlohmann/json** for JSON parsing
- **Smart Pointers** (`shared_ptr`, `unique_ptr`, `weak_ptr`)
- **STL** (`vector`, `map`, `string`, `algorithm`)
- **CMake** build system

## Resources

- [nlohmann/json](https://github.com/nlohmann/json) — JSON library for C++
- [cppreference.com](https://en.cppreference.com/) — C++ reference documentation

---

> **⚠️ Note:** This project is currently in active development. The current version is a baseline implementation focused on core OOP concepts (composition, inheritance, polymorphism, exceptions). The codebase is functional but not yet optimized — expect refactoring, performance improvements, and new features in upcoming updates.

## Roadmap

- [ ] **SFML integration** — replace the text-based interface with a graphical UI (rendering paintings, animated transitions, clickable menus)
- [ ] **Visual mini-games** — reimagine the mini-games with actual graphics (drag-and-drop puzzle, color picker, visual memory cards)
- [ ] **Expanded dataset** — more artists, paintings, and art movements beyond Art Nouveau
- [ ] **Save / Load system** — persistent user progress and collections across sessions
- [ ] **Code optimization** — refactor repetitive logic, improve memory management, and clean up the architecture
- [ ] **Design patterns** — integrate patterns such as Factory, Observer, or Strategy for cleaner extensibility
