/**
 * @file ArtisticDelight.h
 * @brief Definește clasa ArtisticDelight - joc de ghicit culori.
 *
 * Acest fișier conține clasa ArtisticDelight care implementează un mini-joc
 * în care jucătorul trebuie să ghicească culorile folosite într-un tablou.
 */

#ifndef ARTNOUVEAUGUEST_ARTISTICDELIGHT_H
#define ARTNOUVEAUGUEST_ARTISTICDELIGHT_H

#include <memory>
#include <vector>

#include "MiniJoc.h"
#include "Tablou.h"

/**
 * @class ArtisticDelight
 * @brief Joc de ghicit culorile folosite într-un tablou celebru.
 *
 * Derivată din MiniJoc, această clasă implementează un joc creativ
 * în care jucătorul trebuie să ghicească culorile folosite de artist
 * în realizarea unui tablou.
 *
 * Numărul de încercări variază în funcție de dificultate:
 * - Ușor: 10 încercări
 * - Mediu: 7 încercări
 * - Greu: 5 încercări
 *
 * Scorul se calculează pe baza procentului de culori ghicite,
 * cu penalizări pentru culori greșite și bonus pentru încercări rămase.
 *
 * @code
 * auto joc = std::make_unique<ArtisticDelight>("Color Match", Dificultate::Mediu);
 * joc->seteazaTablou(tablou);
 * joc->initializeaza();
 * joc->picteaza("rosu");
 * joc->arataSugestie();
 * double scor = joc->evalueazaAsemanare();
 * @endcode
 */
class ArtisticDelight : public MiniJoc {
private:
    std::shared_ptr<Tablou> tablou_tinta;  // tabloul de recreat
    double scor_asemanare = 0.0;           // 0-100%
    std::vector<std::string> culori_folosite;
    int incercari_ramase = 0;

protected:
    void initializeaza_implementare() override;
    int calculeaza_puncte_implementare() override;
    void afiseaza_reguli_implementare() const override;

public:
    ArtisticDelight(const std::string& nume, Dificultate dif);

    ArtisticDelight(const ArtisticDelight& other);

    ~ArtisticDelight() override = default;

    std::unique_ptr<MiniJoc> clone() const override;

    std::string getTipJoc() const override;

    void seteazaTablou(std::shared_ptr<Tablou> tablou);
    void picteaza(const std::string& culoare);
    double evalueazaAsemanare();
    void arataSugestie() const;

    double getScorAsemanare() const {
        return scor_asemanare;
    }
    int getIncercariRamase() const {
        return incercari_ramase;
    }
    const std::vector<std::string>& getCulorifolosite() const {
        return culori_folosite;
    }
};

#endif  // ARTNOUVEAUGUEST_ARTISTICDELIGHT_H