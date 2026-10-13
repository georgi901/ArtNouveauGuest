# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Changed

- Started the staged architecture and quality improvement process.
- Extracted the reusable application code into `ArtNouveauGuestCore`.
- Added an optional Catch2 test target and CTest integration.
- Registered the existing golden console scenarios as a CTest regression test.
- Extracted JSON loading into `JsonDataLoader` and normalized malformed-data
  failures to `DataLoadingException`.
- Extracted console orchestration into `Application`, `ConsoleUI`, and
  `GalleryService`, leaving a minimal executable entry point.
- Added versioned user-progress persistence with atomic writes, backups, and
  `ARTNOUVEAU_SAVE_PATH` override support.
- Added the optional SFML application foundation with resize-aware letterboxing
  and a separate GUI executable.
- Added SFML screens for the gallery, collection, painting details, and all four
  mini-games.
- Added keyboard navigation, feedback, progress indicators, and explicit GUI
  error reporting.
- Improved the SFML layout so the complete menu and gallery fit inside the
  logical 1280x720 view.
- Added CMake presets for console/test and SFML development workflows.
- Enabled pull-request CI and registered CTest execution in the build job.
- Added current-source Doxygen generation and removed the stale `main.cpp`
  input entry.
- Translated the remaining painting techniques, colors, and brush labels in the
  bundled JSON dataset to English.
- Replaced the legacy README with documentation for the current architecture,
  build commands, tests, GUI, persistence, and quality checks.
