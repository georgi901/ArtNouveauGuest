/**
 * @file Utils.h
 * @brief Funcții șablon utilitare pentru aplicația galeriei.
 *
 * Acest fișier conține funcții șablon care pot lucra cu orice tip
 * care are metodele necesare. Aceste funcții îndeplinesc cerința M3
 * pentru funcții șablon cu minim 2 instanțieri.
 */

#ifndef ARTNOUVEAUGUEST_UTILS_H
#define ARTNOUVEAUGUEST_UTILS_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Găsește un element după nume într-un vector de pointeri shared.
 * @tparam T Tipul elementelor (trebuie să aibă metoda getNume()).
 * @param elemente Vector de pointeri shared către elemente.
 * @param nume Numele de căutat.
 * @return Pointer shared către elementul găsit, sau nullptr dacă nu există.
 *
 * @note Această funcție șablon va fi instanțiată pentru tipurile Artist și Tablou.
 *
 * @code
 * // Instanțiere 1: cautaDupaNume<Artist>
 * auto artist = cautaDupaNume(listaArtisti, "Mucha");
 *
 * // Instanțiere 2: cautaDupaNume<Tablou>
 * auto tablou = cautaDupaNume(listaTablouri, "Zodiac");
 * @endcode
 */
template <typename T>
std::shared_ptr<T> cautaDupaNume(const std::vector<std::shared_ptr<T>>& elemente, const std::string& nume) {
    auto it = std::find_if(elemente.begin(), elemente.end(), [&nume](const std::shared_ptr<T>& element) {
        return element && element->getNume() == nume;
    });
    return (it != elemente.end()) ? *it : nullptr;
}

/**
 * @brief Găsește un element după un câmp personalizat.
 * @tparam T Tipul elementelor.
 * @param elemente Vector de pointeri shared către elemente.
 * @param valoare Valoarea de căutat.
 * @param getter Funcție care extrage câmpul de comparat.
 * @return Pointer shared către elementul găsit, sau nullptr dacă nu există.
 *
 * @code
 * auto tablou = cautaDupaCamp(tablouri, "Zodiac",
 *     [](const Tablou& t) { return t.getTitlu(); });
 * @endcode
 */
template <typename T>
std::shared_ptr<T> cautaDupaCamp(const std::vector<std::shared_ptr<T>>& elemente, const std::string& valoare,
                                 std::function<std::string(const T&)> getter) {
    auto it = std::find_if(elemente.begin(), elemente.end(), [&valoare, &getter](const std::shared_ptr<T>& element) {
        return element && getter(*element) == valoare;
    });
    return (it != elemente.end()) ? *it : nullptr;
}

/**
 * @brief Afișează toate elementele dintr-o colecție.
 * @tparam T Tipul elementelor (trebuie să suporte operator<<).
 * @param elemente Vector de pointeri shared către elemente.
 * @param os Stream-ul de ieșire.
 * @param titlu Titlu opțional de afișat înainte de elemente.
 *
 * @note Această funcție șablon va fi instanțiată pentru tipurile Artist și Tablou.
 *
 * @code
 * // Instanțiere 1: afiseazaToate<Artist>
 * afiseazaToate(artisti, std::cout, "=== Artiști ===");
 *
 * // Instanțiere 2: afiseazaToate<Tablou>
 * afiseazaToate(tablouri, std::cout, "=== Tablouri ===");
 * @endcode
 */
template <typename T>
void afiseazaToate(const std::vector<std::shared_ptr<T>>& elemente, std::ostream& os, const std::string& titlu = "") {
    if (!titlu.empty()) {
        os << "\n" << titlu << "\n";
        os << std::string(titlu.length(), '-') << "\n";
    }

    if (elemente.empty()) {
        os << "(Nu s-au găsit elemente)\n";
        return;
    }

    for (size_t i = 0; i < elemente.size(); ++i) {
        if (elemente[i]) {
            os << (i + 1) << ". " << *elemente[i] << "\n";
        }
    }
}

