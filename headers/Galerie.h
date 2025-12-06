#ifndef ARTNOUVEAUGUEST_GALERIE_H
#define ARTNOUVEAUGUEST_GALERIE_H

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Artist.h"
#include "Tablou.h"
#include "MiniJoc.h"
#include <fstream>

class Galerie {
private:
    std::string nume;
    std::string subiect;
    int an_infiintare;
    std::vector<std::shared_ptr<Artist>> artisti;
    std::vector<std::shared_ptr<Tablou>> tablouri;
    std::vector<std::shared_ptr<MiniJoc>> jocuri;

public:
    Galerie() : an_infiintare(0) {}
    Galerie(const std::string& n, const std::string& subj, int an)
    : nume(n), subiect(subj), an_infiintare(an) {}
    ~Galerie() = default;
    void adaugaTablou(const std::shared_ptr<Tablou>& t) { tablouri.push_back(t); }

    void incarcaArtistiDinFisier(const std::string &caleFisier);
    void incarcaTablouriDinFisier(const std::string &caleFisier);

    void afiseazaArtisti() const;
    void afiseazaTablouri() const;
    std::shared_ptr<Artist> cautaArtist(const std::string& nume) const;
    void adaugaArtist(const std::shared_ptr<Artist>& a) { artisti.push_back(a); }
    std::shared_ptr<Tablou> cautaTablou(const std::string& titlu) const;
    friend std::ostream& operator<<(std::ostream& out, const Galerie& g);
    friend std::istream& operator>>(std::istream& in, Galerie& g) {
        std::cout << "Nume galerie: "; in >> g.nume;
        std::cout << "Locatie: "; in >> g.subiect;
        std::cout << "An infiintare: "; in >> g.an_infiintare;
        return in;
    }

    void adaugaJoc(const std::shared_ptr<MiniJoc>& joc) { jocuri.push_back(joc); }
    std::shared_ptr<MiniJoc> cautaJoc(const std::string& nume) const;
    void afiseazaJocuri() const;
    void joacaJoc(const std::string& nume_joc);
    void afiseazaSugestiiArtisticDelight();
    const std::vector<std::shared_ptr<Tablou>>& getTablouri() const { return tablouri; }
    const std::vector<std::shared_ptr<Artist>>& getArtisti() const { return artisti; }
    const std::vector<std::shared_ptr<MiniJoc>>& getJocuri() const { return jocuri; }
    Galerie(const Galerie& other);

    Galerie& operator=(Galerie other);

    friend void swap(Galerie& first, Galerie& second) noexcept;
};

#endif //ARTNOUVEAUGUEST_GALERIE_H