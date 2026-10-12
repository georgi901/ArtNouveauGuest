#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class Collection
 * @brief Generic template class for managing gallery elements.
 * @tparam T The type of elements stored in the collection.
 *
 * Provides a type-safe container with search, filtering, sorting, and iteration
 * capabilities. Used for managing artists, paintings, and games.
 *
 * @note This class satisfies the Milestone 3 requirement for a template class
 * with at least two instantiations.
 *
 * @code
 * Collection<Artist> artists;
 * artists.add(std::make_shared<Artist>(...));
 * auto found = artists.findByPredicate([](const Artist& a) { return a.getName() == "Mucha"; });
 * @endcode
 */
template <typename T>
class Collection {
public:
    /**
     * @brief Default constructor - creates an empty collection.
     */
    Collection() = default;

    /**
     * @brief Adds an element to the collection.
     * @param element Shared pointer to the element to add.
     */
    void add(std::shared_ptr<T> element) {
        if (element) {
            elemente_.push_back(element);
        }
    }

    /**
     * @brief Removes an element from the collection.
     * @param element Shared pointer to the element to remove.
     * @return true if the element was found and removed, false otherwise.
     */
    bool remove(std::shared_ptr<T> element) {
        auto it = std::find(elemente_.begin(), elemente_.end(), element);
        if (it != elemente_.end()) {
            elemente_.erase(it);
            return true;
        }
        return false;
    }

    /**
     * @brief Gets an element by index.
     * @param index Element index (starting from 0).
     * @return Shared pointer to the element.
     * @throws std::out_of_range if the index is invalid.
     */
    std::shared_ptr<T> get(size_t index) const {
        if (index >= elemente_.size()) {
            throw std::out_of_range("Collection index out of bounds: " + std::to_string(index));
        }
        return elemente_[index];
    }

    /**
     * @brief Finds the first element that matches a predicate.
     * @param predicate Function returning true for the desired elements.
     * @return Shared pointer to the found element, or nullptr if not found.
     *
     * @code
     * auto artist = collection.findByPredicate([](const Artist& a) {
     *     return a.getNationality() == "Czech";
     * });
     * @endcode
     */
    std::shared_ptr<T> findByPredicate(std::function<bool(const T&)> predicate) const {
        for (const auto& element : elemente_) {
            if (element && predicate(*element)) {
                return element;
            }
        }
        return nullptr;
    }

    /**
     * @brief Filters elements that match a predicate.
     * @param predicate Function returning true for elements to include.
     * @return New collection containing only the matching elements.
     *
     * @code
     * auto rarePaintings = paintings.filter([](const Painting& t) {
     *     return t.isRare();
     * });
     * @endcode
     */
    Collection<T> filter(std::function<bool(const T&)> predicate) const {
        Collection<T> result;
        for (const auto& element : elemente_) {
            if (element && predicate(*element)) {
                result.add(element);
            }
        }
        return result;
    }

    /**
     * @brief Sorts the collection using a comparator.
     * @param comparator Function that compares two elements (returns true if the first is less than
     * the second).
     *
     * @code
     * artists.sort([](const Artist& a, const Artist& b) {
     *     return a.getName() < b.getName();
     * });
     * @endcode
     */
    void sort(std::function<bool(const T&, const T&)> comparator) {
        std::sort(elemente_.begin(), elemente_.end(),
                  [&comparator](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
                      return comparator(*a, *b);
                  });
    }

    /**
     * @brief Applies a function to each element (non-const version).
     * @param function Function to apply.
     */
    void forEach(std::function<void(T&)> function) {
        for (auto& element : elemente_) {
            if (element) {
                function(*element);
            }
        }
    }

    /**
     * @brief Applies a function to each element (const version).
     * @param function Function to apply.
     */
    void forEach(std::function<void(const T&)> function) const {
        for (const auto& element : elemente_) {
            if (element) {
                function(*element);
            }
        }
    }

    /**
     * @brief Gets the number of elements in the collection.
     * @return Number of elements.
     */
    size_t size() const {
        return elemente_.size();
    }

    /**
     * @brief Checks whether the collection is empty.
     * @return true if the collection is empty, false otherwise.
     */
    bool empty() const {
        return elemente_.empty();
    }

    /**
     * @brief Clears all elements from the collection.
     */
    void clear() {
        elemente_.clear();
    }

    /**
     * @brief Gets the internal vector (const reference).
     * @return Const reference to the internal vector.
     */
    const std::vector<std::shared_ptr<T>>& getAll() const {
        return elemente_;
    }

    // Support for iterators (for range-based for loops)
    typename std::vector<std::shared_ptr<T>>::iterator begin() {
        return elemente_.begin();
    }
    typename std::vector<std::shared_ptr<T>>::iterator end() {
        return elemente_.end();
    }
    typename std::vector<std::shared_ptr<T>>::const_iterator begin() const {
        return elemente_.begin();
    }
    typename std::vector<std::shared_ptr<T>>::const_iterator end() const {
        return elemente_.end();
    }

private:
    std::vector<std::shared_ptr<T>> elemente_;  ///< Internal storage for elements
};
