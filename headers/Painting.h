#pragma once

/**
 * @file Painting.h
 * @brief Defines the Painting class for representing works of art.
 *
 * This file contains the Painting class, which models a painting from the
 * gallery and includes details such as title, technique, artist, colors, and
 * dimensions.
 */

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Artist;

/**
 * @enum DetailLevel
 * @brief Defines the level of detail used when displaying information.
 */
enum class DetailLevel { Minimal, Complete };

/**
 * @class Painting
 * @brief Represents a painting from the art gallery.
 *
 * The class stores complete information about a painting, including:
 * - Title, technique, and creation year
 * - Colors and brushes used
 * - Dimensions and rarity
 * - The link to the artist (weak_ptr to avoid circular references)
 *
 * @code
 * auto painting = std::make_shared<Painting>("Zodiac", "Lithography", 1896,
 *     true, colors, brushes, {60, 80}, artist);
 * painting->displayPaintingZoom(DetailLevel::Complete);
 * @endcode
 */
class Painting {
private:
    std::string title;
    std::string technique;
    int creation_year = 0;
    bool collected = false;
    bool rare = false;
    std::map<std::string, int> colors;
    std::map<std::string, int> brushes;
    std::pair<int, int> dimensions;
    std::weak_ptr<Artist> artist;
    std::vector<std::string> painting_images;

public:
    Painting()
        : title("Unknown")
        , technique("Unknown")
        , creation_year(0)
        , collected(false)
        , rare(false)
        , colors({})
        , brushes({})
        , dimensions({0, 0}) {
    }
    Painting(const std::string& title, const std::string& technique, int creation_year,

             bool rare, const std::map<std::string, int>& colors,
             const std::map<std::string, int>& brushes, const std::pair<int, int>& dimensions,
             const std::shared_ptr<Artist>& artist, bool collected = false);
    friend std::istream& operator>>(std::istream& in, Painting& t) {
        std::cout << "Painting: " << t.title << "\n";
        std::cout << "Number of images: ";
        size_t n;
        in >> n;
        in.ignore();
        t.painting_images.clear();
        for (size_t i = 0; i < n; ++i) {
            std::string img;
            std::cout << "Image " << i + 1 << ": ";
            std::getline(in, img);
            t.painting_images.push_back(img);
        }

        return in;
    }
    friend std::ostream& operator<<(std::ostream& os, const Painting& painting);
    Painting(const Painting& other);
    Painting& operator=(const Painting& other);
    ~Painting() = default;
    static std::ostream& displayPainting(std::ostream& out, const Painting& t, DetailLevel nivel);
    const std::shared_ptr<Artist> getArtist() const {
        return artist.lock();
    }
    void setArtist(const std::shared_ptr<Artist>& art) {
        artist = art;
    }
    bool isCollected() const {
        return collected;
    }
    void setCollected(bool val) {
        collected = val;
    }
    bool isRare() const {
        return rare;
    }
    const std::string& getTitle() const {
        return title;
    }
    const std::string& getTechnique() const {
        return technique;
    }
    int getCreationYear() const {
        return creation_year;
    }
    void displayPaintingZoom(DetailLevel nivel) const;
    void displayImages(DetailLevel nivel) const;
    void addImage(const std::string& image_path) {
        painting_images.push_back(image_path);
    }
    const std::map<std::string, int>& getColors() const {
        return colors;
    }
};
