/**
 * @file User.cpp
 * @brief Implementation of the User class.
 *
 * Contains the implementation methods for managing users,
 * painting collections, and the points system.
 */

#include "../headers/User.h"

#include <iostream>

#include "../headers/Exceptions.h"
#include "../headers/Gallery.h"
#include "../headers/Painting.h"

User::User(const std::string& n, const std::string& u, const std::string& e, int v,
           const std::string& d)
    : name(n), username(u), email(e), age(v), registration_date(d), points(0) {
}

void User::addPainting(const std::shared_ptr<Painting>& painting) {
    if (!painting) {
        return;
    }
    collection.push_back(painting);
    painting->setCollected(true);
    addActivity("Added painting " + painting->getTitle());
}

std::shared_ptr<Painting> User::findPainting(const std::string& title) const {
    for (const auto& t : collection) {
        if (t->getTitle() == title)
            return t;
    }
    return nullptr;
}

void User::displayCollection() const {
    std::cout << "\n--------------------- " << name << "'s collection ----------------------\n";
    for (const auto& t : collection) {
        std::cout << *t << "\n";
    }
}

void User::addActivity(const std::string& activitate) {
    activity_history.push_back(activitate);
}

std::ostream& operator<<(std::ostream& out, const User& u) {
    out << "\n------------------------------- USER PROFILE --------------------------------\n";
    out << "Name: " << u.name << "\n";
    out << "Username: " << u.username << "\n";
    out << "Email: " << u.email << "\n";
    out << "Age: " << u.age << "\n";
    out << "Registration date: " << u.registration_date << "\n";
    out << "Points: " << u.points << "\n";
    out << "Paintings in collection: " << u.collection.size() << "\n";

    if (!u.activity_history.empty()) {
        out << "\nActivity history:\n";
        for (const auto& act : u.activity_history)
            out << "  - " << act << "\n";
    }
    return out;
}

void User::buyPainting(std::shared_ptr<Painting> painting, int cost) {
    if (!painting) {
        throw PaintingUnavailableException("(painting null)");
    }

    if (points < cost) {
        throw InsufficientPointsException(points, cost);
    }

    if (painting->isCollected()) {
        throw PaintingUnavailableException(painting->getTitle());
    }

    points -= cost;
    addPainting(painting);
    addActivity("Bought painting " + painting->getTitle() + " for " + std::to_string(cost) +
                " points");
}
