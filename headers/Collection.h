
#ifndef ARTNOUVEAUGUEST_COLLECTION_H
#define ARTNOUVEAUGUEST_COLLECTION_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class Collection
 * @brief Clasă șablon generică pentru gestionarea elementelor din galerie.
 * @tparam T Tipul elementelor stocate în colecție.
 *
 * Oferă un container type-safe cu funcționalități de căutare, filtrare,
 * sortare și iterare. Folosită pentru gestionarea Artiștilor, Tablourilor și Jocurilor.
 *
 * @note Această clasă îndeplinește cerința M3 pentru clasă șablon cu minim 2 instanțieri.
 *
 * @code
 * Collection<Artist> artisti;
 * artisti.adauga(std::make_shared<Artist>(...));
 * auto gasit = artisti.cautaDupaPredicate([](const Artist& a) { return a.getNume() == "Mucha"; });
 * @endcode
 */
template <typename T>
class Collection {
public:
    /**
     * @brief Constructor implicit - creează o colecție goală.
     */
    Collection() = default;

    /**
     * @brief Adaugă un element în colecție.
     * @param element Pointer shared către elementul de adăugat.
     */
    void adauga(std::shared_ptr<T> element) {
        if (element) {
            elemente_.push_back(element);
        }
    }

    /**
     * @brief Elimină un element din colecție.
     * @param element Pointer shared către elementul de eliminat.
     * @return true dacă elementul a fost găsit și eliminat, false altfel.
     */
    bool elimina(std::shared_ptr<T> element) {
        auto it = std::find(elemente_.begin(), elemente_.end(), element);
        if (it != elemente_.end()) {
            elemente_.erase(it);
            return true;
        }
        return false;
    }

    /**
     * @brief Obține un element după index.
     * @param index Indexul elementului (începând de la 0).
     * @return Pointer shared către element.
     * @throws std::out_of_range dacă indexul este invalid.
     */
    std::shared_ptr<T> obtine(size_t index) const {
        if (index >= elemente_.size()) {
            throw std::out_of_range("Index colecție în afara limitelor: " + std::to_string(index));
        }
        return elemente_[index];
    }

    /**
     * @brief Găsește primul element care îndeplinește un predicat.
     * @param predicat Funcție care returnează true pentru elementele căutate.
     * @return Pointer shared către elementul găsit, sau nullptr dacă nu există.
     *
     * @code
     * auto artist = colectie.cautaDupaPredicate([](const Artist& a) {
     *     return a.getNationalitate() == "Czech";
     * });
     * @endcode
     */
    std::shared_ptr<T> cautaDupaPredicate(std::function<bool(const T&)> predicat) const {
        for (const auto& element : elemente_) {
            if (element && predicat(*element)) {
                return element;
            }
        }
        return nullptr;
    }

    /**
     * @brief Filtrează elementele care îndeplinesc un predicat.
     * @param predicat Funcție care returnează true pentru elementele de inclus.
     * @return Colecție nouă conținând doar elementele care îndeplinesc predicatul.
     *
     * @code
     * auto tablouriRare = tablouri.filtreaza([](const Tablou& t) {
     *     return t.este_rar();
     * });
     * @endcode
     */
    Collection<T> filtreaza(std::function<bool(const T&)> predicat) const {
        Collection<T> rezultat;
        for (const auto& element : elemente_) {
            if (element && predicat(*element)) {
                rezultat.adauga(element);
            }
        }
        return rezultat;
    }

    /**
     * @brief Sortează colecția folosind un comparator.
     * @param comparator Funcție care compară două elemente (returnează true dacă primul < al doilea).
     *
     * @code
     * artisti.sorteaza([](const Artist& a, const Artist& b) {
     *     return a.getNume() < b.getNume();
     * });
     * @endcode
     */
    void sorteaza(std::function<bool(const T&, const T&)> comparator) {
        std::sort(
            elemente_.begin(), elemente_.end(),
            [&comparator](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) { return comparator(*a, *b); });
    }

    /**
     * @brief Aplică o funcție fiecărui element (versiune non-const).
     * @param functie Funcție de aplicat.
     */
    void pentruFiecare(std::function<void(T&)> functie) {
        for (auto& element : elemente_) {
            if (element) {
                functie(*element);
            }
        }
    }

    /**
     * @brief Aplică o funcție fiecărui element (versiune const).
     * @param functie Funcție de aplicat.
     */
    void pentruFiecare(std::function<void(const T&)> functie) const {
        for (const auto& element : elemente_) {
            if (element) {
                functie(*element);
            }
        }
    }

    /**
     * @brief Obține numărul de elemente din colecție.
     * @return Numărul de elemente.
     */
    size_t dimensiune() const {
        return elemente_.size();
    }

    /**
     * @brief Verifică dacă colecția este goală.
     * @return true dacă este goală, false altfel.
     */
    bool esteGoala() const {
        return elemente_.empty();
    }

    /**
     * @brief Șterge toate elementele din colecție.
     */
    void goleste() {
        elemente_.clear();
    }

    /**
     * @brief Obține vectorul intern (referință const).
     * @return Referință const către vectorul intern.
     */
    const std::vector<std::shared_ptr<T>>& obtineToate() const {
        return elemente_;
    }

    // Suport pentru iteratori (pentru range-based for loops)
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
    std::vector<std::shared_ptr<T>> elemente_;  ///< Stocare internă pentru elemente
};

#endif  // ARTNOUVEAUGUEST_COLLECTION_H