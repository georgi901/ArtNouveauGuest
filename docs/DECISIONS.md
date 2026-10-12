# Architecture Decisions

- Use C++20 as the project language standard because the current source does
  not require a C++23-only feature and C++20 offers broader compiler support.
- Use `ArtNouveauGuest` as the single project and executable name.
- Keep public headers and source files consistently named in English:
  `Artist`, `Painting`, `Gallery`, `User`, `MiniGame`, `GameFactory`, and
  `Exceptions`.
- Standardize headers on `#pragma once` during the naming cleanup.
- Preserve the existing local translation changes as the starting point for
  the improvement plan; do not discard or stash them automatically.
- Extract reusable domain and game code into the `ArtNouveauGuestCore` library
  so the console application and automated tests share the same implementation.
- Use Catch2 v3.5.4 for unit-test infrastructure and register tests through
  CTest, including the existing golden console scenarios.
- Keep JSON parsing in the `JsonDataLoader` infrastructure component rather
  than in `Gallery`, `User`, or the executable composition root.
- Keep console interaction in `ConsoleUI` and application orchestration in
  `Application`, while domain behavior remains in the core library.
- Persist user points and collection titles in a versioned JSON file using an
  environment override, atomic temporary writes, and a backup recovery file.
- Keep the SFML interface as a separate optional `ArtNouveauGuestGui`
  executable, using SFML 2.6.1 and a logical 1280x720 coordinate system.
