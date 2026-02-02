/**
 * @file ArtPuzzle.h
 * @brief Definește clasa ArtPuzzle - joc de puzzle cu fragmente de tablou.
 *
 * Acest fișier conține clasa ArtPuzzle care implementează un mini-joc
 * de tip puzzle în care jucătorul aranjează fragmentele unui tablou.
 */

#ifndef ARTNOUVEAUGUEST_ARTPUZZLE_H
#define ARTNOUVEAUGUEST_ARTPUZZLE_H

#include <memory>
#include <vector>

#include "MiniJoc.h"
#include "Tablou.h"

/**
 * @class ArtPuzzle
 * @brief Joc de puzzle cu fragmente ale unui tablou celebru.
 *
 * Derivată din MiniJoc, această clasă implementează un joc de puzzle
 * în care jucătorul trebuie să aranjeze fragmentele unui tablou
 * în ordinea corectă (0, 1, 2, 3...).
 *
 * Configurația variază în funcție de dificultate:
 * - Ușor: 4 fragmente (2x2), 6 mutări maxime
 * - Mediu: 9 fragmente (3x3), 14 mutări maxime
 * - Greu: 16 fragmente (4x4), 22 mutări maxime
 *
 * Punctajul include bonus pentru mutările rămase neutilizate.
 *
 * @code
 * auto puzzle = std::make_unique<ArtPuzzle>("Puzzle Art", Dificultate::Mediu);
 * puzzle->seteazaTablou(tablou);
 * puzzle->initializeaza();
 * puzzle->afiseazaPuzzle();
 * puzzle->mutaFragment(0, 3);
 * if (puzzle->esteRezolvat()) {
 *     int puncte = puzzle->calculeazaPuncte();
 * }
 * @endcode
 */
class ArtPuzzle : public MiniJoc {
private:
    std::shared_ptr<Tablou> tablou_tinta;
    std::vector<int> ordine_fragmente;
    std::vector<int> ordine_corecta;
    int numar_fragmente;
    int mutari_efectuate;
    int mutari_maxime;
    bool rezolvat;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    ArtPuzzle(const std::string& nume, Dificultate dif);
    ArtPuzzle(const ArtPuzzle& other);
    ~ArtPuzzle() override;

    void seteazaTablou(std::shared_ptr<Tablou> tablou);
    void amestecaFragmente();
    bool mutaFragment(int pozitie1, int pozitie2);
    bool esteRezolvat() const;
    void afiseazaPuzzle() const;

    int getMutariEfectuate() const {
        return mutari_efectuate;
    }
    int getMutariRamase() const {
        return mutari_maxime - mutari_efectuate;
    }
    int getNumarFragmente() const {
        return numar_fragmente;
    }

    std::unique_ptr<MiniJoc> clone() const override;
    std::string getTipJoc() const override;
};

#endif  // ARTNOUVEAUGUEST_ARTPUZZLE_H