#ifndef ARTNOUVEAUGUEST_ARTISTICDELIGHT_H
#define ARTNOUVEAUGUEST_ARTISTICDELIGHT_H

#include "MiniJoc.h"
#include "Tablou.h"
#include <vector>
#include <memory>

class ArtisticDelight : public MiniJoc {
private:
    std::shared_ptr<Tablou> tablou_tinta;      // tabloul de recreat
    double scor_asemanare;                      // 0-100%
    std::vector<std::string> culori_folosite;
    int incercari_ramase;

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


    double getScorAsemanare() const { return scor_asemanare; }
    int getIncercariRamase() const { return incercari_ramase; }
    const std::vector<std::string>& getCulorifolosite() const { return culori_folosite; }
};

#endif //ARTNOUVEAUGUEST_ARTISTICDELIGHT_H