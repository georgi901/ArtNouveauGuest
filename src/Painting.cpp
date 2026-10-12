/**
 * @file Painting.cpp
 * @brief Implementation of the Painting class.
 *
 * Contains the implementation methods for displaying and manipulating paintings.
 */

#include "../headers/Painting.h"

#include <iostream>

#include "../headers/Artist.h"

Painting::Painting(const std::string& title_value, const std::string& technique_value,
                   int creation_year_value, bool rare_value,
                   const std::map<std::string, int>& colors_value,
                   const std::map<std::string, int>& brushes_value,
                   const std::pair<int, int>& dimensions_value,
                   const std::shared_ptr<Artist>& artist_value, bool collected_value)
    : title(title_value)
    , technique(technique_value)
    , creation_year(creation_year_value)
    , collected(collected_value)
    , rare(rare_value)
    , colors(colors_value)
    , brushes(brushes_value)
    , dimensions(dimensions_value)
    , artist(artist_value) {
}

Painting::Painting(const Painting& other)
    : title(other.title)
    , technique(other.technique)
    , creation_year(other.creation_year)
    , collected(other.collected)
    , rare(other.rare)
    , colors(other.colors)
    , brushes(other.brushes)
    , dimensions(other.dimensions)
    , artist(other.artist)
    , painting_images(other.painting_images) {
    std::cout << "Copy constructor for Painting called for: " << title << "\n";
}

Painting& Painting::operator=(const Painting& other) {
    std::cout << "Copy assignment operator for Painting called\n";

    title = other.title;
    technique = other.technique;
    creation_year = other.creation_year;
    collected = other.collected;
    rare = other.rare;
    colors = other.colors;
    brushes = other.brushes;
    dimensions = other.dimensions;
    artist = other.artist;
    painting_images = other.painting_images;

    std::cout << "Copy completed for painting: " << title << "\n";

    return *this;
}

void Painting::displayImages(DetailLevel nivel) const {
    if (painting_images.empty()) {
        std::cout << "There are no images for this painting.\n";
        return;
    }

    if (nivel == DetailLevel::Complete) {
        std::cout << "Painting details images:\n";
        for (size_t i = 1; i < painting_images.size(); ++i) {
            std::cout << "  " << painting_images[i] << "\n";
        }
    } else if (nivel >= DetailLevel::Minimal) {
        std::cout << "Painting: " << painting_images[0] << "\n";
    }
}

void Painting::displayPaintingZoom(DetailLevel nivel) const {
    std::cout << "\n------------------- PAINTING: " << title << " ------------------\n";

    if (nivel == DetailLevel::Complete) {
        std::cout << "\n---------------- PAINTING ZOOM " << dimensions.first << "x"
                  << dimensions.second << " cm"
                  << " ----------------\n";
        std::cout << "\nUsed colors:\n";
        for (const auto& [color, count] : colors)
            std::cout << "  • " << color << ": " << count << " tubes\n";

        std::cout << "\nUsed brush types:\n";
        for (const auto& [tip, count] : brushes)
            std::cout << "  • " << tip << ": " << count << "\n";
        std::cout << "\n---- PAINTING ZOOM " << dimensions.first << "x" << dimensions.second
                  << " cm" << " ----\n";
        displayImages(nivel);
    }

    else if (nivel >= DetailLevel::Minimal) {
        std::cout << "Technique: " << technique << " | Creation year: " << creation_year
                  << " | Size: " << dimensions.first << "x" << dimensions.second << " cm\n";
        std::cout << "Collected: " << (collected ? "Yes" : "No")
                  << " | Rarity: " << (rare ? "Yes" : "No") << "\n";
        std::cout << "\n---------------- PAINTING " << dimensions.first << "x" << dimensions.second
                  << " cm"
                  << " ----------------\n";
        displayImages(nivel);

        auto ptr_artist = artist.lock();
        if (ptr_artist) {
            std::cout << "Artist: " << ptr_artist->getName() << " " << ptr_artist->getFirstName()
                      << " | Period: " << ptr_artist->getArtisticPeriod() << "\n";
        } else {
            std::cout << "Artist: Unknown\n";
        }
    }
}

std::ostream& Painting::displayPainting(std::ostream& out, const Painting& t, DetailLevel nivel) {
    t.displayPaintingZoom(nivel);
    return out;
}
std::ostream& operator<<(std::ostream& out, const Painting& t) {
    return Painting::displayPainting(out, t, DetailLevel::Complete);
}
