cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "ArtNouveauGuest")
set(MAIN_EXECUTABLE_NAME ArtNouveauGuest)


project(ArtNouveauGuest VERSION 0.1.0 LANGUAGES CXX)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)
include(FetchContent)

option(BUILD_TESTS "Build automated tests" ON)
option(BUILD_SFML_APP "Build the optional SFML graphical application" OFF)

###############################################################################

# external dependencies with FetchContent
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# NOTE: Also update env vars used for caching in
#         - .github/actions/configure-cmake/action.yml
#         - .github/workflows/cmake.yml
# FetchContent_Declare(
#         SomeLib
#         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

set(ARTNOUVEAUGUEST_CORE_SOURCES
        headers/Artist.h
        src/Artist.cpp
        headers/Painting.h
        src/Painting.cpp
        headers/Gallery.h
        src/Gallery.cpp
        headers/User.h
        src/User.cpp
        headers/Exceptions.h
        src/Exceptions.cpp
        headers/MiniGame.h
        src/MiniGame.cpp
        headers/ArtisticDelight.h
        src/ArtisticDelight.cpp
        headers/QuickArtLook.h
        src/QuickArtLook.cpp
        headers/ArtQuiz.h
        src/ArtQuiz.cpp
        headers/ArtPuzzle.h
        src/ArtPuzzle.cpp
        headers/GameFactory.h
        src/GameFactory.cpp
        headers/JsonDataLoader.h
        src/JsonDataLoader.cpp
        headers/UserProgressStore.h
        src/UserProgressStore.cpp
        headers/Collection.h
        headers/Utils.h
)

add_library(ArtNouveauGuestCore ${ARTNOUVEAUGUEST_CORE_SOURCES})
target_include_directories(ArtNouveauGuestCore PUBLIC headers)

add_executable(ArtNouveauGuest src/main.cpp)
target_sources(ArtNouveauGuest PRIVATE
    src/Application.cpp
    src/ConsoleUI.cpp
    src/GalleryService.cpp
)
target_link_libraries(ArtNouveauGuest PRIVATE ArtNouveauGuestCore)

add_library(project_warnings INTERFACE)
if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4 /permissive-)
else()
    target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wnon-virtual-dtor
        -Woverloaded-virtual
    )
endif()
target_link_libraries(ArtNouveauGuestCore PRIVATE project_warnings)
target_link_libraries(ArtNouveauGuest PRIVATE project_warnings)

if(MSVC)
    target_compile_definitions(ArtNouveauGuestCore PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(ArtNouveauGuest PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(ArtNouveauGuestCore PUBLIC nlohmann_json::nlohmann_json)
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ArtNouveauGuest ArtNouveauGuestCore)
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${MAIN_EXECUTABLE_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ArtNouveauGuest DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES input.txt COPY_TO_DESTINATION TARGET_NAME ArtNouveauGuest)

if(BUILD_TESTS)
    include(CTest)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Catch2)
    add_subdirectory(tests)
endif()

if(BUILD_SFML_APP)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(SFML)

    add_executable(ArtNouveauGuestGui
        src/gui_main.cpp
        src/SfmlApplication.cpp
        src/GalleryService.cpp
        headers/SfmlApplication.h
    )
    target_link_libraries(ArtNouveauGuestGui PRIVATE
        ArtNouveauGuestCore
        project_warnings
        sfml-graphics
        sfml-window
        sfml-system
    )
    set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ArtNouveauGuestGui)
endif()

find_package(Doxygen QUIET)
if(Doxygen_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating HTML documentation with Doxygen"
        VERBATIM
    )
endif()
# copy_files(FILES input.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
