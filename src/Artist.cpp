/**
 * @file Artist.cpp
 * @brief Implementation of the Artist class.
 *
 * Contains the implementation methods for managing artists,
 * calculating the popularity score, and displaying the profile.
 */

#include "../headers/Artist.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "../headers/Painting.h"

/// Static list of all registered artists
std::vector<std::shared_ptr<Artist>> Artist::artists_list = {};

Artist::Artist(const std::string& name_value, const std::string& first_name_value,
               const std::string& nationality_value, int age_value, int birth_year_value,
               int death_year_value, const std::string& artistic_period_value,
               const std::string& registration_date_value, const std::string& username_value,
               const std::string& email_value, const std::vector<std::string>& history_value,
               const std::string& representative_person_value,
               const std::string& representative_username_value,
               const std::string& representative_email_value,
               const std::vector<std::string>& representative_history_value)
    : name(name_value)
    , first_name(first_name_value)
    , nationality(nationality_value)
    , age(age_value)
    , birth_year(birth_year_value)
    , death_year(death_year_value)
    , artistic_period(artistic_period_value)
    , registration_date(registration_date_value)
    , username(username_value)
    , email(email_value)
    , history(history_value)
    , representative_person(representative_person_value)
    , representative_username(representative_username_value)
    , representative_email(representative_email_value)
    , representative_history(representative_history_value) {
}

void Artist::addPainting(const std::shared_ptr<Painting>& painting) {
    if (!painting) {
        return;
    }
    paintings.push_back(painting);
    painting->setArtist(shared_from_this());
}

int Artist::paintingCount() const {
    return static_cast<int>(paintings.size());
}

int Artist::collectedPaintingCount() const {
    int count = 0;
    for (const auto& t : paintings)
        if (t->isCollected())
            count++;
    return count;
}

int Artist::rarePaintingCount() const {
    int count = 0;
    for (const auto& t : paintings)
        if (t->isRare())
            count++;
    return count;
}

std::vector<std::shared_ptr<Painting>> Artist::getRarePaintings() const {
    std::vector<std::shared_ptr<Painting>> rez;
    for (const auto& t : paintings)
        if (t->isRare())
            rez.push_back(t);
    return rez;
}

double Artist::calculateStarScore() const {
    int total = paintingCount();
    if (total == 0)
        return 0;

    int collected = collectedPaintingCount();
    int rare = rarePaintingCount();

    // for artists with fewer paintings
    if (total < 3) {
        int score = collected * 2;
        if (rare > 0)
            score += 1;
        return std::min(5, score);
    }

    // for artists with more paintings
    double base_score = static_cast<double>(collected) / total * 4.0;
    double rarity_bonus = (rare > 0) ? 0.5 : 0.0;
    double final_score = std::min(5.0, base_score + rarity_bonus);

    return static_cast<int>(std::round(final_score));
}

const std::string Artist::getTitle() const {
    double scor = calculateStarScore();
    if (scor < 1)
        return "Novice";
    else if (scor < 2)
        return "Aspirant";
    else if (scor < 3)
        return "Talented";
    else if (scor < 4)
        return "Expert";
    else
        return "Master";
}

void Artist::displayImages(DetailLevel nivel) const {
    if (artist_images.empty()) {
        std::cout << "There are no images for this artist.\n";
        return;
    }

    if (nivel == DetailLevel::Complete) {
        std::cout << "Images of the artist:\n";
        for (const auto& img : artist_images) {
            std::cout << img << "\n";
        }
    } else if (nivel >= DetailLevel::Minimal) {
        std::cout << "Artist image: " << artist_images[0] << "\n";
    }
}

void Artist::displayArtistProfile(DetailLevel nivel) const {
    std::cout << "--------------------------- ARTIST PROFILE ------------------------------\n";
    std::cout << "Full name: " << name << " " << first_name << "\n";
    std::cout << "Nationality: " << nationality << "\n";

    if (nivel == DetailLevel::Minimal) {
        std::cout << "Artistic period: " << artistic_period << "\n";
        std::cout << "The artist developed in this era through exploration of specific styles and "
                     "techniques.\n";
        std::cout << "Status: ";
        if (death_year == 0) {
            std::cout << "Living (" << age << " years old)\n";
            std::cout << "Has an active profile.\n";
        } else {
            std::cout << "Deceased (" << birth_year << " - " << death_year << ")\n";
            std::cout << "The paintings from the gallery were added by a representative: "
                      << representative_person << "\n";
        }
        std::cout << "\n------------------------------- ARTIST IMAGE --------------------------\n";
        displayImages(nivel);
        return;
    }

    if (death_year == 0) {
        std::cout << "Status: ";
        std::cout << "Living (" << age << " years old)\n";
        std::cout << "Has an active profile.\n";
        std::cout << name << " was born in " << birth_year << " and is still alive.\n";
        std::cout << "  • Username: " << username << "\n";
        std::cout << "  • Email: " << email << "\n";
        if (!history.empty()) {
            std::cout << "  • Activity history:\n";
            for (const auto& act : history)
                std::cout << "    - " << act << "\n";
        }
    } else {
        std::cout << "Status: ";
        std::cout << "Deceased (" << birth_year << " - " << death_year << ")\n";
        std::cout << "The paintings from the gallery were added by a representative: "
                  << representative_person << "\n";
        std::cout << name << " lived between " << birth_year << " and " << death_year << ".\n";
        if (!representative_person.empty()) {
            std::cout << "Representative: " << representative_person << "\n";
            std::cout << "Username: " << representative_username << "\n";
            std::cout << "Email: " << representative_email << "\n";
        }
        if (!representative_history.empty()) {
            std::cout << "Representative activity history:\n";
            for (const auto& act : representative_history)
                std::cout << "    - " << act << "\n";
        }
    }
    std::cout << "Artistic period: " << artistic_period << "\n";
    std::cout << "The artist evolved during this period through exploration of specific styles and "
                 "techniques.\n";

    std::cout << "\n--------------------------- POPULARITY ----------------------------\n";
    std::cout << "Total paintings: " << paintingCount() << "\n";
    std::cout << "Collected paintings: " << collectedPaintingCount() << "\n";
    std::cout << "Rare paintings: " << rarePaintingCount() << "\n";
    std::cout << "Registration date: " << registration_date << "\n";

    double scor = calculateStarScore();
    std::cout << "Popularity score: " << scor << " stars\n";
    std::cout << "Assigned title: " << getTitle() << "\n";

    std::cout << "\n---- ARTIST IMAGES ----\n";
    displayImages(nivel);

    std::cout << "--------------------------------------------------------------------------\n";
    if (!paintings.empty()) {
        std::cout << "\n------------------- PAINTINGS BY THIS ARTIST ------------------------\n";
        for (const auto& t : paintings) {
            t->displayImages(nivel);
        }
    }
}
std::shared_ptr<Painting> Artist::findPainting(const std::string& title) const {
    for (const auto& t : paintings) {
        if (t->getTitle() == title)
            return t;
    }
    return nullptr;
}

std::ostream& Artist::displayArtist(std::ostream& out, const Artist& artist, DetailLevel level) {
    artist.displayArtistProfile(level);
    return out;
}

std::ostream& operator<<(std::ostream& out, const Artist& artist) {
    return Artist::displayArtist(out, artist, DetailLevel::Complete);
}
