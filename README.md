# ArtNouveauGuest

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.26%2B-green.svg)
![Tests](https://img.shields.io/badge/tests-13%20passing-brightgreen.svg)

ArtNouveauGuest is a C++20 interactive art gallery with a console application, an
optional SFML graphical interface, JSON data loading, persistent user progress,
and four art-themed mini-games.

The project was originally created for an Object-Oriented Programming course in
the first year of a Bachelor's degree in Computer Science. It has since been
expanded into a portfolio-oriented application while keeping the original
gallery concept and object-oriented design.

## Description

ArtNouveauGuest is an interactive virtual gallery dedicated exclusively to Art
Nouveau paintings. Each painting can be viewed with details such as its title,
artist, historical period, technique, dimensions, and virtual price in points
when it is available for purchase.

Users can search and filter artworks, earn points by playing mini-games, and
virtually purchase paintings to build a personal collection containing common,
rare, and exceptional works.

## Mini-Games

The application includes four themed mini-games:

- **Artistic Delight** — guess the colors used in a painting. The score is
  based on palette similarity, with bonuses for remaining attempts.
- **Quick Art Look** — match paintings with their artists in a memory-style
  challenge. Difficulty changes the number of pairs and incorrect answers are
  penalized.
- **Art Quiz** — answer questions about artists, years, techniques, and rarity.
  Difficulty changes the number of questions and the penalties.
- **Art Puzzle** — rearrange fragments of a painting in the correct order using
  a limited number of moves.

Each game supports Easy, Medium, and Hard difficulty levels.

## Original OOP Implementation

The original implementation focused on the core object-oriented concepts
required by the course:

- composition between artists, paintings, the gallery, and users;
- parameterized and copy constructors;
- assignment operators and stream output operators;
- smart pointers such as `shared_ptr`, `unique_ptr`, and `weak_ptr`;
- inheritance and polymorphism through the `MiniGame` hierarchy;
- a non-virtual interface for shared game behavior;
- custom exceptions derived from `std::exception`;
- STL containers and algorithms for catalog, collection, and game logic.

The current codebase keeps these concepts but uses English class and file names,
a reusable `ArtNouveauGuestCore` library, and separate console and SFML
application entry points.

## Features

- Artist and painting catalog loaded from JSON.
- Gallery search and artist/painting relationships.
- User points, painting purchases, collections, and persistent progress.
- Versioned save files with temporary writes and backup recovery.
- Console application with deterministic golden scenarios.
- Optional SFML interface with:
  - gallery and painting details;
  - personal collection;
  - Quick Art Look;
  - Art Quiz;
  - Artistic Delight;
  - Art Puzzle.
- Custom exception hierarchy for data, gallery, purchase, and game errors.
- Polymorphic mini-game architecture based on `MiniGame`.
- Catch2 unit and integration tests.
- CMake-based builds with optional sanitizers and static-analysis workflows.

## Requirements

- CMake 3.26 or newer.
- A C++20 compiler:
  - AppleClang or Clang;
  - GCC;
  - MSVC.
- Internet access for the first configure step, because CMake fetches
  `nlohmann/json`, Catch2, and optionally SFML.

## Build and run the console application

From the repository root:

```bash
cmake -S . -B build-clean \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBUILD_TESTS=ON \
  -DBUILD_SFML_APP=OFF
cmake --build build-clean --parallel 2
./build-clean/ArtNouveauGuest
```

The application expects the `data` directory relative to the working directory.
Running the executable from `build-clean` or using the path above from the
repository root works because CMake copies the data files into the build tree.

To run a scripted console scenario:

```bash
./build-clean/ArtNouveauGuest < input.txt
```

## Build and run the SFML application

```bash
cmake -S . -B build-sfml \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBUILD_TESTS=OFF \
  -DBUILD_SFML_APP=ON
cmake --build build-sfml --parallel 2
./build-sfml/ArtNouveauGuestGui
```

The GUI uses a logical 1280x720 view with resize-aware letterboxing. Keyboard
controls are shown on each screen. `Escape` returns to the previous menu or
closes the application from the main menu.

## Run tests

Run the complete automated suite with:

```bash
ctest --test-dir build-clean --output-on-failure
```

The suite currently covers:

- domain relationships and collections;
- points, purchases, and exceptions;
- JSON loading and invalid-file handling;
- progress persistence and backup recovery;
- game factory behavior;
- all four mini-game contracts;
- deterministic console golden scenarios.

The same workflow can be run with CMake presets:

```bash
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
```

## Project structure

```text
.
├── assets/                  # Credits and optional runtime assets
├── data/                    # Artists, paintings, and users JSON files
├── docs/                    # Baseline, decisions, and generated Doxygen output
├── headers/                 # Public domain, service, and UI headers
├── scripts/                 # Build, analysis, and runtime helper scripts
├── src/                     # Console, GUI, domain, and infrastructure sources
├── tests/                   # Catch2 tests and golden scenarios
├── CMakeLists.txt
├── CMakePresets.json
├── Doxyfile
└── CHANGELOG.md
```

The reusable `ArtNouveauGuestCore` library contains domain models, games, JSON
loading, and persistence. The console and SFML executables compose that core
through separate application entry points.

## Dataset and Main Menu

The bundled dataset contains artists, paintings, and users in JSON format. The
console application provides menu actions for:

```text
Display all artists and paintings
Search artists and paintings with minimal or full details
Display the gallery and artist statistics
Inspect rare paintings and user collections
Display available games and play a selected game
Run domain and exception demonstrations
Exit
```

The exact menu text and available actions are maintained by the application, so
this section describes the functionality rather than relying on fixed menu
numbering.

## Technologies

- **C++20**
- **CMake 3.26+**
- **nlohmann/json** for JSON parsing
- **Catch2** for automated tests
- **SFML 2.6+** for the optional graphical interface
- **STL containers and algorithms**
- **Smart pointers** for ownership and lifetime management
- **GitHub Actions**, Cppcheck, Clang-Tidy, sanitizers, and Valgrind

## Progress persistence

The application saves progress to a platform-specific user-data directory.
For isolated manual testing, override the location:

```bash
ARTNOUVEAU_SAVE_PATH="$PWD/manual-progress.json" \
  ./build-clean/ArtNouveauGuest
```

The save format contains a schema version, points, and collected painting
titles. Writes use a temporary file and preserve the previous valid save as a
`.bak` backup.

## Quality checks

The GitHub Actions workflow runs builds and tests across supported compilers and
operating systems. It also includes Cppcheck, Clang-Tidy, sanitizers, and
Valgrind jobs where supported.

Useful local checks:

```bash
git diff --check
clang-format -i headers/*.h src/*.cpp tests/*.cpp
```

## Documentation

Generate the current HTML documentation with:

```bash
doxygen Doxyfile
```

The generated site is written below `docs/html`. Generated documentation is
ignored by Git and should be regenerated from the current source when needed.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE).

## Roadmap

- [x] **SFML integration** with gallery, collection, details, and menus
- [x] **Visual mini-games** for all four game types
- [x] **Save/load system** with versioned files and backup recovery
- [x] **Code modernization** with a reusable core library and C++20
- [x] **Automated quality checks** and cross-platform CI
- [ ] **Expanded dataset** with more artists, paintings, and art movements
- [ ] **Further UI polish** and additional accessibility improvements

## Resources

- [nlohmann/json](https://github.com/nlohmann/json) — JSON library for C++
- [Catch2](https://github.com/catchorg/Catch2) — testing framework
- [SFML](https://www.sfml-dev.org/) — multimedia library
- [cppreference.com](https://en.cppreference.com/) — C++ reference documentation
