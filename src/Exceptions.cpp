/**
 * @file Exceptions.cpp
 * @brief Implementation of the gallery exception classes.
 *
 * Contains the implementation of constructors and methods for
 * all custom exception classes.
 */

#include "../headers/Exceptions.h"

GalleryException::GalleryException(const std::string& message) : message(message) {
}

const char* GalleryException::what() const noexcept {
    return message.c_str();
}

InsufficientPointsException::InsufficientPointsException(int available_points, int required_points)
    : GalleryException("Insufficient points: you have " + std::to_string(available_points) +
                       ", but you need " + std::to_string(required_points))
    , available_points(available_points)
    , required_points(required_points) {
}

int InsufficientPointsException::getAvailablePoints() const {
    return available_points;
}

int InsufficientPointsException::getRequiredPoints() const {
    return required_points;
}

int InsufficientPointsException::getMissingPoints() const {
    return required_points - available_points;
}

PaintingUnavailableException::PaintingUnavailableException(const std::string& painting_title)
    : GalleryException("The painting '" + painting_title + "' is not available")
    , painting_title(painting_title) {
}

const std::string& PaintingUnavailableException::getTitle() const {
    return painting_title;
}

InvalidGameException::InvalidGameException(const std::string& game_name)
    : GalleryException("The game '" + game_name + "' does not exist or cannot be started")
    , game_name(game_name) {
}

const std::string& InvalidGameException::getGameName() const {
    return game_name;
}

DataLoadingException::DataLoadingException(const std::string& file_path,
                                           const std::string& error_type)
    : GalleryException(error_type == "file" ? "Cannot open file: " + file_path
                                            : "Error parsing JSON from file: " + file_path)
    , details(file_path)
    , error_type(error_type) {
}

const std::string& DataLoadingException::getDetails() const {
    return details;
}

const std::string& DataLoadingException::getErrorType() const {
    return error_type;
}
