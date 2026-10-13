#pragma once

/**
 * @file Gallery.h
 * @brief Defines the Gallery class using the Singleton design pattern.
 *
 * This file implements the Singleton design pattern for the Gallery class,
 * ensuring that a single gallery instance exists during the application's life.
 * This is one of the two required design patterns for Milestone 3.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Artist.h"
#include "MiniGame.h"
#include "Painting.h"

/**
 * @class Gallery
 * @brief Singleton class for managing the art gallery.
 *
 * Implements the Singleton pattern to ensure there is exactly one gallery
 * instance during the app life cycle. It manages collections of artists,
 * paintings, and mini-games.
 *
 * @note This class can be used in two ways:
 *       1. As a Singleton via getInstance() - recommended for production
 *       2. With normal constructors - useful for testing
 *
 * Benefits of the Singleton pattern for Gallery:
 * - Ensures data consistency (single source of truth)
 * - Global access point for gallery operations
 * - Lazy initialization (created only when needed)
 *
 * @code
 * // Using the Singleton
 * Gallery& gallery = Gallery::getInstance();
 * gallery.addArtist(artist);
 *
 * // Using the normal constructor (for testing)
 * Gallery galleryTest("Gallery Test", "Testing", 2024);
 * @endcode
 */

class Gallery {
private:
    std::string name;
    std::string subject;
    int founded_year = 0;
    std::vector<std::shared_ptr<Artist>> artists;
    std::vector<std::shared_ptr<Painting>> paintings;
    std::vector<std::shared_ptr<MiniGame>> games;

public:
    // ==================== SINGLETON ====================
    /**
     * @brief Gets the singleton instance of the gallery.
     * @return Reference to the unique Gallery instance.
     *
     * Thread-safe implementation using the "Meyer's Singleton" pattern.
     * The instance is created on the first call and destroyed when the program exits.
     */
    static Gallery& getInstance();

    // ==================== CONSTRUCTORS ====================
    Gallery() : founded_year(0) {
    }
    Gallery(const std::string& n, const std::string& subj, int an)
        : name(n), subject(subj), founded_year(an) {
    }
    ~Gallery() = default;

    // ==================== GESTIONARE TABLOURI ====================
    void addPainting(const std::shared_ptr<Painting>& t) {
        paintings.push_back(t);
    }

    void displayArtists() const;
    void displayPaintings() const;
    std::shared_ptr<Artist> findArtist(const std::string& searched_name) const;
    void addArtist(const std::shared_ptr<Artist>& a) {
        artists.push_back(a);
    }
    std::shared_ptr<Painting> findPainting(const std::string& title) const;
    friend std::ostream& operator<<(std::ostream& out, const Gallery& g);
    friend std::istream& operator>>(std::istream& in, Gallery& g) {
        std::cout << "Nume gallery: ";
        in >> g.name;
        std::cout << "Locatie: ";
        in >> g.subject;
        std::cout << "An infiintare: ";
        in >> g.founded_year;
        return in;
    }

    // ==================== GESTIONARE JOCURI ====================
    void addGame(const std::shared_ptr<MiniGame>& game) {
        games.push_back(game);
    }
    std::shared_ptr<MiniGame> findGame(const std::string& game_name) const;
    void displayGames() const;
    void playGame(const std::string& game_name);
    void displayArtisticDelightHints();

    // ==================== GETTERI ====================
    const std::vector<std::shared_ptr<Painting>>& getPaintings() const {
        return paintings;
    }
    const std::vector<std::shared_ptr<Artist>>& getArtists() const {
        return artists;
    }
    const std::vector<std::shared_ptr<MiniGame>>& getGames() const {
        return games;
    }

    // ==================== COPY-AND-SWAP ====================
    Gallery(const Gallery& other);
    Gallery& operator=(Gallery other);
    friend void swap(Gallery& first, Gallery& second) noexcept;
};
