/**
 * @file MiniGame.cpp
 * @brief Implementation of the abstract MiniGame class.
 *
 * Contains the base implementation for the mini-game system,
 * using the NVI pattern (Non-Virtual Interface).
 */

#include "../headers/MiniGame.h"

#include <iomanip>
#include <iostream>

/// Total number of games played in the session
int MiniGame::total_games_played = 0;
/// Total points awarded across all games
int MiniGame::total_points_awarded = 0;

std::ostream& operator<<(std::ostream& os, const Difficulty& dif) {
    switch (dif) {
        case Difficulty::Easy:
            return os << "Easy";
        case Difficulty::Medium:
            return os << "Medium";
        case Difficulty::Hard:
            return os << "Hard";
        default:
            return os << "Unknown";
    }
}

MiniGame::MiniGame(const std::string& game_name, const std::string& description,
                   Difficulty difficulty)
    : game_name(game_name)
    , description(description)
    , difficulty(difficulty)
    , earned_points(0)
    , maximum_points(100)
    , finished(false) {
    switch (difficulty) {
        case Difficulty::Easy:
            maximum_points = 100;
            break;
        case Difficulty::Medium:
            maximum_points = 200;
            break;
        case Difficulty::Hard:
            maximum_points = 300;
            break;
        default:
            maximum_points = 100;
            break;
    }

    std::cout << "MiniGame constructor: " << game_name << std::endl;
}

MiniGame::MiniGame(const MiniGame& other)
    : game_name(other.game_name)
    , description(other.description)
    , difficulty(other.difficulty)
    , earned_points(other.earned_points)
    , maximum_points(other.maximum_points)
    , finished(other.finished) {
    std::cout << "MiniGame copy constructor: " << game_name << std::endl;
}

MiniGame& MiniGame::operator=(const MiniGame& other) {
    if (this != &other) {
        game_name = other.game_name;
        description = other.description;
        difficulty = other.difficulty;
        earned_points = other.earned_points;
        maximum_points = other.maximum_points;
        finished = other.finished;
    }
    std::cout << "[DEBUG] MiniGame operator=: " << game_name << std::endl;
    return *this;
}

void MiniGame::initialize() {
    std::cout << "\n=== Initializing game: " << game_name << " ===" << std::endl;
    std::cout << "Difficulty: " << difficulty << std::endl;
    std::cout << "Maximum points: " << maximum_points << std::endl;

    initializeImplementation();

    total_games_played++;
    finished = false;
    earned_points = 0;

    std::cout << "Game ready! Success!" << std::endl;
}

int MiniGame::calculatePoints() {
    std::cout << "\n--- Calculating points ---" << std::endl;

    earned_points = calculatePointsImplementation();

    total_points_awarded += earned_points;
    finished = true;

    std::cout << "Points earned: " << earned_points << "/" << maximum_points << std::endl;

    return earned_points;
}
void MiniGame::displayRules() const {
    std::cout << "\n=== RULES: " << game_name << " ===" << std::endl;
    std::cout << "Difficulty: " << difficulty << " | Maximum points: " << maximum_points
              << std::endl;
    std::cout << "---" << std::endl;

    displayRulesImplementation();

    std::cout << "---\n" << std::endl;
}

int MiniGame::getTotalGames() {
    return total_games_played;
}

int MiniGame::getTotalPoints() {
    return total_points_awarded;
}

void MiniGame::displayStatistics() {
    std::cout << "\n--- GLOBAL STATISTICS ---" << std::endl;
    std::cout << "Total games played: " << total_games_played << std::endl;
    std::cout << "Total points awarded: " << total_points_awarded << std::endl;

    if (total_games_played > 0) {
        double average = static_cast<double>(total_points_awarded) / total_games_played;
        std::cout << "Average points/game: " << std::fixed << std::setprecision(2) << average
                  << std::endl;
    }
    std::cout << std::endl;
}

void MiniGame::resetStatistics() {
    total_games_played = 0;
    total_points_awarded = 0;
    std::cout << "[INFO] Statistics reset." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const MiniGame& game) {
    os << game.game_name << " (" << game.getGameType() << ")"
       << " - " << game.difficulty << " - " << game.earned_points << "/" << game.maximum_points
       << " points"
       << " - " << (game.finished ? "Completed" : "Not completed");
    return os;
}