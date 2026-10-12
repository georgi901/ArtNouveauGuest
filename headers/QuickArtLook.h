#pragma once

/**
 * @file QuickArtLook.h
 * @brief Defines the QuickArtLook class - a painting-to-artist matching game.
 *
 * This file contains the QuickArtLook class, which implements a mini-game where
 * the player must match paintings with the correct artists.
 */

#include <memory>
#include <utility>
#include <vector>

#include "Artist.h"
#include "MiniGame.h"
#include "Painting.h"

/**
 * @class QuickArtLook
 * @brief Painting-to-artist matching game.
 *
 * Derived from MiniGame, this class implements a matching game where the player
 * must correctly identify the artist for each painting.
 *
 * The number of pairs varies by difficulty:
 * - Easy: 3 pairs
 * - Medium: 5 pairs
 * - Hard: 8 pairs
 *
 * The score is calculated based on the percentage of correct pairs, with
 * penalties for incorrect answers.
 *
 * @code
 * auto game = std::make_unique<QuickArtLook>("Quick Art", Difficulty::Medium);
 * game->addPair(painting, artist);
 * game->initialize();
 * game->displayPaintings();
 * game->displayArtists();
 * game->verifyPair("Zodiac", "Mucha");
 * @endcode
 */
class QuickArtLook : public MiniGame {
private:
    std::vector<std::pair<std::shared_ptr<Painting>, std::shared_ptr<Artist>>> pairs;
    int correct_pairs = 0;
    int wrong_pairs = 0;

protected:
    void initializeImplementation() override;
    int calculatePointsImplementation() override;
    void displayRulesImplementation() const override;

public:
    QuickArtLook(const std::string& name, Difficulty dif);
    QuickArtLook(const QuickArtLook& other);
    ~QuickArtLook() override = default;

    std::unique_ptr<MiniGame> clone() const override;
    std::string getGameType() const override;

    void addPair(std::shared_ptr<Painting> painting, std::shared_ptr<Artist> artist);
    void displayPaintings() const;
    void displayArtists() const;
    bool verifyPair(const std::string& painting_title, const std::string& artist_name);
    void shufflePairs();

    int getCorrectPairs() const {
        return correct_pairs;
    }
    int getWrongPairs() const {
        return wrong_pairs;
    }
    int getTotalPairs() const {
        return static_cast<int>(pairs.size());
    }
    std::string getPaintingTitle(int index) const;
    std::string getArtistName(int index) const;
};
