#pragma once

/**
 * @file User.h
 * @brief Defines the User class for gallery visitors.
 *
 * This file contains the User class, which models a gallery visitor with a
 * personal painting collection and a points system.
 */

#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Artist.h"
#include "Painting.h"

/**
 * @class User
 * @brief Represents a visitor/user of the art gallery.
 *
 * The class manages:
 * - Personal information (name, username, email, age)
 * - Personal painting collection
 * - Points system for activities
 * - Activity history in the gallery
 *
 * The user can accumulate points through games and use them to buy paintings in
 * their personal collection.
 *
 * @code
 * User user("Ion Popescu", "ion_p", "ion@email.com", 25, "2024-01-15");
 * user.addPoints(100);
 * user.buyPainting(painting, 50);
 * user.displayCollection();
 * @endcode
 */
class User {
private:
    const std::string name;
    const std::string username;
    const std::string email;
    const int age;
    const std::string registration_date;
    std::vector<std::string> activity_history;
    std::vector<std::shared_ptr<Painting>> collection;
    void addActivity(const std::string& activitate);
    int points = 0;

public:
    User(const std::string& n, const std::string& u, const std::string& e, int v,
         const std::string& d);
    ~User() = default;
    void addPainting(const std::shared_ptr<Painting>& painting);
    std::shared_ptr<Painting> findPainting(const std::string& title) const;
    void displayCollection() const;

    friend std::ostream& operator<<(std::ostream& out, const User& u);
    friend std::istream& operator>>(std::istream& in, User& u) {
        size_t n;
        std::cout << "How many paintings do you want to add to your collection? ";
        in >> n;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (size_t i = 0; i < n; ++i) {
            std::string title;
            std::cout << "Painting title " << i + 1 << ": ";
            std::getline(in, title);

            std::shared_ptr<Painting> painting_found = nullptr;
            for (const auto& artist : Artist::getArtistsList()) {
                auto t = artist->findPainting(title);
                if (t) {
                    painting_found = t;
                    break;
                }
            }

            if (painting_found) {
                u.addPainting(painting_found);
                std::cout << "The painting \"" << title << "\" was added to the collection.\n";
            } else {
                std::cout << "The painting \"" << title << "\" was not found.\n";
            }
        }
        return in;
    }

    void addPoints(int p) {
        points += p;
    }
    int getPoints() const {
        return points;
    }
    const std::vector<std::shared_ptr<Painting>>& getCollection() const {
        return collection;
    }
    void buyPainting(std::shared_ptr<Painting> painting, int cost);
};
