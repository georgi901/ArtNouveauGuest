/**
 * @file GameFactory.cpp
 * @brief Implementation of the Factory design pattern for mini-games.
 */

#include "../headers/GameFactory.h"

#include <iostream>

#include "../headers/ArtPuzzle.h"
#include "../headers/ArtQuiz.h"
#include "../headers/ArtisticDelight.h"
#include "../headers/Exceptions.h"
#include "../headers/QuickArtLook.h"

// Static member initialization
bool GameFactory::initialized_ = false;

std::map<std::string, GameFactory::CreatorFunction>& GameFactory::getRegistry() {
    // Static local variable - constructed on first use
    static std::map<std::string, CreatorFunction> registry;

    return registry;
}

void GameFactory::initializeDefaultTypes() {
    if (initialized_) {
        return;
    }

    initialized_ = true;

    auto& registry = getRegistry();

    registry["ArtisticDelight"] = [](Difficulty difficulty) {
        return std::make_unique<ArtisticDelight>("Artistic Delight", difficulty);
    };

    registry["QuickArtLook"] = [](Difficulty difficulty) {
        return std::make_unique<QuickArtLook>("Quick Art Look", difficulty);
    };

    registry["ArtQuiz"] = [](Difficulty difficulty) {
        return std::make_unique<ArtQuiz>("Art Quiz", difficulty);
    };

    registry["ArtPuzzle"] = [](Difficulty difficulty) {
        return std::make_unique<ArtPuzzle>("Art Puzzle", difficulty);
    };

    std::cout << "[GameFactory] Default game types registered: " << registry.size()
              << " types available.\n";
}

std::unique_ptr<MiniGame> GameFactory::createGame(const std::string& type, Difficulty difficulty) {
    if (!initialized_) {
        initializeDefaultTypes();
    }
    auto& registry = getRegistry();

    auto it = registry.find(type);
    if (it == registry.end()) {
        throw InvalidGameException("Unknown game type: " + type);
    }

    std::cout << "[GameFactory] Creating the game: " << type << "\n";
    return it->second(difficulty);
}

void GameFactory::registerGame(const std::string& type, CreatorFunction creator) {
    if (!initialized_) {
        initializeDefaultTypes();
    }
    auto& registry = getRegistry();
    registry[type] = std::move(creator);
    std::cout << "[GameFactory] New game type registered: " << type << "\n";
}

std::vector<std::string> GameFactory::getAvailableTypes() {
    if (!initialized_) {
        initializeDefaultTypes();
    }
    std::vector<std::string> game_types;
    for (const auto& pair : getRegistry()) {
        game_types.push_back(pair.first);
    }
    return game_types;
}

bool GameFactory::isTypeRegistered(const std::string& type) {
    if (!initialized_) {
        initializeDefaultTypes();
    }
    auto& registry = getRegistry();
    return registry.find(type) != registry.end();
}
