#pragma once

/**
 * @file MiniGame.h
 * @brief Defines the abstract MiniGame class used by the game system.
 *
 * This file contains the base MiniGame class that defines the common interface
 * for all mini-games in the gallery. It uses the NVI (Non-Virtual Interface)
 * pattern to ensure consistent behavior.
 */

#include <iostream>
#include <memory>
#include <string>

/**
 * @enum Difficulty
 * @brief Available difficulty levels for games.
 */
enum class Difficulty { Easy, Medium, Hard };

/**
 * @class MiniGame
 * @brief Abstract base class for all mini-games in the gallery.
 *
 * Implements the NVI pattern (Non-Virtual Interface) to separate the public
 * interface from the implementation details of each game. It also manages the
 * global statistics for all games played.
 *
 * Derived classes must implement:
 * - initializeImplementation() - initialization logic
 * - calculatePointsImplementation() - score calculation
 * - displayRulesImplementation() - specific rules
 * - clone() - polymorphic copying
 * - getGameType() - game type name
 *
 * @code
 * class NewGame : public MiniGame {
 *     void initializeImplementation() override { ... }
 *     int calculatePointsImplementation() override { return points; }
 *     void displayRulesImplementation() const override { ... }
 * };
 * @endcode
 */
class MiniGame {
protected:
    std::string game_name;
    std::string description;
    Difficulty difficulty;
    int earned_points = 0;
    int maximum_points = 100;
    bool finished = false;

    static int total_games_played;
    static int total_points_awarded;

    virtual void initializeImplementation() = 0;
    virtual int calculatePointsImplementation() = 0;
    virtual void displayRulesImplementation() const = 0;

    MiniGame& operator=(const MiniGame& other);

public:
    MiniGame(const std::string& game_name, const std::string& description, Difficulty difficulty);
    virtual ~MiniGame() = default;

    MiniGame(const MiniGame& other);

    virtual std::unique_ptr<MiniGame> clone() const = 0;
    virtual std::string getGameType() const = 0;

    void initialize();
    int calculatePoints();
    void displayRules() const;

    static int getTotalGames();
    static int getTotalPoints();
    static void displayStatistics();
    static void resetStatistics();

    const std::string& getName() const {
        return game_name;
    }
    const std::string& getDescription() const {
        return description;
    }
    Difficulty getDifficulty() const {
        return difficulty;
    }
    int getMaximumPoints() const {
        return maximum_points;
    }
    int getEarnedPoints() const {
        return earned_points;
    }
    bool isFinished() const {
        return finished;
    }

    friend std::ostream& operator<<(std::ostream& os, const MiniGame& game);
};

std::ostream& operator<<(std::ostream& os, const Difficulty& dif);
