#ifndef ARTNOUVEAUGUEST_QUICKARTLOOK_H
#define ARTNOUVEAUGUEST_QUICKARTLOOK_H

#include "MiniJoc.h"
#include "Tablou.h"
#include "Artist.h"
#include <vector>
#include <memory>
#include <utility>

class QuickArtLook : public MiniJoc {
private:
    std::vector<std::pair<std::shared_ptr<Tablou>, std::shared_ptr<Artist>>> perechi;
    int perechi_corecte;
    int perechi_gresite;

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

    int getPerechilCorecte() const { return perechi_corecte; }
    int getPerechileGresite() const { return perechi_gresite; }
    int getTotalPerechi() const { return perechi.size(); }
};

#endif //ARTNOUVEAUGUEST_QUICKARTLOOK_HH