#pragma once

/**
 * @file Utils.h
 * @brief Utility template functions for the gallery application.
 *
 * This file contains template functions that can work with any type that has the
 * required methods. These functions satisfy the Milestone 3 requirement for
 * template functions with at least two instantiations.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Finds an element by name in a vector of shared pointers.
 * @tparam T The element type (must have a getName() method).
 * @param elements Vector of shared pointers to elements.
 * @param name The name to search for.
 * @return Shared pointer to the found element, or nullptr if not found.
 *
 * @note This template function will be instantiated for the Artist and Painting types.
 *
 * @code
 * // Instantiation 1: findByName<Artist>
 * auto artist = findByName(artists, "Mucha");
 *
 * // Instantiation 2: findByName<Painting>
 * auto painting = findByName(paintings, "Zodiac");
 * @endcode
 */
template <typename T>
std::shared_ptr<T> findByName(const std::vector<std::shared_ptr<T>>& elements,
                              const std::string& name) {
    auto it =
        std::find_if(elements.begin(), elements.end(), [&name](const std::shared_ptr<T>& element) {
            return element && element->getName() == name;
        });
    return (it != elements.end()) ? *it : nullptr;
}

/**
 * @brief Finds an element using a custom field.
 * @tparam T The element type.
 * @param elements Vector of shared pointers to elements.
 * @param value The value to search for.
 * @param getter Function that extracts the compared field.
 * @return Shared pointer to the found element, or nullptr if not found.
 *
 * @code
 * auto painting = findByField(paintings, "Zodiac",
 *     [](const Painting& t) { return t.getTitle(); });
 * @endcode
 */
template <typename T>
std::shared_ptr<T> findByField(const std::vector<std::shared_ptr<T>>& elements,
                               const std::string& value,
                               std::function<std::string(const T&)> getter) {
    auto it = std::find_if(elements.begin(), elements.end(),
                           [&value, &getter](const std::shared_ptr<T>& element) {
                               return element && getter(*element) == value;
                           });
    return (it != elements.end()) ? *it : nullptr;
}

/**
 * @brief Displays all elements in a collection.
 * @tparam T Element type (must support operator<<).
 * @param elements Vector of shared pointers to elements.
 * @param os Output stream.
 * @param title Optional title to display before the elements.
 *
 * @note This template function will be instantiated for the Artist and Painting types.
 *
 * @code
 * // Instantiation 1: displayAll<Artist>
 * displayAll(artists, std::cout, "=== Artists ===");
 *
 * // Instantiation 2: displayAll<Painting>
 * displayAll(paintings, std::cout, "=== Paintings ===");
 * @endcode
 */
template <typename T>
void displayAll(const std::vector<std::shared_ptr<T>>& elements, std::ostream& os,
                const std::string& title = "") {
    if (!title.empty()) {
        os << "\n" << title << "\n";
        os << std::string(title.length(), '-') << "\n";
    }

    if (elements.empty()) {
        os << "(No elements found)\n";
        return;
    }

    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i]) {
            os << (i + 1) << ". " << *elements[i] << "\n";
        }
    }
}

/**
 * @brief Filters elements based on a predicate.
 * @tparam T The element type.
 * @param elements Vector of shared pointers to elements.
 * @param predicate Function returning true for elements to keep.
 * @return New vector containing only the matching elements.
 *
 * @note This template function will be instantiated for the Artist and Painting types.
 *
 * @code
 * // Instantiation 1: filterElements<Painting>
 * auto rarePaintings = filterElements(paintings, [](const Painting& t) { return t.isRare(); });
 *
 * // Instantiation 2: filterElements<Artist>
 * auto livingArtists = filterElements(artists, [](const Artist& a) { return a.getDeathYear() == 0;
 * });
 * @endcode
 */
template <typename T>
std::vector<std::shared_ptr<T>> filterElements(const std::vector<std::shared_ptr<T>>& elements,
                                               std::function<bool(const T&)> predicate) {
    std::vector<std::shared_ptr<T>> result;
    std::copy_if(
        elements.begin(), elements.end(), std::back_inserter(result),
        [&predicate](const std::shared_ptr<T>& element) { return element && predicate(*element); });
    return result;
}

/**
 * @brief Counts the elements that satisfy a predicate.
 * @tparam T The element type.
 * @param elements Vector of shared pointers to elements.
 * @param predicate Function returning true for elements to count.
 * @return Number of matching elements.
 *
 * @code
 * int rareCount = countElements(paintings, [](const Painting& t) { return t.isRare(); });
 * @endcode
 */
template <typename T>
int countElements(const std::vector<std::shared_ptr<T>>& elements,
                  std::function<bool(const T&)> predicate) {
    return static_cast<int>(std::count_if(elements.begin(), elements.end(),
                                          [&predicate](const std::shared_ptr<T>& element) {
                                              return element && predicate(*element);
                                          }));
}

/**
 * @brief Calculates the sum of a numeric property for all elements.
 * @tparam T The element type.
 * @tparam R The return type of the getter (must be numeric).
 * @param elements Vector of shared pointers to elements.
 * @param getter Function that extracts the property value.
 * @return Sum of all property values.
 *
 * @code
 * int totalPoints = sumProperty<User, int>(users,
 *     [](const User& u) { return u.getPoints(); });
 * @endcode
 */
template <typename T, typename R>
R sumProperty(const std::vector<std::shared_ptr<T>>& elements, std::function<R(const T&)> getter) {
    R sum = R();
    for (const auto& element : elements) {
        if (element) {
            sum += getter(*element);
        }
    }
    return sum;
}

/**
 * @brief Transforms a collection by applying a function to each element.
 * @tparam T Source type.
 * @tparam R Result type.
 * @param elements Vector of source shared pointers.
 * @param transformer Function that transforms T into R.
 * @return Vector of transformed results.
 *
 * @code
 * auto name = transform<Artist, std::string>(artists,
 *     [](const Artist& a) { return a.getName(); });
 * @endcode
 */
template <typename T, typename R>
std::vector<R> transform(const std::vector<std::shared_ptr<T>>& elements,
                         std::function<R(const T&)> transformer) {
    std::vector<R> result;
    result.reserve(elements.size());
    for (const auto& element : elements) {
        if (element) {
            result.push_back(transformer(*element));
        }
    }
    return result;
}
