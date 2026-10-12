#pragma once

/**
 * @file GameFactory.h
 * @brief Implementation of the Factory pattern for creating mini-game instances.
 *
 * This file implements the Factory pattern, which is one of the two required
 * design patterns for Milestone 3.
 */

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MiniGame.h"

// Forward declarations
class ArtisticDelight;
class QuickArtLook;
class ArtQuiz;
class ArtPuzzle;

/**
 * @class GameFactory
 * @brief Factory class for creating mini-game instances.
 *
 * Implements the Factory pattern, allowing game creation without exposing the
 * concrete class instantiation to client code. It also supports registering new
 * game types at runtime.
 *
 * @note This class satisfies the Milestone 3 design pattern requirement.
 *
 * Benefits of the Factory pattern:
 * - Decouples game creation from usage
 * - Makes it easy to add new game types without modifying existing code
 * - Centralizes instantiation logic
 *
 * @code
 * // Create a game using the factory
 * auto game = GameFactory::createGame("ArtQuiz", Difficulty::Medium);
 * game->initialize();
 *
 * // Get all available game types
 * auto types = GameFactory::getAvailableTypes();
 * @endcode
 */
class GameFactory {
public:
    /// Alias for game creation functions
    using CreatorFunction = std::function<std::unique_ptr<MiniGame>(Difficulty)>;

    /**
     * @brief Creates a mini-game of the specified type.
     * @param type The type of game to create.
     *        Valid types: "ArtisticDelight", "QuickArtLook", "ArtQuiz", "ArtPuzzle"
     * @param difficulty The difficulty level for the new game.
     * @return Unique pointer to the created game.
     * @throws InvalidGameException if the game type is not registered.
     *
     * @code
     * auto quiz = GameFactory::createGame("ArtQuiz", Difficulty::Hard);
     * quiz->displayRules();
     * @endcode
     */
    static std::unique_ptr<MiniGame> createGame(const std::string& type, Difficulty difficulty);

    /**
     * @brief Registers a new game type with its creator function.
     * @param type The name of the game type (used as the key).
     * @param creator Function that creates instances of the game.
     *
     * Allows extending the factory without modifying the source code.
     *
     * @code
     * // Register a custom game type
     * GameFactory::registerGame("NewGame", [](Difficulty d) {
     *     return std::make_unique<NewGame>("New Game", d);
     * });
     * @endcode
     */
    static void registerGame(const std::string& type, CreatorFunction creator);

    /**
     * @brief Get all registered game type names.
     * @return Vector containing the registered game type names.
     *
     * @code
     * for (const auto& type : GameFactory::getAvailableTypes()) {
     *     std::cout << "Available: " << type << std::endl;
     * }
     * @endcode
     */
    static std::vector<std::string> getAvailableTypes();

    /**
     * @brief Check if a game type is registered.
     * @param type The game type name to verify.
     * @return true if the type is registered, false otherwise.
     */
    static bool isTypeRegistered(const std::string& type);

private:
    /**
     * @brief Get the singleton registry of game creators.
     * @return Reference to the internal map of creators.
     *
     * Uses the "construct on first use" idiom to avoid static initialization order
     * issues.
     */
    static std::map<std::string, CreatorFunction>& getRegistry();

    /**
     * @brief Initializes the default game types in the registry.
     *
     * Called automatically on the first access to the registry.
     */
    static void initializeDefaultTypes();

    static bool initialized_;  ///< Flag tracking whether default types are registered
};
