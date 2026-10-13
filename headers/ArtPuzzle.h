#pragma once

/**
 * @file ArtPuzzle.h
 * @brief Defines the ArtPuzzle class - a puzzle game with painting fragments.
 *
 * This file contains the ArtPuzzle class, which implements a mini-game where the
 * player arranges the fragments of a painting.
 */

#include <memory>
#include <vector>

#include "MiniGame.h"
#include "Painting.h"

/**
 * @class ArtPuzzle
 * @brief Puzzle game with fragments of a famous painting.
 *
 * Derived from MiniGame, this class implements a puzzle game in which the player
 * must arrange the fragments of a painting in the correct order (0, 1, 2, 3...).
 *
 * The configuration varies by difficulty:
 * - Easy: 4 fragments (2x2), 6 maximum moves
 * - Medium: 9 fragments (3x3), 14 maximum moves
 * - Hard: 16 fragments (4x4), 22 maximum moves
 *
 * The score includes a bonus for remaining unused moves.
 *
 * @code
 * auto puzzle = std::make_unique<ArtPuzzle>("Puzzle Art", Difficulty::Medium);
 * puzzle->setPainting(painting);
 * puzzle->initialize();
 * puzzle->displayPuzzle();
 * puzzle->moveFragment(0, 3);
 * if (puzzle->isSolved()) {
 *     int points = puzzle->calculatePoints();
 * }
 * @endcode
 */
class ArtPuzzle : public MiniGame {
private:
    std::shared_ptr<Painting> target_painting;
    std::vector<int> fragment_order;
    std::vector<int> correct_order;
    int fragment_count = 0;
    int moves_made = 0;
    int maximum_moves = 0;
    bool solved = false;

protected:
    void initializeImplementation() override;
    int calculatePointsImplementation() override;
    void displayRulesImplementation() const override;

public:
    ArtPuzzle(const std::string& name, Difficulty dif);
    ArtPuzzle(const ArtPuzzle& other);
    ~ArtPuzzle() override;

    void setPainting(std::shared_ptr<Painting> painting);
    void shuffleFragments();
    bool moveFragment(int position1, int position2);
    bool isSolved() const;
    void displayPuzzle() const;

    int getMovesMade() const {
        return moves_made;
    }
    int getMovesRemaining() const {
        return maximum_moves - moves_made;
    }
    int getFragmentCount() const {
        return fragment_count;
    }
    int getFragmentAt(int index) const;

    std::unique_ptr<MiniGame> clone() const override;
    std::string getGameType() const override;
};
