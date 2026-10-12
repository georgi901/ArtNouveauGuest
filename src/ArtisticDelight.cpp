/**
 * @file ArtisticDelight.cpp
 * @brief Implementation of the ArtisticDelight class.
 *
 * Contains the game implementation for guessing colors,
 * including similarity evaluation and the hint system.
 */

#include "../headers/ArtisticDelight.h"

#include <algorithm>
#include <cmath>
#include <iostream>

ArtisticDelight::ArtisticDelight(const std::string& name, Difficulty dif)
    : MiniGame(name, "Recreate the painting using the right colors!", dif)
    , target_painting(nullptr)
    , similarity_score(0.0)
    , used_colors()
    , attempts_remaining(0) {
    switch (dif) {
        case Difficulty::Easy:
            attempts_remaining = 10;
            break;
        case Difficulty::Medium:
            attempts_remaining = 7;
            break;
        case Difficulty::Hard:
            attempts_remaining = 5;
            break;
        default:
            attempts_remaining = 10;
            break;
    }

    std::cout << "ArtisticDelight constructor: " << name << std::endl;
}

ArtisticDelight::ArtisticDelight(const ArtisticDelight& other)
    : MiniGame(other)
    , target_painting(nullptr)
    , similarity_score(other.similarity_score)
    , used_colors(other.used_colors)
    , attempts_remaining(other.attempts_remaining) {
    std::cout << "ArtisticDelight copy constructor" << std::endl;
}

std::unique_ptr<MiniGame> ArtisticDelight::clone() const {
    return std::make_unique<ArtisticDelight>(*this);
}

std::string ArtisticDelight::getGameType() const {
    return "Artistic Delight";
}

void ArtisticDelight::setPainting(std::shared_ptr<Painting> painting) {
    target_painting = painting;
    if (painting) {
        std::cout << "Painting set: " << painting->getTitle() << std::endl;
    }
}

void ArtisticDelight::paint(const std::string& color) {
    if (attempts_remaining <= 0) {
        std::cout << "No attempts left!" << std::endl;
        return;
    }

    used_colors.push_back(color);
    attempts_remaining--;

    std::cout << "You used the color: " << color << std::endl;
    std::cout << "Attempts remaining: " << attempts_remaining << std::endl;

    evaluateSimilarity();
}

double ArtisticDelight::evaluateSimilarity() {
    if (!target_painting) {
        similarity_score = 0.0;
        return similarity_score;
    }

    const auto& original_colors = target_painting->getColors();

    if (original_colors.empty()) {
        similarity_score = 0.0;
        return similarity_score;
    }

    int correct_colors = 0;
    for (const auto& color : used_colors) {
        if (original_colors.find(color) != original_colors.end()) {
            correct_colors++;
        }
    }

    double guessed_percentage =
        static_cast<double>(correct_colors) / static_cast<double>(original_colors.size()) * 100.0;

    int wrong_colors = static_cast<int>(used_colors.size()) - correct_colors;
    double penalty = wrong_colors * 5.0;

    similarity_score = std::max(0.0, std::min(100.0, guessed_percentage - penalty));

    std::cout << "Similarity score: " << similarity_score << "%" << std::endl;

    return similarity_score;
}

void ArtisticDelight::showHint() const {
    if (!target_painting) {
        std::cout << "No painting is set!" << std::endl;
        return;
    }

    const auto& original_colors = target_painting->getColors();

    if (original_colors.empty()) {
        std::cout << "The painting has no defined colors." << std::endl;
        return;
    }

    for (const auto& [color, _] : original_colors) {
        bool found = false;
        for (const auto& c : used_colors) {
            if (c == color) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Hint: Try a color that starts with '" << color[0] << "'..." << std::endl;
            return;
        }
    }

    std::cout << "You found all the colors!" << std::endl;
}

void ArtisticDelight::initializeImplementation() {
    similarity_score = 0.0;
    used_colors.clear();

    switch (difficulty) {
        case Difficulty::Easy:
            attempts_remaining = 10;
            break;
        case Difficulty::Medium:
            attempts_remaining = 7;
            break;
        case Difficulty::Hard:
            attempts_remaining = 5;
            break;
        default:
            attempts_remaining = 10;
            break;
    }

    std::cout << "Artistic Delight initialized!" << std::endl;
    std::cout << "Attempts available: " << attempts_remaining << std::endl;

    if (target_painting) {
        std::cout << "Painting to recreate: " << target_painting->getTitle() << std::endl;
    }
}

int ArtisticDelight::calculatePointsImplementation() {
    int points = static_cast<int>((similarity_score / 100.0) * maximum_points);

    int bonus = attempts_remaining * 5;
    int total = points + bonus;

    std::cout << "Similarity score: " << similarity_score << "%" << std::endl;
    std::cout << "Base points: " << points << std::endl;
    std::cout << "Remaining attempts bonus (" << attempts_remaining << " attempts): +" << bonus
              << std::endl;
    std::cout << "Total: " << total << std::endl;

    return total;
}

void ArtisticDelight::displayRulesImplementation() const {
    std::cout << "ARTISTIC DELIGHT - Rules:" << std::endl;
    std::cout << "1. A famous painting will be shown to you." << std::endl;
    std::cout << "2. You must guess the colors used in the painting." << std::endl;
    std::cout << "3. Enter the color names one by one." << std::endl;
    std::cout << "4. The more colors you guess correctly, the higher your score." << std::endl;
    std::cout << "5. You have a limited number of attempts!" << std::endl;
    std::cout << "Attempts available: " << attempts_remaining << std::endl;
}