#!/usr/bin/bash

cppcheck --enable=all \
    --inline-suppr \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=useStlAlgorithm \
    --suppress="unknownMacro:tests/*" \
    --suppress="unusedFunction:src/ArtPuzzle.cpp" \
    --suppress="unusedFunction:src/ArtQuiz.cpp" \
    --suppress="unusedFunction:src/QuickArtLook.cpp" \
    --suppress="unusedFunction:tests/SmokeTests.cpp" \
    --check-level=exhaustive \
    --error-exitcode=1
