#pragma once

/**
 * @file ArtisticDelight.h
 * @brief Defines the ArtisticDelight class - a color-guessing game.
 *
 * This file contains the ArtisticDelight class, which implements a mini-game in
 * which the player must guess the colors used in a painting.
 */

#include <memory>
#include <vector>

#include "MiniGame.h"
#include "Painting.h"

/**
 * @class ArtisticDelight
 * @brief Game for guessing the colors used in a famous painting.
 *
 * Derived from MiniGame, this class implements a creative game where the player
 * must guess the colors used by the artist in creating a painting.
 *
 * The number of attempts varies by difficulty:
 * - Easy: 10 attempts
 * - Medium: 7 attempts
 * - Hard: 5 attempts
 *
 * The score is calculated based on the percentage of correctly guessed colors,
 * with penalties for wrong colors and bonuses for remaining attempts.
 *
 * @code
 * auto game = std::make_unique<ArtisticDelight>("Color Match", Difficulty::Medium);
 * game->setPainting(painting);
 * game->initialize();
 * game->paint("red");
 * game->showHint();
 * double score = game->evaluateSimilarity();
 * @endcode
 */
class ArtisticDelight : public MiniGame {
private:
    std::shared_ptr<Painting> target_painting;  // painting de recreat
    double similarity_score = 0.0;              // 0-100%
    std::vector<std::string> used_colors;
    int attempts_remaining = 0;

protected:
    void initializeImplementation() override;
    int calculatePointsImplementation() override;
    void displayRulesImplementation() const override;

public:
    ArtisticDelight(const std::string& name, Difficulty dif);

    ArtisticDelight(const ArtisticDelight& other);

    ~ArtisticDelight() override = default;

    std::unique_ptr<MiniGame> clone() const override;

    std::string getGameType() const override;

    void setPainting(std::shared_ptr<Painting> painting);
    void paint(const std::string& color);
    double evaluateSimilarity();
    void showHint() const;

    double getSimilarityScore() const {
        return similarity_score;
    }
    int getAttemptsRemaining() const {
        return attempts_remaining;
    }
    const std::vector<std::string>& getUsedColors() const {
        return used_colors;
    }
};
