/**
 * @file QuickArtLook.h
 * @brief Definește clasa QuickArtLook - joc de asociere tablouri-artiști.
 *
 * Acest fișier conține clasa QuickArtLook care implementează un mini-joc
 * în care jucătorul trebuie să asocieze tablourile cu artiștii corecți.
 */

#ifndef ARTNOUVEAUGUEST_QUICKARTLOOK_H
#define ARTNOUVEAUGUEST_QUICKARTLOOK_H

#include <memory>
#include <utility>
#include <vector>

#include "Artist.h"
#include "MiniJoc.h"
#include "Tablou.h"

/**
 * @class QuickArtLook
 * @brief Joc de asociere între tablouri și artiștii lor.
 *
 * Derivată din MiniJoc, această clasă implementează un joc de potrivire
 * în care jucătorul trebuie să identifice corect artistul fiecărui tablou.
 *
 * Numărul de perechi variază în funcție de dificultate:
 * - Ușor: 3 perechi
 * - Mediu: 5 perechi
 * - Greu: 8 perechi
 *
 * Punctajul este calculat pe baza procentului de perechi corecte,
 * cu penalizări pentru răspunsurile greșite.
 *
 * @code
 * auto joc = std::make_unique<QuickArtLook>("Quick Art", Dificultate::Mediu);
 * joc->adaugaPereche(tablou, artist);
 * joc->initializeaza();
 * joc->afiseazaTablele();
 * joc->afiseazaArtisti();
 * joc->verificaPereche("Zodiac", "Mucha");
 * @endcode
 */
class QuickArtLook : public MiniJoc {
private:
    std::vector<std::pair<std::shared_ptr<Tablou>, std::shared_ptr<Artist>>> perechi;
    int perechi_corecte = 0;
    int perechi_gresite = 0;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    QuickArtLook(const std::string& nume, Dificultate dif);
    QuickArtLook(const QuickArtLook& other);
    ~QuickArtLook() override = default;

    std::unique_ptr<MiniJoc> clone() const override;
    std::string getTipJoc() const override;

    void adaugaPereche(std::shared_ptr<Tablou> tablou, std::shared_ptr<Artist> artist);
    void afiseazaTablele() const;
    void afiseazaArtisti() const;
    bool verificaPereche(const std::string& titlu_tablou, const std::string& nume_artist);
    void amestecaPerechile();

    int getPerechilCorecte() const {
        return perechi_corecte;
    }
    int getPerechileGresite() const {
        return perechi_gresite;
    }
    int getTotalPerechi() const {
        return perechi.size();
    }
};

#endif  // ARTNOUVEAUGUEST_QUICKARTLOOK_HH