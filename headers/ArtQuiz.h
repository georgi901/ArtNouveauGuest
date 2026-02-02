/**
 * @file ArtQuiz.h
 * @brief Definește clasa ArtQuiz - joc de întrebări despre artă.
 *
 * Acest fișier conține clasa ArtQuiz care implementează un mini-joc
 * de tip quiz cu întrebări despre tablouri și artiști.
 */

#ifndef ARTNOUVEAUGUEST_ARTQUIZ_H
#define ARTNOUVEAUGUEST_ARTQUIZ_H
#include <memory>
#include <vector>

#include "MiniJoc.h"
#include "Tablou.h"

/**
 * @struct Intrebare
 * @brief Structură pentru reprezentarea unei întrebări din quiz.
 */
struct Intrebare {
    std::string text;
    std::string raspuns_corect;
    std::vector<std::string> variante;  // pentru întrebări cu variante
    int puncte = 0;                     ///< Punctele acordate pentru răspuns corect
};

/**
 * @class ArtQuiz
 * @brief Joc de tip quiz cu întrebări despre tablourile din galerie.
 *
 * Derivată din MiniJoc, această clasă implementează un joc de întrebări
 * care testează cunoștințele despre:
 * - Autorii tablourilor
 * - Anul realizării
 * - Tehnicile folosite
 * - Raritatea tablourilor
 *
 * Numărul de întrebări variază în funcție de dificultate:
 * - Ușor: 3 întrebări
 * - Mediu: 5 întrebări
 * - Greu: 7 întrebări (cu penalizare pentru răspunsuri greșite)
 *
 * @code
 * auto quiz = std::make_unique<ArtQuiz>("Quiz Art Nouveau", Dificultate::Mediu);
 * quiz->adaugaTablou(tablou);
 * quiz->initializeaza();
 * while (quiz->areIntrebariRamase()) {
 *     quiz->afiseazaIntrebareCurenta();
 *     quiz->raspunde(raspuns);
 *     quiz->urmatoraIntrebare();
 * }
 * @endcode
 */
class ArtQuiz : public MiniJoc {
private:
    std::vector<std::shared_ptr<Tablou>> tablouri_quiz;
    std::vector<Intrebare> intrebari;
    int intrebare_curenta = 0;
    int raspunsuri_corecte = 0;
    int raspunsuri_gresite = 0;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    ArtQuiz(const std::string& nume, Dificultate dif);
    ArtQuiz(const ArtQuiz& other);
    ~ArtQuiz() override = default;

    std::unique_ptr<MiniJoc> clone() const override;
    std::string getTipJoc() const override;

    // Funcții specifice
    void adaugaTablou(std::shared_ptr<Tablou> tablou);
    void genereazaIntrebari();
    void afiseazaIntrebareCurenta() const;
    bool raspunde(const std::string& raspuns);
    bool areIntrebariRamase() const;
    void urmatoraIntrebare();

    // Getteri
    int getRaspunsuriCorecte() const {
        return raspunsuri_corecte;
    }
    int getRaspunsuriGresite() const {
        return raspunsuri_gresite;
    }
    int getIntrebariRamase() const {
        return intrebari.size() - intrebare_curenta;
    }
};

#endif  // ARTNOUVEAUGUEST_ARTQUIZ_H