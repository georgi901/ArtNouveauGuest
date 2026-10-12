/**
 * @file Gallery.cpp
 * @brief Implementation of the Gallery class (Singleton).
 *
 * Contains the implementation methods for managing the art gallery,
 * loading data from JSON files, and managing games.
 */

#include "../headers/Gallery.h"

#include <iostream>

#include "../headers/ArtQuiz.h"
#include "../headers/Artist.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Exceptions.h"
#include "../headers/Painting.h"
#include "../headers/QuickArtLook.h"

// ==================== SINGLETON IMPLEMENTATION ====================
Gallery& Gallery::getInstance() {
    std::cout << "[DEBUG] getInstance() called\n";
    static Gallery instanta("Art Nouveau Gallery", "Art Nouveau", 1895);
    std::cout << "[DEBUG] getInstance() returning\n";
    return instanta;
}

std::shared_ptr<MiniGame> Gallery::findGame(const std::string& game_name) const {
    for (const auto& game : games) {
        if (game->getName() == game_name) {
            return game;
        }
    }
    return nullptr;
}

void Gallery::displayGames() const {
    std::cout << "\n==================== AVAILABLE GAMES ====================\n";
    if (games.empty()) {
        std::cout << "There are no games available.\n";
        return;
    }

    for (size_t i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". " << *games[i] << "\n";
    }
    std::cout << "=============================================================\n";
}

void Gallery::playGame(const std::string& game_name) {
    auto game = findGame(game_name);
    if (!game) {
        throw InvalidGameException(game_name);
    }

    game->displayRules();
    game->initialize();
}

void Gallery::displayArtisticDelightHints() {
    std::cout << "\n=== ARTISTIC DELIGHT HINTS ===\n";

    for (const auto& game : games) {
        if (auto ad = std::dynamic_pointer_cast<ArtisticDelight>(game)) {
            std::cout << "Game: " << ad->getName() << "\n";
            ad->showHint();
        }
    }
}

Gallery::Gallery(const Gallery& other)
    : name(other.name)
    , subject(other.subject)
    , founded_year(other.founded_year)
    , artists(other.artists)
    , paintings(other.paintings)
    , games(other.games) {
    std::cout << "[Copy constructor] Gallery: " << name << "\n";
    std::cout << "[DEBUG] Gallery copy constructor CALLED\n";
}

void swap(Gallery& first, Gallery& second) noexcept {
    using std::swap;
    swap(first.name, second.name);
    swap(first.subject, second.subject);
    swap(first.founded_year, second.founded_year);
    swap(first.artists, second.artists);
    swap(first.paintings, second.paintings);
    swap(first.games, second.games);
}

Gallery& Gallery::operator=(Gallery other) {
    std::cout << "[Copy-and-swap] Gallery operator=\n";
    swap(*this, other);
    return *this;
}

void Gallery::displayArtists() const {
    std::cout << "\n----------------------------- Artist list --------------------------------\n";
    for (const auto& artist : artists) {
        std::cout << "\n---------------------------------------------------------------------------"
                     "----\n";
        std::cout << artist->getName() << " " << artist->getFirstName() << " - "
                  << artist->getTitle() << " (" << artist->getAge() << " years)\n";
    }
}

void Gallery::displayPaintings() const {
    std::cout << "\n----------------------------- Painting list -------------------------------\n";
    for (const auto& painting : paintings) {
        std::cout << "\n---------------------------------------------------------------------------"
                     "----\n";
        auto artist = painting->getArtist();
        std::cout << " - " << painting->getTitle() << " - " << " by "
                  << (artist ? artist->getName() : "Unknown") << " "
                  << (artist ? artist->getFirstName() : "Unknown") << "\n";
    }
}

std::shared_ptr<Artist> Gallery::findArtist(const std::string& searched_name) const {
    for (const auto& artist : artists) {
        std::string full_name = artist->getName() + " " + artist->getFirstName();
        std::string reversed_full_name = artist->getFirstName() + " " + artist->getName();

        if (artist->getName() == searched_name || artist->getFirstName() == searched_name ||
            full_name == searched_name || reversed_full_name == searched_name) {
            return artist;
        }
    }
    return nullptr;
}

std::shared_ptr<Painting> Gallery::findPainting(const std::string& title) const {
    for (const auto& painting : paintings) {
        if (painting->getTitle() == title)
            return painting;
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, const Gallery& g) {
    out << "======================================================================================="
           "=\n";
    out << "\n----------------------------------- GALLERY "
           "---------------------------------------\n";
    out << "Gallery: " << g.name << "\n";
    out << "Subject: " << g.subject << "\n";
    out << "Founded year: " << g.founded_year << "\n";
    out << "======================================================================================="
           "=\n";
    out << "-------------------------------------- ARTISTS "
           "----------------------------------------\n";
    for (const auto& a : g.artists) {
        out << "===========================================================\n";
        out << *a << "\n";
        out << "===========================================================\n";
    }
    out << "======================================================================================="
           "=\n";
    out << "-------------------------------------- PAINTINGS "
           "---------------------------------------\n";
    for (const auto& t : g.paintings) {
        out << "===========================================================\n";
        out << *t << "\n";
        out << "===========================================================\n";
    }
    out << "======================================================================================="
           "=\n";
    return out;
}
