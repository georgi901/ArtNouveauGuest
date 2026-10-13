#pragma once

/**
 * @file Exceptions.h
 * @brief Defines the exception hierarchy for the gallery application.
 *
 * This file contains the custom exception classes used for managing errors in the
 * art gallery application. All exceptions derive from GalleryException.
 */

#include <exception>
#include <string>

/**
 * @class GalleryException
 * @brief Base class for all exceptions in the gallery application.
 *
 * Derived from std::exception, this class provides a uniform mechanism for error
 * handling across the application.
 *
 * @code
 * try {
 *     // operation that may fail
 * } catch (const GalleryException& e) {
 *     std::cerr << "Gallery error: " << e.what() << std::endl;
 * }
 * @endcode
 */
class GalleryException : public std::exception {
protected:
    std::string message;

public:
    explicit GalleryException(const std::string& message);
    const char* what() const noexcept override;
};

/**
 * @class InsufficientPointsException
 * @brief Exception thrown when the user does not have enough points.
 *
 * Used when attempting a purchase with insufficient points. It provides
 * information about the available and required points.
 *
 * @code
 * if (points < cost) {
 *     throw InsufficientPointsException(points, cost);
 * }
 * @endcode
 */
class InsufficientPointsException : public GalleryException {
private:
    int available_points = 0;
    int required_points = 0;

public:
    explicit InsufficientPointsException(int available_points, int required_points);
    int getAvailablePoints() const;
    int getRequiredPoints() const;
    int getMissingPoints() const;
};

/**
 * @class PaintingUnavailableException
 * @brief Exception thrown when a painting is not available for purchase.
 *
 * Used when trying to buy a painting that is already collected.
 *
 * @code
 * if (painting->isCollected()) {
 *     throw PaintingUnavailableException(painting->getTitle());
 * }
 * @endcode
 */
class PaintingUnavailableException : public GalleryException {
private:
    std::string painting_title;

public:
    explicit PaintingUnavailableException(const std::string& title);
    const std::string& getTitle() const;
};

/**
 * @class InvalidGameException
 * @brief Exception thrown when an invalid game is requested.
 *
 * Used when the requested game does not exist or cannot be started.
 *
 * @code
 * auto game = gallery.findGame(name);
 * if (!game) {
 *     throw InvalidGameException(name);
 * }
 * @endcode
 */
class InvalidGameException : public GalleryException {
private:
    std::string game_name;

public:
    explicit InvalidGameException(const std::string& game_name);
    const std::string& getGameName() const;
};

/**
 * @class DataLoadingException
 * @brief Exception thrown when data loading from files fails.
 *
 * Used when there are problems reading or parsing JSON files. It can indicate a
 * file opening error or parsing error.
 *
 * @code
 * std::ifstream input(file_path);
 * if (!input.is_open()) {
 *     throw DataLoadingException(file_path, "file");
 * }
 * @endcode
 */
class DataLoadingException : public GalleryException {
private:
    std::string details;
    std::string error_type;

public:
    DataLoadingException(const std::string& file_path, const std::string& error_type);
    const std::string& getDetails() const;
    const std::string& getErrorType() const;
};
