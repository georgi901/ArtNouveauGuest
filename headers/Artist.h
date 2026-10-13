#pragma once

/**
 * @file Artist.h
 * @brief Defines the Artist class for representing artists in the gallery.
 *
 * This file contains the Artist class, which models an artist including personal
 * information, paintings, and the popularity system.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Painting.h"

/**
 * @class Artist
 * @brief Represents an artist in the art gallery.
 *
 * The class manages complete information about an artist:
 * - Personal details (name, nationality, birth/death years)
 * - Associated painting collection
 * - Scoring and title system (Novice, Aspirant, Talented, Expert, Master)
 * - Support for living or deceased artists (with representative data)
 *
 * Uses enable_shared_from_this to allow creating shared_ptr references from
 * inside class methods.
 *
 * @code
 * auto artist = std::make_shared<Artist>("Mucha", "Alfons", "Czech", 0,
 *     1860, 1939, "Art Nouveau");
 * artist->addPainting(painting);
 * std::cout << artist->getTitle(); // "Master"
 * @endcode
 */
class Artist : public std::enable_shared_from_this<Artist> {
private:
    const std::string name;
    const std::string first_name;
    const std::string nationality;
    const int age;
    const int birth_year;
    const int death_year;
    std::string artistic_period;
    std::vector<std::string> artist_images;
    const std::string registration_date;
    std::string username;
    std::string email;
    std::vector<std::string> history;
    std::string representative_person;
    std::string representative_username;
    std::string representative_email;
    std::vector<std::string> representative_history;
    std::vector<std::shared_ptr<Painting>> paintings;
    static std::vector<std::shared_ptr<Artist>> artists_list;

public:
    Artist()
        : name("Unknown")
        , first_name("Unknown")
        , nationality("Unknown")
        , age(0)
        , birth_year(0)
        , death_year(0)
        , artistic_period("Unknown")
        , registration_date("Unknown") {
    }
    Artist(const std::string& name, const std::string& first_name, const std::string& nationality,
           int age, int birth_year, int death_year, const std::string& artistic_period,
           const std::string& registration_date = "", const std::string& username = "",
           const std::string& email = "", const std::vector<std::string>& history = {},
           const std::string& representative_person = "",
           const std::string& representative_username = "",
           const std::string& representative_email = "",
           const std::vector<std::string>& representative_history = {});
    ~Artist() = default;
    static const std::vector<std::shared_ptr<Artist>>& getArtistsList() {
        return artists_list;
    }
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
    static std::ostream& displayArtist(std::ostream& out, const Artist& artist, DetailLevel level);

    void addPainting(const std::shared_ptr<Painting>& painting);
    void addImage(const std::string& image_path) {
        artist_images.push_back(image_path);
    }
    std::shared_ptr<Painting> findPainting(const std::string& title) const;
    const std::vector<std::shared_ptr<Painting>>& getPaintings() const;

    const std::string& getName() const {
        return name;
    }
    const std::string& getFirstName() const {
        return first_name;
    }
    int getAge() const {
        return age;
    }
    int getDeathYear() const {
        return death_year;
    }

    int paintingCount() const;
    int collectedPaintingCount() const;
    int rarePaintingCount() const;
    std::vector<std::shared_ptr<Painting>> getRarePaintings() const;
    std::vector<std::shared_ptr<Painting>> getCollectedPaintings() const;

    static void addToList(const std::shared_ptr<Artist>& artist);

    void displayArtistProfile(DetailLevel nivel) const;
    double calculateStarScore() const;
    const std::string getTitle() const;
    void displayImages(DetailLevel nivel) const;
    const std::string& getArtisticPeriod() const {
        return artistic_period;
    }
};
