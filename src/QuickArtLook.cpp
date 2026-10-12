/**
 * @file QuickArtLook.cpp
 * @brief Implementation of the QuickArtLook class.
 *
 * Contains the implementation of the painting-artist matching game,
 * including shuffling and pair verification.
 */

#include "../headers/QuickArtLook.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "../headers/MiniGame.h"

QuickArtLook::QuickArtLook(const std::string& name, Difficulty dif)
    : MiniGame(name, "Match paintings with the correct artists!", dif)
    , pairs()
    , correct_pairs(0)
    , wrong_pairs(0) {
    std::cout << "QuickArtLook constructor: " << name << std::endl;
}

QuickArtLook::QuickArtLook(const QuickArtLook& other)
    : MiniGame(other), pairs(), correct_pairs(other.correct_pairs), wrong_pairs(other.wrong_pairs) {
    std::cout << "QuickArtLook copy constructor" << std::endl;
}

std::unique_ptr<MiniGame> QuickArtLook::clone() const {
    return std::make_unique<QuickArtLook>(*this);
}

std::string QuickArtLook::getGameType() const {
    return "Quick Art Look";
}

void QuickArtLook::addPair(std::shared_ptr<Painting> painting, std::shared_ptr<Artist> artist) {
    if (!painting || !artist) {
        return;
    }
    pairs.push_back({painting, artist});
    std::cout << "Pair added: " << painting->getTitle() << " - " << artist->getName() << std::endl;
}

void QuickArtLook::displayPaintings() const {
    std::cout << "\n=== PAINTINGS ===\n";
    for (size_t i = 0; i < pairs.size(); i++) {
        std::cout << i + 1 << ". " << pairs[i].first->getTitle() << std::endl;
    }
}

void QuickArtLook::displayArtists() const {
    std::cout << "\n=== ARTISTS ===\n";

    std::vector<std::string> artist_names;
    for (const auto& pair : pairs) {
        artist_names.push_back(pair.second->getName() + " " + pair.second->getFirstName());
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(artist_names.begin(), artist_names.end(), g);

    for (size_t i = 0; i < artist_names.size(); i++) {
        std::cout << char('A' + i) << ". " << artist_names[i] << std::endl;
    }
}

bool QuickArtLook::verifyPair(const std::string& painting_title, const std::string& artist_name) {
    for (const auto& pair : pairs) {
        if (pair.first->getTitle() == painting_title) {
            std::string full_name = pair.second->getName() + " " + pair.second->getFirstName();
            std::string reverse_full_name =
                pair.second->getFirstName() + " " + pair.second->getName();

            if (artist_name == pair.second->getName() || artist_name == full_name ||
                artist_name == reverse_full_name) {
                correct_pairs++;
                std::cout << "✓ Correct! " << painting_title << " is by " << full_name << std::endl;
                return true;
            } else {
                wrong_pairs++;
                std::cout << "✗ Wrong! " << painting_title << " is not by " << artist_name
                          << std::endl;
                return false;
            }
        }
    }

    std::cout << "Painting '" << painting_title << "' was not found." << std::endl;
    return false;
}

void QuickArtLook::shufflePairs() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pairs.begin(), pairs.end(), g);
    std::cout << "Pairs have been shuffled!" << std::endl;
}

void QuickArtLook::initializeImplementation() {
    correct_pairs = 0;
    wrong_pairs = 0;

    shufflePairs();

    size_t max_pairs = 3;
    switch (difficulty) {
        case Difficulty::Easy:
            max_pairs = 3;
            break;
        case Difficulty::Medium:
            max_pairs = 5;
            break;
        case Difficulty::Hard:
            max_pairs = 8;
            break;
        default:
            max_pairs = 3;
            break;
    }

    if (pairs.size() > max_pairs) {
        pairs.resize(max_pairs);
    }

    std::cout << "Quick Art Look initialized!" << std::endl;
    std::cout << "Pairs to guess: " << pairs.size() << std::endl;
}

int QuickArtLook::calculatePointsImplementation() {
    if (pairs.empty()) {
        return 0;
    }

    double correct_percentage = static_cast<double>(correct_pairs) / pairs.size() * 100.0;
    int points = static_cast<int>((correct_percentage / 100.0) * maximum_points);

    int penalty = wrong_pairs * 10;
    points -= penalty;

    points = std::max(0, std::min(points, maximum_points));

    std::cout << "Correct: " << correct_pairs << "/" << pairs.size() << std::endl;
    std::cout << "Wrong: " << wrong_pairs << " (penalty: -" << penalty << ")" << std::endl;

    return points;
}

std::string QuickArtLook::getPaintingTitle(int index) const {
    if (index < 0 || index >= static_cast<int>(pairs.size())) {
        return {};
    }
    return pairs[static_cast<std::size_t>(index)].first->getTitle();
}

std::string QuickArtLook::getArtistName(int index) const {
    if (index < 0 || index >= static_cast<int>(pairs.size())) {
        return {};
    }
    const auto& artist = pairs[static_cast<std::size_t>(index)].second;
    return artist->getName() + " " + artist->getFirstName();
}

void QuickArtLook::displayRulesImplementation() const {
    size_t max_pairs = 3;
    switch (difficulty) {
        case Difficulty::Easy:
            max_pairs = 3;
            break;
        case Difficulty::Medium:
            max_pairs = 5;
            break;
        case Difficulty::Hard:
            max_pairs = 8;
            break;
        default:
            max_pairs = 3;
            break;
    }
    std::cout << "QUICK ART LOOK - Rules:" << std::endl;
    std::cout << "1. You will see a list of paintings and a list of artists." << std::endl;
    std::cout << "2. You must match each painting with the correct artist." << std::endl;
    std::cout << "3. Enter the painting title and artist name." << std::endl;
    std::cout << "4. Incorrect answers reduce the score." << std::endl;
    std::cout << "Pairs to guess: " << max_pairs << std::endl;
}