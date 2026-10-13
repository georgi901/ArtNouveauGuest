/**
 * @file ArtPuzzle.cpp
 * @brief Implementation of the ArtPuzzle class.
 *
 * Contains the implementation of the puzzle game with painting fragments,
 * including shuffling and solution validation.
 */

#include "../headers/ArtPuzzle.h"

#include <algorithm>
#include <iostream>
#include <random>

ArtPuzzle::ArtPuzzle(const std::string& name, Difficulty dif)
    : MiniGame(name, "Arrange the painting fragments in the correct order", dif)
    , target_painting(nullptr)
    , fragment_order()
    , correct_order()
    , fragment_count(0)
    , moves_made(0)
    , maximum_moves(0)
    , solved(false) {
    // Set the number of fragments and maximum moves based on difficulty
    switch (dif) {
        case Difficulty::Easy:
            fragment_count = 4;  // 2x2
            maximum_moves = 6;
            break;
        case Difficulty::Medium:
            fragment_count = 9;  // 3x3
            maximum_moves = 14;
            break;
        case Difficulty::Hard:
            fragment_count = 16;  // 4x4
            maximum_moves = 22;
            break;
        default:
            fragment_count = 4;
            maximum_moves = 6;
            break;
    }

    fragment_order.reserve(static_cast<std::size_t>(fragment_count));
    correct_order.reserve(static_cast<std::size_t>(fragment_count));

    for (int i = 0; i < fragment_count; i++) {
        correct_order.push_back(i);
        fragment_order.push_back(i);
    }

    std::cout << "ArtPuzzle constructor: " << name << "\n";
}

ArtPuzzle::ArtPuzzle(const ArtPuzzle& other)
    : MiniGame(other)
    , target_painting(nullptr)
    , fragment_order(other.fragment_order)
    , correct_order(other.correct_order)
    , fragment_count(other.fragment_count)
    , moves_made(other.moves_made)
    , maximum_moves(other.maximum_moves)
    , solved(other.solved) {
    std::cout << "ArtPuzzle copy constructor\n";
}

ArtPuzzle::~ArtPuzzle() {
    std::cout << "ArtPuzzle destructor: " << getName() << "\n";
}

void ArtPuzzle::setPainting(std::shared_ptr<Painting> painting) {
    target_painting = painting;
    if (painting) {
        std::cout << "Puzzle set for painting: " << painting->getTitle() << "\n";
    }
}

void ArtPuzzle::shuffleFragments() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(fragment_order.begin(), fragment_order.end(), g);
    solved = false;
    std::cout << "Fragments have been shuffled!\n";
}

bool ArtPuzzle::moveFragment(int position1, int position2) {
    if (position1 < 0 || position1 >= fragment_count || position2 < 0 ||
        position2 >= fragment_count) {
        std::cout << "Invalid positions!\n";
        return false;
    }

    if (moves_made >= maximum_moves) {
        std::cout << "You have used all moves!\n";
        return false;
    }

    std::swap(fragment_order[static_cast<std::size_t>(position1)],
              fragment_order[static_cast<std::size_t>(position2)]);
    moves_made++;

    solved = (fragment_order == correct_order);

    return true;
}

bool ArtPuzzle::isSolved() const {
    return solved;
}

int ArtPuzzle::getFragmentAt(int index) const {
    if (index < 0 || index >= static_cast<int>(fragment_order.size())) {
        return -1;
    }
    return fragment_order[static_cast<std::size_t>(index)];
}

void ArtPuzzle::displayPuzzle() const {
    std::cout << "\n=== PUZZLE: ";
    if (target_painting) {
        std::cout << target_painting->getTitle();
    }
    std::cout << " ===\n";

    int dim = (fragment_count == 4) ? 2 : (fragment_count == 9) ? 3 : 4;

    for (int i = 0; i < fragment_count; i++) {
        std::cout << "[" << fragment_order[static_cast<std::size_t>(i)] << "] ";
        if ((i + 1) % dim == 0) {
            std::cout << "\n";
        }
    }

    std::cout << "Moves: " << moves_made << "/" << maximum_moves << "\n";
}

void ArtPuzzle::initializeImplementation() {
    moves_made = 0;
    solved = false;

    fragment_order.clear();
    for (int i = 0; i < fragment_count; i++) {
        fragment_order.push_back(i);
    }

    shuffleFragments();
    std::cout << "Puzzle initialized with " << fragment_count << " fragments.\n";
}

int ArtPuzzle::calculatePointsImplementation() {
    if (!solved) {
        return 0;
    }

    int base_points = maximum_points;

    int remaining_moves = maximum_moves - moves_made;
    int bonus = (remaining_moves * maximum_points) / (maximum_moves * 2);

    std::cout << "Base points: " << base_points << "\n";
    std::cout << "Bonus for remaining moves (" << remaining_moves << " moves): +" << bonus << "\n";

    return base_points + bonus;
}

void ArtPuzzle::displayRulesImplementation() const {
    std::cout << "\n==========================================\n";
    std::cout << "         ART PUZZLE RULES                  \n";
    std::cout << "============================================\n";
    std::cout << "  1. Arrange the fragments in order        \n";
    std::cout << "  2. Swap the positions of two fragments    \n";
    std::cout << "  3. Correct order: 0,1,2,3...              \n";
    std::cout << "  4. You have a limited number of moves     \n";
    std::cout << "============================================\n";
    std::cout << "  Fragments: " << fragment_count << "      \n";
    std::cout << "  Max moves: " << maximum_moves << "    \n";
    std::cout << "============================================\n";
}

std::unique_ptr<MiniGame> ArtPuzzle::clone() const {
    return std::make_unique<ArtPuzzle>(*this);
}

std::string ArtPuzzle::getGameType() const {
    return "ArtPuzzle";
}