/**
 * @brief Filtrează elementele bazat pe un predicat.
 * @tparam T Tipul elementelor.
 * @param elemente Vector de pointeri shared către elemente.
 * @param predicat Funcție care returnează true pentru elementele de păstrat.
 * @return Vector nou conținând doar elementele care îndeplinesc predicatul.
 *
 * @note Această funcție șablon va fi instanțiată pentru tipurile Artist și Tablou.
 *
 * @code
 * // Instanțiere 1: filtreazaElemente<Tablou>
 * auto tablouriRare = filtreazaElemente(tablouri, [](const Tablou& t) { return t.este_rar(); });
 *
 * // Instanțiere 2: filtreazaElemente<Artist>
 * auto artistiInViata = filtreazaElemente(artisti, [](const Artist& a) { return a.getAnDeces() == 0; });
 * @endcode
 */
template <typename T>
std::vector<std::shared_ptr<T>> filtreazaElemente(const std::vector<std::shared_ptr<T>>& elemente,
                                                  std::function<bool(const T&)> predicat) {
    std::vector<std::shared_ptr<T>> rezultat;
    std::copy_if(elemente.begin(), elemente.end(), std::back_inserter(rezultat),
                 [&predicat](const std::shared_ptr<T>& element) { return element && predicat(*element); });
    return rezultat;
}

/**
 * @brief Numără elementele care îndeplinesc un predicat.
 * @tparam T Tipul elementelor.
 * @param elemente Vector de pointeri shared către elemente.
 * @param predicat Funcție care returnează true pentru elementele de numărat.
 * @return Numărul de elemente care îndeplinesc predicatul.
 *
 * @code
 * int nrRare = numaraElemente(tablouri, [](const Tablou& t) { return t.este_rar(); });
 * @endcode
 */
template <typename T>
int numaraElemente(const std::vector<std::shared_ptr<T>>& elemente, std::function<bool(const T&)> predicat) {
    return static_cast<int>(
        std::count_if(elemente.begin(), elemente.end(),
                      [&predicat](const std::shared_ptr<T>& element) { return element && predicat(*element); }));
}

/**
 * @brief Calculează suma unei proprietăți numerice pentru toate elementele.
 * @tparam T Tipul elementelor.
 * @tparam R Tipul returnat de getter (trebuie să fie numeric).
 * @param elemente Vector de pointeri shared către elemente.
 * @param getter Funcție care extrage valoarea proprietății.
 * @return Suma tuturor valorilor proprietății.
 *
 * @code
 * int totalPuncte = sumaProprietate<Utilizator, int>(utilizatori,
 *     [](const Utilizator& u) { return u.getPuncte(); });
 * @endcode
 */
template <typename T, typename R>
R sumaProprietate(const std::vector<std::shared_ptr<T>>& elemente, std::function<R(const T&)> getter) {
    R suma = R();
    for (const auto& element : elemente) {
        if (element) {
            suma += getter(*element);
        }
    }
    return suma;
}

/**
 * @brief Transformă o colecție aplicând o funcție fiecărui element.
 * @tparam T Tipul sursă.
 * @tparam R Tipul rezultat.
 * @param elemente Vector de pointeri shared către elementele sursă.
 * @param transformator Funcție care transformă T în R.
 * @return Vector de rezultate transformate.
 *
 * @code
 * auto nume = transforma<Artist, std::string>(artisti,
 *     [](const Artist& a) { return a.getNume(); });
 * @endcode
 */
template <typename T, typename R>
std::vector<R> transforma(const std::vector<std::shared_ptr<T>>& elemente, std::function<R(const T&)> transformator) {
    std::vector<R> rezultat;
    rezultat.reserve(elemente.size());
    for (const auto& element : elemente) {
        if (element) {
            rezultat.push_back(transformator(*element));
        }
    }
    return rezultat;
}

#endif  // ARTNOUVEAUGUEST_UTILS_H