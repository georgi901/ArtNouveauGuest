# Baseline Before Refactoring

This document records the behavior of the current working tree before the
planned architecture and UI improvements.

## Current application

- **Artists:** 7 records loaded from `data/artists.json`
- **Paintings:** 8 records loaded from `data/paintings.json`
- **Users:** 1 record loaded from `data/users.json`
- **Mini-games:** 4 (`Artistic Delight`, `Quick Art Look`, `Art Quiz`, and
  `Art Puzzle`)
- **Data source:** JSON files loaded at startup with `nlohmann/json`
- **User interface:** interactive console menu
- **Progress storage:** points, collection state, and game state are kept in
  memory during the current process
- **Build:** CMake executable currently named `oop`
- **Language standard:** C++23 is currently configured in `CMakeLists.txt`

## Verified behavior

The current working tree successfully:

- loads the artist, painting, and user JSON files;
- displays the main menu;
- searches for existing and missing artists;
- searches for paintings;
- adds paintings to the in-memory user collection;
- exercises the custom exception hierarchy;
- lists the four available mini-games;
- builds successfully with the local AppleClang toolchain.

The console menu pauses for an additional Enter key after most non-exit
operations. The golden scenarios include those extra newlines.

## Known limitations before refactoring

- The application is console-only.
- JSON loading, application setup, menu interaction, and test demonstrations
  are tightly coupled in `main.cpp` and `Gallery`.
- User progress is not persisted across application restarts.
- A successful purchase is not directly reachable from a clean start because
  the loaded user begins with zero points; the insufficient-points path is
  available and was verified.
- Automated unit tests are not yet configured.
- The project contains legacy/generated files and naming history that will be
  normalized in the first refactoring stages.
- Some existing local changes were already present before this improvement
  plan began; they are intentionally preserved and are not discarded here.
