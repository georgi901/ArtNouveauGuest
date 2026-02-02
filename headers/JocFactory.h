
/**
 * @file JocFactory.h
 * @brief Implementare Factory Pattern pentru crearea instanțelor de mini-jocuri.
 *
 * Acest fișier implementează design pattern-ul Factory, care este unul din
 * cele două pattern-uri cerute pentru Milestone 3.
 */

#ifndef ARTNOUVEAUGUEST_JOCFACTORY_H
#define ARTNOUVEAUGUEST_JOCFACTORY_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MiniJoc.h"

// Declarații forward
class ArtisticDelight;
class QuickArtLook;
class ArtQuiz;
class ArtPuzzle;

/**
 * @class JocFactory
 * @brief Clasă Factory pentru crearea instanțelor de mini-jocuri.
 *
 * Implementează design pattern-ul Factory, permițând crearea jocurilor
 * fără a expune instanțierea claselor concrete către codul client.
 * Suportă înregistrarea de tipuri noi de jocuri la runtime.
 *
 * @note Această clasă îndeplinește cerința M3 pentru design pattern.
 *
 * Beneficiile pattern-ului Factory:
 * - Decuplează crearea jocurilor de utilizare
 * - Ușor de adăugat tipuri noi de jocuri fără a modifica codul existent
 * - Centralizează logica de instanțiere
 *
 * @code
 * // Creează un joc folosind factory-ul
 * auto joc = JocFactory::creeazaJoc("ArtQuiz", Dificultate::Mediu);
 * joc->initializeaza();
 *
 * // Obține toate tipurile de jocuri disponibile
 * auto tipuri = JocFactory::obtineTipuriDisponibile();
 * @endcode
 */
class JocFactory {
public:
    /// Alias pentru funcțiile de creare a jocurilor
    using FunctieCreator = std::function<std::unique_ptr<MiniJoc>(Dificultate)>;

    /**
     * @brief Creează un mini-joc de tipul specificat.
     * @param tip Tipul jocului de creat.
     *        Tipuri valide: "ArtisticDelight", "QuickArtLook", "ArtQuiz", "ArtPuzzle"
     * @param dificultate Nivelul de dificultate pentru noul joc.
     * @return Pointer unic către jocul creat.
     * @throws JocInvalidException dacă tipul de joc nu este înregistrat.
     *
     * @code
     * auto quiz = JocFactory::creeazaJoc("ArtQuiz", Dificultate::Greu);
     * quiz->afiseazaRegulile();
     * @endcode
     */
    static std::unique_ptr<MiniJoc> creeazaJoc(const std::string& tip, Dificultate dificultate);

    /**
     * @brief Înregistrează un nou tip de joc cu funcția sa de creare.
     * @param tip Numele tipului de joc (folosit ca cheie).
     * @param creator Funcție care creează instanțe ale jocului.
     *
     * Permite extinderea factory-ului fără a modifica codul sursă.
     *
     * @code
     * // Înregistrează un tip de joc personalizat
     * JocFactory::inregistreazaJoc("JocNou", [](Dificultate d) {
     *     return std::make_unique<JocNou>("Joc Nou", d);
     * });
     * @endcode
     */
    static void inregistreazaJoc(const std::string& tip, FunctieCreator creator);

    /**
     * @brief Obține toate numele tipurilor de jocuri înregistrate.
     * @return Vector cu numele tipurilor de jocuri disponibile.
     *
     * @code
     * for (const auto& tip : JocFactory::obtineTipuriDisponibile()) {
     *     std::cout << "Disponibil: " << tip << std::endl;
     * }
     * @endcode
     */
    static std::vector<std::string> obtineTipuriDisponibile();

    /**
     * @brief Verifică dacă un tip de joc este înregistrat.
     * @param tip Numele tipului de joc de verificat.
     * @return true dacă tipul este înregistrat, false altfel.
     */
    static bool esteTipInregistrat(const std::string& tip);

private:
    /**
     * @brief Obține registrul singleton al creatorilor de jocuri.
     * @return Referință către map-ul intern de creatori.
     *
     * Folosește idiomul "construct on first use" pentru a evita
     * problemele de ordine de inițializare statică.
     */
    static std::map<std::string, FunctieCreator>& obtineRegistru();

    /**
     * @brief Inițializează tipurile implicite de jocuri în registru.
     *
     * Apelat automat la primul acces la registru.
     */
    static void initializeazaTipuriImplicite();

    static bool initializat_;  ///< Flag pentru a urmări dacă tipurile implicite sunt înregistrate
};

#endif  // ARTNOUVEAUGUEST_JOCFACTORY_H