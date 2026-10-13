/**
 * @file Exceptions.cpp
 * @brief Implementation of the gallery exception classes.
 *
 * Contains the implementation of constructors and methods for
 * all custom exception classes.
 */

#include "../headers/Exceptions.h"

GalleryException::GalleryException(const std::string& message_value) : message(message_value) {
}

const char* GalleryException::what() const noexcept {
    return message.c_str();
}

InsufficientPointsException::InsufficientPointsException(int available_points_value,
                                                         int required_points_value)
    : GalleryException("Insufficient points: you have " + std::to_string(available_points_value) +
                       ", but you need " + std::to_string(required_points_value))
    , available_points(available_points_value)
    , required_points(required_points_value) {
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

PaintingUnavailableException::PaintingUnavailableException(const std::string& painting_title_value)
    : GalleryException("The painting '" + painting_title_value + "' is not available")
    , painting_title(painting_title_value) {
}

const std::string& PaintingUnavailableException::getTitle() const {
    return painting_title;
}

InvalidGameException::InvalidGameException(const std::string& game_name_value)
    : GalleryException("The game '" + game_name_value + "' does not exist or cannot be started")
    , game_name(game_name_value) {
}

const std::string& InvalidGameException::getGameName() const {
    return game_name;
}

DataLoadingException::DataLoadingException(const std::string& file_path_value,
                                           const std::string& error_type_value)
    : GalleryException(error_type_value == "file" ? "Cannot open file: " + file_path_value
                                                  : "Error parsing JSON from file: " + file_path_value)
    , details(file_path_value)
    , error_type(error_type_value) {
}

const std::string& DataLoadingException::getDetails() const {
    return details;
}

const std::string& DataLoadingException::getErrorType() const {
    return error_type;
}
